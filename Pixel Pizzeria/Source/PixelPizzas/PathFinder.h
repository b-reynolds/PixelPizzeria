#pragma once
#include <deque>
#include <stack>
#include "Node.h"
#include "Map.h"
#include <random>

struct LessThanByF
{
	bool operator() (const Node &n1, const Node &n2) const
	{
		return n1.getF() < n2.getF();
	}
};

class PathFinder
{

private:

	static PathFinder* instance;

	const int COST_DIAGONAL = 14;
	const int COST_NONDIAGONAL = 10;

	PathFinder();

	void sortByLowestF(std::deque<Node> &deque) const;

	int getManhattanDistance(const sf::Vector2i &start, const sf::Vector2i &end) const;
	int getMovementCost(const sf::Vector2i &start, const sf::Vector2i &end) const;
	std::vector<Node> getNeighbours(const Node &node, Map &map);

	bool isOnList(const Node &node, const std::deque<Node>& list);

public:

	static PathFinder* getInstance();

	std::stack<sf::Vector2i> findPath(Map &map, const sf::Vector2i &start, const sf::Vector2i &end);

	~PathFinder();

};

