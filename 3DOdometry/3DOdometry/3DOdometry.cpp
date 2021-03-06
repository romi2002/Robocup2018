// Verificacion.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iomanip>
#include<iostream>
#include <math.h>
#include <vector>

using namespace std;

#include "Point3D.h"

Point3D getFinalPoint(Point3D &previous, double magnitude, double pitch, double yaw) {
	Point3D next = next.getVector(magnitude, pitch, yaw);
	previous += next;
	return previous;
}

bool checkIfPreviouslyVisited(vector<Point3D> previouslyVisited, Point3D coord) {
	for (int i = previouslyVisited.size() - 1; i >= 0; --i) {
		if (previouslyVisited[i] == coord) {
			return true;
		}
	}
	return false;
}

int main(){

	Point3D start, pos1(2, 3, - 5), pos2(8, -9, 43), pos3(-17, 33, 2), pos4(10,52,88), pos5(-2,3,-5);

	vector<Point3D> previouslyVisited;

	previouslyVisited.emplace_back(start);
	previouslyVisited.emplace_back(pos1);
	previouslyVisited.emplace_back(pos2);
	previouslyVisited.emplace_back(pos3);
	previouslyVisited.emplace_back(pos4);

	bool wasVisited = checkIfPreviouslyVisited(previouslyVisited, start);
	cout << "CASO 1 " << endl;
	if (wasVisited)
		cout << "si fue visitada, correcto" << endl;
	else
		cout << "no fue visitada, incorrecto" << endl;




	cout << "CASO 2 " << endl;
	wasVisited = checkIfPreviouslyVisited(previouslyVisited, pos5);
	if (wasVisited)
		cout << "si fue visitada, incorrecto" << endl;
	else
		cout << "no fue visitada, correcto" << endl;




	cout << endl << "PROGRAM HAS BEEN TERMINATED! " << endl;
	int opcion;
	cin >> opcion;

    return 0;
}

