#include <iostream>
#include <fstream>
#include <random>
using namespace std;

struct level_data
{
    string words;
    int answers_count;
    int extra_count;
    string answers[40];
};
struct player{
    string name;
    int score;
};

level_data get_game();
string show_game(player, player, level_data, string [], string);
bool find_in_array(int, string[], string);
bool same_array(int, string[], string[]);


void challenge(){
    cout << "\033[2J\033[1;1H"; //clear the screen
    int turn = 1;
    player player1, player2;
    player1.score = 0;
    player2.score = 0;
    cout << "player1 name: ";
    cin >> player1.name;
    cout << "player2 name: ";
    cin >> player2.name;
    cout << "\033[2J\033[1;1H"; //clear the screen
    level_data game = get_game();
    string response[game.answers_count];
    int count = 0;
    while(true){
        if(same_array(game.answers_count, response, game.answers)){
            cout << "\033[2J\033[1;1H"; //clear the screen
            if(player1.score > player2.score){
                cout << player1.name << " won ^___^" << endl;
            }else{
                cout << player2.name << " won ^___^" << endl;
            }
            
            cout << "press enter to continue...";
            cin.ignore();
            cin.ignore();
            break;
        }
        string sturn;
        if(turn == 1)
            sturn = player1.name;
        else
            sturn = player2.name;
        string res = show_game(player1, player2, game, response, sturn);
        if(!find_in_array(game.answers_count, response, res) && find_in_array(game.answers_count, game.answers, res)){
            response[count] = res;
            count++;
            if(turn == 1)
                player1.score += res.length();
            else
                player2.score += res.length(); 
        }else if(res == "*"){
            cout << sturn << " want's to left the game" << endl;
            cout << "press enter to continue...";
            cin.ignore();
            cin.ignore();
            break;
        }
        if(turn == 1)
            turn++;
        else
            turn--;
    }

}

level_data get_game() {
    fstream file("files/levels.txt");
    int seasons;
    file >> seasons;
    int level_counts[seasons];
    int count=0;
    for(int i=0; i<seasons; i++){
        file >> level_counts[i];
        count += level_counts[i];
    }
    level_data levels[count];

    for(int i=0; i<count; i++){
        level_data temp;
        file >> temp.words;
        file >> temp.answers_count;
        file >> temp.extra_count;
        for(int j=0; j<(temp.answers_count+temp.extra_count); j++){
            file >> temp.answers[j];
        }
        levels[i] = temp;
    }
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type> range(1,count);
    int rand_num = range(rng);
    level_data rand_level = levels[rand_num-1];
    file.close();
    return rand_level;
}

bool find_in_array(int len, string response[], string word){
    for(int i=0; i<len; i++){
        if(response[i]==word)
            return true;
    }
    return false;
}
bool find_in_array(int min, int max, string response[], string word){
    for(int i=min-1; i<(max + min); i++){
        if(response[i]==word)
            return true;
    }
    return false;
}
bool same_array(int len, string first[], string seccond[]){
    for(int i=0; i<len; i++){
        bool flag = false;
        for(int j=0; j<len; j++){
            if(first[i]==seccond[j])
                flag=true;
        }
        if(flag==false)
            return false;
    }
    return true;
}

string show_game(player player1, player player2, level_data game, string response[], string turn){
    cout << "\033[2J\033[1;1H"; //clear the screen
    cout << "Player1: " << player1.name << '\t' << "score: " << player1.score << '\t';
    cout << "Player2: " << player2.name << '\t' << "score: " << player2.score << endl;
    cout << "turn: " << turn << endl;
    int words_len = game.words.length();
    for(int i=0; i< words_len; i++)
        cout << game.words[i] << " ";
    cout << endl;
    for(int i=0; i<game.answers_count; i++){
        if(!find_in_array(game.answers_count, response, game.answers[i])){
            int wlen = game.answers[i].length();
            for(int j=0; j<wlen; j++)
                cout << "- ";
            cout << endl;
        }else{
            cout << game.answers[i] << endl;
        }
    }
    cout << "if you want go back to main menu enter *" << endl;
    cout << turn << " enter word: ";
    string res = "";
    cin >> res;
    return res;
}