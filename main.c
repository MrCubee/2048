#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int gNumbers[] = {2, 4};
int board[4][4];
int ended = 0;

void createGame();
void printUI();
void genPosition(int type[4][4]);
void move(int x, int y, int type[4][4]);
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
                move(0, 1, board);
                break;
            case '6':
                move(1, 0, board);
                break;
            case '8':
                move(0, -1, board);
                break;
            case '4':
                move(-1, 0, board);
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
    genPosition(board);
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

void genPosition(int type[4][4])
{
    int number = 0;
    for (int x = 0; x < 4; ++x)
        for (int y = 0; y < 4; ++y)
            number += (type[x][y] != 0);
    if (number == 16) {
        end(0);
        return;
    }
    do {
        int x = rand() % 4;
        int y = rand() % 4;
        int number = rand() % 2;
        if (type[x][y] == 0) {
            type[x][y] = gNumbers[number];
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

void move(int x, int y, int type[4][4])
{
    if (ended) return;
    for (int X = (x!=-1?3:0); x!=-1?X>=0:X<4; x!=-1?--X:++X) {
        for (int Y = (y==-1?3:0); y==-1?Y>=0:Y<4; y==-1?--Y:++Y) {
            int value = type[X][Y];
            if (value == 0)
                continue;
            int xTemp = X;
            int yTemp = Y;
            do {
                xTemp+=x;
                yTemp+=y;
                if (isValid(xTemp, yTemp, value)) {
                    type[xTemp - x][yTemp - y] = 0;
                    type[xTemp][yTemp] += value;
                    value = type[xTemp][yTemp];
                    if (value >= 2048) {
                        end(1);
                        return;
                    }
                } else
                    break;
            } while (1);
        }
    }
    genPosition(type);
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

void aiPlay()
{
    int moves[4][2] = {{0, 1},{1, 0},{-1, 0},{0, -1}};
    int scores[4];

    int search_board[4][4];
    strcpy(search_board, board);

    for (int i = 0; i < 4; ++i) {
        move(moves[i][0], moves[i][1], search_board);
        scores[i] += 1;
    }
}