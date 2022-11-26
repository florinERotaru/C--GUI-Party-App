#ifndef GENERARE_TABEL_H_
#define GENERARE_TABEL_H_
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
#define MAXIM_PUNCTE_EXTENDED 30
#define MAXIM_PUNCTE_EXPRESS 20
#define RADIUS 8
#include "structuri.h"
#include <time.h>
#include <math.h>
#define COMPUTER 13

using namespace std;
void Start_Game();
void butonStop();
void drawSegment(Punct end1, Punct end2)
{
    setlinestyle(SOLID_LINE, 1, 2);
    line(end1.x, end1.y, end2.x, end2.y );
}

int distanta(Punct p1, Punct p2)
{
    return sqrt( (p1.x-p2.x)* (p1.x-p2.x)  +   (p1.y-p2.y)*(p1.y-p2.y) );
}

int determinaPunctul(int xCoord, int yCoord )
{

    for (int i=0; i<joc.table.nrPuncte; i++)
        if (((joc.puncte[i].x - xCoord)*(joc.puncte[i].x - xCoord)+(joc.puncte[i].y - yCoord)*(joc.puncte[i].y - yCoord))<= RADIUS*RADIUS)
            return i;
    return -1;
}
bool onSegment(Punct p, Punct q, Punct r)
{
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) && q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
       return true;

    return false;
}

// gasim orientarea
//returneaza orientarea
// 0 --> coliniare
// 1 --> dupa a. c
// 2 --> contra
int orientation(Punct p, Punct q, Punct r)
{
    int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0;  // collinear

    return (val > 0)? 1: 2; // clock or counterclock wise
}

// true - intersectie, else false
bool intersectie(Punct p1, Punct q1, Punct p2, Punct q2)
{
    // gasim cele 4 orientari
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // cxaz general
    if (o1 != o2 && o3 != o4)
        return true;

    // Special Cases
    // p1, q1 and p2 col. p2 e pe p1q1
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;

    // p1, q1 and q2 col.  q2 e pe p1q1
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;

    // p2, q2 and p1 col. and p1 e pe p2q2
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;

     // p2, q2 and q1 co. and q1 e pe  p2q2
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;

    return false;
}

int dotProduct(Punct p1, Punct p2)
{
    return p1.x * p2.x + p1.y * p2.y;
}
bool circleSegmentDoIntersect(Punct P1,Punct P2,Punct C)
{
    Punct d, f;
    d.x=P2.x - P1.x; //d= P2-P1
    d.y=P2.y - P1.y;
    f.x=P1.x - C.x; //f=P1-C
    f.y=P1.y - C.y;
    float a=dotProduct(d, d); //produs scalar
    float b=2*dotProduct(f, d); //produs scalar
    float c=(dotProduct(f, f)-(RADIUS*RADIUS)); //ax^2 + bx + c
    double discriminant = (b*b-4*a*c);
    if (discriminant < 0) return false;
    if (discriminant = 0) return true;
    discriminant=sqrt(discriminant);
    double t1 = (-b - discriminant)/(2*a);
    double t2 = (-b + discriminant)/(2*a);
    return (t1 >= 0 && t1 <= 1) || (t2 >= 0 && t2 <= 1);
}
bool any_intersection(Punct p, Punct q, int P1, int P2)
{

    for (int i=0; i<joc.nrSegm; ++i)
        if (intersectie(p, q, joc.segmente[i].p1, joc.segmente[i].p2)) // cu alte semg
            return true;
    for (int i=0; i<=joc.table.nrPuncte; i++)
    {
            if (circleSegmentDoIntersect(p, q, joc.puncte[i]) && i != P1 && i != P2) // cu puncte
                return true;
    }
    return false;
}


