#ifndef MENU_H_
#define MENU_H_
#include <iostream>
#include <graphics.h>
#include <winbgim.h>
#include <stdlib.h>
#include <cstring>
#include <conio.h>
#include <stdio.h>
#include <cmath>
#include "generare_tabel.h"
#define TITLE "Segmente"
#define MOD1 "Player 1 VS Player 2"
#define MOD2 "Player VS Computer"
#define REGULI "Reguli"
#define EXIT "Iesire"
#define COLOR CYAN
#define MAX_STR 256
#define COMPUTER 13
void buton_mod1()
{
    int mijloc_x;
    int mijloc_y;
    mijloc_x = getmaxx()/2;
    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
    outtextxy(mijloc_x - textwidth(MOD1)/2, 350, MOD1);
    rectangle(mijloc_x - textwidth(MOD1), 350 - textheight(MOD1), mijloc_x + textwidth(MOD1), 350 + 2 * textheight(MOD1));

}

void buton_mod2()
{
    int mijloc_x;
    int mijloc_y;
    mijloc_x = getmaxx()/2;
    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
    outtextxy(mijloc_x - textwidth(MOD2)/2, 420, MOD2);
    rectangle(mijloc_x - textwidth(MOD1), 420 - textheight(MOD2), mijloc_x + textwidth(MOD1), 420 + 2 * textheight(MOD2));
}

void buton_reguli()
{
    int mijloc_x;
    int mijloc_y;
    mijloc_x = getmaxx()/2;
    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
    outtextxy(mijloc_x - textwidth(REGULI)/2, 490, REGULI);
    rectangle(mijloc_x - textwidth(MOD1), 490 - textheight(REGULI), mijloc_x + textwidth(MOD1), 490 + 2 * textheight(REGULI));

}

void buton_iesire()
{
    int mijloc_x;
    int mijloc_y;
    mijloc_x = getmaxx()/2;
    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
    outtextxy(mijloc_x - textwidth(EXIT)/2, 560, EXIT);
    rectangle(mijloc_x - textwidth(MOD1), 560 - textheight(EXIT), mijloc_x + textwidth(MOD1), 560 + 2 * textheight(EXIT));
}

void CitesteSir(int x, int y, char mesaj[256], char S[256])
{
    char Enter = 13; char BackSpace = 8; char Escape = 27; char s2[2]; s2[1]='\0';
    char MultimeDeCaractereAcceptabile[MAX_STR]="0123456789abcdefghijklmnopqrstuvwxyz~!`@#$%+-^&*/\\()_=[],;.?<>:;{} ";
    char S_initial[MAX_STR]; char tasta; char S_[MAX_STR]; char mesaj_[MAX_STR];
    strcpy(mesaj_,mesaj);
    strcpy(S_initial,S); settextstyle(BOLD_FONT, HORIZ_DIR, 2); setcolor(WHITE);
    settextjustify(0,0); outtextxy(x,y,mesaj_);
    x=x+textwidth(mesaj);strcpy(S,"");
    strcpy(S_,S); strcat(S_,"_");
    setcolor(BLACK); outtextxy(x,y,S_);
    s2[0]=tasta; strcat(S,s2); strcpy(S_,S); strcat(S_,"_");
    setcolor(WHITE); outtextxy(x,y,S_);

    do {
        tasta=getch();
        if (tasta==0) { tasta=getch(); Beep(1000,500); }
        else
            if (strchr(MultimeDeCaractereAcceptabile, tasta))
            {
                // stergem fostul sir
                strcpy(S_,S); strcat(S_,"_");
                setcolor(BLACK); outtextxy(x,y,S_);
                s2[0]=tasta; strcat(S,s2); strcpy(S_,S); strcat(S_,"_");
                setcolor(WHITE); outtextxy(x,y,S_);
            }
            if (tasta==BackSpace)
                    if (!(strcmp(S,""))) Beep(500,100);
                    else
                    {
                        setcolor(BLACK); outtextxy(x,y,S_); setcolor(WHITE);
                        S[strlen(S)-1]='\0'; strcpy(S_,S); strcat(S_,"_") ;
                        outtextxy(x,y,S_); Beep(200,20);
                    }
            else
                if (tasta!=Enter && tasta!=Escape) { Beep(200,20); }
    } while (tasta!=Enter && tasta!=Escape);
    if (tasta == Escape) strcpy(S,S_initial);
    setcolor(BLACK); outtextxy(x,y,S_);setcolor(WHITE); outtextxy(x,y,S);
}

