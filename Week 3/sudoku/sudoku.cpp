#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include <cstdint>

class Sudoku {
    private:
        uint16_t cells[9][9];
    public:
        uint16_t get(int i, int j) const {
            assert((0 <= i) && (i < 9));
            assert((0 <= j) && (j < 9));
            return cells[i][j];
        }
        void unset(int i, int j);
        void set(int i, int j, uint16_t val);
        bool is_complete() const;

        Sudoku& operator = (const Sudoku& other) {
            for (size_t i = 0; i < 9; ++i) {
                for (size_t j = 0; j < 9; ++j) {
                    this->cells[i][j] = other.cells[i][j];
                }
            }
            return *this;
        }

        friend std::istream& operator >> (std::istream& is, Sudoku& s);
};

bool Sudoku::is_complete() const {
    for (size_t i = 0; i < 9; ++i) {
        for (size_t j = 0; j < 9; ++j) {
            if (this->cells[i][j] == 0) {
                return false;
            }
        }
    }
    return true;
}

void Sudoku::unset(int i, int j) {
    assert((0 <= i) && (i < 9));
    assert((0 <= j) && (j < 9)); 
    this->cells[i][j] = 0;
}

void Sudoku::set(int i, int j, uint16_t val) {
    assert((0 <= i) && (i < 9));
    assert((0 <= j) && (j < 9)); 
    this->cells[i][j] = val;
}

std::istream& operator >> (std::istream& is, Sudoku& s) {
    for (size_t i = 0; i < 9; ++i) {
        for (size_t j = 0; j < 9; ++j) {
            is >> s.cells[i][j];
        }
    }
    return is;
}

std::ostream& operator << (std::ostream& os, const Sudoku& s) {
     for (size_t i = 0; i < 9; ++i) {
        for (size_t j = 0; j < 9; ++j) {
            os << s.get(i, j);
            if (j < 8) {
                os << " ";
            }
        }
        os << std::endl;
    }
    return os;
}

int main() {
    Sudoku s;
    std::cin >> s;
    s.set(0, 0, 2);
    std::cout >> s;
}
