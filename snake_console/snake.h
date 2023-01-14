#ifndef SNAKE_H
#define SNAKE_H

#include <chrono>
#include <thread>
#include <iostream>   // Standard Header
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <stdio.h>
#include "ncurses.h"

#if HAVE_STROPTS_H
#include <stropts.h>
#endif

using namespace std;
class Field;
class Snake;
class Printer;

class Field
{
protected:
    static const int HEIGHT = 20;
    static const int WIDTH = 80;
    int field[HEIGHT][WIDTH];   
public:
     
};

class Snake : public virtual Field
{
protected:
    class FR;
    int len;
    FR *head;
    int resx;
    int resy;

    class FR
    {
    public:
        FR *nFR;
        int x;
        int y;
        FR()
        {
            x = 0;
            y = 0;
            nFR = nullptr;
        }
        FR(int x, int y, FR *nFR = nullptr)
        {
            this->x = x;
            this->y = y;
            this->nFR = nFR;
        }
    };
public:
    Snake();

    bool checkPrevLast(FR *last, int x, int y);
    void AddLast(int x, int y);
    void AddFirst(int x, int y);
    
    int getLen() {return len;}
    FR operator[](const int index);
    
    bool pop_head();
    bool pop_last();
    
    ~Snake();
    
};
class Printer : public virtual Field
{
public:
    void Print();

    void PrintGameOver();
   
 };

 class Game : public Snake, public Printer
{
protected:
    int count_apples = 0;
    void step_left();
    void step_right();
    void step_up();
    void step_down();
public:
    Game();
    bool GameOver();
    bool Move(int d);
    void GetApple();
    void EatApple(int x, int y); 
};



#endif