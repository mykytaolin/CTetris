#ifndef CTETRIS_TETRIS_H
#define CTETRIS_TETRIS_H

typedef struct TetBlock {
    int b;
}TetBlock;

typedef struct TetFigure {
    int x;
    int y;
    int size;  // field behind a falling figure is a square with size of this variable
    TetBlock* blocks;  // this variable will contain the list of blocks relevant to this figure
}TetFigure;

typedef struct TetFiguresT {  // for describing the figure we have to have:
    int count;  // number of this figures
    int size;  // length of the side of square field on which this figure is placed
    TetBlock* blocks;  // and list of blocks,
    // block variable is variable which refers to unbreakable memory field which contain an info about,
    // all block templates
}TetFiguresT;

typedef struct TetField {  // containing height and width of game field and variable which contain list of blocks
    int width;
    int height;
    TetBlock* blocks;

}TetField;

typedef struct TetGame {
    TetField* field;  // information about game field and info about block on it
    TetFigure* figure; // info about type of falling figure
    TetFiguresT* figurest;  // info about all figures on the game field
}TetGame;

TetGame* createTetGame(int field_width, int field_height, int figure_size,
                       int count, TetBlock* figures_template);  // protorype of function which init base game structure

void calculateTet(TetGame* tetg);


#endif //CTETRIS_TETRIS_H