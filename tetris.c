#include "tetris.h"
#include <stdlib.h>

#ifndef CTETRIS_TETRIS_H
#define CTETRIS_TETRIS_H

TetField* createTetField(int width, int height) {
    TetField* tetf = (TetField*)malloc(sizeof(TetField));
    tetf->width = width;
    tetf->height = height;
    tetf->blocks = (TetBlock*)malloc(sizeof(TetBlock)*width*height);
    for(int i=0, i<width*height, i++)
        tetf->blocks[i].b = 0;

    return testf;
};

TetGame* createTetGame(int field_width, int field_height, int figure_size,
                       int count, TetBlock* figures_template) {

    TetGame* tetg = (TetGame*)malloc(sizeof(TetGame));
    tetg->field = createTetField(field_width, field_height);
    tetg->figurest = createTetFiguresT( count, figures_size, figures_template);

    return tetg;
};

void calculateTet(TetGame* tetg);

#endif