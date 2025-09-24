#include <array>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

class TicTacToe {
public:
    static constexpr int X = 1;
    static constexpr int O = -1;
    static constexpr int EMPTY = 0;

    TicTacToe() { clearBoard(); }

    void clearBoard() {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                board[i][j] = EMPTY;
        player = X; // first player is X
    }

    void putMark(int i, int j) {
        if (i < 0 || i > 2 || j < 0 || j > 2)
            throw std::invalid_argument("Invalid board position");
        if (board[i][j] != EMPTY)
            throw std::invalid_argument("Board position occupied");

        board[i][j] = player;
        player = -player; // switch players (O = -X)
    }

    bool isWin(int mark) const {
        return ((board[0][0] + board[0][1] + board[0][2] == mark * 3) || // row 0
            (board[1][0] + board[1][1] + board[1][2] == mark * 3) || // row 1
            (board[2][0] + board[2][1] + board[2][2] == mark * 3) || // row 2
            (board[0][0] + board[1][0] + board[2][0] == mark * 3) || // col 0
            (board[0][1] + board[1][1] + board[2][1] == mark * 3) || // col 1
            (board[0][2] + board[1][2] + board[2][2] == mark * 3) || // col 2
            (board[0][0] + board[1][1] + board[2][2] == mark * 3) || // diag
            (board[2][0] + board[1][1] + board[0][2] == mark * 3));  // rev diag
    }

    int winner() const {
        if (isWin(X)) return X;
        if (isWin(O)) return O;
        return EMPTY;
    }

    std::string toString() const {
        std::ostringstream sb;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                switch (board[i][j]) {
                case X:     sb << "X"; break;
                case O:     sb << "O"; break;
                case EMPTY: sb << " "; break;
                }
                if (j < 2) sb << "|";
            }
            if (i < 2) sb << "\n-----\n";
        }
        return sb.str();
    }

private:
    std::array<std::array<int, 3>, 3> board{};
    int player;
};

int main() {
    TicTacToe game;
    /* X moves: */              /* O moves: */
    game.putMark(1, 1);          game.putMark(0, 2);
    game.putMark(2, 2);          game.putMark(0, 0);
    game.putMark(0, 1);          game.putMark(2, 1);
    game.putMark(1, 2);          game.putMark(1, 0);
    game.putMark(2, 0);

    std::cout << game.toString() << "\n";

    int winningPlayer = game.winner();
    const char* outcome[3] = { "O wins", "Tie", "X wins" };
    std::cout << outcome[1 + winningPlayer] << "\n";
}
