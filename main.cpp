#include <iostream>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include "myLibrary.h"
#include <random>
using namespace std;

void gotoxy(int column, int line);
struct Point {
    int x, y;
};
void randomXY(int& x, int& y)
{
    int minX = 11;
    int maxX = 99;
    x = minX + rand() % (maxX - minX + 1);
    int minY = 2;
    int maxY = 25;
    y = minY + rand() % (maxY - minY + 1);
}

class CONRAN {
public:
    int userPoint = 0;
    struct Point A[100];
    struct Point B;
    int DoDai;
    CONRAN() {
        DoDai = 3;
        // Đặt vị trí bắt đầu cố định cho rắn
        A[0].x = 50; A[0].y = 13;
        A[1].x = A[0].x - 1; A[1].y = A[0].y;
        A[2].x = A[0].x - 2; A[2].y = A[0].y;
        B.x = 0; // Khởi tạo B
        B.y = 0; // Khởi tạo B
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

int main()
{
    srand(static_cast<unsigned int>(time(0)));
    CONRAN r;
    int Huong = 0;
    char t;

    //Ẩn nháy chuột
    hideCursor();

    r.drawFood();
    //Vẽ tường
    while (1)
    {
        r.clearSnake(); // Xóa rắn cũ
        r.DiChuyen(Huong); // Di chuyển rắn
        r.drawWall();

        if (_kbhit()) {
            t = _getch();
            if (t=='a' && Huong != 0) Huong = 2; // Không cho phép quay ngược lại sang phải
             if (t=='w' && Huong != 1) Huong = 3; // Không cho phép quay ngược lại xuống dưới
             if (t=='d' && Huong != 2) Huong = 0; // Không cho phép quay ngược lại sang trái
             if (t=='s' && Huong != 3) Huong = 1; // Không cho phép quay ngược lại lên trên
        }
        if (r.eatFood()) {
            r.DoDai++;
            r.drawFood();
        }
        if (r.checkCollision()) {
            system("cls");
            gotoxy(50, 13);
            cout << "Game Over!";
            gotoxy(47, 14);
            cout << "Diem cua ban la: " << r.userPoint + (r.DoDai - 3)*10;
            getch();
            break;
        }
        gotoxy(0, 0);
        cout << "Diem hien tai: " << r.userPoint + (r.DoDai - 3)*10;
        r.drawSnake();
        Sleep(200); // Tốc độ di chuyển
    }

    return 0;
}

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

void gotoxy(int column, int line)
{
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE),
        coord
    );
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
    if (A[0].x <= 10 || A[0].x >= 100 || A[0].y <= 1 || A[0].y >= 26) {
        return true;
    }
    // Kiểm tra va chạm với chính nó
    for (int i = 1; i < DoDai; i++) {
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