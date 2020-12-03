#include "chess960.h"
#include <iostream>

using std::cout;

bool properBishops(char * board) {
    int indices = 0;
    int count = 0;

    for (int i=0; i<8; i++)
        if (*(board+i) == 'B') { indices += i; count++; };

    return (indices % 2) && (count == 2);
}

bool properRooksAndKing(char * board) {
    char pieces[3];

    for (int i=0, j=0; i<8 && j<3; i++)
        if (*(board+i) == 'R' || *(board+i) == 'K') pieces[j++] = *(board+i);
    
    return (pieces[0] == 'R') && (pieces[1] == 'K') && (pieces[2] = 'R');
}

bool properKnightsAndQueen(char * board) {
    int knightCount = 0;
    int queenCount = 0;

    for (int i=0; i<8 && knightCount < 3; i++) {
        if (*(board+i) == 'N') knightCount++;
        else if (*(board+i) == 'Q') queenCount++;
    }

    return (knightCount == 2) && (queenCount == 1);
}

int main() {

    Chess960 chess;
    char * iter;
    int successTestsCount = 0;

    for (int i=0; i<100; i++) {

        chess = Chess960();
        iter = chess.board();

        if (properBishops(iter) &&
            properRooksAndKing(iter) &&
            properKnightsAndQueen(iter)) successTestsCount++;

        else {
            cout << "Failed test: ";
            for (int j=0; j<8; j++) cout << *(iter+j) << ", ";
            cout << "\n\n";
        }

    }

    cout << "\nResult: " << successTestsCount << "/100 successful tests\n\n";
    cout << "Sample board:\n";
    chess.showBoard();

}