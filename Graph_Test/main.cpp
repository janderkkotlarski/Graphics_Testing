#include <iostream>
#include <string>
#include <cassert>
#include <vector>

#include <SFML/Graphics.hpp>

float modor(const sf::Vector2f& reimu)
{
    return reimu.x*reimu.x + reimu.y*reimu.y;
}

class complex
{
    sf::Vector2f n_reimu;

    float n_modu;

    void modulize()
    {
        n_modu = modor(n_reimu);
    }

    void recomp(const sf::Vector2f& reimu)
    {
        n_reimu = reimu;
    }

public:

    sf::Vector2f get_vect()
    {
        return n_reimu;
    }

    void adding(const complex& comp)
    {
        complex temp{comp};

        n_reimu = n_reimu + temp.get_vect();
    }

    void subbing(const complex& comp)
    {
        complex temp{comp};

        n_reimu = n_reimu - temp.get_vect();
    }

    void multing(const complex& comp)
    {
        complex temp{comp};

        recomp(sf::Vector2f(get_vect().x*temp.get_vect().x - get_vect().y*temp.get_vect().y,
                            get_vect().x*temp.get_vect().y + get_vect().y*temp.get_vect().x));
    }

    complex(const sf::Vector2f& reimu)
        : n_reimu(reimu), n_modu(modor(n_reimu))
    {
    }

    ~complex()
    {
    }

};

complex adder(const complex& comp_1, const complex& comp_2)
{
    complex comp_3{comp_1};

    complex comp_4{comp_2};

    comp_3.adding(comp_4);

    return comp_3;
}

complex subber(const complex& comp_1, const complex& comp_2)
{
    complex comp_3{comp_1};

    complex comp_4{comp_2};

    comp_3.subbing(comp_4);

    return comp_3;
}

complex multer(const complex& comp_1, const complex& comp_2)
{
    complex comp_3{comp_1};

    complex comp_4{comp_2};

    comp_3.multing(comp_4);

    return comp_3;
}

int main()
{
    const float win_x{300.0f};
    const float win_y{300.0f};

    const int size_x{100};
    const int size_y{100};

    const int poz_x{25};
    const int poz_y{40};

    const int rgba{4};
    const int total{size_x*size_y*rgba};

    const float pos_x{100.0f};
    const float pos_y{100.0f};

    const std::string name{"Graphics Test"};

    const sf::Color black{0, 0, 0};

    sf::Uint8* pixels = new sf::Uint8[total];

    for (int count{0}; count < size_x*size_y; ++count)
    {
        pixels[count*rgba] = 127;
        pixels[count*rgba + 1] = 127;
        pixels[count*rgba + 2] = 127;
        pixels[count*rgba + 3] = 255;
    }


    pixels[0] = 0;
    pixels[1] = 255;
    pixels[2] = 255;
    pixels[3] = 255;

    sf::Texture texel;

    if (!texel.create(size_x, size_y))
    {
        std::cerr << "Texture creation failed!\n";
        return 1;
    }

    texel.update(pixels);

    sf::Sprite cirno;

    cirno.setTexture(texel);

    cirno.setPosition(pos_x, pos_y);

    sf::RenderWindow window(sf::VideoMode(win_x, win_y), name, sf::Style::Default);

    while(window.isOpen())
    {
        sf::Event event;

        window.clear(black);

        window.draw(cirno);

        window.display();

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
        }
    }

    std::cout << "It worked!\n";

    return 0;
}

