// Verificacion.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iomanip>
#include<iostream>
#include <math.h>
#include <vector>
using namespace std;

#include "Point3D.h"


int main(){

	Point3D result;
	char op = 'b';
	double magnitude, theta, phi;
	while (op != 'a') {
		cout << "INTRODUCE MAGNITUDE, THETA , AND  PHI " << endl;
		cin >> magnitude >> theta >> phi;
		result = result.getVector(magnitude, phi, theta);
		cout << "RESULT : " << result.getX() << " " << result.getY() << " " << result.getZ() << endl;
		cout << "TIRED ? TYPE a" << endl << endl;
		cin >> op;

	}

	cout << "PROGRAM HAS BEEN TERMINATED! " << endl;
	int opcion;

	cin >> opcion;


    return 0;
}

