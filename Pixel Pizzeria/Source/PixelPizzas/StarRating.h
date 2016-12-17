#pragma once
#include <SFML/Graphics.hpp>

class StarRating
{

private:

	sf::Image imgStarRating;
	sf::Texture txtrStarRating;
	sf::Sprite sprStarRating;

	unsigned int rating;

public:

	void setRating(const unsigned int &rating);
	void setPosition(const sf::Vector2f &position);

	sf::FloatRect getRect() const;

	void draw(sf::RenderWindow &window) const;

	StarRating();
	~StarRating();

};

