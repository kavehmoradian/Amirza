#include <iostream>
#include <fstream>

using namespace std;

struct User
{
    string username;
    string password;
    int level;
    int coins;
    int extra;
    int chance;
};

int main_menu() {

    int inp = 0;
    static bool flag = false;
    while (inp>5 || inp<1) {
    cout << "\033[2J\033[1;1H"; //clear the screen
    cout << "Welcome to this game ^___^" << endl;
    cout << "-------------------------------" << endl;
    cout << "|  ******* Main Menu *******  |" << endl;
    cout << "|  1.Signup                   |" << endl;
    cout << "|  2.Login                    |" << endl;
    cout << "|  3.Rank                     |" << endl;
    cout << "|  4.Challenge                |" << endl;
    cout << "|  5.Exix                     |" << endl;
    cout << "-------------------------------" << endl;
    if(flag == true)
        cout << "your input must be in range (1-5) : " << endl;
    cout << "Please enter your choice: "; 
    cin >> inp;
    if(inp<1 || inp>5)
        flag = true;
    else
        flag = false;
    }
    return inp;

}

int inner_menu(string username) {

    int inp = 0;
    static bool flag = false;
    while (inp>5 || inp<1) {
    cout << "\033[2J\033[1;1H"; //clear the screen
    cout << "Welcome " << username << " :-)" << endl;
    cout << "-----------------------------------" << endl;
    cout << "|  ******* Internal Menu *******  |" << endl;
    cout << "|  1.Continue game                |" << endl;
    cout << "|  2.Choose level                 |" << endl;
    cout << "|  3.Wheel of Luck                |" << endl;
    cout << "|  4.Edit profile                 |" << endl;
    cout << "|  5.Logout                       |" << endl;
    cout << "-----------------------------------" << endl;
    if(flag == true)
        cout << "your input must be in range (1-5) : " << endl;
    cout << "Please enter your choice: "; 
    cin >> inp;
    if(inp<1 || inp>5)
        flag = true;
    else
        flag = false;
    }
    return inp;

}

void ranking(){
    fstream users("files/user.txt");
    int user_count;
    users >> user_count;
    User users_list[user_count];
    User temp_user;
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

    int i,j;
    User temp;
    for(i=0; i<user_count-1; i++){
        for(j=i+1; j<user_count; j++){
            if(users_list[i].level>users_list[j].level){
                temp = users_list[j];
                users_list[j]=users_list[i];
                users_list[i]=temp;
            }
        }
    }
    cout << "\033[2J\033[1;1H"; //clear the screen
    cout << "Ranking:" << endl;
    int count=1;
    for(int i=user_count-1; i>=0; i--){
        cout << count <<" --> " << users_list[i].username << endl;
        count++;
    }
    cout << "press enter to continue...";
    cin.ignore();
    cin.ignore();
}