void desen_culoare(int color, int nr_player)
{
    if(nr_player == 1)
    {
        setfillstyle(SOLID_FILL, color);
        fillellipse(300 + textwidth("Alege-ti culoarea: ") + 50, 340, 20, 20);
    }
    if(nr_player == 2)
    {
        setfillstyle(SOLID_FILL, color);
        fillellipse(300 + textwidth("Alege-ti culoarea: ") + 50, 440, 20, 20);
    }

}


void alege_culoare(int nr_jucator)
{
    int k = 1;
    char tasta;
    char ENTER = 13, ARROW_LEFT = 75, ARROW_RIGHT = 77;

    if(nr_jucator == 1)
    {
        settextstyle(BOLD_FONT, HORIZ_DIR, 2);
        outtextxy(300, 350, "Alege-ti culoarea: ");
        desen_culoare(k, 1);
        joc.player1.color = 1;
        while(1)
        {

            tasta = getch();
            if(tasta == ARROW_LEFT)
            {
                --k;
                if(k == 0)
                    --k;
                desen_culoare(abs(k)%14, 1);
                joc.player1.color = abs(k)%14;
            }
            else if(tasta == ARROW_RIGHT)
            {
                ++k;
                if(k == 0)
                    ++k;
                desen_culoare(abs(k)%14, 1);
                joc.player1.color = abs(k)%14;
            }
            else if(tasta == ENTER)
                break;

        }
    }
    else
    {
        k = 2;
        settextstyle(BOLD_FONT, HORIZ_DIR, 2);
        outtextxy(300, 450, "Alege-ti culoarea: ");
        desen_culoare(k, 2);
        joc.player2.color = k;
        while(1)
        {
            tasta = getch();
            if(tasta == ARROW_LEFT)
            {
                --k;
                if(k == 0)
                    --k;
                desen_culoare(abs(k)%14, 2);
                joc.player2.color = abs(k)%14;
            }
            else if(tasta == ARROW_RIGHT)
            {
                ++k;
                if(k == 0)
                    ++k;
                desen_culoare(abs(k)%14, 2);
                joc.player2.color = abs(k)%14;
            }
            else if(tasta == ENTER)
                break;

        }
    }


    //getch(); closegraph();
}


int convert_to_int(char num[])
{
    int nr = 0;
    for(int i = 1; i < strlen(num); i++)
    {
        nr = nr*10 + (num[i] - '0'); //ascii(x) - ascii(0) = x-0
    }               //'3' -  '0' =>
   // 54
   // 1. 50 + 4
    //strlen=2

    return nr;
}

void enter_details(int nr_jucatori)
{
    initwindow(getmaxwidth(), getmaxheight());
    readimagefile("Capture.JPG", 0,0, getmaxx(), getmaxy());
    char nume_persoana[MAX_STR]= "";
    char mesaj[MAX_STR] = "";
    if(nr_jucatori == 1)
    {
        strcpy(mesaj,"Introdu numele jucatorului: ");
        CitesteSir(300, 300, mesaj, nume_persoana);
        strcpy(joc.player1.name, nume_persoana);
        alege_culoare(1);
        char mesaj_2[MAX_STR] = "";
        char puncte[MAX_STR] = "";
        strcpy(mesaj_2, "Introdu numar puncte ( de la 3 la 75) ):");
        CitesteSir(300, 400, mesaj_2, puncte);
        puncte[strlen(puncte)] = NULL;
        int nr_puncte=convert_to_int(puncte);
        if (nr_puncte <3 || nr_puncte > 75)
            {
                enter_details(nr_jucatori);
                return;
            }
        joc.table.nrPuncte = nr_puncte;
        outtextxy(300, 500, "Alege dificultatea: ");
        outtextxy(300 + textwidth("Alege dificultatea: ") + 25, 500, "EASY");
        rectangle(300 + textwidth("Alege dificultatea: "), 470, 300 + textwidth("Alege dificultatea: ") + 20 + textwidth("EASY") + 30, 510);
        outtextxy(300 + textwidth("Alege dificultatea: ") + 30 + textwidth("EASY") + 45, 500, "HARD");
        rectangle(300 + textwidth("Alege dificultatea: ") + 20 + textwidth("EASY") + 30, 470, 300 + textwidth("Alege dificultatea: ") + 20 + textwidth("EASY") + 30 + textwidth("HARD") + 50, 510);

        while(1)
        {
            if(ismouseclick(WM_LBUTTONDOWN))
            {
                int x = mousex();
                int y = mousey();
                clearmouseclick(WM_LBUTTONDOWN);
                if(y <= 510 && y >= 470 && x >= 300 + textwidth("Alege dificultatea: ") && x <= 300 + textwidth("Alege dificultatea: ") + 50 + textwidth("EASY"))
                {
                    //mutare_AI();
                    joc.table.dificultate = 1;
                    break;

                }
                else if(y <= 510 && y >= 470 && x >= 300 + textwidth("Alege dificultatea: ") + 20 + textwidth("EASY") + 30 && x <= 300 + textwidth("Alege dificultatea: ") + 20 + textwidth("EASY") + 30 + textwidth("HARD") + 50)
                {
                    //smart_ai
                    joc.table.dificultate = 2;
                    break;
                }
            }

        }

    }
    if(nr_jucatori == 2)
    {
        strcpy(mesaj,"Introdu numele jucatorului 1: ");
        CitesteSir(300, 300, mesaj, nume_persoana);
        strcpy(joc.player1.name, nume_persoana);

        alege_culoare(1);

        char nume_persoana2[MAX_STR]= "";
        char mesaj_2[MAX_STR] = "";
        strcpy(mesaj_2,"Introdu numele jucatorului 2: ");
        CitesteSir(300, 400, mesaj_2, nume_persoana2);
        strcpy(joc.player2.name, nume_persoana2);
        alege_culoare(2);
        char mesaj_3[MAX_STR] = "";
        char puncte[MAX_STR] = "";
        strcpy(mesaj_3, "Introdu numar puncte ( de la 3 la 75) :");
        CitesteSir(300, 500, mesaj_3, puncte);
        puncte[strlen(puncte)] = NULL;
        int nr_puncte=convert_to_int(puncte);
        if (nr_puncte <3 || nr_puncte > 75)
            {
                enter_details(nr_jucatori);
                return;
            }
        joc.table.nrPuncte = nr_puncte;
        // fara dificultate
    }


    closegraph();
}