bool arePcteComuneCuAltePcte(int x, int y, int k)
{
    Punct p;
    p.x=x;
    p.y=y;
    for (int i=0; i<k; i++)
        if ( distanta(p, joc.puncte[i]) <RADIUS*6)
            return true;
    return false;

}
void drawPoint(Punct centru, int dim, int color)
{

    setcolor(color);
    setfillstyle(SOLID_FILL, color);
    fillellipse(centru.x, centru.y, dim, dim);


}
void marcheaza(Punct centru, int dim, int color)
{

    setcolor(color);
    setfillstyle(SOLID_FILL, color);
    fillellipse(centru.x, centru.y, dim, dim);

}
void expressGame()
{
    int x=getmaxwidth();
    int y=getmaxheight();
    joc.nrSegm=0;
    joc.table.pointColor= 	LIGHTGRAY;
    srand (time(NULL));
    int x1,y1;
    initwindow(x, y, "Express Game");
    readimagefile("Capture.JPG", 0,0, x, y);
    butonStop();
    rectangle((x/2)-(y/3), y/9 ,(x/2)-(y/3)+(y*2/3), (y/9+y*2/3));
    for (int i=0; i<(joc.table.nrPuncte); i++)
    {
        do
        {
            x1=rand()%(y*2/3-20)+((x/2)-(y/3)+10);
            y1=rand()%(y*2/3-20)+((y/9)+10);
        }while (arePcteComuneCuAltePcte(x1, y1, i));
        joc.puncte[i].x=x1;
        joc.puncte[i].y=y1;
        joc.puncte[i].used=false;
        drawPoint(joc.puncte[i], RADIUS, joc.table.pointColor);
    }

}
void extendedGame()
{
    joc.nrSegm=0;
    joc.table.pointColor= RED;
    srand (time(NULL));
    int x=getmaxwidth();
    int y=getmaxheight();
    int x1,y1;
    initwindow(x, y, "Express Game");
    readimagefile("Capture.JPG", 0,0, x, y);
    butonStop();
    rectangle((x/2)-(0.4 * y), y/15 ,(x/2)-((0.4) * y)+(y*0.8), (y/15+y*0.8));
    for (int i=0; i<(joc.table.nrPuncte); i++)
    {
        do
        {
            x1=rand()%(y*4/5-20)+((x/2)-((0.4)*y)+10);
            y1=rand()%(y*4/5-20)+((y/15)+10);
        } while (arePcteComuneCuAltePcte(x1, y1, i));
        joc.puncte[i].x=x1;
        joc.puncte[i].y=y1;
        joc.puncte[i].used=false;
        drawPoint(joc.puncte[i], RADIUS, joc.table.pointColor);
    }

}

void butonStop()
{
    int XMAX = getmaxx();
    rectangle(XMAX-30,3,XMAX-3,27);
    outtextxy(XMAX-20,7,"X"); // butonul dreapta sus
}

void puncteBlocate()
{
    joc.table.puncte_blocate = joc.table.nrPuncte - joc.table.puncte_utilizate; //presupunem
    for(int i = 0; i < joc.table.nrPuncte; i++)
    {
        for(int j = 0; j < joc.table.nrPuncte; j++)
        {
            if(!any_intersection(joc.puncte[i], joc.puncte[j], i, j) && joc.puncte[i].used == false && joc.puncte[j].used == false && i != j)
            {
                joc.table.puncte_blocate--;
                break;
            }
        }
    }
}

void miscare(int PLAYER_COLOR)
{

    int mx1, my1;
    int mx2, my2;
    int P1=-1;
    int P2=-1;
    Punct click;
    do
    {
        do
        {
            if (ismouseclick(WM_LBUTTONDOWN))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                mx1 = mousex();
                my1 = mousey();
                if(mx1 >= getmaxx()-30 && mx1 <= getmaxx() && my1 >= 0 && my1 <= 30)
                {
                    closegraph();
                    Start_Game();

                }
                P1=determinaPunctul(mx1, my1);

                click.x = mx1;
                click.y = my1;
            }
        }while (P1 == -1 || joc.puncte[P1].used == true ); //primul punct selectat corect

        marcheaza(joc.puncte[P1], RADIUS+1, USED);



     do
        {
            if (ismouseclick(WM_LBUTTONDOWN))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                mx2 = mousex();
                my2 = mousey();
                if(mx2 >= getmaxx()-30 && mx2 <= getmaxx() && my2 >= 0 && my2 <= 30)
                {
                    closegraph();
                    Start_Game();
                }
                P2=determinaPunctul(mx2, my2);          //al doilea punct
                if(P2 == -1 || joc.puncte[P2].used == true || P2 == P1 || any_intersection(joc.puncte[P1], joc.puncte[P2], P1, P2) )
                {
                    marcheaza(joc.puncte[P1], RADIUS+1, BLACK);
                    marcheaza(joc.puncte[P1], RADIUS,joc.table.pointColor); //al doilea punct selectat gresit

                    P1=-1;
                    P2=-1;
                    break;
                }
                else
                {
                     marcheaza(joc.puncte[P2], RADIUS+1, USED);//al doilea punct selectat corect

                }


            }
        }while(P2 == -1 );
    }while( P1 < 0 || P2 < 0 );

        setcolor(PLAYER_COLOR);
        drawSegment(joc.puncte[P1], joc.puncte[P2]);
        joc.segmente[joc.nrSegm].p1 = joc.puncte[P1];
        joc.segmente[joc.nrSegm].p2 = joc.puncte[P2];
        joc.nrSegm++;
        joc.table.puncte_utilizate += 2;
        joc.puncte[P1].used=true;
        joc.puncte[P2].used=true;
        puncteBlocate();
}

