#include <SFML/Graphics.hpp>
#include <deque>
#include <chrono>
#include <thread>

const int BLOCK_SIZE = 10;
const int WIDTH = 1000;
const int HEIGHT = 800;
int SLEEP_DURATION = 100;

int main()
{	
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Snake Game");// Window for the game
    window.setFramerateLimit(60);

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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && direction != sf::Vector2i(0, 1)){
            direction = sf::Vector2i(0, -1);}
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && direction != sf::Vector2i(0, -1)){
            direction = sf::Vector2i(0, 1);}
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && direction != sf::Vector2i(1, 0))
    	    direction = sf::Vector2i(-1, 0);        
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && direction != sf:: Vector2i(-1,0))
	    direction = sf::Vector2i(1, 0);

        for (int i = snake.size() -1; i > 0; i--){
		snake[i].setPosition(snake[i - 1].getPosition());
	}

        snake.front().move(direction.x * BLOCK_SIZE, direction.y * BLOCK_SIZE);

	//controls the speed of the snake with sleep duration
	std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DURATION));

	// increase the size of the snake
        if (snake.front().getGlobalBounds().intersects(food.getGlobalBounds()))
        {
            food.setPosition(rand() % (WIDTH - BLOCK_SIZE), rand() % (HEIGHT - BLOCK_SIZE));
            sf::RectangleShape tail(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
            tail.setFillColor(sf::Color::Green);
            tail.setPosition(snake.back().getPosition());
            snake.push_back(tail);
//	    SLEEP_DURATION -=20;
        }
	//close the window when the snake hits the borders of the window
	if (snake.front().getPosition().x < 0 || snake.front().getPosition().x >= WIDTH ||
	    snake.front().getPosition().y < 0 || snake.front().getPosition().y >= HEIGHT){
	       window.close();
		main();
	}
	//closes the window
	 window.clear();
        for (auto block : snake)
            window.draw(block);
        window.draw(food);
        window.display();
    }

    return 0;
}
