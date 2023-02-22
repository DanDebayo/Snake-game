#include <SFML/Graphics.hpp>
#include <deque>
#include <chrono>
#include <thread>
#include <iostream>

const int BLOCK_SIZE = 10;
const int WIDTH = 1000;
const int HEIGHT = 800;
int SLEEP_DURATION = 100;

int main(){

    // create the window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Snake Game");

    // create a rectangle shape to use as the menu background
    sf::RectangleShape menuBackground(sf::Vector2f(WIDTH, HEIGHT));
    menuBackground.setFillColor(sf::Color(0, 128, 0)); // set the background color to green

    // create a font and text for the menu title
    sf::Font font;
    if (!font.loadFromFile("Tron.ttf"))
    {
        std::cout << "Error loading font" << std::endl;
    }

    sf::Text title("Snake Game", font, 80);
    title.setFillColor(sf::Color::Blue);
    title.setPosition((WIDTH - title.getGlobalBounds().width) / 2, 100);

    // create a font and text for the play button
    sf::Text playButton("Play", font, 50);
    playButton.setFillColor(sf::Color::Blue);
    playButton.setPosition((WIDTH - playButton.getGlobalBounds().width) / 2, 300);

   //create a font and text for the exit button 
    sf::Text exitButton("Exit", font, 50);
    exitButton.setFillColor(sf::Color::Red);
    exitButton.setPosition((WIDTH - exitButton.getGlobalBounds().width) / 2, 500);

    bool startgame =false;

    // loop to handle events and draw the menu
    while (window.isOpen() && !startgame)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || exitButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                // check if the play button was clicked
                if (playButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                {
                    startgame = true; // exit the menu loop and start the game
			break;	       
              } 
            }
        }

        // clear the window and draw the menu
        window.clear();
        window.draw(menuBackground); // draw the menu background first
        window.draw(title);
        window.draw(playButton);
        window.display();
    }


    // body of the snake
    std::deque<sf::RectangleShape> snake;
    sf::RectangleShape head(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
    head.setFillColor(sf::Color::Green);
    head.setPosition(WIDTH / 3, HEIGHT / 3);
    snake.push_back(head);

    //creating the food
    sf::RectangleShape food(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
    food.setFillColor(sf::Color::Red);
    food.setPosition(WIDTH / 2, HEIGHT / 2);

    sf::Vector2i direction(0, 1);

    //when the window opens, start the game
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
	{
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //controls for the snake
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && direction != sf::Vector2i(0, 1)) {
            direction = sf::Vector2i(0, -1);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && direction != sf::Vector2i(0, -1)) {
            direction = sf::Vector2i(0, 1);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && direction != sf::Vector2i(1, 0)) {
            direction = sf::Vector2i(-1, 0);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && direction != sf::Vector2i(-1, 0)) {
            direction = sf::Vector2i(1, 0);
        }



        //move the snake
        sf::RectangleShape newHead(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
        newHead.setFillColor(sf::Color::Green);
        newHead.setPosition(snake.front().getPosition() + sf::Vector2f(direction * BLOCK_SIZE));
        snake.push_front(newHead);

        //check if the snake has collided with itself
        for (auto it = std::next(snake.begin()); it != snake.end(); ++it) {
            if (snake.front().getGlobalBounds().intersects(it->getGlobalBounds())) {
                std::cout << "Game over" << std::endl;
                window.close();
                break;
            }
        }

        //check if the snake has eaten the food
        if (snake.front().getGlobalBounds().intersects(food.getGlobalBounds())) {
            food.setPosition(rand() % (WIDTH / BLOCK_SIZE) * BLOCK_SIZE, rand() % (HEIGHT / BLOCK_SIZE) * BLOCK_SIZE);
        } else {
            snake.pop_back();
        }

	if (snake.front().getPosition().x < 0 || snake.front().getPosition().x >= WIDTH ||
    	    snake.front().getPosition().y < 0 || snake.front().getPosition().y >= HEIGHT){
                   std::cout << "Game Over" << std::endl;
		   window.close();
		   break;
	}

        // clear the window and draw the snake and food
        window.clear();
        window.draw(food);
        for (auto& block : snake) {
            window.draw(block);
        }
        window.display();

        // pause for a short duration before moving the snake again
        std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DURATION));
    }

    return 0;
}
