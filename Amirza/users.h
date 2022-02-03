#include <iostream>
#include <fstream>
#include <random>
using namespace std;

struct user
{
    string username;
    string password;
    int level;
    int coins;
    int extra;
    int chance;
};

void update_user(string username, user user_info){
    fstream users("files/user.txt");
    int user_count;
    users >> user_count;
    user users_list[user_count];
    user temp_user;
    for(int i=0; i<user_count; i++){
        users >> temp_user.username;
        users >> temp_user.password;
        users >> temp_user.level;
        users >> temp_user.coins;
        users >> temp_user.extra;
        users >> temp_user.chance;
        users_list[i] = temp_user;
    }
    users.close();
    ofstream new_users("files/user.txt");
    new_users << user_count << endl;
    for(int i=0; i<user_count; i++){
        if(username != users_list[i].username){
            new_users << users_list[i].username << "\t" << users_list[i].password << "\t";
            new_users << users_list[i].level << "\t" << users_list[i].coins << "\t";
            new_users << users_list[i].extra << "\t" << users_list[i].chance << "\t" << endl;
        }else{
            new_users << user_info.username << "\t" << user_info.password << "\t";
            new_users << user_info.level << "\t" << user_info.coins << "\t";
            new_users << user_info.extra << "\t" << user_info.chance << "\t" << endl;
        }
    }
    new_users.close();
}

void add_user(user user_info){
    fstream users("files/user.txt");
    int user_count;
    users >> user_count;
    user users_list[user_count+1];
    user temp_user;

    for(int i=0; i<user_count; i++){
        users >> temp_user.username;
        users >> temp_user.password;
        users >> temp_user.level;
        users >> temp_user.coins;
        users >> temp_user.extra;
        users >> temp_user.chance;
        users_list[i] = temp_user;
    }
    users_list[user_count] = user_info;
    user_count++;
    users.close();
    ofstream new_users("files/user.txt");
    new_users << user_count << endl;
    for(int i=0; i<user_count; i++){
        new_users << users_list[i].username << "\t" << users_list[i].password << "\t";
        new_users << users_list[i].level << "\t" << users_list[i].coins << "\t";
        new_users << users_list[i].extra << "\t" << users_list[i].chance << "\t" << endl;
    }
    new_users.close();

}

bool check_user_exists(string username){
    fstream users("files/user.txt");
    int user_count;
    users >> user_count;
    user temp_user;
    for(int i=0; i<user_count; i++){
        users >> temp_user.username;
        users >> temp_user.password;
        users >> temp_user.level;
        users >> temp_user.coins;
        users >> temp_user.extra;
        users >> temp_user.chance;

        if(temp_user.username==username){
            users.close();
            return true;
        }
    }
    users.close();
    return false;
}

user get_user(string username, string password){
    fstream users("files/user.txt");
    int user_count;
    users >> user_count;
    user target ={""};
    user temp_user;
    for(int i=0; i<user_count; i++){
        users >> temp_user.username;
        users >> temp_user.password;
        users >> temp_user.level;
        users >> temp_user.coins;
        users >> temp_user.extra;
        users >> temp_user.chance;

        if(temp_user.username==username && temp_user.password==password){
            target = temp_user;
            break;
        }
    }
    users.close();
    return target;
}

user register_user(string username, string password){
    user new_user = {""};
    if(!check_user_exists(username)){
     new_user.username = username;
     new_user.password = password;
     new_user.level = 1;
     new_user.extra = 0;
     new_user.coins = 0;
     new_user.chance = 0;
     add_user(new_user);
    }

    return new_user;

}

user wheel_of_luck(user user_info){
    cout << "\033[2J\033[1;1H"; //clear the screen
    if(user_info.chance >= 1){
        random_device dev;
        mt19937 rng(dev());
        uniform_int_distribution<mt19937::result_type> range1_20(1,20);
        int rand_num = range1_20(rng);
        int prize = 0;
        if(1<=rand_num && rand_num<=6)
            prize = 50;
        else if(7<=rand_num && rand_num<=10)
            prize = 70;
        else if(11<=rand_num && rand_num<=14)
            prize = 90;
        else if(15<=rand_num && rand_num<=17)
            prize = 110;
        else if(18<=rand_num && rand_num<=19)
            prize = 150;
        else if(rand_num==20)
            prize = 220;

        user_info.chance --;
        user_info.coins += prize;
        update_user(user_info.username, user_info);
        cout << "You won " << prize << " coins :-) have fun:-)" << endl;
        cout << "now you have " << user_info.chance << " chance(s)" << endl;
        cout << "Press enter to continue...";
        cin.ignore();
        cin.ignore();
    }else{
        cout << "You have no chance :-)" << endl << "Press enter to continue...";
        cin.ignore();
        cin.ignore();
    }

    return user_info;
}

user update_profile(){
    cout << "\033[2J\033[1;1H"; //clear the screen
    string username;
    string password;
    cout << "Enter your username: ";
    cin >> username;
    cout << endl << "Enter your password: ";
    cin >> password;
    cout << endl;
    user user_info = get_user(username, password);
    if(user_info.username != ""){
        bool flag = false;
        cout << "\033[2J\033[1;1H"; //clear the screen
        while(true){
            if(flag)
                cout << "there is a another account with that user name -__- try again:)" << endl;
            cout << "Enter your new username: ";
            cin >> user_info.username;
            cout << endl << "Enter your new password: ";
            cin >> user_info.password;
            cout << endl;
            if(check_user_exists(user_info.username))
                flag=true;
            else
                break;

        }
        update_user(username, user_info);
        cout << "Profile Updated :-)" << endl;
    }else{
        cout << "there is no user with this informations :-|" << endl;
    }
    cin.ignore();
    cout << "press enter to continue...";
    cin.ignore();
    return user_info;
}
