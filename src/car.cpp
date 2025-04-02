#include "car.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

inline int RandomInt(){
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    srand((time_t)ts.tv_nsec);
    return rand();
}

Car::Car(int entry_num){
    switch((int) (entry_num / 9)){
        //enter from the left boundary
        case 0:
            pos[0] = entry_num;
            pos[1] = 0;
            direction = 0;
            break;
        //enter from the down boundary
        case 1:
            pos[0] = 8;
            pos[1] = entry_num - 9;
            direction = 1;
            break;
        //enter from the right boundary
        case 2:
            pos[0] = 26 - entry_num;
            pos[1] = 8;
            direction = 2;
            break;
        //enter from the up boundary
        case 3:
            pos[0] = 0;
            pos[1] = 35 - entry_num;
            direction = 4;
            break;
        default:
            std::cerr << "entry number" << entry_num << " out of range" << std::endl;
            break;
    }
}

bool Car::moving(){
    int random = RandomInt();
    if (random % 5 == 0){
        //turn right
        direction = (direction + 1) % 4;
    } else if (random % 5 == 1){
        //turn left
        direction = (direction -1) % 4;
    }
    switch(direction){
        //moving right
        case 0:
            pos[0]++;
            break;
        //moving down
        case 1:
            pos[1]--;
            break;
        //moding left
        case 2:
            pos[0]--;
            break;
        //moving up
        case 3:
            pos[1]++;
            break;
    }
    //return true if the car departs the cells
    return (pos[0] * (8 - pos[0]) < 0) || (pos[1] * (8 - pos[1]) < 0);
}
