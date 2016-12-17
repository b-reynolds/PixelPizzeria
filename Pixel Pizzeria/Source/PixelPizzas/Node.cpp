#include "Node.h"

void Node::setParent(Node* pParent)
{
	this->pParent = pParent;
}

void Node::setH(int h)
{
	this->h = h;
}

void Node::setG(int g)
{
	this->g = g;
}

sf::Vector2i Node::getPosition() const
{
	return this->position;
}

Node* Node::getParent() const
{
	return pParent;
}

int Node::getH() const
{
	return h;
}

int Node::getG() const
{
	return g;
}

int Node::getF() const
{
	return h + g;
}

bool Node::isTraversable() const
{
	return traversable;
}

bool Node::operator==(Node node) const
{
	return this->position == node.getPosition();
}

Node::Node(sf::Vector2i position, bool traversable, Node* pParent)
{
	this->position = position;
	this->pParent = pParent;
	this->traversable = traversable;
	h = 0;
	g = 0;
}

Node::~Node()
{
}