void mutare_AI()
{
    for(int i=0; i< joc.table.nrPuncte; i++)
    {
        for (int j=i+1; j< joc.table.nrPuncte; j++)
            if(joc.puncte[i].used==false && joc.puncte[j].used==false && !any_intersection(joc.puncte[i], joc.puncte[j], i, j ) )
            {

                marcheaza(joc.puncte[i], RADIUS+1,  USED);
                marcheaza(joc.puncte[j], RADIUS+1, USED);
                setcolor(COMPUTER);
                drawSegment(joc.puncte[i], joc.puncte[j]);
                joc.segmente[joc.nrSegm].p1 = joc.puncte[i];
                joc.segmente[joc.nrSegm].p2 = joc.puncte[j];
                joc.table.puncte_utilizate += 2;
                joc.puncte[i].used=true;
                joc.puncte[j].used=true;
                joc.nrSegm++;
                puncteBlocate();
                return;
            }
    }
}
void mutare_Neblocare_max()
{
    int k=joc.table.puncte_blocate;
    int maxim=0;
    Punct p1max, p2max;
    for (int i=0; i<joc.table.nrPuncte; i++)
        for (int j=i+1; j<joc.table.nrPuncte; j++)
            {
                if (any_intersection(joc.puncte[i], joc.puncte[j], i, j ) || joc.puncte[i].used==true || joc.puncte[j].used==true )
                    continue;

                joc.segmente[joc.nrSegm].p1 = joc.puncte[i];
                joc.segmente[joc.nrSegm].p2 = joc.puncte[j];
                joc.table.puncte_utilizate += 2;
                joc.nrSegm++;
                puncteBlocate(); //salveaza in joc. ... .pcte blocate
                if (k == joc.table.puncte_blocate && distanta(joc.puncte[i], joc.puncte[j]) > maxim) //este > maxim, si NU a blocat
                    {
                        p1max=joc.puncte[i];
                        p2max=joc.puncte[j];
                        maxim= distanta(joc.puncte[i], joc.puncte[j]);
                    }
                Punct P;
                P.x=0;
                P.y=0;
                joc.nrSegm--;
                joc.segmente[joc.nrSegm].p1 =  P;
                joc.segmente[joc.nrSegm].p2 = P;
                joc.table.puncte_utilizate -= 2;
                puncteBlocate();       // sterge punctele i, j

            }
    joc.segmente[joc.nrSegm].p1 = p1max;
    joc.segmente[joc.nrSegm].p2 = p2max;
    joc.table.puncte_utilizate += 2;
    joc.nrSegm++;
    marcheaza(p1max, RADIUS,  USED);
    marcheaza(p2max, RADIUS,  USED);
    setcolor(COMPUTER);
    drawSegment(p1max, p2max);
    int P1, P2;
    P1=determinaPunctul(p1max.x, p1max.y);
    P2=determinaPunctul(p1max.x, p1max.y);
    joc.puncte[P1].used=true;
    joc.puncte[P2].used=true;
     puncteBlocate();



}
void mutare_Neblocare()
{
    int k=joc.table.puncte_blocate;
    for (int i=0; i<joc.table.nrPuncte; i++)
        for (int j=i+1; j<joc.table.nrPuncte; j++)
            {
                if (any_intersection(joc.puncte[i], joc.puncte[j], i, j ) || joc.puncte[i].used==true || joc.puncte[j].used==true)
                    continue;
                joc.segmente[joc.nrSegm].p1 = joc.puncte[i];
                joc.segmente[joc.nrSegm].p2 = joc.puncte[j];
                joc.table.puncte_utilizate += 2;
                joc.nrSegm++;
                puncteBlocate(); //salveaza in joc. ... .pcte blocate
                if (k == joc.table.puncte_blocate && i != j)
                    {
                        marcheaza(joc.puncte[i], RADIUS,  USED);
                        marcheaza(joc.puncte[j], RADIUS,  USED);
                        setcolor(COMPUTER);
                        drawSegment(joc.puncte[i], joc.puncte[j]);
                        joc.puncte[i].used=true;
                        joc.puncte[j].used=true;

                        return;
                    }
                    else
                    {
                        Punct P;
                        P.x=0;
                        P.y=0;
                        joc.nrSegm--;
                        joc.segmente[joc.nrSegm].p1 =  P;
                        joc.segmente[joc.nrSegm].p2 = P;
                        joc.table.puncte_utilizate -= 2;
                    }
            }

}
void mutare_Blocare()
{
    int k=joc.table.puncte_blocate;
    int n=0;
    for (int i=0; i<joc.table.nrPuncte; i++)
        for (int j=i+1; j<joc.table.nrPuncte; j++)
            {
                if (any_intersection(joc.puncte[i], joc.puncte[j], i, j ) || joc.puncte[i].used==true || joc.puncte[j].used==true)
                    continue;
                joc.segmente[joc.nrSegm].p1 = joc.puncte[i];
                joc.segmente[joc.nrSegm].p2 = joc.puncte[j];
                joc.table.puncte_utilizate += 2;
                joc.nrSegm++;
                puncteBlocate(); //salveaza in joc. ... .pcte blocate
                if (k != joc.table.puncte_blocate && i != j)
                    {
                        marcheaza(joc.puncte[i], RADIUS,  USED);
                        marcheaza(joc.puncte[j], RADIUS,  USED);
                        setcolor(COMPUTER);
                        drawSegment(joc.puncte[i], joc.puncte[j]);
                        joc.puncte[i].used=true;
                        joc.puncte[j].used=true;

                        return;
                    }
                    else
                    {
                        Punct P;
                        P.x=0;
                        P.y=0;
                        joc.nrSegm--;
                        joc.segmente[joc.nrSegm].p1 =  P;
                        joc.segmente[joc.nrSegm].p2 = P;
                        joc.table.puncte_utilizate -= 2;
                    }
            }

}

