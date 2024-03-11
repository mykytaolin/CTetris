#include <stdlib.h>
#include <stdio.h>
#include "tetris.h"

// init global variable which have a templates of figures
// every figure will set in some area 5x5 blocks, where
// 0 - empty figure blocks, 1 - not empty
TetBlock tet_templates[] = {
        0,0,1,0,0,
        0,0,1,0,0,
        0,0,1,0,0,
        0,0,1,0,0,
        0,0,1,0,0,

        0,0,0,0,0,
        0,0,1,0,0,
        0,1,1,1,0,
        0,0,0,0,0,
        0,0,0,0,0,

        0,0,0,0,0,
        0,0,1,1,0,
        0,0,1,0,0,
        0,0,1,0,0,
        0,0,0,0,0,

        0,0,0,0,0,
        0,1,1,0,0,
        0,0,1,0,0,
        0,0,1,0,0,
        0,0,0,0,0,

        0,0,0,0,0,
        0,0,1,1,0,
        0,1,1,0,0,
        0,0,0,0,0,
        0,0,0,0,0,

        0,0,0,0,0,
        0,1,1,0,0,
        0,0,1,1,0,
        0,0,0,0,0,
        0,0,0,0,0,
};

void PrintTetGame(TetGame* tetg) {
    TetField* tf = tetg->field;  // init variables for convenient access to filed and figure
    TetFigure*t = tetg->figure;
    for(int i=0; i<tf->height; i++) {
        for(int j=0; j<tf->width; j++) {
            int sym = 0;
            if(tf->blocks[i*tf->width+j].b != 0)  // if current field block is not empty showing it on the screen
                sym = 1;  // earlier there was printf() but change for some variable value that's show us
                // which block we have to print
            else {  // if not we have to check
                int x = j - t->x;
                int y = i - t->y;
                if(x >=0 && x<t->size && y>=0 && y<t->size)
                    if(t->blocks[y*t->size+x].b != 0)
                        sym = 1;
            };
            printf("%d", sym); // but printf not guarantied of immediately showing sym on screen
        };
    };
    fflush(stdout); //  for immediately showing sym we have to free some buffer
};

int main(int argc, char* argv[]) {
    TetGame* tetg = createTetGame(34, 30, 5, 6, tet_templates);
    TetPlayer playing;
    player.action = TET_PLAYER_NOP;
    tetg->player = &player;

    while(tetg->playing != TET_GAMEOVER) {
        calculateTet(tetg);
        PrintTetGame(tetg);  // procedure for showing game situation on the screen
    };
    freeTetGame(tetg);
    return 0;
}
