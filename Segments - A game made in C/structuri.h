#ifndef STRUCTURI_H_
#define STRUCTURI_H_
#include <iostream>
#include <graphics.h>
#include <winbgim.h>
#include <stdlib.h>
#include <conio.h>
#define TITLE "Segmente"
#define MOD1 "Player 1 VS Player 2"
#define MOD2 "Player VS AI"
#define SETTINGS "Setari"
#define EXIT "Iesire"
#define COLOR CYAN
#define USED LIGHTGREEN
using namespace std;

struct Player
{
    char name[256];
    int color;
    int score;
    bool winner;
};

int mx, my;

struct Table
{
    int nrPuncte;
    int pointColor;
    int puncte_utilizate;
    int puncte_blocate;
    int dificultate;
};



struct Punct
{
    int x;
    int y;
    bool used;

    //+ elem grafice
};



struct Segment
{
    Punct p1;
    Punct p2;
    //+ elem grafice
};

struct Joc
{
    int nrSegm;
    Player player1, player2, computer;
    Table table;
    Punct puncte[100];
    Segment segmente[100];


};
Joc joc;


#endif
