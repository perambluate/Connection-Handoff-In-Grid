#include "policy.h"
#include "BS_power.h"
#include "car.h"
#include "random.h"
#include <vector>
#include <iostream>

using namespace std;

void Best::Handoff(Car &car, int last_BS, int max_BS, int policy_index){
    if(last_BS != max_BS)
        Policy::updateBS_Handoff(car, max_BS, policy_index);
}

void Entropy::Handoff(Car &car, int last_BS, int max_BS, int policy_index, vector<vector<vector<double>>> &Power){
    if(getPower(car.getPos(), max_BS, Power) - getPower(car.getPos(), last_BS, Power) > getEntropy())
        Policy::updateBS_Handoff(car, max_BS, policy_index);
}

void Threshold::Handoff(Car &car, int last_BS, int max_BS, int policy_index, vector<vector<vector<double>>> &Power){
    if(last_BS != max_BS && getPower(car.getPos(), last_BS, Power) < getThres())
            Policy::updateBS_Handoff(car, max_BS, policy_index);
}

void MyPolicy::Handoff(Car &car, int last_BS, int max_BS, int policy_index, vector<vector<vector<double>>> &Power, const double BS_pos_arr[][2]){
    if(last_BS != max_BS && getPower(car.getPos(), last_BS, Power) < Threshold::getThres())
        Policy::updateBS_Handoff(car, max_BS, policy_index);
    else if(getPower(car.getPos(), max_BS, Power) - getPower(car.getPos(), last_BS, Power) > Entropy::getEntropy()){
        double d_old = Distance(car.getPos(), BS_pos_arr[last_BS]), \
        d_new = Distance(car.getPos(), BS_pos_arr[max_BS]);
        double prob = handoffProb(d_old, d_new);
        if(getRandom() < prob)
            Policy::updateBS_Handoff(car, max_BS, policy_index);
    }
}

void policySelector(Policy *policy, Car &car, int max_BS, vector<vector<vector<double>>> &Power, const double BS_pos_arr[][2], int policy_index){
    switch(policy->getPolicyID()){
        case 0:
            dynamic_cast<Best*>(policy)->Handoff(car, car.getBS(policy_index), max_BS, policy_index);
            break;
        case 1:
            dynamic_cast<Entropy*>(policy)->Handoff(car, car.getBS(policy_index), max_BS, policy_index, Power);
            break;
        case 2:
            dynamic_cast<Threshold*>(policy)->Handoff(car, car.getBS(policy_index), max_BS, policy_index, Power);
            break;
        case 3:
            dynamic_cast<MyPolicy*>(policy)->Handoff(car, car.getBS(policy_index), max_BS, policy_index, Power, BS_pos_arr);
            break;
        default:
            cerr << "No matched policy!\n";
            break;
    }
}