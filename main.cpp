#include <SFML/Graphics.hpp>
using namespace sf;
#pragma once
#include <SFML/Graphics.hpp>

const float WINDOW_WIDTH = 800;
const float WINDOW_HEIGHT = 600;
const std::string WINDOW_TITLE = "SFML Lesson2";
const float FPS = 60.f;

const float batWidth = 20.f;
const float batHeight = 80.f;
const float batOffset = 50.f;
const sf::Vector2f batSize(20.f, 80.f);
const sf::Color leftBatColor{ 158,20,37 };
const sf::Color rightBatColor{ 20,158,49 };
const float batspeed = 5.f;

const float ballRadius = 25.f;
const sf::Color ballColor{ sf::Color::Yellow };
int main()
{
	// Объект, который, собственно, является главным окном приложения
	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
	window.setFramerateLimit(FPS);
	//создание объектов игры
	//ракетки
	RectangleShape leftBat, rightBat;
	leftBat.setSize(batSize);
	rightBat.setSize(batSize);
	leftBat.setFillColor(leftBatColor);
	rightBat.setFillColor(rightBatColor);
	leftBat.setPosition(batOffset, (WINDOW_HEIGHT - batHeight) / 2);
	rightBat.setPosition(WINDOW_WIDTH - batOffset, (WINDOW_HEIGHT - batHeight) / 2);
	float leftbatspeedy = 0.f;
	float rightbatspeedy = 0.f;

	//шарик
	CircleShape ball(ballRadius);
	ball.setFillColor(ballColor);
	ball.setPosition((WINDOW_WIDTH - 2 * ballRadius) / 2,
		(WINDOW_HEIGHT - 2 * ballRadius) / 2);
	float ball_dx = 2.f;
	float ball_dy = 2.f;
	float arr_speed[]{ -5.f,-4.f,-3.f, -2.f, -1.f, 1.f, 2.f, 3.f, 4.f, 5.f };
	int index = rand() % 10;
	float ball_speedx = arr_speed[index];
    index = rand() % 10;
	float ball_speedy = arr_speed[index];
	srand(time(nullptr));
	// Счет
	int leftplayerscore = 0;
	int rightplayerscore = 0;
	Font font;
	font.loadFromFile("ds-digib.ttf");
	Text  leftplayerscoreText;
	leftplayerscoreText.setString (std::to_string(leftplayerscore));//передать строку для отображения
	leftplayerscoreText.setFont(font);
	leftplayerscoreText.setCharacterSize(64);
	leftplayerscoreText.setPosition(200.f, 10.f);

	Text  rightplayerscoreText;
	rightplayerscoreText.setString(std::to_string(rightplayerscore));
	rightplayerscoreText.setFont(font);
	rightplayerscoreText.setCharacterSize(64);
	rightplayerscoreText.setPosition(550.f, 10.f);

	// Главный цикл приложения. Выполняется, пока открыто окно
	while (window.isOpen())
	{
		//1 Обрабатываем очередь событий в цикле
		Event event;
		while (window.pollEvent(event))
		{
			// Пользователь нажал на «крестик» и хочет закрыть окно?
			if (event.type == Event::Closed)
				// тогда закрываем его
				window.close();
		}
		//2 Обновление объектов
		//шарик
		ball.move(ball_speedx, ball_speedy);
		if (ball.getPosition().x <= 0)  
		{
			ball_speedx = -ball_speedx;
			rightplayerscore++;
			rightplayerscoreText.setString(std::to_string(rightplayerscore));
		}
		if (ball.getPosition().x >= (WINDOW_WIDTH - 2 * ballRadius))
		{
			ball_speedx = -ball_speedx;
			leftplayerscore++;
			leftplayerscoreText.setString(std::to_string(rightplayerscore));
		}
		if (ball.getPosition().y <= 0 || ball.getPosition().y >= (WINDOW_HEIGHT - 2 * ballRadius)) {
			ball_speedy = -ball_speedy;
		}
		//Проверка нажатия клавиш
		//усли клавиша w нажата - левая ракетка вверх
		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			leftbatspeedy = batspeed;
			if (leftBat.getPosition().y <= 0)
			{
				leftbatspeedy = -leftbatspeedy;
				leftBat.move(0, -leftbatspeedy);
			}
		}

		leftBat.move(0, leftbatspeedy);
		leftbatspeedy = 0.f;
		//ракетка вниз
		if (Keyboard::isKeyPressed(Keyboard::X)) {
			leftbatspeedy = batspeed;
		}
		leftBat.move(0, leftbatspeedy);
		leftbatspeedy = 0.f;
		//усли клавиша Up нажата - правая ракетка вверх
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			rightbatspeedy = -batspeed;
			rightbatspeedy = -batspeed;
			if (rightBat.getPosition().y <= 0)
			{
				rightbatspeedy = -rightbatspeedy;
				rightBat.move(0, -rightbatspeedy);
			}
		}
		rightBat.move(0, rightbatspeedy);
		rightbatspeedy = 0.f;
		//ракетка вниз
		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			rightbatspeedy = batspeed;
		}
		rightBat.move(0, rightbatspeedy);
		rightbatspeedy = 0.f;
		//3 Отрисовка окна
		//3.1 Очистка окна
		window.clear();
		//3.2 Отрисовка объектов (В ПАМЯТИ!)
		window.draw(leftBat);
		window.draw(rightBat);
		window.draw(ball);
		window.draw(leftplayerscoreText);
		window.draw(rightplayerscoreText);
		//3.3 вывод на экран
		window.display();
	}
	return 0;
}
