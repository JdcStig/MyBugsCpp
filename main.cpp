#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;
using namespace sf;

enum Direction { NORTH, SOUTH , EAST , WEST };

struct bug
{
    CircleShape shape;
    bool isSelected = false;
    char Type='N';
    Direction direction;
    int Size=0;
    int id=0;

    bug()
    {
        shape.setRadius(20);
    }

    bool contains(int x, int y)
    {
        int shapeX = ((int)shape.getPosition().x / 50) * 50;
        int shapeY = ((int)shape.getPosition().y / 50) * 50;
        return x == shapeX && y == shapeY;
    }

    Vector2f getPosition()
    {
        int shapeX = ((int)shape.getPosition().x / 50) * 50;
        int shapeY = ((int)shape.getPosition().y / 50) * 50;
        return Vector2f(shapeX, shapeY);
    }
} ;

void mouseReleased(int x, int y);
void createBug(vector<bug*> &bugs);
void displayBugsCoordinates();

vector<bug*> bugs;
bug *selectedBug = nullptr;

void runGame()

{ // width and height in pixels , 1 bug is 50px
    sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!");

    vector<sf::RectangleShape> bg;
    for (int r = 0; r < 10; r++)
    {
        for (int c = 0; c < 10; c++)
        {
            sf::RectangleShape shape;
            shape.setPosition(r * 50 + 50, c * 50 + 50); // Adjust position to have a 50-pixel gap
            shape.setSize(Vector2f(50, 50));                //brown                                 green
            shape.setFillColor((r + c) % 2 == 0 ? Color(139, 69, 19) :Color(144, 238, 144));
            bg.push_back(shape);
        }
    }

    createBug(bugs);

    int dir = 0;

    // Create buttons                    length    height
    RectangleShape upbutton(Vector2f(500, 50)); //Adjust button shape
    upbutton.setFillColor(Color(192, 192, 192)); //  color silver
    upbutton.setPosition(50, 0); // Adjusting the position of up the button


    RectangleShape downButton(Vector2f(500, 50));
    downButton.setFillColor(Color(192, 192, 192));
    downButton.setPosition(50, 550); // Adjust position for the down button


    RectangleShape rightButton(Vector2f(50, 500));
    rightButton.setFillColor(Color(192, 192, 192));
    rightButton.setPosition(550, 50); // Adjust position for the right button


    RectangleShape leftButton(Vector2f(50, 500));
    leftButton.setFillColor(Color(192, 192, 192));
    leftButton.setPosition(0, 50); // Adjust possition for the left button



    window.setFramerateLimit(40);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                int mouseX = event.mouseButton.x;
                int mouseY = event.mouseButton.y;
            }
            else if (event.type == sf::Event::MouseButtonReleased)
            {
                int mouseX = event.mouseButton.x;
                int mouseY = event.mouseButton.y;
                mouseReleased(mouseX, mouseY);
            }
            else if (event.type == sf::Event::MouseMoved)
            {
                if (selectedBug != nullptr)
                {
                }
            }


            if (event.type == Event::MouseButtonPressed)
            {
                //makes sure that the mouse clickk event is within the bounds of the button and not outside it
                if (event.mouseButton.x >= upbutton.getPosition().x && event.mouseButton.x <= upbutton.getPosition().x + upbutton.getSize().x &&
                    event.mouseButton.y >= upbutton.getPosition().y && event.mouseButton.y <= upbutton.getPosition().y + upbutton.getSize().y)
                {
                    // Move all bugs up by 1 bug (aka 50 pixels)
                    for (bug* t : bugs)
                    {
                        t->shape.move(0, -50);
                    }
                }
            }


            if (event.type == Event::MouseButtonPressed)
            {

                if (event.mouseButton.x >= downButton.getPosition().x && event.mouseButton.x <= downButton.getPosition().x + downButton.getSize().x &&
                    event.mouseButton.y >= downButton.getPosition().y && event.mouseButton.y <= downButton.getPosition().y + downButton.getSize().y)
                {
                    // Move all bugs down by 1 bug (50 pixels)
                    for (bug* t : bugs)
                    {
                        t->shape.move(0, 50);
                    }
                }
            }



            if (event.type == Event::MouseButtonPressed)
            {

                if (event.mouseButton.x >= rightButton.getPosition().x && event.mouseButton.x <= rightButton.getPosition().x + rightButton.getSize().x &&
                    event.mouseButton.y >= rightButton.getPosition().y && event.mouseButton.y <= rightButton.getPosition().y + rightButton.getSize().y)
                {
                    // Move all bugs right by 1 bug (50 pixels)
                    for (bug* t : bugs)
                    {
                        t->shape.move(50, 0);
                    }
                }
            }


            if (event.type == Event::MouseButtonPressed)
            {

                if (event.mouseButton.x >= leftButton.getPosition().x && event.mouseButton.x <= leftButton.getPosition().x + leftButton.getSize().x &&
                    event.mouseButton.y >= leftButton.getPosition().y && event.mouseButton.y <= leftButton.getPosition().y + leftButton.getSize().y)
                {
                    // Move all bugs right by 1 bug (50 pixels)
                    for (bug* t : bugs)
                    {
                        t->shape.move(-50, 0);
                    }
                }
            }

        }

        dir *= -1;
        window.clear();

        // Draw background board
        for (RectangleShape &s : bg)
        {
            window.draw(s);
        }

        // Draw bug
        for (bug* t : bugs)
        {
            window.draw(t->shape);
        }


