#include "BS_power.h"
#include "car.h"
#include "policy.h"
#include "random.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <vector>
#include <string>
#include <cmath>
#include <typeinfo>
using namespace std;

#define delta 2e-3 //the resolution of time
#define arrStep 1000 // # of arrival steps
#define totStep 86400 // # of moving step in simulation, which is equivalent to # of seconds in a day
#define Poisson(r) (double)(1 - exp(-r * delta)) //the prob. followed with Poisson dist.
#define cell_length 100 //(m/cell), the lenght of a cell using for computing distance
#define tvPrint(text, value) cout << text << "\t" << value << endl;

#define Multi_Policy

const int grid_size[2] = {9, 9}; //the size of the grid
const double BS_pos_arr[4][2] = {
    {3.3, 3.5}, {6.4, 3.1}, {3.6, 6.8}, {6.6, 6.58}
}; //the position of 4 BS
const int num_BS = sizeof(BS_pos_arr) / sizeof(BS_pos_arr[0]);
const double Pt = 100; //(dB), the transmitting power of BS
const double P_min = 10; //(dB), the min power for computing AVGmin
const int lambda_inverse_arr[3] = {2, 3, 5}; //(ms/car), the inverse of arrival rate
vector<vector<vector<double>>> Power(grid_size[0], vector<vector<double>>(grid_size[1], vector<double>(num_BS)));
vector<vector<int>> MaxPowerBS(grid_size[0], vector<int>(grid_size[1]));
vector<Car> Cars; //storing the cars in the effective range of cells during the simulation

vector<Policy*> Policies;
void eachStep(vector<double> &);

int main(){
    // for(int k = 0; k < 3; k++){
        Policies.push_back(new Best());
        Policies.push_back(new Threshold(P_min));
        Policies.push_back(new Entropy(5));
        Policies.push_back(new Threshold(17.5));
        Policies.push_back(new MyPolicy(10, 10));
        // double lambda = 1. / (double)lambda_inverse_arr[k];
        double lambda = 0.5;
        double arrProb = Poisson(lambda);
        cout << "lambda = " << lambda << " arrProb = " << arrProb << endl;
        // tvPrint("arrProb", arrProb);
        int N_cars = 0;
        vector<int> Handoffs(Policies.size(), 0);
        vector<double> totPower(Policies.size(), 0);
        computePowerOverGrid(Pt, grid_size, num_BS, BS_pos_arr, Power, MaxPowerBS);
        cout << "step\tcar#\t";
        for(int i = 0; i < Policies.size(); i++)
            cout << "Policy_" << i << "\t";
        cout << endl;
        int steps = 2000;
        for(int i = 0; i < steps; i++){
            for(int j = 0; j < arrStep; j++)
                Arrival(arrProb, Cars, MaxPowerBS, Policies);
            cout << i << "\t" << Cars.size() << "\t";
            if (!Cars.empty())
                N_cars += Cars.size();
            eachStep(totPower);
            for(int i = 0; i < Policies.size(); i++){
                int totHandoff = Policies[i]->getHandoff();
                cout << totHandoff - Handoffs[i]  << "\t";
                Handoffs[i] = Policies[i]->getHandoff();
            }
            cout << endl;
        }
        cout << "------summary------" << endl;
        tvPrint("total # of cars", N_cars);
        for(int i = 0; Policies.size() - i; i++){
            Policies[i]->printPolicy();
            // tvPrint("total handoff", Handoffs[i]);
            tvPrint("total handoff", Policies[i]->getHandoff());
            tvPrint("avg power", (double)(totPower[i] / N_cars));
        }
        double Pmax = (double)(totPower[0] / N_cars), \
        Pmin = (double)(totPower[1] / N_cars);
        double Pavg = (Pmax + Pmin) / 2;
        tvPrint("Pmax", Pmax);
        tvPrint("Pmin", Pmin);
        tvPrint("Pavg", Pavg);
        Policies.clear();
        Cars.clear();
        cout << "------end of the simulation------" << endl;
    // }
    return 0;
}

void eachStep(vector<double> &sum){
    if (sum.size() != Policies.size())
        throw "the size of input vector is error in eachStep\n";
    if(!Cars.empty()){
        for(auto car = Cars.begin(); Cars.end() - car; car++){
            int* last_pos = car->getPos();
            int last_BS = car->getBS();
            bool isDepart = car->moving();
            if (isDepart){
                car = Cars.erase(car);
                car--;
                continue;
            }
            int max_BS = getMaxBS(car->getPos(), MaxPowerBS);
                for(int i = 0; Policies.size() - i; i++){
                    sum[i] += getPower(last_pos, car->getBS(i), Power);
                    policySelector(Policies[i], *car, max_BS, Power, BS_pos_arr, i);
                }
        }
    }
}