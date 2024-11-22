#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include "myLibrary.h"

using namespace std;

void printScore()
{
    vector<pair<string, int>> players;
    ifstream inputFile("highscore.txt");
    if (inputFile.is_open())
    {
        string line;
        while (getline(inputFile, line))
        {
            istringstream iss(line);
            string name;
            int point;

            if (getline(iss, name, '"') && getline(iss, name, '"') && iss >> point)
            {
                players.push_back(make_pair(name, point));
            }
        }
    }

    system("cls");  
    cout << "==============================" << endl;
    cout << "        HIGH SCORES          " << endl;
    cout << "==============================" << endl;
    cout << left << setw(5) << "Rank" << setw(20) << "Player Name" << setw(10) << "Score" << endl;
    int i = 1;
    for (const auto &player : players)
    {
        cout << left << setw(5) << i++
             << setw(20) << player.first 
             << setw(10) << player.second 
             << endl;
    }
    cout << "==============================" << endl;
    cout << "Press any key to return to the menu.";
    _getch();  
}

void saveScore(const string& username, int point) {
    vector<pair<string, int>> players;

    // Đọc dữ liệu từ file
    ifstream inFile("highscore.txt");
    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            istringstream iss(line);
            string name;
            int score;

            // Đọc tên bọc trong dấu ngoặc kép
            if (getline(iss, name, '"') && getline(iss, name, '"') && iss >> score) {
                players.push_back(make_pair(name, score));
            }
        }
        inFile.close();
    }

    // Thêm điểm mới
    players.push_back(make_pair(username, point));

    // Sắp xếp danh sách theo điểm giảm dần
    sort(players.begin(), players.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        return a.second > b.second;
    });

    // Ghi lại danh sách vào file
    ofstream outFile("highscore.txt", ios::trunc);
    if (outFile.is_open()) {
        for (const auto& player : players) {
            outFile << "\"" << player.first << "\" " << player.second << endl;
        }
        outFile.close();
    }
}