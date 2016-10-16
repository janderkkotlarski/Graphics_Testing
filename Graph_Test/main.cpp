#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <cmath>

#include <SFML/Graphics.hpp>

float modor(const sf::Vector2f& reimu)
{
    return sqrt(reimu.x*reimu.x + reimu.y*reimu.y);
}

class complex
{
    const sf::Vector2f n_init;

    sf::Vector2f n_reimu;

    float n_modu;

    void modulize()
    {
        n_modu = modor(n_reimu);
    }

    void reimure(const sf::Vector2f& reimu)
    {
        n_reimu = reimu;
        modulize();
    }

public:

    sf::Vector2f get_vect()
    {
        return n_reimu;
    }

    float get_abs()
    {
        return n_modu;
    }

    void recomp(const complex& comp)
    {
        complex temp{comp};

        reimure(temp.get_vect());
    }

    void adding(const complex& comp)
    {
        complex temp{comp};

        reimure(n_reimu + temp.get_vect());
    }

    void addinit()
    {
        reimure(n_reimu + n_init);
    }

    void multing(const complex& comp)
    {
        complex temp{comp};

        reimure(sf::Vector2f(get_vect().x*temp.get_vect().x - get_vect().y*temp.get_vect().y,
                            get_vect().x*temp.get_vect().y + get_vect().y*temp.get_vect().x));
    }

    complex(const sf::Vector2f& reimu)
        : n_init(reimu), n_reimu(reimu), n_modu(modor(n_reimu))
    {
    }

    ~complex()
    {
    }};

complex multer(const complex& comp_1, const complex& comp_2)
{
    complex comp_3{comp_1};

    complex comp_4{comp_2};

    comp_3.multing(comp_4);

    return comp_3;
}

void fractalize(complex& comp)
{
    comp.recomp(multer(comp, comp));
    comp.addinit();
}

void fractionize(sf::Vector2f& current, const sf::Vector2f& init)
{
    const sf::Vector2f temp{current.x*current.x - current.y*current.y + init.x,
                            2*current.x*current.y + init.y};

    current = temp;
}

float floater(const int inter)
{
    return static_cast<float>(inter);
}

int main()
{
    const float win_x{800.0f};
    const float win_y{800.0f};

    const int side{800};
    const float sidef{0.25f*floater(side)};

    const int size_x{2*side};
    const int size_y{2*side};

    const int rgba{4};
    const int total{size_x*size_y*rgba};

    const float pos_x{0.0f};
    const float pos_y{0.0f};

    const std::string name{"Graphics Test"};

    const sf::Color black{0, 0, 0};

    const int iters{10};

    const float thresh{2.0f};

    sf::Uint8* pixels = new sf::Uint8[total];

    for (int count_x{0}; count_x < size_x; ++count_x)
    {
        for (int count_y{0}; count_y < size_y; ++count_y)
        {
            const int count_c{count_x*count_y};

            int mandel{0};

            // complex comp(sf::Vector2f(floater(count_x - side)/sidef, floater(count_y - side)/sidef));

            const sf::Vector2f init{floater(count_x - side)/sidef, floater(count_y - side)/sidef};

            if (count_y == 0)
            {
                std::cout << init.x << " : " << init.y << "\n";
            }



            sf::Vector2f current{init};

            int iterations{0};

            while (iterations < 255 && false)
            {

                fractionize(current, init);

                ++iterations;

                if (modor(current) > 2.0f)
                {
                    mandel = iterations;
                    iterations = 255;
                }
            }

            pixels[count_c*rgba] = mandel;
            pixels[count_c*rgba + 1] = mandel;
            pixels[count_c*rgba + 2] = mandel;
            pixels[count_c*rgba + 3] = 255;
        }
    }

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

