#include <iostream>
#include "Map.h"
#include "AquaMonstera.h"
#include "Inventory.h"
#include "Gacha.h"
#include "Message.h"
#include "Game.h"
#include <SFML/Graphics.hpp>
#include <fstream>
using namespace std;

// A button class to create button for the game screen
class Button {
public:
    // Constructor
    Button(float x, float y, float width, float height, const std::string& text)
        : rect(sf::Vector2f(width, height)), normalColor(sf::Color::Black), hoverColor(sf::Color::White), isHovered(false), buttonText() {
        rect.setPosition(x, y);
        rect.setFillColor(sf::Color::Transparent);

        buttonText.setFont(font);
        buttonText.setString(text);  

        buttonText.setCharacterSize(48);
        buttonText.setFillColor(sf::Color::Black);

        // Center the text inside the button
        sf::FloatRect textBounds = buttonText.getLocalBounds();
        buttonText.setOrigin(textBounds.left + textBounds.width / 2.0f,
            textBounds.top + textBounds.height / 2.0f);
        buttonText.setPosition(x + 100.0f, y + height / 2.0f);

        if (!font.loadFromFile("AncientModernTales.ttf"))
        {
            std::cerr << "Failed to load font." << std::endl;
        }
    }

    // Draw button function
    void draw(sf::RenderWindow& window) const {
        window.draw(rect);
        window.draw(buttonText);
    }

    // Check if mouse position is over the button
    bool isMouseOver(const sf::RenderWindow& window) const {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        return rect.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
    }

    // Gray out the button
    void setGrayedOut(bool grayedOut) {
        if (grayedOut) {
            buttonText.setFillColor(sf::Color(128, 128, 128)); // Grey color
        }
    }

    // Update mouse position to check hover
    void update(sf::Vector2f mousePos) {
        // Check if the mouse is over the button
        isHovered = rect.getGlobalBounds().contains(mousePos);

        // Update the color based on the hover state
        buttonText.setFillColor(isHovered ? hoverColor : normalColor);
    }

    // Check if mouse is over the button
    bool isMouseOver() const {
        return isHovered;
    }

private:
    sf::RectangleShape rect;
    sf::Text buttonText;
    sf::Font font;  
    sf::Color normalColor;
    sf::Color hoverColor;
    bool isHovered;
};

// Draw the title of game on screen
void drawTitle(float x, float y, float width, float height, sf::RenderWindow& window)
{
    sf::Text title;
    sf::Font font;
    string text = "Monstera";
    if (!font.loadFromFile("AncientModernTales.ttf"))
    {
        std::cerr << "Failed to load font." << std::endl;
    }
    title.setFont(font);
    title.setString(text);

    title.setCharacterSize(128);
    title.setFillColor(sf::Color::White);
    title.setPosition(width / 2.0f - 200.0f, 100.0f);
    window.draw(title);
}

// Function to check if a game file exists
bool doesGameFileExist() {
    std::ifstream file("save_data.txt");
    return file.good();
}

int main()
{
    // Create random seed value using time
    srand(static_cast<unsigned>(std::time(nullptr))); 

    // Load the background image
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("background.jpg")) {
        std::cerr << "Failed to load background image." << std::endl;
        return 1;
    }
    sf::Sprite backgroundImage(backgroundTexture);

    // Create a window
    sf::RenderWindow window(sf::VideoMode(1080, 720), "Monstera");

    // Adjust the scale of the background image
    float scaleX = static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x;
    float scaleY = static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y;
    backgroundImage.setScale(scaleX, scaleY);

    // Create three buttons
    Button continueButton(0, window.getSize().y - 240.0f, window.getSize().x, 50.0f, "Continue");
    Button newGameButton(0, window.getSize().y - 160.0f, window.getSize().x, 50.0f, "New Game");
    Button exitGameButton(0, window.getSize().y - 80.0f, window.getSize().x, 50.0f, "Exit");
    
    // Get game instance
    Game* game = game->getInstance();

    // Render Window
    while (window.isOpen() && game->getGameRunning() == true)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // If save file exist, click button to continue game
                    if (continueButton.isMouseOver(window)) {
                        if (doesGameFileExist()) {
                            game->LoadGame("save_data.txt");
                            game->StartGame();
                        }
                    }
                    // Creates a new game instance
                    else if (newGameButton.isMouseOver(window)) {
                        // Create new game
                        game->getInstance();
                        game->StartGame();
                    }
                    // Save game and exit game
                    else if (exitGameButton.isMouseOver(window)) {
                        game->SaveGame("save_data.txt");
                        std::cout << "Exiting..." << std::endl;
                        event.type = sf::Event::Closed;
                        window.close();
                        return 0;
                    }
                }
            }
        }

        //// Update button state based on mouse position
        sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
        continueButton.update(mousePos);
        newGameButton.update(mousePos);
        exitGameButton.update(mousePos);

        // Check if the game file exists and update the "Continue" button accordingly
        continueButton.setGrayedOut(!doesGameFileExist());

        // Clear window
        window.clear();

        // Draw the buttons
        window.draw(backgroundImage);
        continueButton.draw(window);
        newGameButton.draw(window);
        exitGameButton.draw(window);

        // Draw title
        drawTitle(0, 0, window.getSize().x, window.getSize().y, window);

        // Display content on window
        window.display();
    }

    return 0;
}