#include <iostream>
#include "views.h"
#include "users.h"
#include "challenge.h"
#include "game.h"

using namespace std;

int temp_season = 0;
bool is_authenticated = false;
user account;
user_data temp_data;

user login();
void signup();
user play(user, user_data, bool);

int main()
{
    while(true){
        if(is_authenticated==false){
            int inp;
            inp = main_menu(); // a function from ./views.h
            switch(inp){
                case 1:
                    signup();
                    break;
                case 2:
                    account = login();
                    is_authenticated = true;
                    break;          
                case 3:
                    ranking();// a function from ./views.h
                    break;
                case 4:
                    challenge();// a function from ./chalange.h
                    break;
                case 5:
                    cout << "\033[2J\033[1;1H"; //clear the screen
                    cout << "bye :))" << endl;
                    exit(0);
                    break;
            }

        }else{
            int inp;
            inp = inner_menu(account.username); // a function from ./views.h
            switch(inp){
                case 1:
                    temp_data.coin = account.coins;
                    temp_data.level = account.level;
                    temp_data.extra = account.extra;
                    temp_data.help = 0; 
                    account = play(account, temp_data, true);
                    update_user(account.username, account);
                    break;
                case 2:
                    temp_data.coin = account.coins;
                    temp_data.level = choose_level(account.level);
                    temp_data.extra = 0;
                    temp_data.help = 0;  
                    account = play(account, temp_data, false);        
                    break;
                case 3:
                    account = wheel_of_luck(account);
                    break;
                case 4:
                account = update_profile();
                    break;
                case 5:
                    is_authenticated=false;
                    break;
            }
        }
    }
    return 0;

}


user login(){
    bool flag = false;
    user temp;
    string username, password;
    while(true){
        cout << "\033[2J\033[1;1H"; //clear the screen
        if(flag)
            cout << "there is no user with that data -___- try again :)" << endl;
        cout << "Enter your username: ";
        cin >> username;
        cout << endl << "Enter your password: ";
        cin >> password;
        temp = get_user(username, password);
        if(temp.username=="")
            flag=true;
        else{
            temp_season = get_game_data(temp.level).season;
            cout << "\033[2J\033[1;1H"; //clear the screen
            cout << "You have successfully logged in *__*" << endl;
            cout << "Press enter to continue...";
            cin.ignore();
            cin.ignore();
            break;
        }
            
    }
    return temp;
}

void signup(){
    bool flag = false;
    user temp;
    string username, password;
    while(true){
        cout << "\033[2J\033[1;1H"; //clear the screen
        if(flag)
            cout << "we have another user with this username -___- try again :)" << endl;
        cout << "Enter username: ";
        cin >> username;
        cout << endl << "Enter password: ";
        cin >> password;
        temp = register_user(username, password);
        if(temp.username=="")
            flag=true;
        else{
            cout << "\033[2J\033[1;1H"; //clear the screen
            cout << "Your account created, now you can login *__*" << endl;
            cout << "Press enter to continue...";
            cin.ignore();
            cin.ignore();
            break;
        }
    }
}

user play(user acc, user_data data, bool save){
    game_data level = get_game_data(data.level);
    string ans[level.answers_count];
    string ext[level.extra_count];
    int ans_count = 0;
    int ext_count = 0;

    while (true)
    {
        if(same_array(level.answers_count, ans, level.answers)){
            cout << "\033[2J\033[1;1H"; //clear the screen
            acc.level++;
            acc.coins += 100;
            while (acc.extra>=6)
            {
                acc.coins += 50;
                acc.extra -= 6;
            }
            cout << "you pass this level ^___^ and you got 100 coins *___*" << endl;
            cout << "press enter to go back to the menu...";
            if(level.season != temp_season && save){
                acc.chance++;
                temp_season = acc.chance;
            }
            cin.ignore();
            cin.ignore();
            break;
            
        }

        string res = show(level, data, ans);
        if(!find_in_array(level.answers_count, ans, res) && find_in_array(level.answers_count, level.answers, res)){
            ans[ans_count] = res;
            ans_count++; 
            data.help = 0;
        }else if(!find_in_array(level.extra_count, ext, res) && find_in_array(level.answers_count, level.extra_count, level.answers, res)){
            ext[ext_count] = res;
            ext_count++; 
            data.extra += 1;
            acc.extra ++;
        }else if(res == "#"){
            if(acc.coins>=80){
                data.help++;
                acc.coins -= 80;
                data.coin -= 80;
            }
        }else if(res == "*")
            break;
        
    }
    
    return acc;
}
