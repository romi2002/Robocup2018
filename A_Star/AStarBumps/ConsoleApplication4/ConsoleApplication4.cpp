// ConsoleApplication4.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include "windows.h"

using namespace std;

#include "Node.h"
#include "Path.h"

template<class T>
void removeFromVector(vector <T> &vec, T elem) {

	for (int i = vec.size() - 1; i >= 0; --i) {
		if (vec[i] == elem) {
			vec.erase(vec.begin() + i);
			break;
		}
	}
}

void addNeighbors(Node *node, vector<vector<Node>> &maze ) {

	int x = node->getX();
	int y = node->getY();
	int cols = maze[0].size();
	int rows = maze.size();

	if (x < cols - 1) {

		if (!maze[y][x].getHasWallRight()) {
			node->addNeighbor(&maze[y][x + 1]);
		}
	}

	if (x > 0) {

		if (!maze[y][x].getHasWallLeft()) {
			node->addNeighbor(&maze[y][x - 1]);
		}
	}
	if (y < rows - 1) {

		if (!maze[y][x].getHasWallDown()) {
			node->addNeighbor(&maze[y + 1][x]);
		}
	}
	if (y > 0) {

		if (!maze[y][x].getHasWallUp()) {
			node->addNeighbor(&maze[y - 1][x]);
		}
	}
}

template <class T>
bool isInVector(vector<T> &vec, T &elem) {
	for (T e : vec) {
		if (e == elem) {
			return true;
		}
	}

	return false;
}

int calculateDistance(Node *a, Node *b) {
	int dx = abs(a->getX() - b->getX());
	int dy = abs(a->getY() - b->getY()); 
	return (dx + dy); 
}

void updateWalls(vector <vector<Node>> &maze) {
	int cols = maze[0].size();
	int rows = maze.size();
	
	for (int y = 0; y < maze.size(); ++y) {
		for (int x = 0; x < maze[0].size(); ++x) {	
			if (x - 1 < cols - 1) {

				if (maze[y][x].getHasWallRight()) {
					maze[y][x + 1].setHasWallLeft(true);
				}
			}

			if (x + 1 > 0) {

				if (maze[y][x ].getHasWallLeft()) {
					maze[y][x - 1].setHasWallRight(true);
				}
	
			}
			if (y -  1 < rows - 1) {
				
				if (maze[y][x].getHasWallDown()) {
					maze[y + 1][x].setHasWallUp(true);
				}
			}
			if (y + 1 > 0) {

				if (maze[y][x].getHasWallUp()) {
					maze[y - 1][x].setHasWallDown(true);
				}

			}
		}
	}
}

void printMaze(vector <vector <Node>> maze) {
	cout << "PRINTING MAZE...";
	for (int y = 0; y < maze.size(); ++y) {
		cout << endl;
		for (int x = 0; x < maze[0].size(); ++x) {
			if (maze[y][x].getHasWallUp()) {
				cout << " UP ";
			}
			else {
				cout << "|--|";
			}

			if (maze[y][x].getHasWallDown()) {
				cout << " DN ";
			}
			else {
				cout << "|--|";
			}
			if (maze[y][x].getHasWallLeft()) {
				cout << " LF ";
			}
			else {
				cout << "|--|";
			}
			if (maze[y][x].getHasWallRight()) {
				cout << " RT ";
			}
			else {
				cout << "|--|";
			}
			cout << "/";

		}
	}
}

