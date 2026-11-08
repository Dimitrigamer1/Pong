#include <SFML/Graphics.hpp>
#include <iostream>
	
int main() {
	sf::RenderWindow window(sf::VideoMode({ 1200, 600 }), "Pong");

	sf::Font font("tiny2 duo.ttf");

	if (!font.openFromFile("tiny2 duo.ttf")) {
		std::cerr << "Failed to load font...ha";
		return -1;
	}

	sf::Vector2f pad1pos = { 15, 250 };
	sf::Vector2f pad2pos = { 1165, 250 };

	float speed = 450.f;

	sf::Vector2f ballpos = { 600, 300 };

	float ballXspeed = 350.0f;
	float ballYspeed = 350.0f;

	sf::RectangleShape pad1({ 20, 125 });
	pad1.setFillColor(sf::Color::White);
	pad1.setPosition(pad1pos);

	sf::RectangleShape pad2({ 20, 125 });
	pad2.setFillColor(sf::Color::White);
	pad2.setPosition(pad2pos);

	sf::CircleShape ball(12.f);
	ball.setFillColor(sf::Color::White);
	ball.setPosition(ballpos);

	sf::RectangleShape block({ 10, 600 });
	block.setFillColor(sf::Color::White);
	block.setPosition({ 590, 0 });

	int score1 = 0;
	int score2 = 0;

	sf::Text score1text(font);
	score1text.setFillColor(sf::Color::White);
	score1text.setPosition({ 240, 30 });
	score1text.setCharacterSize(80.f);

	sf::Text score2text(font);
	score2text.setFillColor(sf::Color::White);
	score2text.setPosition({ 840, 30 });
	score2text.setCharacterSize(80.f);
	
	sf::Clock clock;
	
	while (window.isOpen()) {
		if (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
			window.close();
		}

		float dt = clock.restart().asSeconds();

		ball.move({ ballXspeed * dt, ballYspeed * dt });

		if (ball.getPosition().y >= window.getSize().y - 24.f || ball.getPosition().y <= 0) {
			ballYspeed *= -1.f;
		}

		if (ball.getPosition().x >= window.getSize().x - 24.f) {
			score1++;
			ball.setPosition({ 600, 300 });
		}
		else if (ball.getPosition().x <= 0) {
			score2++;
			ball.setPosition({ 600, 300 });
		}

		sf::FloatRect pad1rec = pad1.getGlobalBounds();
		sf::FloatRect pad2rec = pad2.getGlobalBounds();
		sf::FloatRect ballrec = ball.getGlobalBounds();

		if (ballrec.findIntersection(pad1rec) || ballrec.findIntersection(pad2rec)) {
			ballXspeed *= -1.f;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
			if (pad1pos.y - speed * dt >= 0.f) {
				pad1pos.y -= speed * dt;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
			if (pad1pos.y + speed * dt <= window.getSize().y - 125.f) {
				pad1pos.y += speed * dt;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
			if (pad2pos.y - speed * dt >= 0.f) {
				pad2pos.y -= speed * dt;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
			if (pad2pos.y + speed * dt <= window.getSize().y - 125.f) {
				pad2pos.y += speed * dt;
			}
		}

		pad1.setPosition(pad1pos);
		pad2.setPosition(pad2pos);


		score1text.setString(std::to_string(score1));
		score2text.setString(std::to_string(score2));

		window.clear(sf::Color::Black);

		window.draw(pad1);
		window.draw(pad2);
		window.draw(ball);
		window.draw(score1text);
		window.draw(score2text);
		window.draw(block);

		window.display();
	}
}