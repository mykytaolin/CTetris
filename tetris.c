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

void plantFigure(TetGame* tetg) {  // function that define figure placement after falling
    // this func is exec after collision, so figure can't have not zero blocks crossed the pole
    TetFigure* t = tetg->figure;  // get the figure from link of variable tetg
    for(int i=0; i<t->size; i++) // if figure size > 0
        for(int j=0; j<t->size; j++)
            if(t->blocks[i*t->size+j].b != 0) {  // if blocks != 0 - define the pole coordinates that block has and replace it data on the field
                int fx = t->x + j;
                int gy = t->y + i;
                tetg->field->blocks[fy*tetg->field->width+fx].b =  // access to block[fx, fy] and copy value of b
                        //  from variable t[i, j] to tetg->field codeblock with coordinates[fx, fy]
                        t->blocks[i*t->size+j].b;
            };
};

int LineFilledTet(int i, TetField* tfl) {  // func for checking the line for containing objects
    for(int j=0; j<tfl->width; j++)
        if(tfl->block[i*tfl->width+j].b == 0)  // if we find the empty block in line return 0 if not - 1
            return 0;
        return 1;
};

void dropLineTet(int i; TetField* tfl) {  // procedure for droping line from field
    if(i == 0) {  // if line 0 - we just erase objects from it
        for(int j=0; j<tfl->width; j++)
            tfl->block[j].b = 0;
    }
        else {  // if not drag the previous line and drop on the current line
            for(int k=i; k>0; k--) {
                for(int j=0; j<tfl->width; j++)
                    tfl->block[k*tfl->width+j].b == tfl->block[(k-1)*tfl->width+j].b
                    // k - index of current line; k-1 index of upper line
                    // procedure start from the current position(k=i) to first position(k>0)
            };
    };
};

int eraseLineTet(TetGame* tetg) {  // func for erasing lines on gamefield
    TetField* tfl = tetg->field; // copy field value from codeblock tetg to tfl for convinience
    int count = 0;  // number of erased lines will contained in count variable
    for(int i=tfl->hieght-1; i>=0; i--) {
        // we will delete lines from the end and move lines down
        while(LineFilledTet(i, tfl)) {  // while current line is filled
            dropLineTet(i, tfl);  // delete this line and move down
            count++;  // and add erasedlines by 1
        };
    };
    return count;
};

TetFigure* createTetFigure(TetGame* tetg) {
    TetFigure* t = (TetFigure*)malloc(sizeof(TetFigure));  // set the memory for structure
    t->x = 0;
    t->y = 0;
    t->size = tetg->figurest->size;  // size of figure range the same as size of template
    t->blocks = (TetBlock*)malloc(sizeof(TetBlock)*t->size*t->size);  // set memory for keeping blocks
    return t;
};

void freeTetFigure(TetFigure*  tf) {
    // fistly we have to free object from memory and after that free structure and descripting from memory
    if(tf) {
        if(tf->blocks)
            free(tf->blocks);
        free(tf);
    };
};

void dropNewFigure(TetGame* tetg) {  // droping new figure
    TetFigure* t = createTetFigure(tetg);  // creating new figure in memory
    t->x = tetg->width/2 - t->size/2;  // set the coordinates in the middle of the field
    t->y = 0; setting the y coordinate to 0, so the figure will appear at the top of field
    int fnum = rand() % tetg->figurest->count;  // kind of template will take in random way from all templates
    for(int i=0; i<t->size; i++)
        for(int j=0; j<t->size; j++) {
            // let's copy templates to our object range. The number of template define the movement in
            // list of blocks which equal the taked template
            t->blocks[i*t->size+j].b = tetg->figurest->blocks[fnum*t->size*t->size +
                i*t->size+j].b;
        };
    freeFigure(tetg->figure);  // deleting the last figure and replace it with new one
    tetg->figure = t;
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