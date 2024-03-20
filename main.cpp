// Sample program main.cpp
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
using namespace sf;
using namespace std;


struct tile
{
    CircleShape shape;
    bool isHighlighted = false;
    bool isPlayer1; // used to indicated if this is player 1.
    bool isKing = false;
    Texture crown;

    void setImage(string img)
    {
       crown.loadFromFile(img);

    }
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

    void draw(sf::RenderWindow &window)
    {
        window.draw(shape);

        if(isKing)
        {
            Sprite sp;
            sp.setPosition(shape.getPosition().x+13,shape.getPosition().y+13 );
            sp.setTexture(crown);
            window.draw(sp);
        }
        if(isHighlighted)
        {
            Color c(255,255,255, 150);
            CircleShape high(23);
            high.setPosition(shape.getPosition());
            high.setFillColor(c);
            window.draw(high);
        }

    }
};

void drawText(string txt, int x, int y, RenderWindow &window, int size = 18);
void keyPressed(Keyboard::Key, sf::CircleShape&);
void mouseClicked(int x, int y);
void setUpTiles();
void drawUsedTiles(sf::RenderWindow &window);
int gameOver();

tile *selectedTile = nullptr;
vector<tile> tiles;
bool player1 = true; // indicates if it is currently player 1's turn;
vector<tile> usedTiles;
Image img;
sf::Font font;

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 500), "SFML works!");
   // sf::CircleShape shape(25.f);
   // shape.setFillColor(sf::Color::Green);
  //  shape.setPosition(0,400);
    int dirY = 15, dirX = 6;
    vector<RectangleShape> background;

    setUpTiles();
    for(int r = 0; r < 8; r++)
    {
        for(int c = 0; c < 8; c++)
        {
            sf::RectangleShape shape(Vector2f(48,48));
            shape.setFillColor((r+c)%2==0?Color::Black:Color::White);
            shape.setPosition((c*50)+1,(r*50)+1);
            shape.setOutlineColor(Color::Black);
            shape.setOutlineThickness(1);
            background.push_back(shape);
        }
    }
    // set up the panel for used tiles.
    sf::RectangleShape rightPanel(Vector2f(200,400));
    rightPanel.setFillColor(Color::White);
    rightPanel.setPosition(400,0);
    rightPanel.setOutlineColor(Color::Black);
    rightPanel.setOutlineThickness(1);
    background.push_back(rightPanel);

    sf::RectangleShape bottomPanel(Vector2f(600,100));
    bottomPanel.setFillColor(Color::White);
    bottomPanel.setPosition(0,400);
    bottomPanel.setOutlineColor(Color::Black);
    bottomPanel.setOutlineThickness(1);
    background.push_back(bottomPanel);

    window.setFramerateLimit(40);

    if (!font.loadFromFile("arial.ttf"))
    {
        std::cout << "Error loading font"<<std::endl;
    }

    if(img.loadFromFile("crown.jpg"));
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
            }
        }

        window.clear();
        for(RectangleShape &s : background)
        {
            window.draw(s);
        }
        for(tile &s : tiles)
        {
            s.draw(window);
        }
        CircleShape shape(23.0f);

        shape.setFillColor(Color::Red);
        shape.setOutlineColor(Color::Black);
        shape.setOutlineThickness(2);
        shape.setPosition(10, 410);
        window.draw(shape);
        drawText("Player 1", 60, 424, window);

        CircleShape shape2(23);
        shape2.setFillColor(Color::Magenta);
        shape2.setOutlineColor(Color::Black);
        shape2.setOutlineThickness(2);
        shape2.setPosition(300, 410);
        window.draw(shape2);
        drawText("Player 2", 360, 424, window);

        sf::CircleShape square(10.f, 4);
        square.setFillColor(Color::Blue);
        if(player1)
        {
            square.setPosition(140, 426);
        }
        else
        {
            square.setPosition(440, 426);
        }
        window.draw(square);
        drawUsedTiles(window);

        if(gameOver()==1)
        {
            RectangleShape rectBG;
            rectBG.setSize(Vector2f(300, 100));
            rectBG.setPosition(50, 150);
            rectBG.setFillColor(Color::White);
            rectBG.setOutlineColor(Color(150,150,150));
            rectBG.setOutlineThickness(5);
            window.draw(rectBG);
            drawText("Game Over. Player 1 Wins.",60, 175, window, 21);
        }
        else if(gameOver()==2)
        {
            RectangleShape rectBG;
            rectBG.setSize(Vector2f(300, 100));
            rectBG.setPosition(50, 150);
            rectBG.setFillColor(Color::White);
            rectBG.setOutlineColor(Color(150,150,150));
            rectBG.setOutlineThickness(5);
            window.draw(rectBG);
            drawText("Game Over. Player 2 Wins.",60, 175, window, 21);
        }
        window.display();
    }

    return 0;
}

