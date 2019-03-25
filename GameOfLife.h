#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

std::vector<std::vector<int>> grid;
std::vector<std::vector<int>> tickGrid;

// TODO: Save options into a file.
int width = 15;
int height = 15;
int speed = 1;
int starting = 200;

int iteration = 0;

void menu();
void newGame();
void options();
void printGame();
bool simulate();
int neighbors(int, int);

#endif