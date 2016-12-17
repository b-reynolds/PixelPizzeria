#pragma once
#include <SFML/System/Vector2.hpp>

class Node
{

private:

	Node* pParent;

	sf::Vector2i position;
	bool traversable;

	int h;
	int g;

public:

	Node(sf::Vector2i position, bool traversable, Node* pParent);

	sf::Vector2i getPosition() const;

	void setParent(Node* pParent);
	Node* getParent() const;

	void setH(int h);
	int getH() const;

	void setG(int g);
	int getG() const;

	int getF() const;

	bool isTraversable() const;
	bool operator==(Node node) const;

	~Node();

};

