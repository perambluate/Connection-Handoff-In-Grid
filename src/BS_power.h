#ifndef BS_POWER_H
#define BS_POWER_H

#include <vector>
#include <cmath>

using namespace std;

#define cell_length 100
#define square(x) (double)(x * x)
#define Loss(d) (double)(33 + 20 * log10(d)) //(dB), path loss with distance d(m)
#define getEntries(index, Matrix) Matrix[*index][*(index + 1)] //get the values of the matrix in the position

double Distance(int pos[2], const double BS_pos[2]);
void computePowerOverGrid(const int Pt, const int grid_size[2], const int num_BS, const double BS_pos_arr[][2], vector<vector<vector<double>>> &Power, vector<vector<int>> &MaxPowerBS);
double getPower(int pos[2], int BS, vector<vector<vector<double>>> &Power);
int getMaxBS(int pos[2], vector<vector<int>> &MaxPowerBS);

#endif // BS_POWER_H