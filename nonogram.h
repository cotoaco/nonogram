#include <vector>
#include <string>

class NonogramGame {
public:
    NonogramGame();

    bool LoadFromFile(std::string filename);
    bool SaveToFile(std::string filename);

    void Print();
    bool Check();

    void Clear(char symbol);
    void SolveRowsSimple();

private:
    int rows;
    int cols;

    std::vector<std::vector<char>> field;
    std::vector<std::vector<int>> rowHints;
    std::vector<std::vector<int>> colHints;

    std::vector<int> MakeHints(std::vector<char> line);
    void UpdateHints();

    void GenerateRows(
        int hintIndex,
        int startPos,
        std::vector<int> hints,
        std::vector<char> row,
        std::vector<std::vector<char>>& results
    );
};
