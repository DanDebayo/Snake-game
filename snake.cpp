  
#include <SFML/Graphics.hpp>
#include <deque>
#include <chrono>
#include <thread>
#include <sstream>
#include <iostream>
#include <array>

const int BLOCK_SIZE = 10;
const int WIDTH = 800;
const int HEIGHT = 600;
int SLEEP_DURATION = 100;


const char MAP_HEIGHT = 61;
const char MAP_WIDTH = 81;
const char CELL_SIZE = 31; 

enum class Cell
{
    Empty,
    Wall
};


std::array<std::array<Cell, MAP_WIDTH>, MAP_HEIGHT> convert_sketch(const std::array<std::string, MAP_HEIGHT>& i_map_sketch);
void draw_map(const std::array<std::array<Cell, MAP_WIDTH>, MAP_HEIGHT>& i_map, sf::RenderWindow& i_window);


int main(){

	int score = 0;
	bool game_paused = false;

std::array<std::string, MAP_HEIGHT> map_sketch = {
        "##########################",
        "#                        #",
        "# #         #######      #",
        "# #         #      #     #",
        "# #####     #   ######   #",
        "#     #     #        #   #",
        "#     #     # #####      #",
        "#     #     #     #      #",
        "#   #         #   #      #",
        "#      ####   #          #",
        "#  #      #   #   #      #",
        "#    ###  #   ### #      #",
        "#   #            ## # #  #",
        "#      # # # #           #",
        "#   #    #      # ###    #",
        "#     #  # # ####        #",
        "# #####   #   # # #####  #", 
        "#                        #", 
        "##########################"
    };
    std::array<std::array<Cell, MAP_WIDTH>, MAP_HEIGHT> map = convert_sketch(map_sketch);

    // create the window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Snake Game");
    window.setFramerateLimit(60);
  
     // create a rectangle shape to use as the menu background
    sf::RectangleShape menuBackground(sf::Vector2f(WIDTH, HEIGHT));
    menuBackground.setFillColor(sf::Color(100, 250, 50)); // set the background color to green
	 
   
    sf::Texture menutexture;
    menutexture.setSmooth(true);
    if (!menutexture.loadFromFile("image3.png")){
	    std::cout << "Failed to load texture"<< std::endl;
    }else{
   	menuBackground.setTexture(&menutexture);
	menuBackground.setTextureRect(sf::IntRect(10, 10, 100, 100));
             }
    

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

   
    // body of the snake
    std::deque<sf::RectangleShape> snake;
    sf::RectangleShape head(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
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
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        

	//Pausing the game
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P){
		game_paused = !game_paused;
	}

     }
	

	std::ostringstream str1;
	str1 << score;
	std::string score_text = str1.str();
    
    sf::Text Score(score_text, font, 20);
    Score.setFillColor(sf::Color::Red);
    Score.setOutlineColor(sf::Color(80, 37, 3));
    Score.setPosition(0 , 0);


	if(!game_paused){

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
          newHead.setPosition(snake.front().getPosition() + sf::Vector2f(direction * BLOCK_SIZE));
        snake.push_front(newHead);
     

      //Texture for the snake
	sf::Texture snaketexture;
    if (!snaketexture.loadFromFile("image2.png")){
	    std::cout << "Failed to load texture"<< std::endl;
    }else{
  	head.setTexture(&snaketexture);
        head.setTextureRect(sf::IntRect(10, 10, 100, 100));

	for(auto& block : snake){
		block.setTexture(&snaketexture);		
        block.setTextureRect(sf::IntRect(10, 10, 100, 100));
  	    }
    }
   


        //check if the snake has collided with itself
        for (auto it = std::next(snake.begin()); it != snake.end(); ++it) {
            if (snake.front().getGlobalBounds().intersects(it->getGlobalBounds())) {
                std::cout << "Game over" << std::endl;
                window.close();
                break;
            }
        }

      // check for collision with wall cells
	if (map[(int)newHead.getPosition().y / CELL_SIZE][(int)newHead.getPosition().x / CELL_SIZE] == Cell::Wall) {
		std::cout << "game over" << std::endl;
	    window.close();
            break;	    // collision detected with a wall cell, end the game or perform any other necessary action
	}

   
        //check if the snake has eaten the food
        if(snake.front().getGlobalBounds().intersects(food.getGlobalBounds())) {
	
            food.setPosition(rand() % (WIDTH / BLOCK_SIZE) * BLOCK_SIZE, rand() % (HEIGHT / BLOCK_SIZE) * BLOCK_SIZE);
	  score++; 

	}else{
		snake.pop_back();
	}

	//check if food land inside the walls
	if (map[(int)food.getPosition().y / CELL_SIZE][(int)food.getPosition().x / CELL_SIZE] == Cell::Wall){
            
		food.setPosition(rand() % (WIDTH / BLOCK_SIZE) * BLOCK_SIZE, rand() % (HEIGHT / BLOCK_SIZE) * BLOCK_SIZE);
	}
		



        // clear the window and draw the snake and food
        window.clear();
        window.draw(food);

	draw_map(map, window);
	window.draw(Score);

	
        for (auto& block : snake) {
            window.draw(block);
        }
        window.display();

	}else{
		sf::Text paused_text("Game Paused. Press P to resume." ,font, 40);
                paused_text.setOutlineColor(sf::Color(85, 200, 85));
		paused_text.setPosition((WIDTH - paused_text.getGlobalBounds().width)/2, 100);
		window.clear();
		window.draw(paused_text);
		window.display();
	}


        // pause for a short duration before moving the snake again
        std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DURATION));
    }

    return 0;
}

std::array<std::array<Cell, MAP_WIDTH>, MAP_HEIGHT> convert_sketch(const std::array<std::string, MAP_HEIGHT>& i_map_sketch)
{
    std::array<std::array<Cell, MAP_WIDTH>, MAP_HEIGHT> output_map{};

    for (unsigned char a = 0; a < MAP_HEIGHT; a++)
    {
        for (unsigned char b = 0; b < MAP_WIDTH; b++)
        {
            output_map[a][b] = Cell::Empty;

            switch (i_map_sketch[a][b])
            {
            case '#':
                {
                    output_map[a][b] = Cell::Wall;
                    break;
                }
            default:
                {
                    // Do nothing, since the default value is already Cell::Empty
                    break;
                }
            }
        }
    }

    return output_map;
}

void draw_map(const std::array<std::array<Cell, MAP_WIDTH>, MAP_HEIGHT>& i_map, sf::RenderWindow& i_window)
{
    sf::RectangleShape cell_shape(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    sf::Texture cell_tex;
    
   
     if (!cell_tex.loadFromFile("image3.png")){
	      
	    std::cout << "Failed to load file" << std::endl;
    }else{

                    cell_shape.setTexture(&cell_tex);
                   
    }
    
 
    for (unsigned char a = 0; a < MAP_HEIGHT; a++)
    {
        for (unsigned char b = 0; b < MAP_WIDTH; b++)
        {
           cell_shape.setPosition(b * CELL_SIZE, a * CELL_SIZE);
        

            switch (i_map[a][b])
            {
            case Cell::Wall:
                {
	       
		    i_window.draw(cell_shape);	

                    break;
                }
            default:
                {
                    // Do nothing, since the default value is already Cell::Empty
                    break;
                }
            }
        }
    }
}
