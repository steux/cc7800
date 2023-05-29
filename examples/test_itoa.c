#include "stdlib.h"
#include "conio.h"

ramchip char buffer[7];
ramchip char y;

void main()
{
    y = 0;
    clrscr();
    itoa(0, buffer, 10);
    gotoxy(0, y++); cputs(buffer);
    itoa(10, buffer, 10);
    gotoxy(0, y++); cputs(buffer);
    itoa(17, buffer, 10);
    gotoxy(0, y++); cputs(buffer);
    itoa(100, buffer, 10);
    gotoxy(0, y++); cputs(buffer);
    itoa(107, buffer, 10);
    gotoxy(0, y++); cputs(buffer);
    itoa(198, buffer, 10);
    gotoxy(0, y++); cputs(buffer);
    itoa(1999, buffer, 10);
    gotoxy(0, y++); cputs(buffer);
    itoa(13100, buffer, 10);
    gotoxy(0, y++); cputs(buffer);
    itoa(20001, buffer, 10);
    gotoxy(0, y++); cputs(buffer);
    itoa(32765, buffer, 10);
    gotoxy(0, y++); cputs(buffer);
    itoa(-100, buffer, 10);
    gotoxy(0, y++); cputs(buffer);
    itoa(-10101, buffer, 10);
    gotoxy(0, y++); cputs(buffer);
}

