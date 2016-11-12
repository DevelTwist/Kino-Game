#ifndef CONIO_H
#define CONIO_H

#include <windows.h>

#define BLACK            0
#define BLUE             0x1
#define GREEN            0x2
#define AQUA             0x3
#define RED              0x4
#define PURPLE           0x5
#define YELLOW           0x6
#define WHITE            0x7
#define GRAY             0x8
#define LIGHT_BLUE       0x9
#define LIGHT_GREEN      0xA
#define LIGHT_AQUA       0xB
#define LIGHT_RED        0xC
#define LIGHT_PURPLE     0xD
#define LIGHT_YELLOW     0xE
#define LIGHT_WHITE      0xF

void bgcolor(WORD color);
void gotoxy(int x, int y);
void textcolor(WORD textcolor);
void scrsize(int w, int h);
void textbgcolor(WORD textcolor, WORD bgcolor);
void clrscr();
int kbhit();

void clrscr(){
    system("cls");
}

void bgcolor(WORD color){
    char scolor[10];
    WORD bgcolor = (color & 0xF) << 4;
    sprintf(scolor, "color %x", bgcolor);
    system(scolor);
}

void gotoxy(int x, int y){
    HANDLE hConsole;
    COORD dwPos;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hConsole, dwPos);
}

void textcolor(WORD textcolor){
    textbgcolor(textcolor, 0);
}

void textbgcolor(WORD textcolor, WORD bgcolor){
    WORD color = (bgcolor & 0xF) << 4 | (textcolor & 0xF);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute (hConsole, color);
}

void scrsize(int w, int h){
    COORD dwSize = {w, h};
    SMALL_RECT Rect = {0,0,w-1,h-1};
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleScreenBufferSize(hConsole, dwSize);
    SetConsoleWindowInfo(hConsole, TRUE, &Rect);
}

int kbhit(void)
{
   DWORD nEventos;
   INPUT_RECORD *eventos;
   DWORD leidos;
   int retval = 0;
   int i;

   GetNumberOfConsoleInputEvents(GetStdHandle(STD_INPUT_HANDLE),
      &nEventos);

   eventos = (INPUT_RECORD *)malloc(nEventos*sizeof(INPUT_RECORD));
   PeekConsoleInput(GetStdHandle(STD_INPUT_HANDLE),
      eventos, nEventos, &leidos);
   for(i = 0;  i < nEventos; i++)
      if(eventos[i].EventType == KEY_EVENT && eventos[i].Event.KeyEvent.bKeyDown) retval = 1;

   free( eventos );
   return retval;
}

#endif // CONIO_H
