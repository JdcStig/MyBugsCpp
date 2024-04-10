#include "Bug.h"
#include <iostream>



Bug::Bug(char type ,int id, int x, int y, Direction direction, int size, int hopLength , bool alive)
        : type(type),id(id), Current_Position(x, y), direction(direction), size(size) , hopLength(hopLength) , alive(alive){}
//initialized The bug class and stating what is expected at each stage.

char Bug::getType() const  {
    return type;
}

int Bug::getId() const {
    return id;
}

std::pair<int, int> Bug::getCurrent_Position() const {
    return Current_Position;
}

Direction Bug::getDirection() const {
    return direction;
}

int Bug::getSize() const {
    return size;
}

int Bug::gethopLength() const {
    return hopLength;
}

bool Bug::getDorA() const {
    return  alive;
}



Bug* findBugById(const std::vector<Bug*>& bugs, int id) {

    for (Bug* bug : bugs)
    {
        if (bug->getId() == id) {
            return bug;
        }
    }
    return nullptr; // If the ID the user is searching for doesnt exist it will return a null pointer indicating so
}




void createBugs(std::vector<Bug*> &bugs) {
    std::ifstream inputFile("bugs.txt");
    if (!inputFile) {
        std::cout << "Cannot find File";
        return;
    }

    std::string line;

    while (std::getline(inputFile, line))
    {
        std::stringstream readingIn(line);
        bool alive=true;
        char type;
        int id, x, y, directionStore, size, hopLength;
        readingIn >> type >> id >> x >> y >> directionStore >> size >> hopLength;
        Direction direction = static_cast<Direction>(directionStore);//converts the number being read in from a file to an enum

        //https://stackoverflow.com/questions/8357240/how-to-automatically-convert-strongly-typed-enum-into-int

        Bug* bug = new Bug(type , id, x, y, direction, size , hopLength,alive);

        bugs.push_back(bug);
    }
    inputFile.close();
}

void displayAllBugs(const std::vector<Bug*>& bugs) {
    std::cout << "All Bugs:\n";
    for (Bug* b : bugs)
    {

        //https://workat.tech/problem-solving/tutorial/cpp-stl-pair-complete-guide-ia62jqg0dszu#:~:text=Pairs%20store%20values%20as%20%7Bfirst,accessed%20using%20the%20second%20keyword.

        int bugX = b->getCurrent_Position().first;
        int bugY = b->getCurrent_Position().second;

        std::cout << "Bug Type: " << b->getType() <<" Bug ID: " << b->getId() << ", Position: (" << bugX << ", " << bugY << "), ";

        std::cout << "Direction: ";
        switch (b->getDirection()) {
            case

                Direction::North:
                std::cout << "North";

                break;

            case Direction::East:
                std::cout << "East";

                break;

            case Direction::South:
                std::cout << "South";

                break;

            case Direction::West:
                std::cout << "West";

                break;
        }
        std::cout << ", Size: " << b->getSize() << ", Hop Length: " << b->gethopLength() <<" , State: ";

        switch (b->getDorA()) {
            case

                0:
                std::cout << "Dead \n";

                break;

            case 1:
                std::cout << "Alive\n";

                break;
        }

    }

    //move
    //block
}



