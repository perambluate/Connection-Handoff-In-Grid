#include "BS_power.h"
#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

double Distance(int pos[2], const double BS_pos[2]){
    double dx = pos[0] - BS_pos[0], \
    dy = pos[1] - BS_pos[1];
    // cout << "dx:" << dx << "dy:" << dy << endl;
    return sqrt(square(dx) + square(dy)) * cell_length;
}

void computePowerOverGrid(const int Pt, const int grid_size[2], const int num_BS, const double BS_pos_arr[][2], vector<vector<vector<double>>> &Power, vector<vector<int>> &MaxPowerBS){
    for (int i = 0; i < grid_size[0]; i++){
        for (int j = 0; j < grid_size[1]; j++){
            int index = -1;
            double max = -100;
            for (int k = 0; k < num_BS; k++){
                int pos[2] = {i, j};
                Power[i][j][k] = Pt - Loss(Distance(pos, BS_pos_arr[k]));
                // cout << Power[i][j][k] << '\t';
                if (max < Power[i][j][k]){
                    max = Power[i][j][k];
                    index = k;
                }
            }
            MaxPowerBS[i][j] = index;
            // cout << endl;
            // cout << "Max index:" << index << endl;
        }
    }        
}

double getPower(int pos[2], int BS, vector<vector<vector<double>>> &Power){
    try{
        return getEntries(pos, Power)[BS];
    } catch(const std::out_of_range &e){
        // throw std::runtime_error("out of range in getPower");
        cerr << "out of range in getPower" << endl;
        return -1;
    }
}

int getMaxBS(int pos[2], vector<vector<int>> &MaxPowerBS){
    try{
        return getEntries(pos, MaxPowerBS);
    } catch(const std::out_of_range &e){
        // throw std::runtime_error("out of range in getMaxBS");
        cerr << "out of range in getMaxBS" << endl;
        return -1;
    }
}