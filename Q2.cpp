#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>

class Cell {
public:
    std::string data;
    bool selected;
    int row, col;
    Cell* right;
    Cell* down;
    Cell(int r = 0, int c = 0) : data(""), selected(false), row(r), col(c), right(nullptr), down(nullptr) {}
};

class Spreadsheet {
private:
    Cell* head;
    int rows, cols;
public:
    Spreadsheet(int r, int c) : rows(r), cols(c) { head = createGrid(); }

    Cell* createGrid() {
        Cell* top = nullptr;
        Cell* prevRow = nullptr;
        for (int i = 0; i < rows; i++) {
            Cell* rowHead = new Cell(i, 0);
            if (!top) top = rowHead;
            Cell* curr = rowHead;
            for (int j = 1; j < cols; j++) {
                curr->right = new Cell(i, j);
                curr = curr->right;
            }
            if (prevRow) {
                Cell* up = prevRow;
                Cell* down = rowHead;
                while (up && down) {
                    up->down = down;
                    up = up->right;
                    down = down->right;
                }
            }
            prevRow = rowHead;
        }
        return top;
    }
