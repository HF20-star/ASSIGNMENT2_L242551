#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

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

    Cell* getCell(int r, int c) {
        Cell* rowPtr = head;
        for (int i = 0; i < r && rowPtr; i++) rowPtr = rowPtr->down;
        Cell* colPtr = rowPtr;
        for (int j = 0; j < c && colPtr; j++) colPtr = colPtr->right;
        return colPtr;
    }

    template<typename F>
    void traverse(F func) {
        Cell* rptr = head;
        while (rptr) {
            Cell* cptr = rptr;
            while (cptr) {
                func(cptr);
                cptr = cptr->right;
            }
            rptr = rptr->down;
        }
    }

    void insertData(const std::string& val) {
        traverse([&](Cell* c) { if (c->selected) c->data = val; });
    }

    int countSelected() {
        int count = 0;
        traverse([&](Cell* c) { if (c->selected) count++; });
        return count;
    }

    double sumSelected() {
        double sum = 0;
        traverse([&](Cell* c) {
            if (c->selected) {
                bool isNum = true;
                const std::string& s = c->data;
                for (int i = 0; i < s.length(); i++) {
                    if ((s[i] < '0' || s[i]>'9') && s[i] != '.') isNum = false;
                }
                if (isNum && s != "") sum += std::stod(s);
            }
            });
        return sum;
    }

    double avgSelected() {
        double sum = 0; int count = 0;
        traverse([&](Cell* c) {
            if (c->selected) {
                bool isNum = true;
                const std::string& s = c->data;
                for (int i = 0; i < s.length(); i++) {
                    if ((s[i] < '0' || s[i]>'9') && s[i] != '.') isNum = false;
                }
                if (isNum && s != "") { sum += std::stod(s); count++; }
            }
            });
        return count ? sum / count : 0;
    }

    int getRows() { return rows; }
    int getCols() { return cols; }
};