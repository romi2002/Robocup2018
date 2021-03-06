#ifndef __UTILS_H_
#define __UTILS_H_
#ifdef ARDUINO
#include <Arduino.h>
#include <ArduinoSTL.h>
#else


#include <vector>
#include <math.h>
#endif

#include "Coord.h"


using namespace std;

enum Direction {
	Up,
	Down,
	Left,
	Right
};

enum Color {
    White,
    Black,
    Silver
};

enum BumpLevel {
    Flat,
    Small,
    Medium,
    Max
};

float mapD(float x, float in_min, float in_max, float out_min, float out_max);

float shortestAngleTurn(float currentAngle, float target);

vector<Coord> getClosestFrom(vector <Coord>& vec, Coord start);

template<class T>
void removeFromVector(vector<T> &vector, T element){
    for(int j = vector.size() - 1; j >= 0; --j){
        if(vector[j] == element){
            vector.erase(vector.begin() + j);
        }
    }
}

template <class T>
int countsOnVector(vector<T> & vector, T element){
    int counter = 0;
    for(T el : vector){
        if(element == el)
            counter++;
    }

    return counter;
}

#endif
