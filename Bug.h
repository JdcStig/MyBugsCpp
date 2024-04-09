#ifndef BUG_H
#define BUG_H

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <list>


enum class Direction { North, South, East,  West };

class Bug {

public:
    char type;
    int id;
    std::pair<int, int> Current_Position;
    Direction direction;
    int size;
    int hopLength;

    Bug(char type , int id, int x, int y, Direction direction, int size, int hopLength);

    char getType() const;
    int getId() const;
    std::pair<int, int> getCurrent_Position() const;
    Direction getDirection() const;
    int getSize() const;
    int gethopLength() const;

};

void createBugs(std::vector<Bug*> &bugs);

void displayAllBugs(const std::vector<Bug*>& bugs);


#endif // BUG_H
