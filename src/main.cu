#include <iostream>
#include <SFML/Graphics.hpp>
#include "lga.h"
#include "experiments.h"

// Config
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 1000;
const int GRID_SIZE = 250;// NxN 

sf::RenderWindow WINDOW;
sf::Clock _clock;

void drawObstacle(float x, float y, sf::RenderWindow* window) {
		sf::RectangleShape obstacle;
		obstacle.setSize( sf::Vector2f(10, 10) );
		obstacle.setFillColor(sf::Color::Red);
		obstacle.setPosition(x, y);
		window->draw(obstacle);
}


void drawParticle(float x, float y, sf::RenderWindow* _window) {	
		sf::CircleShape particle(4, 4);
		sf::Color color(255, 255, 255, 100);
		particle.setFillColor(color);
		particle.setPosition(x, y);
		_window->draw(particle);
}


void drawGrid(sf::RenderWindow* _window, int* grid, int size_x, int size_y) {
		for (int cell = 0; cell < size_x*size_y*4; cell++) {
			int x = (cell/4) % size_x;
			int y = (cell/4) / size_x;
			float real_x = ( (float) SCREEN_WIDTH/ size_x)*(x + 1);
			float real_y = ( (float) SCREEN_WIDTH/ size_y)*(y + 1);
			if (grid[cell] > 0) {
				drawParticle(real_x, real_y, _window);
			}
            if(grid[cell] == -1){
                drawObstacle(real_x, real_y, _window);
            }
			
		}
}


void StartSimulation() {
    // Initialize grid
    int size_x = GRID_SIZE;
    int size_y = GRID_SIZE;
    int* r_grid = (int*) malloc( sizeof(int)*size_x*size_y*4  );// return grid
    for (int i = 0; i < size_x*size_y*4; i++){
        r_grid[i] = 0;
    }

    // Generate experiment
    experiment_2(r_grid, size_x);

    while (WINDOW.isOpen()) {
        WINDOW.clear( sf::Color(0, 0, 0) );
        sf::Event event;
        while (WINDOW.pollEvent(event)) {
            if (event.type == sf::Event::Closed) { WINDOW.close(); }
        }
        drawGrid(&WINDOW, r_grid, size_x, size_y);
        nextStep(r_grid, size_x, size_y);
        WINDOW.display();
    }
}


int main(){
    printf("Running... \n");

    WINDOW.create( sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "pene" );
    WINDOW.setFramerateLimit(60);

    StartSimulation();

    printf(" Finish ...");
    return 0;
}