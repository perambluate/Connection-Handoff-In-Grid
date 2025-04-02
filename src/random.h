#ifndef RANDOM_H
#define RANDOM_H

#include "car.h"
#include "policy.h"
#include <vector>

using namespace std;

double getRandom(); //generate random #
void Arrival(double arrProb, vector<Car> &Cars, vector<vector<int>> &MaxPowerBS); //generate the car arrivals following the Poisson process
void Arrival(double arrProb, vector<Car> &Cars, vector<vector<int>> &MaxPowerBS, vector<Policy*> &Policies); //generate the car arrivals following the Poisson process

#endif // RANDOM_H