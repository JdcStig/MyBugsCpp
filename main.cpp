#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;
using namespace sf;

struct tile
{
    CircleShape shape;
    bool isSelected = false;
    Color color;
    int health;
    int id;
    tile() : color(Color::White) // default color is white
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
void createTile(vector<tile*> &tiles);
void displayBugsCoordinates();

vector<tile*> tiles;
tile *selectedTile = nullptr;

void runGame()
{                                                   //width and height in pixels , 1 tile is 50px
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

    createTile(tiles);

    int dir = 0;

    // Create buttons               //length    height
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
                if (selectedTile != nullptr)
                {
                }
            }


            if (event.type == Event::MouseButtonPressed)
            {
                //makes sure that the mouse clickk event is within the bounds of the button and not outside it
                if (event.mouseButton.x >= upbutton.getPosition().x && event.mouseButton.x <= upbutton.getPosition().x + upbutton.getSize().x &&
                    event.mouseButton.y >= upbutton.getPosition().y && event.mouseButton.y <= upbutton.getPosition().y + upbutton.getSize().y)
                {
                    // Move all bugs up by 1 tile (aka 50 pixels)
                    for (tile* t : tiles)
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
                    // Move all bugs down by 1 tile (50 pixels)
                    for (tile* t : tiles)
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
                    // Move all bugs right by 1 tile (50 pixels)
                    for (tile* t : tiles)
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
                    // Move all bugs right by 1 tile (50 pixels)
                    for (tile* t : tiles)
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

        // Draw tiles
        for (tile* t : tiles)
        {
            window.draw(t->shape);
        }






//checks to make sure that the bugs wont be going off the board if moved in a certain direction


        for (tile* t : tiles)
        {
            if (t->shape.getPosition().y - 50 >= 0) // Check moving up is within the board    -50 is due to the ap needed to display buttons
            {
                t->shape.move(0, -50);
            }
        }

// Move all bugs down by 1 tile (aka 50 pixels) if within bounds
        for (tile* t : tiles)
        {
            if (t->shape.getPosition().y + 50 < window.getSize().y)
            {
                t->shape.move(0, 50);
            }
        }

// Move all bugs right by 1 tile (aka 50 pixels) if within bounds
        for (tile* t : tiles)
        {
            if (t->shape.getPosition().x + 50 < window.getSize().x)
            {
                t->shape.move(50, 0);
            }
        }

// Move all bugs left by 1 tile (aka 50 pixels) if within bounds
        for (tile* t : tiles)
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

bool tileEmpty(int x, int y)
{
    for (tile* t : tiles)
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
    int tileX = (x / 50) * 50;
    int tileY = (y / 50) * 50;

    if (selectedTile == nullptr)
    {
        for (tile* t : tiles)
        {
            if (t->contains(tileX, tileY))
            {
                selectedTile = t;
                selectedTile->shape.setOutlineColor(Color::Green);
                break; // Once tile selected no need to check for another as only one can be selected at any given time
            }
        }
    }
    else
    {
        Vector2f pos = selectedTile->getPosition();

        // checks if the distance between the current and target tile is within the correct range e.g 1 tile range
        int checkForX = tileX - pos.x;
        int checkForY = tileY - pos.y;

        // Check if the movement is within one tile distance and the target tile is empty
        if (((abs(checkForX) == 50 && checkForY == 0) || (abs(checkForY) == 50 && checkForX == 0) ||   // horizontal or vertical movement
             (abs(checkForX) == 50 && abs(checkForY) == 50)) &&                                     // diagonal movement
            tileEmpty(tileX, tileY))
        {
            selectedTile->shape.setPosition(tileX + 5, tileY + 5);
        }

        // Clear selection after movement
        selectedTile->shape.setOutlineColor(Color::White);
        selectedTile = nullptr;
    }
}

void createTile(vector<tile*> &tiles)
{
    ifstream inputFile("bugs.txt");
    if (!inputFile)
    {
        cout << "Unable to open file bugs.txt";
        return;
    }

    string line;
    while (getline(inputFile, line))
    {
        tile* t = new tile();
        stringstream ss(line);
        int id, x, y, color, health;
        ss >> id >> x >> y >> color >> health;
        t->shape.setPosition((x * 50) + 5, (y * 50) + 5);
        switch (color)
        {
            case 0:
                t->shape.setFillColor(Color::Red);
                break;
            case 1:
                t->shape.setFillColor(Color::Yellow);
                break;
            case 2:
                t->shape.setFillColor(Color::Blue);
                break;
        }
        t->shape.setOutlineThickness(5);
        t->health = health;
        t->id = id;
        tiles.push_back(t);
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
    for (tile* t : tiles)
    {
        Vector2f pos = t->getPosition();
        int tileX = pos.x / 50;  //need to divide by 50 as each tile is 50x50
        int tileY = pos.y / 50;
        cout << "Bug ID: " << t->id << " - Tile (" << tileX << ", " << tileY << ") - Health: " << t->health << "\n";
    }
}

void findBugByID()
{
    int id;
    cout << "Enter Bug ID: ";
    cin >> id;

    bool found = false;
    for (tile* t : tiles)
    {
        if (t->id == id)
        {
            found = true;
            Vector2f pos = t->getPosition();
            int tileX = pos.x / 50;
            int tileY = pos.y / 50;
            cout << "Bug ID: " << t->id << ", Coordinates: (" << tileX << ", " << tileY << "), Health: " << t->health << endl;
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
