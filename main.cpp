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
};

void mouseReleased(int x, int y);
void createTile(vector<tile*> &tiles);
vector<tile*> tiles;
tile *selectedTile = nullptr;

void runGame()
{
    sf::RenderWindow window(sf::VideoMode(400, 400), "SFML works!");

    vector<sf::RectangleShape> bg;
    for (int r = 0; r < 8; r++)
    {
        for (int c = 0; c < 8; c++)
        {
            sf::RectangleShape shape;
            shape.setPosition(r * 50, c * 50);
            shape.setSize(Vector2f(50, 50));                //Brown                             //Light Green
            shape.setFillColor((r + c) % 2 == 0 ? Color(139, 69, 19) :Color(144, 238, 144));

            bg.push_back(shape);
        }
    }

    createTile(tiles);

    int dir = 0;
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
        }

        dir *= -1;
        window.clear();
        for (RectangleShape &s : bg)
        {
            window.draw(s);
        }
        for (tile* t : tiles)
        {
            window.draw(t->shape);
        }
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
                break; // Once tile selected i dont need to check for another as i can only select 1 at a time
            }
        }
    }
    else
    {
        Vector2f pos = selectedTile->getPosition();
        if (abs(tileX - pos.x) == 50 && abs(tileY - pos.y) == 50 && tileEmpty(tileX, tileY))
        {
            selectedTile->shape.setPosition(tileX + 5, tileY + 5);
        }

        // Make it so nothing is now selected  after a movement
        selectedTile->shape.setOutlineColor(Color::White);
        selectedTile = nullptr;
    }
}

void createTile(vector<tile*> &tiles)
{
    ifstream inputFile("bugs.txt");
    if (!inputFile)
    {
        cout << "Can not open file bugs.txt";
        return;
    }

    string line;
    while (getline(inputFile, line))
    {
        tile* t = new tile();
        stringstream ss(line);
        int x, y;
        int color;
        ss >> x >> y >> color;
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
        tiles.push_back(t);
    }
    inputFile.close();
}

void displayMenu()
{
    cout << "Menu:\n";
    cout << "1. Start Game\n";
    cout << "2. Exit\n";
    cout << "Enter your choice:\n";
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
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 2);

    return 0;
}
