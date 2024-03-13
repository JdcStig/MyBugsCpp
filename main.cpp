// Sample program main.cpp
#include <SFML/Graphics.hpp>
#include <vector>
using namespace sf;
using namespace std;


struct tile
{
    CircleShape shape;

    bool isSelected(int x, int y)
    {
        int posX = shape.getPosition().x;
        int posY = shape.getPosition().y;

        return (x >= posX && x <= posX+46 &&y >= posY && y <= posY+46 );
    }
    Vector2f getPosition()
    {
        int currX = (shape.getPosition().x/50)*50;
        int currY = (shape.getPosition().y/50)*50;

        return Vector2f(currX, currY);
    }
};

void keyPressed(Keyboard::Key, sf::CircleShape&);
void mouseClicked(int x, int y);
tile *selectedTile = nullptr;
vector<tile> tiles;

int main()
{
    sf::RenderWindow window(sf::VideoMode(400, 400), "SFML works!");
    sf::CircleShape shape(25.f);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(100,0);
    int dirY = 15, dirX = 6;
    vector<RectangleShape> background;

    int st = 0;
    for(int r = 7; r >= 0; r--)
    {
        if(r >=5 || r <=2) {
            for (int c = st; c <= 7; c += 2) {
                tile t;
                t.shape = CircleShape(23.0f);
                t.shape.setFillColor(r <=2?Color::Red:Color::Magenta);
                t.shape.setOutlineColor(Color::Black);
                t.shape.setOutlineThickness(2);
                t.shape.setPosition((c * 50)+2, (r * 50)+2);
                tiles.push_back(t);
            }
            if (r % 2 == 1) {
                st++;
            } else {
                st--;
            }
        }

    }
    for(int r = 0; r < 8; r++)
    {
        for(int c = 0; c < 8; c++)
        {
            sf::RectangleShape shape(Vector2f(50,50));
            shape.setFillColor((r+c)%2==0?Color::Black:Color::White);
            shape.setPosition(c*50,r*50);
            background.push_back(shape);
        }
    }
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if(event.type == Event::MouseButtonReleased)
            {

                mouseClicked(event.mouseButton.x, event.mouseButton.y);

            }
            else if(event.type == Event::KeyReleased )
            {

                   keyPressed(event.key.code, shape);

            }
        }

        window.setFramerateLimit(40);


        window.clear();
        for(RectangleShape &s : background)
        {
            window.draw(s);
        }
        for(tile &s : tiles)
        {
            window.draw(s.shape);
        }
        window.display();
    }

    return 0;
}

void keyPressed(Keyboard::Key key, sf::CircleShape &shape)
{
    if(key == Keyboard::Num1)
    {
        shape.setFillColor(Color::Red);
    }
    else if(key == Keyboard::Num3)
    {
        shape.setFillColor(Color::Blue);
    }
}

void mouseClicked(int x, int y)
{
    if(selectedTile == nullptr)
    {
        for(tile &t : tiles)
        {
            if(t.isSelected(x, y))
            {
                selectedTile = &t;
                t.shape.setOutlineColor(Color::Blue);
                break;
            }
        }
    }
    else
    {
        int newX = ((x/50)*50)+2, newY = ((y/50)*50)+2;
        int currX = selectedTile->getPosition().x ;
        int currY = selectedTile->getPosition().y;

        if(abs(newX - currX) == 50 && abs(newY - currY) == 50)
        {
            selectedTile->shape.setPosition(newX, newY);
        }
        else if(abs(newX - currX) == 100 && abs(newY - currY) == 100)
        {
            int diffX = (newX - currX)/2;
            int diffY = (newY - currY)/2;
            Vector2f mid(currX + diffX, currY+diffY);
            for(auto it = tiles.begin(); it!= tiles.end();it++)
            {
                if(it->getPosition() == mid)
                {
                    it = tiles.erase(it);
                    selectedTile->shape.setPosition(newX, newY);

                    break;
                }
            }
        }
        selectedTile->shape.setOutlineColor(Color::Black);
        selectedTile=nullptr;
    }
}