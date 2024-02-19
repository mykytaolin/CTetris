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

void moveFigureDown(TetGame* tetg) {  // procedure for moving figure down
    tetg->figure->y++;  // enough just to increase y coordinate(figure) by 1
};

void moveFigureUp(TetGame* tetg) {  // procedure for moving figure up
    tetg->figure->y--;  // enough just to discrease y coordinate(figure) by 1
};

void moveFigureLeft(TetGame* tetg) {  // procedure for moving figure left
    tetg->figure->x--;  // enough to discrease x coordinate(figure) by 1
};

void moveFigureRight(TetGame* tetg) {  // procedure for moving figure right
    tetg->figure->x++;  // enough to increase x coordinate(figure) by 1
};

int collisionTet(TetGame* tetg) {
    TetFigure* t = tetg->figure;  // for convenient access to needed data,
    TetField* tf = tetg->field;   // declaring variable to falling figure and game field
    for(int i=0; i<t->size, i++)  // theoretically, collision can happend only in field of figure visualisation
        for(int j=0; j<t->size; j++) {  // all information about 2 dimension object always saved in 1 dimensional arrays
                                        // [j; x] == [x; y]
            if(t->blocks[i*t->size+j]).b != 0 {  // if that figure block not empty - we have to calculate
            int fx = t->x + j;                   //  block coordinates on the game field
            int fy = t->y + i;
            if(tf->blocks[fy*tf->width+fx].b != 0)  // if in the same place on field exist none empty block
                return 1;                           // so there is collision and we returning 1
            if(fx < 0 || fx >= tf->width || fy < 0 || fy >= tf->height)  // the same principle for collisions with field borders
                return 1;
            };
        };
    return 0;   // if there are no collisions return 0
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

        case TET_PLAYER_LEFT:
            moveFigureLeft(tetg);
            if(collisionTet(tetg))
                moveFigureRight;
            break;

        case TET_PLAYER_DOWN:
            moveFigureDown(tetg);
            if(collisionTet(tetg))
                moveFigureUp;
            break;

        case TET_PLAYER_UP: {  //  if player move figure up - mean he is rotating it
            TetFigure* t = rotFigure(tetg);  // init variable to contain figure after rotation
            TetFigure* told = tetg->figure;  // init variable to contain old version
            tetg->figure = t;
            if(collisionTet(tetg)) {  // if collision - returning to old version and deleting new version
                tetg->figure = told;
                freeFigure(t);
            };
            else {  // if no collision do opositive
                freeFigure(told);
            };
        };
            break;

        case TET_PLAYER_NOP:  // if AFK
        default:
            break;
    };

    tetg->ticks_left--;

};

#endif