void mutare_super_smart_AI()
{
    puncteBlocate();
    int n=joc.nrSegm;
    cout<<" Blocate mod 4 = "<<joc.table.puncte_blocate % 4<<endl;
    cout<<" Total mod 4 = "<<joc.table.nrPuncte % 4<<endl;
    if (joc.table.puncte_blocate % 4 == joc.table.nrPuncte % 4)
    {
        mutare_Neblocare_max();
        cout<< "NU BLOCHEZ, sunt egale"<<endl;
    }
    else
    {
        mutare_Blocare();
        cout<< "BLOCHEZ..."<<endl;
    }
    if ( n == joc.nrSegm)
    {
        cout<<" BLOCARE NEREUSITA"<<endl;
        mutare_AI();
    }
}

void mutare_smart_AI()
{
    puncteBlocate();
    int n=joc.nrSegm;
    cout<<" Blocate mod 4 = "<<joc.table.puncte_blocate % 4<<endl;
    cout<<" Total mod 4 = "<<joc.table.nrPuncte % 4<<endl;
    if (joc.table.puncte_blocate % 4 == joc.table.nrPuncte % 4)
    {
        mutare_Neblocare();
        cout<< "NU BLOCHEZ, sunt egale"<<endl;
    }
    else
    {
        mutare_Blocare();
        cout<< "BLOCHEZ..."<<endl;
    }
    if ( n == joc.nrSegm)
    {
        cout<<" BLOCARE NEREUSITA"<<endl;
        mutare_AI();
    }
}
bool gameOver()
{
    puncteBlocate();
    return joc.table.nrPuncte == joc.table.puncte_utilizate + joc.table.puncte_blocate; //P = B + U
}




/// T = nr total puncte, U = puncte utilizate, (T - Ut) = puncte neutilizate
/// B = puncte izolate, L = puncte libere
/// La sfarsitul jocului T = U + B, caci L = 0
/// Nr pctelor utilizate indica castigatorul

#endif
