#include <iostream>
#include <stdlib.h>
#include <vector>
#include "GameOfLife.h"
#include <chrono>
#include <thread>

int main() {
    menu();
}

void menu() {
    int option = -1;
    while (option != 3) {
        std::cout << "Welcome to Conway's Game of Life by Van" << std::endl;
        // TODO: Display currently selected options.
        std::cout << "Please select an option from the menu:" << std::endl;
        std::cout << "1 - Start a new game" << std::endl;
        std::cout << "2 - Change options" << std::endl;
        std::cout << "3 - Exit game" << std::endl;
        std::cout << "Enter option: ";
        std::cin >> option;
        // TODO: Check for input errors.

        switch (option) {
            case 1:
                newGame();

                std::cout << "Would you like to return to menu? [y/n]" << std::endl;
                char input;
                std::cin >> input;
                if (input == 'n') {
                    return;
                }
                std::cout << std::endl;
                break;
            case 2:
                options();
                break;
            case 3:
                break;
            default:
                std::cout << std::endl << "Please select a valid option" << std::endl;
                break;
        }
    }
}

void newGame() {
    int lifeCount = starting;
    for (int i = 0; i < height; i++) {
        std::vector<int> x;
        for (int j = 0; j < width; j++) {
            x.push_back(0);
        }
        grid.push_back(x);
    }
    for (int i = 0; i < starting; i++) {
        grid[rand() % height][rand() % width] = 1;
    }
    printGame();
    tickGrid = grid;
    while(simulate());
}

void options() {
    int option = -1;
    while (option != 5) {
        std::cout << std::endl << "Please select an option from the menu:" << std::endl;
        std::cout << "1 - Change height" << std::endl;
        std::cout << "2 - Change width" << std::endl;
        std::cout << "3 - Change gamespeed" << std::endl;
        std::cout << "4 - Change starting cells" << std::endl;
        std::cout << "5 - Return to menu" << std::endl;
        std::cout << "Enter option: ";
        std::cin >> option;
        // TODO: Check for input errors.

        switch (option) {
            case 1:
                std::cout << std::endl << "The current height is: " << height << std::endl;
                std::cout << "Please enter a new height to use: ";
                std::cin >> height;
                break;
            case 2:
                std::cout << std::endl << "The current width is: " << width << std::endl;
                std::cout << "Please enter a new width to use: ";
                std::cin >> width;
                break;
            case 3:
                std::cout << std::endl << "The current gamespeed is: " << speed << std::endl;
                std::cout << "Please enter a new gamespeed to use between 1 and 10: ";
                std::cin >> speed;
                break;
            case 4:
                std::cout << std::endl << "The current number of starting cells are: "
                  << starting << std::endl;
                std::cout << "Please enter a new number of starting cells to use: ";
                std::cin >> starting;
                break;
            case 5:
                std::cout << std::endl;
                return;
            default:
                std::cout << std::endl << "Please select a valid option" << std::endl;
                break;
        }
    }
}

void printGame() {
    std::cout << std::endl << "Generation " << iteration << std::endl;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (grid[i][j] == 1) {
                std::cout << "# ";
            }
            else {
                std::cout << ". ";
            }
        }
        std::cout << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::seconds(speed));
}

bool simulate() {
    int alive = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int liveNeighbors = neighbors(i, j);
            if (grid[i][j] == 1) {
                alive++;
                // Rule 1.
                if (liveNeighbors < 2) {
                    tickGrid[i][j] = 0;
                    alive--;
                }
                // Rule 2.
                else if (liveNeighbors == 2 || liveNeighbors == 3) {
                    // Cell lives.
                }
                // Rule 3.
                else if (liveNeighbors > 3) {
                    tickGrid[i][j] = 0;
                    alive--;
                }
            }
            else {
                // Rule 4.
                if (liveNeighbors == 3) {
                    tickGrid[i][j] = 1;
                    alive++;
                }
            }
        }
    }
    iteration++;
    grid = tickGrid;
    printGame();
    if (alive == 0) {
        // Game is over.
        return false;
    }
    else {
        return true;
    }
}

int neighbors(int h, int w) {
    // Check all neighboring 8 squares.
    int live = 0;
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (h + i >= 0 && h + i < height 
              && w + j >= 0 && w + j < width
              && (i != 0 || j !=0)) {
                if (grid[h + i][w + j] == 1) {
                    live++;
                }
            }
        }
    }
    return live;
}