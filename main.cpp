#include <iostream>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include "myLibrary.h"
#include <random>
using namespace std;
void gotoxy( int column, int line );
struct Point{
    int x,y;
};
void randomXY(int &x, int &y)
{
    int minX = 11;
    int maxX = 99;
    x = minX + rand() % (maxX - minX + 1);
    int minY = 2;
    int maxY = 25;
    y = minY + rand() % (maxY - minY + 1);

}
class CONRAN{
public:
    struct Point A[100];
    struct Point B;
    int DoDai;
    CONRAN(){
        DoDai = 3;
        randomXY(A[0].x, A[0].y);
        if(A[0].x == 11) A[0].x += 3; // nếu đầu rắn sát tường thì lùi thêm 3 ô
        A[1].x= A[0].x + 1; A[1].y = A[0].y;
        A[2].x= A[0].x + 2; A[2].y = A[0].y;
    }

    void DiChuyen(int Huong){
        for (int i = DoDai-1; i>0;i--)
            A[i] = A[i-1];
        if (Huong==0) A[0].x = A[0].x + 1;
        if (Huong==1) A[0].y = A[0].y + 1;
        if (Huong==2) A[0].x = A[0].x - 1;
        if (Huong==3) A[0].y = A[0].y - 1;

    }
    void drawWall();
    void drawSnake();
    void clearSnake();
    void drawFood();
};

int main()
{
    srand(time(0));
    CONRAN r;
    int Huong = 0;
    char t;

    //Ẩn nháy chuột
    hideCursor();

    r.drawFood();
    //Vẽ tường
    while(1)
    {
        r.clearSnake(); // Xóa rắn cũ
        r.DiChuyen(Huong); // Di chuyển rắn
        r.drawWall();

        if (kbhit()){
             t = getch();
             if (t=='a' && Huong != 0) Huong = 2; // Không cho phép quay ngược lại sang phải
             if (t=='w' && Huong != 1) Huong = 3; // Không cho phép quay ngược lại xuống dưới
             if (t=='d' && Huong != 2) Huong = 0; // Không cho phép quay ngược lại sang trái
             if (t=='s' && Huong != 3) Huong = 1; // Không cho phép quay ngược lại lên trên
         }
         r.drawSnake();
        Sleep(300); // Tốc độ di chuyển
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

void gotoxy( int column, int line )
{
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(
        GetStdHandle( STD_OUTPUT_HANDLE ),
        coord
    );
}
// Xóa rắn
void CONRAN::clearSnake() {
    for (int i = 0; i < DoDai; i++) {
        gotoxy(A[i].x, A[i].y);
        cout << " "; // In khoảng trắng để xóa rắn cũ
    }
}

//Vẽ Rắn
void CONRAN::drawSnake()
{
    SetColor(10);
    for (int i = 0; i < DoDai; i++){
        gotoxy(A[i].x, A[i].y);
        cout << "0" ;
    }
    SetColor(7);
}
//Vẽ Mồi
void CONRAN::drawFood()
{
    SetColor(8);
    while(1)
    {
        // tạo mồi ngẫu nhiên
        randomXY(B.x, B.y);

        // kiểm tra xem mồi có trùng với con rắn không
        bool loop = false;
        for (int i = 0; i < DoDai; i++)
        {
            if(A[i].x == B.x && A[i].y == B.y)
            {
                loop = true;
                break;
            }
        }
        if(!loop) break;
    }
    gotoxy(B.x, B.y);
    cout << "@"; // in cục mồi
    SetColor(7);
}