//void searchForNextGoal(vector <vector <Node>>& maze, Node *start, Node *&end) {
//
//	int distance = 0, minorDistance = 1000, newX, newY;
//	cout << "INCIA DESDE " << start->getX() << " " << start->getY() << endl;
//	cout << "LAS NO VISITADAS SON : " << endl;
//	for (int y = 0; y < maze.size(); ++y) {
//		for (int x = 0; x < maze[0].size(); ++x) {
//			if (!maze[y][x].getWasVisited()) {
//				Node* candidate = &maze[y][x];
//				distance = calculateDistance(start, candidate);
//				cout << x << " " << y << "    " << distance << endl;
//				if (minorDistance > distance) {
//					minorDistance = distance;
//					end = candidate;
//
//					cout << "NUEVO VALOR DE END : " << x << " " << y << endl;
//				}
//			}
//		}
//	}
//
//	cout << "LA TILE MAS CERCANA NO VISITADA ES (" << end->getX() << "," << end->getY() << ")" << endl;
//}

vector<Node*> getCandidates(vector<vector<Node>> maze) {
	vector <Node*> vec;
	for (int y = 0; y < maze.size(); ++y) {
		for (int x = 0; x < maze[0].size(); ++x) {
			if (maze[y][x].getWasVisited()) {

				//cout << "LA TILE VISITADA ES (" << x << "," << y << ")" << endl;
				vector <Node*> neighbors = maze[y][x].getNeighbors();

				//cout << "SUS VECINOS NO VISITADOS SON : ";

				for (int i = neighbors.size() - 1; i >= 0; --i) {
					if (!neighbors[i]->getWasVisited()) {
						Node* elem = neighbors[i];
						if (!isInVector(vec, elem)) {
							vec.emplace_back(neighbors[i]);
							//cout << "(" << neighbors[i]->getX() << "," << neighbors[i]->getY() << ")  ";
						}
					}
				}

				//cout << endl;
			}
		}
	}
	return vec;
}

vector <Node*> getClosestFrom(vector <Node*>& vec, Node* start) {
	vector <Node*> listOfClosest;

	int distance = 0, minorDistance = 1000;
	for (int i = 0; i < vec.size(); ++i) {
		Node* candidate = vec[i];
		distance = calculateDistance(start, candidate);
		if(minorDistance >= distance) {
			if (minorDistance > distance) {
				minorDistance = distance;
				listOfClosest.clear();
			}

			listOfClosest.emplace_back(candidate);
		}
	}

	//cout << "LA TILE NO VISITADA MAS CERCANA (PROVENIENTE DE UNA TILE VISITADA) ES : " << end->getX() << " " << end->getY() << endl;
	return listOfClosest;

}

Path getPath(vector <vector<Node>>& maze, int xS, int yS, int xE, int yE) {
	vector <Node*> openSet;
	vector <Node*> closedSet;
	Node* start = &maze[yS][xS];
	Node* end = &maze[yE][xE];

	vector<Node*> endNeighbors = end->getNeighbors();

	for (vector<Node>& row : maze)
		for (Node& node : row) {
			node.setParent(nullptr);

		}
	
	openSet.emplace_back(start);


	while (openSet.size() > 0) {

		int winnerIndex = 0;
		for (int i = 0; i < openSet.size(); ++i) {
			if (openSet[i]->getF() < openSet[winnerIndex]->getF()) {
				winnerIndex = i;
			}
		}

		Node* current = openSet[winnerIndex];

		if (current == end) {
			// cout << "DONE!" << endl;
			vector <Node*> path;
			Node* temp = current;
			path.emplace_back(temp);

			int cost = 0;

			while (temp->getParent() != nullptr) {
				cost += temp->getCost();
				path.emplace_back(temp->getParent());
				temp = temp->getParent();
			}
			
			Path finalPath(path);
			finalPath.setCost(cost);

			return finalPath;
		}

		removeFromVector(openSet, current);
		closedSet.emplace_back(current);

		addNeighbors(current, maze);

		for (Node* neighbor : current->getNeighbors()) {

			if ((neighbor->getWasVisited() || isInVector(endNeighbors, neighbor)) || neighbor == end) {

				if (!isInVector(closedSet, neighbor)) {
					//	int tempG = current->getG() + 1; // version without bump count
				
					int tempG =	current->getG() + neighbor->getCost();

					bool newPath = false;
					if (isInVector(openSet, neighbor)) {
						if (tempG < neighbor->getG()) {
							neighbor->setG(tempG);
							newPath = true;
						}
					}
					else {
						neighbor->setG(tempG);
						openSet.emplace_back(neighbor);
						newPath = true;
					}
					if (newPath) {
						neighbor->setH(calculateDistance(neighbor, end));
						neighbor->setF(neighbor->getG() + neighbor->getH());
						neighbor->setParent(current);
					}

				}
			}

		}


	}

	cout << "NO SOLUTION" << endl;
	return Path();

}

