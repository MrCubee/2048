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
void aiPlay();

int main()
{
    srand(time(NULL));
    createGame();
    char c;
    while (ended == 0) {
        c = getchar();
        switch (c) {
            case 'h':
                printf("\e[1;1H\e[2J");
                printf("Voici comment jouer : \n");
                printf("    8    \n");
                printf("    ^    \n");
                printf("4 <   > 6\n");
                printf("    v    \n");
                printf("    2    \n");
                printf("Pour arrêter la game > 5\n");
                printf("Une fois terminer, tapez 0\n");
                break;
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
            case '0':
                while(ended == 0) {
                    aiPlay();
                }
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
    printf("Comment jouer ? Tapez h ;)");
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

int isValid(int x, int y, int value)
{
    return x < 4
           && x >= 0
           && y < 4
           && y >= 0
           && (board[x][y] == value
               || board[x][y] == 0);
}

void move(int x, int y)
{
    if (ended) return;
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
                if (isValid(xTemp, yTemp, value)) {
                    board[xTemp - x][yTemp - y] = 0;
                    board[xTemp][yTemp] += value;
                    value = board[xTemp][yTemp];
                    if (value >= 2048) {
                        end(1);
                        return;
                    }
                } else
                    break;
            } while (1);
        }
    }
    genPosition();
    printUI();
}

void end(int win)
{
    ended = 1;
    if (win == 0)
        printf("VOUS AVEZ PERDU !\n");
    else
        printf("VOUS AVEZ GAGNE !\n");
}

void aiPlay() {
    int moves[4][2] = {{0, 1},{1, 0},{-1, 0},{0, -1}};
    int scores[4];

    for (int i = 0; i < 4; ++i) {
        move(moves[i][0], moves[i][1]);
        scores[i] += 1;

        for (int depth = 0; depth < 5; ++depth) {
            int search_board[4][4];
        }
    }
}