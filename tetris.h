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

enum {  // list of const for game status
    TET_GAMEOVER = 0,
    TET_PLAYING
};

enum {  // constants describing player's actions
    TET_PLAYER_NOP = 0,  // AFK
    TET_PLAYER_UP,  // pressing up key
    TET_PLAYER_DOWN,  // pressing down key
    TET_PLAYER_LEFT,  // pressing left key
    TET_PLAYER_RIGHT  // pressing right key
};

typedef struct TetPlayer {  // structure describe player actions
    int action;
}TetPlayer;

typedef struct TetGame {
    TetField* field;  // information about game field and info about block on it
    TetFigure* figure; // info about type of falling figure
    TetFiguresT* figurest;  // info about all figures on the game field
    TetPlayer* player;  // variable for interacting with user
    int ticks;  //  the number of takts for moving stored in variable ticks
    int ticks_left;  //  variable ticks_left containing number of takts we skip before figure falling
    int playing;  //  game status
    int score;  // user's scores
}TetGame;

TetGame* createTetGame(int field_width, int field_height, int figure_size,
                       int count, TetBlock* figures_template);  // protorype of function which init base game structure

void calculateTet(TetGame* tetg);


#endif //CTETRIS_TETRIS_H