#include <stdlib.h>
#include <string.h>
#include "ttfe.h"

game *__ttfe_board_create(size_t size)
{
    game *result;

    if (!size)
        return NULL;
    result = malloc(sizeof(game));
    if (!result)
        return NULL;
    *result = (game) {0};
    result->board_size = size;
    result->board = malloc(size * size * sizeof(unsigned short));
    if (!result->board) {
        free(result);
        return NULL;
    }
    memset(result->board, 0, size * size);
    return result;
}

game *board_create(size_t size)
__attribute__ ((weak, alias("__ttfe_board_create")));

void __ttfe_board_destroy(game *context)
{
    if (!context)
        return;
    free(context->board);
    free(context);
}

void board_destroy(game *context)
__attribute__ ((weak, alias("__ttfe_board_destroy")));
