#include "myLibrary.h"
#include "CONRAN.h"
#include "menu.h"
#include "printScore_saveScore.h"
#include "gameOver.h"
using namespace std;

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
    while (1)
    {
        r.clearSnake(); // Xóa rắn cũ
        r.DiChuyen(Huong); // Di chuyển rắn
        r.drawWall(); //Vẽ tường

        if (_kbhit()) {
            t = _getch();
            if (t=='a' && Huong != 0) Huong = 2; // Không cho phép quay ngược lại sang phải
            if (t=='w' && Huong != 1) Huong = 3; // Không cho phép quay ngược lại xuống dưới
            if (t=='d' && Huong != 2) Huong = 0; // Không cho phép quay ngược lại sang trái
            if (t=='s' && Huong != 3) Huong = 1; // Không cho phép quay ngược lại lên trên
        }
        if (r.eatFood()) {
            PlaySound(TEXT("eatFood.wav"), NULL, SND_FILENAME | SND_ASYNC);
            r.DoDai++;
            r.drawFood();
        }
        if (r.checkCollision()) {
            PlaySound(TEXT("lose.wav"), NULL, SND_FILENAME | SND_ASYNC);
            std::this_thread::sleep_for(std::chrono::seconds(2));
            int point = r.userPoint + (r.DoDai - 3)*10;
            bool newGame;
            continueGame(point, newGame);
            if (newGame)
                main();
        }
        gotoxy(0, 0);
        cout << "Diem hien tai: " << r.userPoint + (r.DoDai - 3)*10;
        r.drawSnake();
        Sleep(speed); // Tốc độ di chuyển
    }

    return 0;
}
