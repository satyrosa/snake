#include "snake.h"
Snake::Snake()
{
    len = 0;
    head = nullptr;
}

bool Snake::pop_last()//Удаляет последний элемент в списке змеи. Используетя для движения
{
        if(head == nullptr)
        {
            return false;
        }
        else
        {
            FR *curr = head;
            FR *toDel = head;
            while(toDel->nFR)
            {
                toDel = toDel->nFR;
            }
            field[toDel->x][toDel->y] = 0;
            resx = toDel->x;
            resy = toDel->y;
            while(curr->nFR != toDel)
            {
                curr = curr->nFR;
            }
            curr->nFR = nullptr;
            delete toDel;
            len--;
            return true;
        }
}

bool Snake::checkPrevLast(FR *last, int x, int y)
{
    FR *prevLast = head;
    while(prevLast->nFR != last)
        prevLast = prevLast->nFR;
    if(prevLast->x == x and prevLast->y == y)
        return false;
    else
        return true;
}

bool Snake::pop_head()//Удаляет первый элемент в списке змей, используется для зачистки памяти
{
    if(head == nullptr)
    {
        return false;
    }
    else
    {
        FR *temp = head;
        head = head -> nFR;
        delete temp;
        len--;
        return true;
    }
}

void Snake::AddFirst(int x, int y)//Добавляет первый элемент в змеесписок. Используется для движения
{
    if(head == nullptr)
    {
        head = new FR(x, y);
    }
    else
    {
        head = new FR(x, y, head);
    }
    len++;
    //field[head->x][head->y] = 1;
}

void Snake::AddLast(int x, int y)//Добавляет последний элемент в список змеи, используется при поедании яблока
{
    if(head == nullptr)
    {
        head = new FR(x, y);
        field[x][y] = 1;
    }
    else
    {
        FR *curr = this->head;
        while(curr->nFR != nullptr)
        {
            curr = curr->nFR;
        }
        curr->nFR = new FR(x, y);
        curr = curr->nFR;
        if(checkPrevLast(curr, curr->x + 1, curr->y))
        {
            resx = curr->x+1;
            resy = curr->y;
        }
        else
        {
            resx = curr->x-1;
            resy = curr->y;
        }
        field[x][y] = 1;
    }
    len++;
}

Snake::~Snake()
{
    while(pop_head()){}
}


void Game::step_left()
{
    int x = head->x;
    int y = head->y - 1;
    AddFirst(x, y);
    pop_last();
}

void Game::step_right()
{
    int x = head->x;
    int y = head->y + 1;
    AddFirst(x, y);
    pop_last();
}

void Game::step_up()
{
    int x = head->x - 1;
    int y = head->y;
    AddFirst(x, y);
    pop_last();
}

void Game::step_down()
{
    int x = head->x + 1;
    int y = head->y;
    AddFirst(x, y);
    pop_last();
}

Game::Game() // Конструктор основного класса. Выстраивает начальное поле
{
    int x, y;
    for(int i = 0; i < HEIGHT; i++)
    {
        for(int j = 0; j < WIDTH; j++)
        {
            field[i][j] = 0;
        }
    }
   for(int i = 0; i < 4; i++)
    {
        x = HEIGHT/2+i;
        y = WIDTH/2;
        AddLast(x, y);
    }
    resx = x+1;
    resy = y;
}

bool Game::GameOver()
{
    if(head->x == 0 or head->y == 0 or head->x == HEIGHT or head -> y == WIDTH
    or field[head->x][head->y] == 1)
        return false;
    else
    {
        EatApple(resx, resy);
        field[head->x][head->y] = 1;
        return true;
    }
}

void Game::GetApple()
{
    int x, y;
    if(count_apples == 0)
    {
        x = rand()%HEIGHT;
        y = rand()%WIDTH;
        while(field[x][y] != 0)
        {
            x = rand()%HEIGHT;
            y = rand()%WIDTH;
        }
        if(x == 0) x++;
        if(y == 0) y++;

        field[x][y] = 2;
        count_apples++;
    }
}

void Game::EatApple(int x, int y)
{
    if(field[head->x][head->y] == 2)
    {
        AddLast(x, y);
        count_apples--;
    }
}

bool Game::Move(int d = KEY_UP)
{
    switch(d)
    {
        case KEY_LEFT:
            step_left();
            break;
        case KEY_RIGHT:
            step_right();
            break;
        case KEY_DOWN:
            step_down();
            break;
        case KEY_UP:
            step_up();
            break;
    }
    return GameOver();
}



void Printer::Print()
{
    for(int i = 0; i < HEIGHT; i++)
    {
        for(int j = 0; j< WIDTH; j++)
        {
            if(i==0 or i == HEIGHT-1) {printw("-");}
            else if(j == 0 or j == WIDTH-1) {printw("|");}
            else if(field[i][j] == 0) {printw(" ");}
            else if (field[i][j] == 2) {printw("o");}
            else printw("#");
        }
        printw("\n");
    }
}

void Printer::PrintGameOver()
{
    
    for(int i = 0; i < HEIGHT; i++)
    {
        for(int j = 0; j < WIDTH; j++)
        {
            if(i==0 or i == HEIGHT-1) {printw("-");}
            else if(j == 0 or j == WIDTH-1) {printw("|");}
            else if(i == HEIGHT/2 and j == WIDTH/2-4) printw("GAME OVER");
            else if(j > WIDTH/2 - 4 and j < WIDTH/2+5 and i == HEIGHT/2) printw("");
            else printw(" ");
        }
        printw("\n");
    }
}
