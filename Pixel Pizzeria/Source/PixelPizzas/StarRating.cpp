#include "StarRating.h"


void StarRating::setRating(const unsigned int &rating)
{
	this->rating = rating;
	txtrStarRating.loadFromImage(imgStarRating, sf::IntRect(0, 33 * rating, 165, 33));
	sprStarRating.setTexture(txtrStarRating);
	sf::FloatRect rectStarRating = sprStarRating.getLocalBounds();
	sprStarRating.setOrigin(rectStarRating.left + rectStarRating.width / 2.0f, rectStarRating.top + rectStarRating.height / 2.0f);
}

void StarRating::setPosition(const sf::Vector2f& position)
{
	sprStarRating.setPosition(position);
}

sf::FloatRect StarRating::getRect() const
{
	return sprStarRating.getGlobalBounds();
}

void StarRating::draw(sf::RenderWindow& window) const
{
	window.draw(sprStarRating);
}

StarRating::StarRating()
{
	if(!imgStarRating.loadFromFile("Assets/Sidebar/Stars.png"))
	{
		printf("Error: failed to load Stars.png\n");
	}
	setRating(0);
}

StarRating::~StarRating()
{
}
