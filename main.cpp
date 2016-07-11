#include <iostream>
#include <fstream>
#include <string.h>

const int N = 100;

using namespace std;

void goNextLine(ifstream &file){
    char c = '*';
    while(c != '\n'){
        file.get(c);
    }
}

void getName(char* name, ifstream &file){
    char c1 = '*';
    char c2 = c1;

    while(c2 != '-' || c1 != ' '){
        c2 = c1;
        file.get(c1);
    }

    file.get(name, 100, ':');
}

int checkName(char name[], char list[][100]){
    for(int i = 0; i < N; i++){
        if(!strcmp(name, list[i])){
            return i;
        }
    }

    return 0;
}

void sortList(char rank[][100], int frequency[]){  //! check later
    int j;
    int itemp;
    char ctemp[100];

    for(int i = 1; i < N - 1; i++){
        j = i;
        while(frequency[j] > frequency[j - 1] && j > 0) {
            itemp = frequency[j - 1];
            frequency[j - 1] = frequency[j];
            frequency[j] = itemp;

            strcpy(ctemp, rank[j - 1]);
            strcpy(rank[j - 1], rank[j]);
            strcpy(rank[j], ctemp);
            j--;
        }
    }
}

void printRanking(char rank[][100], int frequency[]){
    for(int i = 0; i < N; i++){
        if(frequency[i] > 1) {
            cout << i + 1 << ". " << rank[i] << ": " << frequency[i] << endl;
        }
    }
    cout << endl;
}

int main() {
    int j = 0;
    int position;
    char name[100];
    char rank[N][100];
    int frequency[N];
    ifstream conversation("input.txt");

    for(int i = 0; i < N; i++){
        strcpy(rank[i], "0");
    }

    for(int i = 0; i < N; i++){
        frequency[i] = -1;
    }

    while(!conversation.eof()){
        getName(name, conversation);
        goNextLine(conversation);



        position = checkName(name, rank);
        if(position > 0){
            frequency[position]++;
        }else{
            while(frequency[j] != -1){
                j++;
            }
            frequency[j] = 1;
            strcpy(rank[j], name);
        }

        if(!conversation.eof()){
            conversation.get();
        }
    }
    sortList(rank, frequency);
    printRanking(rank, frequency);

    conversation.close();
    return 0;
}