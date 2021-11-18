#ifndef _TTFE_H_
#define _TTFE_H_

#include <stddef.h>

typedef struct game_s {
    size_t board_size;
    unsigned short *board;
} game;

game *board_create(size_t size);
void board_destroy(game *context);

#endif
