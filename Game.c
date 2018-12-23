/*
* Snake-Game created by SomeRandomDev
* Date: 20.12.2018 - 23.12.2018
* 
* This is a simple 'Snake Game' where
* you controll with 'w', 'a', 's', 'd'.
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define width 20
#define height 9
#define max_lenght (width - 2) * (height - 2)

#define wall '#'
#define nothing ' '
#define snake_head '@'
#define snake_body '~'
#define fruit 'F'

int printf(const char * restrictformat, ... );
int system(const char *command);
void moveSnake(int x, int y);
int getX(int n);
int getY(int n);
void genFruit();
int random_number(int min_num, int max_num);

int dir;
int grid[width][height];
int snake[max_lenght];
int gameOver;

int fruitX;
int fruitY;

/*Gets the keyboardinput*/
void input()
{
    int c;
    if(_kbhit()) //If key pressed
        if((c = _getch()) != EOF)
            if(c == 'w' || c == 's' || c == 'a' || c == 'd')
                dir = c;
}

void update()
{
    switch(dir)
    {
        case 'a':
            moveSnake(getX(snake[0]) - 1, getY(snake[0]));
            break;
        case 'd':
            moveSnake(getX(snake[0]) + 1, getY(snake[0]));
            break;
        case 'w':
            moveSnake(getX(snake[0]), getY(snake[0]) - 1);
            break;
        case 's':
            moveSnake(getX(snake[0]), getY(snake[0]) + 1);
            break;
    }

    //If collides with the wall
    if(getX(snake[0]) < 1 || getX(snake[0]) > width - 2 || getY(snake[0]) < 1 || getY(snake[0]) > height - 2)
        gameOver = 1;

    int a, b;
    int curr_lenght;
    curr_lenght = a = b = 0;
    while(snake[curr_lenght] != '\0')
        curr_lenght++;

    if(curr_lenght == max_lenght){
        gameOver = 2;
        return;
    }

    for(a = 0; a < curr_lenght; a++)
        for(b = 0; b < curr_lenght; b++)
            if(snake[a] == snake[b] && a != b) //Checks if the snake collides with itself
                gameOver = 1;

    if(getX(snake[0]) == fruitX && getY(snake[0]) == fruitY) //checks if the snake collides with the fruit
    {
        snake[curr_lenght] = snake[curr_lenght - 1];
        genFruit();
    }
} 

void moveSnake(int x, int y)
{
    int curr_lenght, i;
    curr_lenght = i = 0;
    while(snake[curr_lenght] != '\0')
        curr_lenght++;
    for(i = curr_lenght; i > 1; i--)
    {
        snake[i - 1] = snake[i-2];
    }
    snake[0] = x * 10 + y;
}

int getX(int n)
{return n / 10;}

int getY(int n)
{return n % 10;}

int random_number(int min_num, int max_num)
{
    int result = 0, low_num = 0, hi_num = 0;

    if (min_num < max_num)
    {
        low_num = min_num;
        hi_num = max_num + 1;  // include max_num in output
    } else {
        low_num = max_num + 1; // include max_num in output
        hi_num = min_num;
    }

    srand(time(NULL));
    result = (rand() % (hi_num - low_num)) + low_num;
    return result;
}

void genFruit()
{
    fruitX = random_number(1, width - 2);
    fruitY = random_number(1, height - 2);
}

void draw()
{
    system("cls");
    int i, x, y, curr_lenght, should_paint;
    curr_lenght = i = 0;
    while(snake[curr_lenght] != '\0')
        ++curr_lenght;

    if(gameOver == 1)
    {
        printf("Game Over! Your score: %i\n", curr_lenght);
        return;
    }
    if(gameOver == 2)
    {
        printf("You won! Your score: %i\n", curr_lenght);
        return;
    }

    for (y = 0; y < height; y++)
    {
        for(x = 0; x < width; x++)
        {
            should_paint = 1;
            for(i = 0; i < curr_lenght; i++)
            {
                if(x == getX(snake[i]) && y == getY(snake[i]))
                {
                    if(i == 0){
                        putchar(snake_head);
                    }else if(should_paint == 1){
                        putchar(snake_body);
                    }
                    should_paint = 0;
                    continue;
                }
            }
            if(x == fruitX && y == fruitY && should_paint == 1)
            {
                should_paint = 0;
                putchar(fruit);
            }

            if((y == 0 || y == height-1 || x == 0 || x == width-1) && should_paint == 1)
            {putchar(wall);}
            else if(should_paint == 1)
            {putchar(nothing);}
        }
        putchar('\n');
    }
}

void gameLoop()
{
    input();
    update();
    draw();
    int c, d;
    for (c = 1; c <= 32767; c++)
       for (d = 1; d <= 32767  / 7; d++)
       {}
    
    if(gameOver == 0)
        gameLoop();
}

void init()
{
    genFruit();
    gameOver = 0;
    snake[0] = 2 * 10 + 2; // x * 10 + y
}

int main()
{
    init();
    draw();
    gameLoop();
    system("pause");
    return 0;
}
