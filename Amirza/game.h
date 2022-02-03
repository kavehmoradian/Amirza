#include <iostream>
#include <fstream>
#include <random>
using namespace std;

struct game_data
{
    string words;
    int answers_count;
    int extra_count;
    int season;
    string answers[40];
};

struct user_data
{
    int level;
    int coin;
    int extra;
    int help;
};

game_data get_game_data(int level){
    fstream lvs("files/levels.txt");
    int seasons;
    lvs >> seasons;
    int level_counts[seasons];
    int count=0;
    for(int i=0; i<seasons; i++){
        lvs >> level_counts[i];
        count += level_counts[i];
    }
    game_data levels[count];

    for(int i=0; i<count; i++){
        game_data temp;
        lvs >> temp.words;
        lvs >> temp.answers_count;
        lvs >> temp.extra_count;
        for(int j=0; j<(temp.answers_count+temp.extra_count); j++){
            lvs >> temp.answers[j];
        }
        int sum = 0;
        for (int j=0; j<seasons; j++){
            if(i>=sum && i<=sum+level_counts[j])
                temp.season = j+1;
            sum += level_counts[j];
        }
        levels[i] = temp;
    }
    game_data res = levels[level-1];
    lvs.close();
    return res;
}

bool find_in_array_(int len, string response[], string word){
    for(int i=0; i<len; i++){
        if(response[i]==word)
            return true;
    }
    return false;
}

string show(game_data game, user_data user, string response[]){
    cout << "\033[2J\033[1;1H"; //clear the screen
    cout << "season: " << game.season << '\t' << "level: " << user.level << '\t';
    cout << "coin: " << user.coin << '\t' << "extra words: " << user.extra << endl;
    int words_len = game.words.length();
    for(int i=0; i< words_len; i++)
        cout << game.words[i] << " ";
    cout << endl;
    int helped = 0;
    for(int i=0; i<game.answers_count; i++){
        if(!find_in_array_(game.answers_count, response, game.answers[i])){
            int wlen = game.answers[i].length();
            for(int j=0; j<wlen; j++)
                if(helped<user.help){
                    cout << game.answers[i][j];
                    helped++;
                }else{
                    cout << "- ";
                }
            cout << endl;
        }else{
            cout << game.answers[i] << endl;
        }
    }
    cout << "if you want go back to internal menu enter *" << endl;
    cout << "if you need help enter #" << endl;
    cout << "enter word: ";
    string res = "";
    cin >> res;
    return res;
}

int choose_level(int max){
    int res=0;
    while (res<1 || res>max)
    {
        cout << "\033[2J\033[1;1H"; //clear the screen
        cout << "you can choose a level in range 1 and " << max << ": " << endl;
        cin >> res;
    }
    return res;
}