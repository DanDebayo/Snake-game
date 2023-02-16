#include <SFML/Graphics.hpp>

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

    // Create a square shape
    sf::RectangleShape square(sf::Vector2f(50, 50));
    square.setFillColor(sf::Color::Green);
    square.setPosition(400, 300);

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear screen
        window.clear();

        // Move the square
        square.move(1, 0);

        // Draw the square
        window.draw(square);

        // Update the window
        window.display();
    }

    return 0;
}
