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
    menuBackground.setFillColor(sf::Color(100, 250, 50)); // set the background color to green
    

    // create a font and text for the menu title
    sf::Font font;
    if (!font.loadFromFile("Tron.ttf"))
    {
        std::cout << "Error loading font" << std::endl;
    }

    sf::Text title("Snake Game", font, 80);
    title.setFillColor(sf::Color::Red);
    title.setOutlineThickness(10.f);
    title.setOutlineColor(sf::Color(80, 37, 4));
    title.setPosition((WIDTH - title.getGlobalBounds().width) / 2, 100);

    // create a font and text for the play button
    sf::Text playButton("Play", font, 50);
    playButton.setFillColor(sf::Color::Red);
    playButton.setOutlineThickness(10.f);
    playButton.setOutlineColor(sf::Color(80, 37, 3));
    playButton.setPosition((WIDTH - playButton.getGlobalBounds().width) / 2, 300);

   //create a font and text for the exit button 
    sf::Text exitButton("Exit", font, 50);
    exitButton.setFillColor(sf::Color::Red);
    exitButton.setOutlineThickness(10.f);
    exitButton.setOutlineColor(sf::Color(80, 37, 8));
    exitButton.setPosition((WIDTH - exitButton.getGlobalBounds().width) / 2, 500) ;

    bool startgame =false;

    // loop to handle events and draw the menu
    while (window.isOpen() && !startgame)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                // check if the play button was clicked
                if (playButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                {
                    startgame = true; // exit the menu loop and start the game
			break;

              }else if (exitButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                {
                   window.close(); // exit the menu loop and exit the game      
              } 
            }
        }

        // clear the window and draw the menu
        window.clear();
        window.draw(menuBackground); // draw the menu background first
        window.draw(title);
        window.draw(playButton);
	window.draw(exitButton);
        window.display();
    }

    //create a rectangle wall
    sf::RectangleShape wallTop(sf::Vector2f(WIDTH, HEIGHT));
    wallTop.setSize(sf::Vector2f(WIDTH, 10.f));
    wallTop.setFillColor(sf::Color::Blue);
    wallTop.setPosition(0, 0);
    
    sf::RectangleShape wallBottom(sf::Vector2f(WIDTH, HEIGHT));
    wallBottom.setSize(sf::Vector2f(WIDTH, 10.f));
    wallBottom.setFillColor(sf::Color::Blue);
    wallBottom.setPosition(0, 790);
    
    sf::RectangleShape wallLeft(sf::Vector2f(WIDTH, HEIGHT));
    wallLeft.setSize(sf::Vector2f(10.f, HEIGHT));
    wallLeft.setFillColor(sf::Color::Blue);
    wallLeft.setPosition(0, 0);

    sf::RectangleShape wallRight(sf::Vector2f(WIDTH, HEIGHT));
    wallRight.setSize(sf::Vector2f(10.f, HEIGHT));
    wallRight.setFillColor(sf::Color::Blue);
    wallRight.setPosition(990, 0);


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

        if (snake.front().getGlobalBounds().intersects(wallTop.getGlobalBounds()) || snake.front().getGlobalBounds().intersects(wallBottom.getGlobalBounds()) || 
	    snake.front().getGlobalBounds().intersects(wallLeft.getGlobalBounds()) || snake.front().getGlobalBounds().intersects(wallRight.getGlobalBounds())){
                   std::cout << "Game Over" << std::endl;
		   window.close();
		   break;
           	}
                   

        // clear the window and draw the snake and food
        window.clear();
	window.draw(wallRight);
	window.draw(wallBottom);
	window.draw(wallLeft);
	window.draw(wallTop);
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