//checks to make sure that the bugs wont be going off the board if moved in a certain direction


        for (bug* t : bugs)
        {
            if (t->shape.getPosition().y - 50 >= 0) // Check moving up is within the board    -50 is due to the ap needed to display buttons
            {
                t->shape.move(0, -50);
            }
        }

// Move all bugs down by 1 bug (aka 50 pixels) if within bounds
        for (bug* t : bugs)
        {
            if (t->shape.getPosition().y + 50 < window.getSize().y)
            {
                t->shape.move(0, 50);
            }
        }

// Move all bugs right by 1 bug (aka 50 pixels) if within bounds
        for (bug* t : bugs)
        {
            if (t->shape.getPosition().x + 50 < window.getSize().x)
            {
                t->shape.move(50, 0);
            }
        }

// Move all bugs left by 1 bug (aka 50 pixels) if within bounds
        for (bug* t : bugs)
        {
            if (t->shape.getPosition().x - 50 >= 0)
            {
                t->shape.move(-50, 0);
            }
        }


        // Draws all the move buttons
        window.draw(upbutton);
        window.draw(downButton);
        window.draw(rightButton);
        window.draw(leftButton);


        window.display();
    }
}

bool SpaceEmpty(int x, int y)
{
    for (bug* t : bugs)
    {
        if (t->contains(x, y))
        {
            return false;
        }
    }
    return true;
}

void mouseReleased(int x, int y)
{
    int bugX = (x / 50) * 50;
    int bugY = (y / 50) * 50;

    if (selectedBug == nullptr)
    {
        for (bug* t : bugs)
        {
            if (t->contains(bugX, bugY))
            {
                selectedBug = t;
                selectedBug->shape.setOutlineColor(Color::Green);
                break; // Once bug selected no need to check for another as only one can be selected at any given time
            }
        }
    }
    else
    {
        Vector2f pos = selectedBug->getPosition();

        // checks if the distance between the current and target bug is within the correct range e.g 1 bug range
        int checkForX = bugX - pos.x;
        int checkForY = bugY - pos.y;

        // Check if the movement is within one bug distance and the target bug is empty
        if (((abs(checkForX) == 50 && checkForY == 0) || (abs(checkForY) == 50 && checkForX == 0) ||   // horizontal or vertical movement
             (abs(checkForX) == 50 && abs(checkForY) == 50)) &&                                     // diagonal movement
             SpaceEmpty(bugX, bugY))
        {
            selectedBug->shape.setPosition(bugX + 5, bugY + 5);
        }

        // Clear selection after movement
        selectedBug->shape.setOutlineColor(Color::White);
        selectedBug = nullptr;
    }
}

void createBug(vector<bug*> &bugs)
{
    ifstream inputFile("bugs.txt");
    if (!inputFile)
    {
        cout << "Cannot find bugs.txt";
        return;
    }

    string line;
    while (getline(inputFile, line))
    {
        bug* t = new bug();
        stringstream ss(line);
        char type;
        int id, x, y, Size;
        char dir; // temporary store var for direction
        ss >> type >> id >> x >> y  >> dir >> Size;

        // Convert character direction to enum value
        switch (dir)
        {
            case 'N':
                t->direction = NORTH;
                break;
            case 'S':
                t->direction = SOUTH;
                break;
            case 'E':
                t->direction = EAST;
                break;
            case 'W':
                t->direction = WEST;
                break;
        }

        t->shape.setPosition((x * 50) + 5, (y * 50) + 5);
        switch (type)
        {
            case 'C':
                t->shape.setFillColor(Color::Red);
                break;
            case 'H':
                t->shape.setFillColor(Color::Yellow);
                break;
            case 'F':
                t->shape.setFillColor(Color::Blue);
                break;
        }
        t->shape.setOutlineThickness(5);
        t->Size = Size;
        t->id = id;
        bugs.push_back(t);
    }
    inputFile.close();
}


void displayMenu()
{
    cout << "Menu:\n";
    cout << "1. Start Game\n";
    cout << "2. Display Bugs Coordinates\n";
    cout << "3. Find Bug by ID\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
}

void displayBugsCoordinates()
{
    cout << "Bugs Coordinates:\n";
    for (bug* t : bugs)
    {
        Vector2f pos = t->getPosition();
        int bugX = pos.x / 50;  //need to divide by 50 as each bug is 50x50
        int bugY = pos.y / 50;
        cout << "Bug Type: " << t->Type << " Bug ID: " << t->id << " - CoOrdinates (" << bugX << ", " << bugY << ")";

        if (t->direction == NORTH) {
            cout << " Facing North";
        }

        else if (t->direction == SOUTH) {
            cout << " Facing South";
        }

        else if (t->direction == EAST) {
            cout << " Facing East";
        }

        else if (t->direction == WEST) {
            cout << " Facing West";
        }

        cout << " - Size: " << t->Size << "\n";

    }
}

void findBugByID()
{
    int id;
    cout << "Enter Bug ID: ";
    cin >> id;

    bool found = false;
    for (bug* t : bugs)
    {
        if (t->id == id)
        {
            found = true;
            Vector2f pos = t->getPosition();
            int bugX = pos.x / 50;
            int bugY = pos.y / 50;
            cout << "Bug ID: " << t->id << ", Coordinates: (" << bugX << ", " << bugY << "), Size: " << t->Size << endl;
            break;
        }
    }

    if (!found)
    {
        cout << "Bug with ID " << id << " not found." << endl;
    }
}

int main()
{
    int choice;
    do
    {
        displayMenu();
        cin >> choice;

        switch (choice)
        {
            case 1:
                runGame();
                break;
            case 2:
                displayBugsCoordinates();
                break;
            case 3:
                findBugByID();
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 4);

    return 0;
}
