#pragma once

void randomXY(int& x, int& y)
{
    int minX = 11;
    int maxX = 99;
    x = minX + rand() % (maxX - minX + 1);
    int minY = 2;
    int maxY = 25;
    y = minY + rand() % (maxY - minY + 1);
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