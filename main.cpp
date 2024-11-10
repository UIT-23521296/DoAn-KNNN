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
        randomXY(A[0].x, A[0].y);
        if (A[0].x < 13) A[0].x = 13; // Đảm bảo cách xa tường trái
        if (A[0].x > 97) A[0].x = 97; // Đảm bảo cách xa tường phải
        if (A[0].y < 3) A[0].y = 3;   // Đảm bảo cách xa tường trên
        if (A[0].y > 24) A[0].y = 24; // Đảm bảo cách xa tường dưới
        A[1].x= A[0].x + 1; A[1].y = A[0].y;
        A[2].x= A[0].x + 2; A[2].y = A[0].y;
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

int selectSpeed(int &speed) {
    int choice = 0;

    while (true) {
        system("cls");  // Xóa màn hình
        cout << "==============================" << endl;
        cout << "      CHOOSE SPEED           " << endl;
        cout << "==============================" << endl;
        cout << "1. Slow (500 ms)" << endl;
        cout << "2. Medium (200 ms)" << endl;
        cout << "3. Fast (100 ms)" << endl;
        cout << "4. Back to Menu" << endl;
        cout << "==============================" << endl;
        cout << "Select a speed (1-4): ";
        cin >> choice;

        if (choice == 1) {
            speed = 500;  // Tốc độ chậm
            break;
        } else if (choice == 2) {
            speed = 200;  // Tốc độ vừa
            break;
        } else if (choice == 3) {
            speed = 100;  // Tốc độ nhanh
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

    while (true) {
        system("cls");  // Xóa màn hình

        // Hiển thị menu
        cout << "==============================" << endl;
        cout << "      MENU CHINH GAME        " << endl;
        cout << "==============================" << endl;
        cout << "1. Start Game" << endl;
        cout << "2. Choose Speed (Current speed: " << speed << " ms)" << endl;
        cout << "3. Exit" << endl;
        cout << "==============================" << endl;
        cout << "Select an option (1-3): ";
        cin >> choice;

        if (choice == 1) {
            // Bắt đầu trò chơi với tốc độ hiện tại
            break;
        } else if (choice == 2) {
            selectSpeed(speed);  // Chọn tốc độ
        } else if (choice == 3) {
            exit(0);  // Thoát game
        } else {
            cout << "Invalid choice, please select again." << endl;
        }
    }
}




int main()
{
    srand(static_cast<unsigned int>(time(0)));
    CONRAN r;
    int Huong = 0;
    char t;
    int selectedOption = 0;
    int speed = 200;

    //Ẩn nháy chuột
    hideCursor();
    //Chọn tốc độ rắn
    displayMenu(speed);
    system("cls");


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
        Sleep(speed); // Tốc độ di chuyển
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
