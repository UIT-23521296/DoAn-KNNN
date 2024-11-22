#pragma once
#include "RandomXY.h"
#include "myLibrary.h"
#include "printScore_saveScore.h"
#include <iostream>

using namespace std;

void continueGame(int &userPoint, bool &newGame) {
    newGame = false;
    system("cls");
    gotoxy(50, 13);
    cout << "Game Over!";
    gotoxy(47, 14);
    cout << "Diem cua ban la: " << userPoint;
    gotoxy(30, 15);
    cout << "Press any key to continue, or press 'Enter' to quit.";
    char choice = _getch();
    if (choice == 13)
    {
        system("cls");
        gotoxy(55, 13);
        cout << "Good bye!";
        getch();
        exit(0);
    }
    else
    {
        while (true) {
        system("cls");
        cout << "==============================" << endl;
        cout << "      GAME OVER OPTIONS      " << endl;
        cout << "==============================" << endl;
        cout << "1. Save Score" << endl;
        cout << "2. Start New Game" << endl;
        cout << "3. Exit" << endl;
        cout << "==============================" << endl;
        cout << "Select an option (1-3): ";
        int option;
        cin >> option;

        if (option == 1) {
            // Lưu điểm
            cout << "Enter player's name: ";
            cin.ignore();
            string userName;
            getline(cin, userName);
            saveScore(userName, userPoint);
            cout << "Press any key to return to the main menu.";
            getch();
            newGame = true;
            break;
        } else if (option == 2) {
            // Start New Game
            system("cls");
            newGame = true;
            break;
        } else if (option == 3) {
            // Thoát game
            system("cls");
            gotoxy(55, 13);
            cout << "Good bye!";
            getch();
            exit(0);
        } else {
            cout << "Invalid option. Please try again." << endl;
        }
        }
    }
}