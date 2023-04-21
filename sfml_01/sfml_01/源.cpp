#include "SFML\Graphics.hpp"
#include <vector>
#include"Enermy.h"
#include "Hero.h"
#include "Rocket.h"
#include<iostream>
using namespace std;

sf::Vector2f viewSize(1024, 768);
sf::VideoMode vm(viewSize.x, viewSize.y);
sf::RenderWindow window(vm, "Hello SFML Game !!!", sf::Style::Default);

void spawnEnemy();
void shoot();
bool checkCollision(sf::Sprite sprite1, sf::Sprite sprite2);
void reset();
sf::Vector2f playerPosition;
bool playerMoving = false;

sf::Texture skyTexture;
sf::Sprite skySprite;

sf::Texture bgTexture;
sf::Sprite bgSprite;

Hero hero;

std::vector<Enermy*> enemies;
std::vector<Rocket*> rockets;

float currentTime;
float prevTime = 0.0f;

int score = 0;
bool gameover = true;

// Text 
sf::Font headingFont;
sf::Text headingText;

sf::Font scoreFont;
sf::Text scoreText;
void init() {


	skyTexture.loadFromFile("data/back.jfif");
	skySprite.setTexture(skyTexture);

	bgTexture.loadFromFile("data/rocket.png");
	bgSprite.setTexture(bgTexture);

	hero.init("data/enemy.png", sf::Vector2f(viewSize.x * 0.25f, viewSize.y * 0.5f), 200);
	// Create Sprite and Attach a Texture 
	bgSprite.setTexture(bgTexture); 
	// Load font 
	cout<<headingFont.loadFromFile("data/l.ttf")<<endl;
	cout<<scoreFont.loadFromFile("data/l.ttf");

	// Set Heading Text 
	headingText.setFont(headingFont);
	headingText.setString("game over"); 
	headingText.setCharacterSize(84);
	headingText.setFillColor(sf::Color::Red);
	sf::FloatRect headingbounds = headingText.getLocalBounds(); 
	headingText.setOrigin(headingbounds.width / 2, headingbounds.height / 2); 
	headingText.setPosition(sf::Vector2f(viewSize.x * 0.5f, viewSize.y * 0.10f));
	// Set Score Text 
	scoreText.setFont(scoreFont);
	scoreText.setString("score: 0");
	scoreText.setCharacterSize(45); 
	scoreText.setFillColor(sf::Color::Red); 
	sf::FloatRect scorebounds = scoreText.getLocalBounds(); 
	scoreText.setOrigin(scorebounds.width / 2, scorebounds.height / 2); 
	scoreText.setPosition(sf::Vector2f(viewSize.x * 0.5f, viewSize.y * 0.10f));
	srand((int)time(0));

}


void updateInput() {

	sf::Event event;

	// while there are pending events...
	while (window.pollEvent(event)) {

		if (event.type == sf::Event::KeyPressed) {

			if (event.key.code == sf::Keyboard::Up) {


				hero.jump(750.0f);
			}

			if (event.key.code == sf::Keyboard::Down) {

				shoot();
			}
			if (event.key.code == sf::Keyboard::Enter) { 
				if (gameover) { gameover = false; reset(); } 
				else { shoot(); } 
			}

		}
		
		if (event.key.code == sf::Keyboard::Escape || event.type == sf::Event::Closed)
			window.close();
	}

}


void update(float dt) {

	hero.update(dt);

	currentTime += dt;

	// Spawn Enemies

	if (currentTime >= (prevTime + 1.125f)) {

		spawnEnemy();

		prevTime = currentTime;

	}

	// Update Enemies

	for (int i = 0; i < enemies.size(); i++) {

		Enermy* enemy = enemies[i]; enemy->update(dt);

		if (enemy->getSprite().getPosition().x < 0) {

			enemies.erase(enemies.begin() + i);

			delete(enemy);

			gameover = true;
		}
	}



	// Update rockets

	for (int i = 0; i < rockets.size(); i++) {

		Rocket* rocket = rockets[i];

		rocket->update(dt);

		if (rocket->getSprite().getPosition().x > viewSize.x) {

			rockets.erase(rockets.begin() + i);
			delete(rocket);

		}

	}

	// Check collision between Rocket and Enemies

	for (int i = 0; i < rockets.size(); i++) {
		for (int j = 0; j < enemies.size(); j++) {

			Rocket* rocket = rockets[i];
			Enermy* enemy = enemies[j];

			if (checkCollision(rocket->getSprite(), enemy->getSprite())) {


				rockets.erase(rockets.begin() + i);
				enemies.erase(enemies.begin() + j);

				delete(rocket);
				delete(enemy);

				printf(" rocket intersects enemy \n");
			}

		}
	}
	score++; std::string finalScore = "Score: " + std::to_string(score); 
	scoreText.setString(finalScore); 
	sf::FloatRect scorebounds = scoreText.getLocalBounds(); 
	scoreText.setOrigin(scorebounds.width / 2, scorebounds.height / 2); 
	scoreText.setPosition(sf::Vector2f(viewSize.x * 0.5f, viewSize.y * 0.10f));

}

void draw() {

	window.draw(skySprite);
	window.draw(bgSprite);

	window.draw(hero.getSprite());

	for (Enermy* enemy : enemies) {

		window.draw(enemy->getSprite());
	}

	for (Rocket* rocket : rockets) {

		window.draw(rocket->getSprite());
	}
	if (gameover) { window.draw(headingText); }
	else { window.draw(scoreText); }


}



int main() {

	sf::Clock clock;
	window.setFramerateLimit(60);

	init();

	while (window.isOpen()) {

		updateInput();

		sf::Time dt = clock.restart();
		if (!gameover)update(dt.asSeconds());


		window.clear(sf::Color::Red);

		draw();

		window.display();

	}

	return 0;
}


void spawnEnemy() {


	//printf("spawnEnemy \n");

	int randLoc = rand() % 3;

	sf::Vector2f enemyPos;

	float speed;

	switch (randLoc) {
	case 0: enemyPos = sf::Vector2f(viewSize.x, viewSize.y * 0.75f); speed = -400; break;
	case 1: enemyPos = sf::Vector2f(viewSize.x, viewSize.y * 0.60f); speed = -550; break;
	case 2: enemyPos = sf::Vector2f(viewSize.x, viewSize.y * 0.40f); speed = -650; break;
	default: printf("incorrect y value \n"); break;
	}

	Enermy* enemy = new Enermy();
	enemy->init("data/hero.png", enemyPos, speed);
	enemies.push_back(enemy);
}

void shoot() {

	Rocket* rocket = new Rocket();

	rocket->init("data/rocket.png", hero.getSprite().getPosition(), 400.0f);

	rockets.push_back(rocket);

}


bool checkCollision(sf::Sprite sprite1, sf::Sprite sprite2) {

	sf::FloatRect shape1 = sprite1.getGlobalBounds();
	sf::FloatRect shape2 = sprite2.getGlobalBounds();

	if (shape1.intersects(shape2)) {

		return true;

	}
	else {

		return false;

	}

}
void reset() 
{ score = 0; currentTime = 0.0f; prevTime = 0.0; 
for (Enermy* enemy : enemies) { delete(enemy); }
for (Rocket* rocket : rockets) { delete(rocket); }
enemies.clear(); rockets.clear(); 
prevTime = 0.0; scoreText.setString("Score: 0");
}