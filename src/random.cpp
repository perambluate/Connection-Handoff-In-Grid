#include "random.h"
#include "BS_power.h"
#include "car.h"
#include "policy.h"
#include <stdlib.h>
#include <ctime>
#include <time.h>
#include <vector>

using namespace std;

double getRandom(){
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    srand((time_t)ts.tv_nsec);
    return (double) rand() / RAND_MAX;
}

void Arrival(double arrProb, vector<Car> &Cars, vector<vector<int>> &MaxPowerBS){
    for (int i = 0; i < 36; i++){
        // double random = getRandom();
        if (getRandom() < arrProb){
            Car car = Car(i);
            car.setBS(getMaxBS(car.getPos(), MaxPowerBS));
            Cars.push_back(car);
        }
    }
}

void Arrival(double arrProb, vector<Car> &Cars, vector<vector<int>> &MaxPowerBS, vector<Policy*> &Policies){
    for (int i = 0; i < 36; i++){
        // double random = getRandom();
        if (getRandom() < arrProb){
            Car car = Car(i);
            int max_BS = getMaxBS(car.getPos(), MaxPowerBS);
            car.setBS_size(Policies.size());
            for(auto policy = Policies.begin(); Policies.end() - policy; policy++){
                int policy_index = (int) (policy - Policies.begin());
                car.setBS(max_BS, policy_index);
            }
            Cars.push_back(car);
        }
    }
}