void buton_replay()
{
    setcolor(WHITE);

    outtextxy(getmaxx()/4 + getmaxx()/2, getmaxy() - 200, "REPLAY");
}


void winning_screen(char c[], int castiga)
{
    delay(600);
    if(castiga == 1)
    {
        char aux[MAX_STR];
        strcpy(aux, c);
        c[strlen(c)] = NULL;
        strcat(c, " won!");
        settextstyle(BOLD_FONT, HORIZ_DIR, 5);
        setcolor(WHITE);
        outtextxy(getmaxx()/2 - 125, getmaxy()-100, c);
        strcpy(c, aux);

    }
    else if(castiga == 2)
    {
        settextstyle(BOLD_FONT, HORIZ_DIR, 5);
        outtextxy(getmaxx()/2 - 125, getmaxy()-100, "Computer won!");

    }

}

void round_express()
{
    expressGame();
    joc.table.puncte_utilizate = 0;
    joc.nrSegm = 0;
    joc.player1.winner = false;
    joc.player2.winner = false;
    joc.table.puncte_blocate=0;
    while(1)
    {
        if(!gameOver())
        {

            miscare(joc.player1.color);
            puncteBlocate();
            if (gameOver())
            {
                joc.player1.winner = true;
                winning_screen(joc.player1.name, 1);
                buton_replay(); //apare butonu replay
                while(1)
                {
                    if(ismouseclick(WM_LBUTTONDOWN))
                    {
                        int x1 = mousex();
                        int y1 = mousey();
                        clearmouseclick(WM_LBUTTONDOWN);
                        if(x1 >= getmaxx()/4 + getmaxx()/2 && x1 <= getmaxx()/4 + getmaxx()/2 + textwidth("REPLAY") && y1 >= getmaxy() - 200 && y1 <= getmaxy()-180)
                        {
                            closegraph();
                            round_express(); //replay
                            return;
                        }
                        if(x1 >= getmaxx()-30 && x1 <= getmaxx() && y1 >= 0 && y1 <= 30)
                        {
                            closegraph();
                            Start_Game();
                        }
                    }
                }


            }
                miscare(joc.player2.color);
                puncteBlocate();
        }
        else
        {
            joc.player2.winner = true;
            winning_screen(joc.player2.name, 1);
            buton_replay(); //apare butonu replay
            while(1)
            {
                if(ismouseclick(WM_LBUTTONDOWN))
                {
                    int x1 = mousex();
                    int y1 = mousey();
                    clearmouseclick(WM_LBUTTONDOWN);
                    if(x1 >= getmaxx()/4 + getmaxx()/2 && x1 <= getmaxx()/4 + getmaxx()/2 + textwidth("REPLAY") && y1 >= getmaxy() - 200 && y1 <= getmaxy()-180)
                    {
                        closegraph();
                        round_express();
                        return;
                    }
                    if(x1 >= getmaxx()-30 && x1 <= getmaxx() && y1 >= 0 && y1 <= 30)
                    {
                        closegraph();
                        Start_Game();
                    }
                }
            }

            break;
        }

    }

}

