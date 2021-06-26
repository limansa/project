#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

ostream& operator<<(ostream& os, const sf::Vector2f& vec) {
    os << "(" << vec.x << "," << vec.y << ")";
    return os;
}

int main()
{
    sf::Font font;
    if (font.loadFromFile("arial.ttf") == false)
        return EXIT_FAILURE;
    sf::Text word("Hello", font);
    sf::Text word2("Hello", font);
    sf::RenderWindow w(sf::VideoMode(400, 200), "Hello");
    sf::Event evt;
    
    while(w.isOpen()) {
        if (w.pollEvent(evt)) {
            switch(evt.type) {
                case sf::Event::Closed:
                    w.close();
                    break;
                default:
                    break;
            }
        }

        w.clear();

        int text_length = 70;
        float x = word.getPosition().x;
        if (x > 400-text_length && x < 400.01 - text_length) {
            cout << "**********************" << endl;
            word2.setPosition(-text_length, -10);
        } else if (x > 400-text_length && x < 400) {
            word2.move(0.02, 0.01);
            w.draw(word2);
        } else if (x > 400) {
            word.setPosition(0, 0);
        }

        word.move(0.02, 0.01);
        word.setOutlineThickness(0.1);
        w.draw(word);
        w.display();

//        cout << "w1" << word.getPosition() << " w2" <<word2.getPosition() << endl;
    }

    return EXIT_SUCCESS;
}

