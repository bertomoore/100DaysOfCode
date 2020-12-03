#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>

using std::chrono::system_clock;
using std::cout;
using std::find;
using std::mt19937;
using std::vector;

class Chess960 {
private:
    char piecePlacement[8] = {};

public:
    Chess960() {

        // Random number generator
        unsigned seed = system_clock::now().time_since_epoch().count();
        mt19937 random_number (seed);

        // Available indices on the board
        vector<int> freeSquares;
        for (int i=0; i<8; i++) freeSquares.push_back(i);
        
        // Place dark bishop
        int currentIndex = (random_number() % 4) * 2;
        piecePlacement[currentIndex] = 'B';

        freeSquares.erase(freeSquares.begin() + currentIndex);

        // Place light bishop
        currentIndex = (random_number() % 4) * 2 + 1;
        piecePlacement[currentIndex] = 'B';

        freeSquares.erase(
            find(freeSquares.begin(),
            freeSquares.begin()+7,
            currentIndex)
        );

        // Place the rest of the pieces through iteration
        char pieces[] = {'N', 'N', 'Q', 'R', 'K', 'R'};
        for (int i=0; i<6; i++) {

            // The queen and knights order doesn't matter
            if (i<3) {
                currentIndex = random_number() % freeSquares.size();
                piecePlacement[freeSquares.at(currentIndex)] = pieces[i];
                freeSquares.erase(freeSquares.begin() + currentIndex);
            }

            // The king and rooks must stay in array order
            else {
                piecePlacement[freeSquares.front()] = pieces[i];
                freeSquares.erase(freeSquares.begin());
            }
            
        }

    }

    char * board() { return piecePlacement; }

    void showBoard() {
        
        for (int i=0; i<17; i++) {

            switch(i) {

                // Columns with pieces
                case 1:
                case 3:
                case 13:
                case 15:

                    char piece;
                    for (int j=0; j<8; j++) {

                        piece = (i == 1 || i == 15) ? 
                                (*(piecePlacement+j)) : 'p';

                        cout << "| " << piece << " ";
                    
                    }
                    cout << "|\n";
                    break;

                // Columns without pieces
                case 5:
                case 7:
                case 9:
                case 11:

                    for (int j=0; j<8; j++) cout << "|   ";
                    cout << "|\n";
                    break;

                // Column borders
                default:
                    for (int j=0; j<33; j++) cout << '-';
                    cout << "\n";

            }

        }

    }

};