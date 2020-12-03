# Chess 960

Today, we will create a Fischer chess board, also known as a Chess960 board. The idea is to randomize the first and last rows to discourage memorizing opening moves.

There are two rules that need to be followed in implementation:
- Bishops must be on opposite color squares
- The king must be between the rooks

Using these rules, there are 960 ways to create a board, hence the name. The goal is to create an array of the randomized row and output a sample board using the command line

## Planning

For a pseudo random number generator, we'll go with *Mersenne Twister 19937*, because that's apparently the *de facto* choice for randomization through software and it's in the standard library. The example in [cplusplus.com](http://www.cplusplus.com/reference/random/mersenne_twister_engine/mersenne_twister_engine/) worked perfectly for this purpose.

```cpp
unsigned  seed = system_clock::now().time_since_epoch().count();
mt19937  random_number (seed);
```
## Keep track of empty squares

The best approach is to use a mutable data structure like a vector to contain the values 0 through 7. Once an index is chosen and used, all we need to do is simply delete it.

```cpp
vector<int> freeSquares;
for (int i=0; i<8; i++) freeSquares.push_back(i);
```

## Piece placement

Placing the dark bishop is just a matter of randomly choosing from the 4 dark squares:
```cpp
int  currentIndex = (random_number() % 4) * 2;
piecePlacement[currentIndex] = 'B';
freeSquares.erase(freeSquares.begin() +  currentIndex);
```

We can take the same approach in choosing the light bishop, but we need to manually find the index number to delete:
```cpp
currentIndex = (random_number() % 4) * 2 + 1;
piecePlacement[currentIndex] = 'B';
freeSquares.erase(
    find(freeSquares.begin(),
    freeSquares.begin()+7,
    currentIndex)
);
```

Let's enter the rest of the pieces in an array. For the first half (knights and queen), randomly choose the placement from the values still available in `freeSquare`. For the second half (rooks and king), place them in the order of values left in `freeSquare`; as long as the other pieces were randomly placed, the indices left will be reasonably random.

```cpp
char pieces[] = {'N', 'N', 'Q', 'R', 'K', 'R'};

for (int i=0; i<6; i++) {

    if (i<3) {
        currentIndex = random_number() % freeSquares.size();piecePlacement[freeSquares.at(currentIndex)] = pieces[i];
        freeSquares.erase(freeSquares.begin() + currentIndex);
    }

    else {
        piecePlacement[freeSquares.front()] = pieces[i];
        freeSquares.erase(freeSquares.begin());
    }       

}
```

## Output

To display the board, loop through 17 times (8 for each board row and 9 for the row separators) and use a switch to control the output.

```cpp
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
```

Now, it's time to test! I created test functions to make sure the Chess960 rules are followed and the row has the appropriate amount of pieces.

For the bishops
```cpp
bool properBishops(char * board) {
    int indices = 0;
    int count = 0;

    for (int i=0; i<8; i++)
        if (*(board+i) == 'B') { indices += i; count++; };

    return (indices % 2) && (count == 2);
}
```

For the rooks and king
```cpp
bool properRooksAndKing(char * board) {
    char pieces[3];

    for (int i=0, j=0; i<8 && j<3; i++)
        if (*(board+i) == 'R' || *(board+i) == 'K') pieces[j++] = *(board+i);
    
    return (pieces[0] == 'R') && (pieces[1] == 'K') && (pieces[2] = 'R');
}
```

Last but not least, the knights and queen
```cpp
bool properKnightsAndQueen(char * board) {
    int knightCount = 0;
    int queenCount = 0;

    for (int i=0; i<8 && knightCount < 3; i++) {
        if (*(board+i) == 'N') knightCount++;
        else if (*(board+i) == 'Q') queenCount++;
    }

    return (knightCount == 2) && (queenCount == 1);
}
```

Now the moment of truth... drum roll please...

```
Result: 100/100 successful tests

Sample board:
---------------------------------
| R | K | Q | B | R | N | B | N |
---------------------------------
| p | p | p | p | p | p | p | p |
---------------------------------
|   |   |   |   |   |   |   |   |
---------------------------------
|   |   |   |   |   |   |   |   |
---------------------------------
|   |   |   |   |   |   |   |   |
---------------------------------
|   |   |   |   |   |   |   |   |
---------------------------------
| p | p | p | p | p | p | p | p |
---------------------------------
| R | K | Q | B | R | N | B | N |
---------------------------------
```

Very nice!