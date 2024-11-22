#pragma once
#include "RandomXY.h"
#include <iostream>

using namespace std;

struct Point {
    int x, y;
};

class CONRAN {
public:
    int userPoint = 0;
    struct Point A[100];
    struct Point B;
    int DoDai;
    CONRAN() {
        DoDai = 3;
        randomXY(A[0].x, A[0].y);
        if (A[0].x < 13) A[0].x = 13; // Đảm bảo cách xa tường trái
        if (A[0].x > 97) A[0].x = 97; // Đảm bảo cách xa tường phải
        if (A[0].y < 3) A[0].y = 3;   // Đảm bảo cách xa tường trên
        if (A[0].y > 24) A[0].y = 24; // Đảm bảo cách xa tường dưới
        A[1].x= A[0].x + 1; A[1].y = A[0].y;
        A[2].x= A[0].x + 2; A[2].y = A[0].y;
    }

    void DiChuyen(int Huong) {
        for (int i = DoDai - 1; i > 0; i--)
            A[i] = A[i - 1];
        if (Huong == 0) A[0].x = A[0].x + 1;
        if (Huong == 1) A[0].y = A[0].y + 1;
        if (Huong == 2) A[0].x = A[0].x - 1;
        if (Huong == 3) A[0].y = A[0].y - 1;
    }

    void drawWall();
    void drawSnake();
    void clearSnake();
    void drawFood();
    bool checkCollision();
    bool eatFood();
};

//Vẽ tường
void CONRAN::drawWall()
{
    SetColor(12);
    int x = 10, y = 1;

    //Tường trên
    while (x <= 100)
    {
        gotoxy(x, y);
        cout << "=";
        x++;
    }

    //Tường dưới
    x = 10, y = 26;
    while (x <= 100)
    {
        gotoxy(x, y);
        cout << "=";
        x++;
    }

    //Tường trái
    x = 10, y = 2;
    while (y <= 26)
    {
        gotoxy(x, y);
        cout << "=";
        y++;
    }

    //Tường phải
    x = 100, y = 2;
    while (y <= 26)
    {
        gotoxy(x, y);
        cout << "=";
        y++;
    }
    SetColor(7);
}

// Xóa rắn
void CONRAN::clearSnake() {
    for (int i = 0; i < DoDai; i++) {
        gotoxy(A[i].x, A[i].y);
        cout << " ";
    }
}

//Vẽ Rắn
void CONRAN::drawSnake()
{
    SetColor(10);
    for (int i = 0; i < DoDai; i++) {
        gotoxy(A[i].x, A[i].y);
        cout << "0";
    }
    SetColor(7);
}

//Vẽ Mồi
void CONRAN::drawFood()
{
    SetColor(8);
    while (1)
    {
        randomXY(B.x, B.y);

        bool loop = false;
        for (int i = 0; i < DoDai; i++)
        {
            if (A[i].x == B.x && A[i].y == B.y)
            {
                loop = true;
                break;
            }
        }
        if (!loop) break;
    }
    gotoxy(B.x, B.y);
    cout << "@";
    SetColor(7);
}

// Kiểm tra va chạm
bool CONRAN::checkCollision() {
    // Kiểm tra va chạm với tường
    if (A[0].x < 11 || A[0].x > 99 || A[0].y < 2 || A[0].y > 25) {
        return true;
    }
    // Kiểm tra va chạm với chính nó
    for (int i = 3; i < DoDai; i++) {
        if (A[0].x == A[i].x && A[0].y == A[i].y) {
            return true;
        }
    }
    return false;
}

// Kiểm tra ăn mồi
bool CONRAN::eatFood() {
    if (A[0].x == B.x && A[0].y == B.y) {
        return true;
    }
    return false;
}