#ifndef EXPERIMENTS
#define EXPERIMENTS

#include <iostream>


void experiment_1(int* grid, int size_x){
    // Generate obstacles
    for (int x = 0; x < 120; x++) {
        for (int y = 50; y < 52; y++) {
            int index = x + y * size_x;
            grid[index*4] = -1;
            grid[index*4 + 1] = -1;
            grid[index*4 + 2] = -1;
            grid[index*4 + 3] = -1;
        }
    }
    for (int x = 125; x < 250; x++) {
        for (int y = 50; y < 52; y++) {
            int index = x + y * size_x;
            grid[index*4] = -1;
            grid[index*4 + 1] = -1;
            grid[index*4 + 2] = -1;
            grid[index*4 + 3] = -1;
        }
    }

    // Generate particles
    for (int x = 0; x < 250; x++) {
        for (int y = 0; y < 50; y++) {
            int index = x + y * size_x;
            grid[index*4 + rand()%(4)] = 1;
        }
    }
}


// Lateral collision
void experiment_2(int* grid, int size_x){
    for (int x = 0; x < 120; x++) {
        for (int y = 0; y < 250; y++) {
            int index = x + y * size_x;
            grid[index*4 + 0] = 1;
        }
    }

    for (int x = 130; x < 250; x++) {
        for (int y = 0; y < 250; y++) {
            int index = x + y * size_x;
            grid[index*4 + 2] = 1;
        }
    }
}
#endif