#include "snake.cpp"


int main()
{
    initscr();
    cbreak();
    noecho();
    halfdelay(1000);
    keypad(stdscr, true);
    
    Game g;

    g.Print();
    int d, dd;   
    d = getch();
    halfdelay(5);
    
    while(g.Move(d))
    { 
        dd = d;
        clear();
        refresh();
        g.Print();
        d = getch();
        if(d == ERR)
        {
            d = dd; 
        }
        g.Print();
        g.GetApple();
    }

    clear();
    refresh();
    g.PrintGameOver();
    halfdelay(100000);
    getch();
    endwin();
    
}