void round_AI()
{
    extendedGame();
    //afiseaza scor pl1
    //afiseaza scor pl2
    joc.table.puncte_utilizate=0;
    joc.nrSegm=0;
    joc.player1.winner = false;
    joc.table.puncte_blocate=0;
    while(1)
    {
        if(!gameOver())
        {

            miscare(joc.player1.color);
            cout<< "=============="<<endl;
            cout<<"Puncte blocate = "<<joc.table.puncte_blocate<<endl;
            puncteBlocate();
            if (gameOver())
            {
                joc.player1.winner = true;
                winning_screen(joc.player1.name, 1);
                buton_replay();
                while(1)
                {
                    if(ismouseclick(WM_LBUTTONDOWN))
                    {
                        int x1 = mousex();
                        int y1 = mousey();
                        clearmouseclick(WM_LBUTTONDOWN);
                        if(x1 >= getmaxx()/4 + getmaxx()/2 && x1 <= getmaxx()/4 + getmaxx()/2 + textwidth("REPLAY") && y1 >= getmaxy() - 200 && y1 <= getmaxy()-180)
                        {
                            closegraph();
                            round_AI();
                            return;
                        }
                        if(x1 >= getmaxx()-30 && x1 <= getmaxx() && y1 >= 0 && y1 <= 30)
                        {
                            closegraph();
                            Start_Game();
                        }
                    }
                }
                break;
            }
            delay(700);
            if(joc.table.dificultate == 2)
                mutare_super_smart_AI();
            else
                if(joc.table.dificultate == 1)
                mutare_AI();
            puncteBlocate();
            cout<<"Puncte blocate = "<<joc.table.puncte_blocate<<endl;
        }
        else
        {

            winning_screen("", 2);
            buton_replay();
            while(1)
            {
                if(ismouseclick(WM_LBUTTONDOWN))
                {
                    int x1 = mousex();
                    int y1 = mousey();
                    clearmouseclick(WM_LBUTTONDOWN);
                    if(x1 >= getmaxx()/4 + getmaxx()/2 && x1 <= getmaxx()/4 + getmaxx()/2 + textwidth("REPLAY") && y1 >= getmaxy() - 200 && y1 <= getmaxy()-180)
                    {
                        closegraph();
                        round_AI();
                        return;
                    }
                    if(x1 >= getmaxx()-30 && x1 <= getmaxx() && y1 >= 0 && y1 <= 30)
                    {
                        closegraph();
                        Start_Game();
                    }
                }
            }
            //round_AI();
            break;
        }

    }

}

void Start_Game()
{
    initwindow(1280, 720, "Segmente.exe");
    readimagefile("bg.jpg", 0, 0, getmaxx(), getmaxy());

    int mijloc_x = getmaxx()/2;
    buton_mod1();
    buton_mod2();
    buton_reguli();
    buton_iesire();
    while(1)
    {

        if(ismouseclick(WM_LBUTTONDOWN))
        {
            int x = mousex();
            int y = mousey();
            clearmouseclick(WM_LBUTTONDOWN);
            if(x >= mijloc_x - textwidth(MOD1) && x <= mijloc_x + textwidth(MOD1))
            {
                if(y >= 350 - textheight(MOD1) && y <= 350 + 2 * textheight(MOD1))
                {
                    closegraph();
                    enter_details(2);
                    round_express();

                }
                else if(y >= 420 - textheight(MOD2) && y <= 420 + 2 * textheight(MOD2))
                {
                    closegraph();
                    enter_details(1);
                    round_AI();

                }
                else if(y >= 490 - textheight(REGULI) && y <= 490 + 2 * textheight(REGULI))
                {
                    readimagefile("reguli.jpg", 0, 0, getmaxx(), getmaxy());
                    butonStop();
                    while(1)
                    {
                        if(ismouseclick(WM_LBUTTONDOWN))
                        {
                            int x1 = mousex();
                            int y1 = mousey();
                            clearmouseclick(WM_LBUTTONDOWN);
                            if(x1 >= getmaxx()-30 && x1 <= getmaxx() && y1 >= 0 && y1 <= 30) //stop
                            {
                                closegraph();
                                Start_Game();
                                break;
                            }
                        }
                    }
                }
                else if(y >= 560 - textheight(EXIT) && y <= 560 + 2 * textheight(EXIT))
                {

                    return;
                    //iesim de tot din joc
                }

            }

        }

    }
}


#endif
