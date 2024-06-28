#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include<fstream>


void checkCollision(float px, float py, float ow, float oh, float ww, float wh, float& vx, float& vy) {

    //upper boundary collision
    if (py <= 0) {
        vy *= -1;
    }
    //left bounday collision
    if (px <= 0) {
        vx *= -1;
    }
    //right bounday collision
    if (px + ow >= ww) {
        vx *= -1;
    }
    //down boundary collision
    if (py + oh >= wh) {
        vy *= -1;
    }

}


int main()
{



    float window_height;
    float window_weidth;

    std::vector<sf::Text> recName;
    std::vector<sf::RectangleShape> rectangle;
    std::vector<sf::Vector2f> recVelocity;

    std::vector< sf::Text> cirName;
    std::vector<sf::CircleShape> circle;
    std::vector<sf::Vector2f> cirVelocity;

    //loading data 
    std::ifstream file("command/command.txt");
    if (!file.is_open()) {
        std::cout << "failed to opent the command file \n";
        return 0;
    }

    sf::Font myFont;
    if (!myFont.loadFromFile("font/arial.ttf"))
    {
        std::cout << "error while loading font \n";
    }

    sf::Text sampleText;
    sampleText.setFont(myFont);
    sampleText.setCharacterSize(24);

    std::string input;
    while (file >> input) {


        if (input == "Window") {
            file >> window_height;
            file >> window_weidth;
        }
        if (input == "Rectangle") {
            std::string Name;
            file >> Name;

            float px, py, vx, vy, r, g, b, ww, wh;
            file >> px >> py >> vx >> vy >> r >> g >> b >> ww >> wh;
            sf::RectangleShape recTemp(sf::Vector2f(ww, wh));
            recTemp.setPosition(px, py);
            recTemp.setFillColor(sf::Color(r, g, b));
            rectangle.push_back(recTemp);

            recVelocity.push_back(sf::Vector2f(vx, vy));

            sampleText.setString(Name);
            sampleText.setPosition((px + (ww / (float)2) - (float)sampleText.getLocalBounds().width / 2),
                (py + (wh / (float)2) - (float)12));
            recName.push_back(sampleText);

        }
        if (input == "Circle") {

            std::string Name;
            file >> Name;

            float px, py, vx, vy, r, g, b, radius;
            file >> px >> py >> vx >> vy >> r >> g >> b >> radius;
            sf::CircleShape  cirTemp(radius);
            cirTemp.setPosition(px, py);
            cirTemp.setFillColor(sf::Color(r, g, b));
            circle.push_back(cirTemp);

            cirVelocity.push_back(sf::Vector2f(vx, vy));

            sampleText.setString(Name);
            sampleText.setPosition((px + radius - ((float)sampleText.getLocalBounds().width / 2)),
                (py + radius - float(12)));
            cirName.push_back(sampleText);

        }

    }



    sf::RenderWindow window(sf::VideoMode(window_weidth, window_height), "Bouncing Shape");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        for (int i = 0; i < (int)rectangle.size(); i++) {

            //change pos of shape
            float px = rectangle[i].getPosition().x;
            float py = rectangle[i].getPosition().y;

            float new_px = px + recVelocity[i].x;
            float new_py = py + recVelocity[i].y;

            rectangle[i].setPosition(new_px, new_py);

            //change pos of name 
            recName[i].setPosition((new_px + (rectangle[i].getSize().x / (float)2) - ((float)recName[i].getLocalBounds().width / 2)),
                (new_py + (rectangle[i].getSize().y / (float)2) - (float)12));

            checkCollision(
                new_px, new_py,
                rectangle[i].getSize().x, rectangle[i].getSize().y,
                window_weidth, window_height,
                recVelocity[i].x, recVelocity[i].y
            );

        }
        for (int i = 0; i < (int)circle.size(); i++) {

            //change pos of shape
            float px = circle[i].getPosition().x;
            float py = circle[i].getPosition().y;

            float new_px = px + cirVelocity[i].x;
            float new_py = py + cirVelocity[i].y;

            circle[i].setPosition(new_px, new_py);

            //change pos of name 
            cirName[i].setPosition((new_px + (circle[i].getRadius()) - ((float)cirName[i].getLocalBounds().width / 2)),
                (new_py + (circle[i].getRadius()) - (float)12));

            checkCollision(
                new_px, new_py,
                2 * circle[i].getRadius(), 2 * circle[i].getRadius(),
                window_weidth, window_height,
                cirVelocity[i].x, cirVelocity[i].y
            );

        }

        //std::cout << rec[0].getPosition().x  " " << rec[0].getPosition().y << "\n";

        window.clear();
        for (auto& rec : rectangle) window.draw(rec);
        for (auto& rText : recName) window.draw(rText);
        for (auto& rec : circle) window.draw(rec);
        for (auto& rText : cirName) window.draw(rText);
        window.display();
    }

    return 0;
}