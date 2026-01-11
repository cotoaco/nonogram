#include <iostream>
#include "nonogram.h"

int main() {
    NonogramGame game;

    int choice = -1;
    std::string filename;

    while (choice != 0) {
        std::cout << "\n===== NONOGRAM MENU =====\n";
        std::cout << "1. Load from file\n";
        std::cout << "2. Print field\n";
        std::cout << "3. Clear field\n";
        std::cout << "4. Solve rows (simple)\n";
        std::cout << "5. Check solution\n";
        std::cout << "6. Save to file\n";
        std::cout << "0. Exit\n";
        std::cout << "Choose: ";

        std::cin >> choice;

        if (choice == 1) {
            std::cout << "Enter file name: ";
            std::cin >> filename;

            if (game.LoadFromFile(filename)) {
                std::cout << "Loaded successfully\n";
            } else {
                std::cout << "Load error\n";
            }
        }

        else if (choice == 2) {
            game.Print();
        }

        else if (choice == 3) {
            char c;
            std::cout << "Enter symbol (. or #): ";
            std::cin >> c;
            game.Clear(c);
            std::cout << "Field cleared\n";
        }

        else if (choice == 4) {
            game.SolveRowsSimple();
            std::cout << "Solver finished\n";
        }

        else if (choice == 5) {
            if (game.Check()) {
                std::cout << "Solution is correct\n";
            } else {
                std::cout << "Solution is NOT correct\n";
            }
        }

        else if (choice == 6) {
            std::cout << "Enter file name: ";
            std::cin >> filename;

            if (game.SaveToFile(filename)) {
                std::cout << "Saved successfully\n";
            } else {
                std::cout << "Save error\n";
            }
        }

        else if (choice == 0) {
            std::cout << "Goodbye!\n";
        }

        else {
            std::cout << "Wrong menu item\n";
        }
    }

    return 0;
}