int gameOver()
{
    int count1=0, count2=0;
    for(tile t: tiles)
    {
        if(t.isPlayer1)
        {
            count1++;
        }
        else if(t.isPlayer1 == false)
        {
            count2++;
        }
    }
    if(count1 == 0)
        return 2;
    if(count2 == 0)
        return 1;
    return 0;
}

void drawText(string txt, int x, int y, RenderWindow &window, int size)
{
    sf::Text text;

// select the font
    text.setFont(font); // font is a sf::Font

// set the string to display
    text.setString(txt);

// set the character size
    text.setCharacterSize(size); // in pixels, not points!

// set the color
    text.setFillColor(sf::Color::Red);

// set the text style
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    text.setPosition(x, y);
// inside the main loop, between window.clear() and window.display()
    window.draw(text);
}
void setUpTiles() {
    int st = 0;
    for(int r = 7; r >= 0; r--)
    {
        if(r >=5 || r <=2) {
            for (int c = st; c <= 7; c += 2) {
                tile t;
                t.shape = CircleShape(23.0f);
                t.isPlayer1 = r <=2;
                t.shape.setFillColor(r <=2?Color::Red:Color::Magenta);
                t.shape.setOutlineColor(Color::Black);
                t.shape.setOutlineThickness(2);
                t.shape.setPosition((c * 50)+2, (r * 50)+2);
                t.setImage("crown.png");
                tiles.push_back(t);
            }
            st = st==0?1:0;
        }

    }
}

bool isTileOccupied(int x, int y)
{
    for(tile &t : tiles)
    {
        if(t.isSelected(x,y))
        {
            return true;
        }
    }
    return false;
}
void mouseClicked(int x, int y)
{
    if(selectedTile == nullptr)
    {
        for(tile &t : tiles)
        {
            if(t.isSelected(x, y) && player1 && t.isPlayer1)
            {
                selectedTile = &t;
                t.isHighlighted = true;
                t.shape.setOutlineColor(Color::Blue);
                break;
            }
            else if(t.isSelected(x, y) && !player1 && !t.isPlayer1)
            {
                selectedTile = &t;
                t.isHighlighted = true;
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

        if(abs(newX - currX) == 50
        && ((newY - currY == 50 && player1) ||(newY - currY == -50 && !player1)||(abs(newY - currY)==50 && selectedTile->isKing))
        && !isTileOccupied(newX, newY)) // one cell away in a diagonal direction
        {
            selectedTile->shape.setPosition(newX, newY);

            if(player1 && newY >= 350)
            {
                selectedTile->isKing = true;
            }
            if(!player1 && newY <= 10)
            {
                selectedTile->isKing = true;
            }
            player1 = !player1;
        }
        else if(abs(newX - currX) == 100 &&
        ( (newY - currY == 100 && player1) ||(newY - currY == -100 && !player1)|| (abs(newY - currY)==100 && selectedTile->isKing) )
        && !isTileOccupied(newX, newY)) // two cells away in a diaganol direction
        {
            int diffX = (newX - currX)/2;
            int diffY = (newY - currY)/2;
            Vector2f mid(currX + diffX, currY+diffY);
            // find the tile that was just jumped and remove it from the active tiles, placing it in the used tiles
            for(auto it = tiles.begin(); it!= tiles.end();it++)
            {
                if(it->getPosition() == mid && it->isPlayer1 != selectedTile->isPlayer1)
                {
                    if(player1 && newY >= 350)
                    {
                        selectedTile->isKing = true;
                    }
                    if(!player1 && newY <= 10)
                    {
                        selectedTile->isKing = true;
                    }
                    selectedTile->shape.setPosition(newX, newY);
                    selectedTile->isHighlighted = false;
                    player1 = !player1;
                    it->isHighlighted = false;
                    usedTiles.push_back(*it);
                    it = tiles.erase(it);
                    break;
                }
            }

        }
        selectedTile->shape.setOutlineColor(Color::Black);
        selectedTile->isHighlighted = false;
        selectedTile=nullptr;
    }
}

void drawUsedTiles(sf::RenderWindow &window)
{
    int countP1 = 0, countP2= 0;
    for(tile &t : usedTiles)
    {
        int x=400, y=0;
        if(t.isPlayer1) // player 1's tiles will be placed in columns 1 and 2
        {
            x= 400;
            y = countP1 * 50;
            if(countP1 > 8)
            {
                y =y%390;
                x+=50;
            }
            countP1++;
        }
        else // player 1's tiles will be placed in columns 3 and 4
        {
            x= 500;
            y = countP2 * 50;
            if(countP2 > 8)
            {
                y =y%390;
                x+=50;
            }
            countP2++;
        }
        t.shape.setPosition(x+2, y+2);
        t.draw(window);
    }
}