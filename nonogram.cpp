#include "nonogram.h"
#include <iostream>
#include <fstream>

NonogramGame::NonogramGame() {
    rows = 0;
    cols = 0;
}

bool NonogramGame::LoadFromFile(std::string filename) {
    std::ifstream file(filename.c_str());

    if (!file.is_open()) {
        std::cout << "File error\n";
        return false;
    }

    file >> rows >> cols;

    field.clear();
    field.resize(rows);

    for (int i = 0; i < rows; i++) {
        field[i].resize(cols);
        for (int j = 0; j < cols; j++) {
            file >> field[i][j];
        }
    }

    UpdateHints();
    return true;
}

bool NonogramGame::SaveToFile(std::string filename) {
    std::ofstream file(filename.c_str());

    if (!file.is_open()) return false;

    file << rows << " " << cols << "\n";

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            file << field[i][j] << " ";
        }
        file << "\n";
    }

    return true;
}

void NonogramGame::Print() {
    std::cout << "\nNONOGRAM\n";

    for (int i = 0; i < rows; i++) {
        for (int h = 0; h < rowHints[i].size(); h++) {
            std::cout << rowHints[i][h] << " ";
        }

        std::cout << "| ";

        for (int j = 0; j < cols; j++) {
            std::cout << field[i][j] << " ";
        }
        std::cout << "\n";
    }
}

std::vector<int> NonogramGame::MakeHints(std::vector<char> line) {
    std::vector<int> result;
    int count = 0;

    for (int i = 0; i < line.size(); i++) {
        if (line[i] == '#') {
            count++;
        } else {
            if (count > 0) {
                result.push_back(count);
                count = 0;
            }
        }
    }

    if (count > 0) result.push_back(count);
    if (result.size() == 0) result.push_back(0);

    return result;
}

void NonogramGame::UpdateHints() {
    rowHints.clear();
    colHints.clear();

    for (int i = 0; i < rows; i++) {
        rowHints.push_back(MakeHints(field[i]));
    }

    for (int j = 0; j < cols; j++) {
        std::vector<char> column;
        for (int i = 0; i < rows; i++) {
            column.push_back(field[i][j]);
        }
        colHints.push_back(MakeHints(column));
    }
}

bool NonogramGame::Check() {
    for (int i = 0; i < rows; i++) {
        if (MakeHints(field[i]) != rowHints[i]) return false;
    }

    for (int j = 0; j < cols; j++) {
        std::vector<char> column;
        for (int i = 0; i < rows; i++) {
            column.push_back(field[i][j]);
        }
        if (MakeHints(column) != colHints[j]) return false;
    }

    return true;
}

void NonogramGame::Clear(char symbol) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            field[i][j] = symbol;
        }
    }
}

void NonogramGame::GenerateRows(
    int hintIndex,
    int startPos,
    std::vector<int> hints,
    std::vector<char> row,
    std::vector<std::vector<char>>& results
) {
    if (hintIndex == hints.size()) {
        results.push_back(row);
        return;
    }

    int len = hints[hintIndex];

    for (int i = startPos; i + len <= cols; i++) {
        std::vector<char> newRow = row;

        for (int j = 0; j < len; j++) {
            newRow[i + j] = '#';
        }

        GenerateRows(hintIndex + 1, i + len + 1, hints, newRow, results);
    }
}

void NonogramGame::SolveRowsSimple() {
    for (int i = 0; i < rows; i++) {
        if (rowHints[i].size() == 1 && rowHints[i][0] == 0) {
            for (int j = 0; j < cols; j++) {
                field[i][j] = '.';
            }
            continue;
        }

        std::vector<std::vector<char>> variants;
        std::vector<char> emptyRow(cols, '.');

        GenerateRows(0, 0, rowHints[i], emptyRow, variants);

        for (int j = 0; j < cols; j++) {
            bool allBlack = true;
            bool allWhite = true;

            for (int k = 0; k < variants.size(); k++) {
                if (variants[k][j] == '#') allWhite = false;
                else allBlack = false;
            }if (allBlack) field[i][j] = '#';
            if (allWhite) field[i][j] = '.';
        }
    }
}
