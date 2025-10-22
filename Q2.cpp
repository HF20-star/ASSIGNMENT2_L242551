#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
using namespace std;

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

int main() {
    int rows = 4, cols = 4;
    Spreadsheet sheet(rows, cols);
    sf::RenderWindow window(sf::VideoMode(600, 600), "Mini Spreadsheet");

    sf::Vector2f cellSize(120, 80);
    std::string inputText = "";
    sf::Text inputDisplay;
    sf::Font font;
    font.loadFromFile("C:/Windows/Fonts/arial.ttf"); 
    inputDisplay.setFont(font);
    inputDisplay.setCharacterSize(20);
    inputDisplay.setFillColor(sf::Color::Black);
    bool typing = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    int col = event.mouseButton.x / cellSize.x;
                    int row = event.mouseButton.y / cellSize.y;
                    if (row < rows && col < cols) {
                        Cell* c = sheet.getCell(row, col);
                        if (c) c->selected = !c->selected;
                        typing = true;
                    }
                }
            }
            else if (event.type == sf::Event::TextEntered && typing) {
                if (event.text.unicode == 8 && !inputText.empty()) inputText.pop_back();
                else if (event.text.unicode >= 32 && event.text.unicode < 128) inputText += static_cast<char>(event.text.unicode);
            }
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter) {
                    sheet.insertData(inputText);
                    inputText = "";
                }
                else if (event.key.code == sf::Keyboard::Escape) window.close();
            }
        }

        window.clear(sf::Color::White);

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                Cell* c = sheet.getCell(i, j);
                sf::RectangleShape rect(cellSize);
                rect.setPosition(j * cellSize.x, i * cellSize.y);
                rect.setFillColor(c->selected ? sf::Color(173, 216, 230) : sf::Color::White);
                rect.setOutlineColor(sf::Color::Black);
                rect.setOutlineThickness(2);
                window.draw(rect);

                sf::Text txt(c->data.empty() ? " " : c->data.c_str(), font, 20);
                txt.setPosition(j * cellSize.x + 5, i * cellSize.y + 5);
                txt.setFillColor(sf::Color::Black);
                window.draw(txt);
            }
        }

        inputDisplay.setString("Type and press Enter: " + inputText);
        inputDisplay.setPosition(10, rows * cellSize.y + 10);
        window.draw(inputDisplay);

        sf::Text stats;
        stats.setFont(font);
        stats.setCharacterSize(18);
        stats.setFillColor(sf::Color::Red);
        stats.setPosition(10, rows * cellSize.y + 40);
        stats.setString("Count: " + std::to_string(sheet.countSelected()) +
            "  Sum: " + std::to_string(sheet.sumSelected()) +
            "  Avg: " + std::to_string(sheet.avgSelected()));
        window.draw(stats);

        window.display();
    }
    return 0;
}
