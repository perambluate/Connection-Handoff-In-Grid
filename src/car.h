#ifndef CAR_H
#define CAR_H

#include <vector>
#include <iostream>
#include <stdexcept>

using namespace std;

class Car{
    public:
        Car(int); //constructor which init position, direction from the entry #
        int *getPos();
        // void setBS(int);
        void setBS_size(int);
        void setBS(int, int index = 0);
        // int getBS();
        int getBS(int index = 0);
        bool moving();
    private:
        int pos[2]; //the position of the car
        vector<int> BS; //the dynamic array to record BS for different policies
        int direction; //the direction of the car
};

inline int* Car::getPos(){return pos;}
inline void Car::setBS_size(int BS_size){BS.resize(BS_size);}
inline void Car::setBS(int new_BS, int index){
    if (index >= BS.size()) setBS_size(index + 1);
    BS[index] = new_BS;
}
inline int Car::getBS(int index){
    try{
        return BS[index];
    } catch(const out_of_range &e){
        cerr << "out of range in car.getBS" << endl;
        return -1;
        // throw runtime_error("out of range in car.BS");
    }
}

#endif //CAR_H