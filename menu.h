#pragma once 
#include <iostream>
#include "myLibrary.h"
#include "RandomXY.h"
#include "printScore_saveScore.h"
using namespace std;

void selectSpeed(int &speed, string &sSpeed) {
    int choice = 0;

    while (true) {
        system("cls");  // Xóa màn hình
        cout << "==============================" << endl;
        cout << "      CHOOSE SPEED           " << endl;
        cout << "==============================" << endl;
        cout << "1. Slow" << endl;
        cout << "2. Medium" << endl;
        cout << "3. Fast" << endl;
        cout << "4. Back to Menu" << endl;
        cout << "==============================" << endl;
        cout << "Select a speed (1-4): ";
        cin >> choice;

        if (choice == 1) {
            speed = 500;  // Tốc độ chậm
            sSpeed = "Slow";
            break;
        } else if (choice == 2) {
            speed = 200;  // Tốc độ vừa
            sSpeed = "Medium";
            break;
        } else if (choice == 3) {
            speed = 100;  // Tốc độ nhanh
            sSpeed = "Fast";
            break;
        } else if (choice == 4) {
            break;  // Quay lại menu chính
        } else {
            cout << "Invalid choice, please select again." << endl;
        }
    }
}

void displayMenu(int &speed) {
    int choice = 0;
    string sSpeed = "Medium";
    while (true) {
        system("cls");  // Xóa màn hình

        // Hiển thị menu
        cout << "==============================" << endl;
        cout << "          MENU GAME        " << endl;
        cout << "==============================" << endl;
        cout << "1. Start Game" << endl;
        cout << "2. Choose Speed (Current speed: " << sSpeed << ")" << endl;
        cout << "3. Print point" << endl;
        cout << "4. Exit" << endl;
        cout << "==============================" << endl;
        cout << "Select an option (1-4): ";
        cin >> choice;

        if (choice == 1) {
            // Bắt đầu trò chơi với tốc độ hiện tại
            break;
        } else if (choice == 2) {
            selectSpeed(speed, sSpeed);  // Chọn tốc độ
        }
        else if (choice == 3) {
            printScore();
        }
        else if (choice == 4) {
            system("cls");
            gotoxy(55, 13);
            cout << "Good bye!";
            getch();
            exit(0); // Thoát game
        } else {
            cout << "Invalid choice, please select again." << endl;
        }
    }
}