int main() {

	vector <vector<Node>> maze;
	int cols = 5, rows = 7;

	for (int y = 0; y < rows; ++y) {
		maze.emplace_back();
		for (int x = 0; x < cols; ++x) {
			maze[y].emplace_back(Node(x, y));
		}
	}
	maze[0][0].setWasVisited(true);

	maze[1][0].setHasWallDown(true);
	maze[3][0].setHasWallDown(true);
	maze[3][0].setHasWallRight(true);
	maze[4][0].setHasWallRight(true);
	maze[5][0].setHasWallRight(true);
	maze[0][1].setHasWallDown(true);
	maze[2][1].setHasWallDown(true);
	maze[4][1].setHasWallDown(true);
	maze[5][1].setHasWallDown(true);
	maze[0][2].setHasWallDown(true);
	maze[4][2].setHasWallDown(true);
	maze[0][3].setHasWallDown(true);
	maze[1][3].setHasWallRight(true);
	maze[3][3].setHasWallDown(true);
	maze[4][3].setHasWallRight(true);
	maze[5][3].setHasWallRight(true);
	maze[6][3].setHasWallRight(true);
	maze[2][4].setHasWallDown(true);


	maze[2][0].setBumpLevel(Small);
	maze[5][0].setBumpLevel(Small);
	maze[3][1].setBumpLevel(Medium);
	maze[4][1].setBumpLevel(Max);
	maze[5][1].setBumpLevel(Max);
	maze[0][2].setBumpLevel(Small);
	maze[2][2].setBumpLevel(Small);
	maze[5][3].setBumpLevel(Medium);
	maze[2][4].setBumpLevel(Small);
	maze[5][4].setBumpLevel(Small);


	updateWalls(maze);


	for (int y = 0; y < maze.size(); ++y) {
		for (int x = 0; x < maze[0].size(); ++x) {
			addNeighbors(&maze[y][x], maze);
		}
	}

	vector<Node*> candidates = getCandidates(maze);
	Node* start = &maze[0][0];

	Node* returnTo = start;

	while (candidates.size() != 0) {

		vector <Node*> target = getClosestFrom(candidates, start);

		int minorIndex = 0, minorCost = 10000;
		Path bestPath;
		for (int i = 0; i < target.size(); ++i) {
			Path buffer = getPath(maze, start->getX(), start->getY(), target[i]->getX(), target[i]->getY());
			int cost = buffer.getCost();
			if (cost < minorCost) {
				minorIndex = i;
				minorCost = cost;
				bestPath = buffer;
			}
		}

		Node* goal = target[minorIndex];

		cout << "StartX: " << start->getX() << " StartY: " << start->getY() << endl;
		cout << "EndX: " << goal->getX() << " EndY: " << goal->getY() << endl;

		if (target.size() > 0) {
			bestPath.printPath();
			goal->setWasVisited(true);
			start = goal;
			candidates = getCandidates(maze);
			int i;
			cin >> i;
		}
		else {
			cout << "Nothing to do" << endl;
			int i;
			cin >> i;
			return 0;
		}
	}

	cout << "REGRESANDO A CASA :)" << endl;
	getPath(maze, start->getX(), start->getY(), returnTo->getX(), returnTo->getY()).printPath();
	
	int i;
	cout << "AFUERA" << endl;
	cin >> i;
	return 0;
}

