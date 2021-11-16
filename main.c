#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int gNumbers[] = {2, 4};
int board[4][4];
int ended = 0;

void createGame();
void printUI();
void genPosition();
void move(int x, int y);
void end(int win);

int main()
{
    srand(time(NULL));
    createGame();
    while (ended == 0) {
        char c = getchar();
        switch (c) {
            case '2':
                move(0, 1);
                break;
            case '6':
                move(1, 0);
                break;
            case '8':
                move(0, -1);
                break;
            case '4':
                move(-1, 0);
                break;
            case '5':
                return EXIT_SUCCESS;
            default:
                printUI();
                break;
        }
    }
    return EXIT_SUCCESS;
}

void createGame()
{
    for (int x = 0; x < 4; ++x) {
        for (int y = 0; y < 4; ++y) {
            board[x][y] = 0;
        }
    }
    genPosition();
    printUI();
}

void printUI()
{
    printf("\e[1;1H\e[2J");
    printf("\\ & & & &\n");
    for (int y = 0; y < 4; ++y) {
        printf("&");
        for (int x = 0; x < 4; ++x) {
            if (board[x][y] == 0)
                printf(" .");
            else
                printf(" %d", board[x][y]);
        }
        printf("\n");
    }
}

void genPosition()
{
    int number = 0;
    for (int x = 0; x < 4; ++x)
        for (int y = 0; y < 4; ++y)
            number += (board[x][y] != 0);
    if (number == 16) {
        end(0);
        return;
    }
    do {
        int x = rand() % 4;
        int y = rand() % 4;
        int number = rand() % 2;
        if (board[x][y] == 0) {
            board[x][y] = gNumbers[number];
            return;
        }
    } while (1);
}

void move(int x, int y)
{
    clock_t start = clock();
    for (int X = (x!=-1?3:0); x!=-1?X>=0:X<4; x!=-1?--X:++X) {
        for (int Y = (y==-1?3:0); y==-1?Y>=0:Y<4; y==-1?--Y:++Y) {
            int value = board[X][Y];
            if (value == 0)
                continue;
            int xTemp = X;
            int yTemp = Y;
            do {
                xTemp+=x;
                yTemp+=y;
                if (xTemp < 4
                    && xTemp >= 0
                    && yTemp < 4
                    && yTemp >= 0
                    && (board[xTemp][yTemp] == value
                        || board[xTemp][yTemp] == 0)) {
                    board[xTemp-x][yTemp-y] = 0;
                    board[xTemp][yTemp] += value;
                    value = board[xTemp][yTemp];
                    if(value >= 2048)
                        end(1);
                } else
                    break;
            } while (1);
        }
    }
    genPosition();
    printUI();
    clock_t result = clock() - start;
    printf("Les opérations ont pris %ld millis !\n", result);
}

void end(int win)
{
    ended = 1;
    if (win == 0)
        printf("VOUS AVEZ PERDU !\n");
    else
        printf("VOUS AVEZ GAGNE !\n");
}