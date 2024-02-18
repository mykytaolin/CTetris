#include "tetris.h"
#include <stdlib.h>

#ifndef CTETRIS_TETRIS_H
#define CTETRIS_TETRIS_H

// define an algorithm of init templates
TetFiguresT* createTetFiguresT(int count, int figures_size, TetBlock* figures_template) {
    TetFiguresT* tetft = (TetFiguresT*)malloc(sizeof(TetFiguresT));
    tetft->count = count; // number of templates
    tetft->size = figure_size; // size of figure area
    tetft->blocks = figures_template; // size of list of blocks already define by user of our game model

    return tetft;
};

void freeTetFiguresT(TetFiguresT* tetft) {  // function to freeing memory
    if (tetft)
        free(tetft);
};

TetField* createTetField(int width, int height) {
    TetField* tetf = (TetField*)malloc(sizeof(TetField));
    tetf->width = width;
    tetf->height = height;
    tetf->blocks = (TetBlock*)malloc(sizeof(TetBlock)*width*height);
    for(int i=0, i<width*height, i++)
        tetf->blocks[i].b = 0;

    return testf;
};

void freeTetField(TetField* tetf) {  // function to freeing memory
    if (tetf) {  // we malloc 2 times so we need to free memory twice but in reversed way last->first
        if(tetf->blocks)
            free(tetf->blocks);
        free(tetf);
    };
};

TetGame* createTetGame(int field_width, int field_height, int figure_size,
                       int count, TetBlock* figures_template) {

    TetGame* tetg = (TetGame*)malloc(sizeof(TetGame));
    tetg->field = createTetField(field_width, field_height);
    tetg->figurest = createTetFiguresT( count, figures_size, figures_template);

    return tetg;
};

void freeTetGame(TetGame* tetg) {  // when we free memory from base game structure we using created method
    if (tetg) {  // where we work with structural compoments and after that with structure
        freeTetField(tetg->field);
        freeTetFiguresT(tetg->figurest);
        free(tetg);
    };
};

void calculateTet(TetGame* tetg) { // creating the func calculating of one tact of game cycle
    if(tetg->ticks_left <= 0) {
        tetg->ticks_left = tetg->ticks;  // with moving figure we also have to update the number of ticks for next moving
        // the number of takts for moving stored in variable ticks
        moveFigureDown(tetg); // moving figure on one block down
        if(collisionTet(tetg)) {  // if collision - move figure up and raise figure's blocks on the field
            moveFigureUp(tetg);  // and droping new figure
            plantFigure(tetg);
            // before droping figure we have to calculate number of lines full of blocks, delete this lines and
            // add their count to user's score in the game
            tetf->score += eraseLineTet(tetg);
            dropNewFigure(tetg);
            if collisionTet(tetg) { // if just after appearing new figure happends collision - means
                // there are no empty space on the field, so the game have to over
                tetg->playing = TET_GAMEOVER; // the variable playing contain game status
                return;
            // procedure calculating of one tact of game cycle will calling 30 times per second
            // but figure falling slower, so we need to skip a number of takts before figure falling
            // variable ticks_left will contain this number
            };
        };
    };

    switch(tetg->player->action) {  //  processing player's actions
        case TET_PLAYER_RIGHT:  // if player moving figure to the right
            moveFigureRight(tetg);  //  moving to right
            if(collisionTet(tetg))  // if was a collision
                moveFigureLeft(tetg);  //  moving figure in oppositive way
            break;

    };
};

#endif