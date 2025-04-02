#ifndef POLICY_H
#define POLICY_H
#include "car.h"
#include <string>
#include <sstream>
#include <vector>
#include <iostream>

using namespace std;

class Policy{
    public:
        virtual void Handoff(Car &, int, int, int){};
        void setPolicyID(int); //set policy ID
        int getPolicyID(); //get policy ID
        void setPolicyInfo(string); //set policy info
        // virtual void printPolicy(){};
        void printPolicy();
        int getHandoff();
        // void updateHandoff();
        void updateBS_Handoff(Car &, int, int policy_index = 0); //update the BS of car and the handoff #
    private:
        int _handoff = 0;
        int _policy_id = -1;
        string _policy_info = "";
};

//Best policy with policy number 0
class Best : public Policy{
    public:
        Best(){
            Policy::setPolicyID(0);
            Policy::setPolicyInfo("Best policy");
        }
        void Handoff(Car &, int, int, int);
        void printPolicy();
};

//Entropy policy with policy number 1
class Entropy : virtual public Policy{
    public:
        Entropy(double entropy) : _entropy(entropy){
            Policy::setPolicyID(1);
            stringstream ss;
            ss << "Entropy policy with entropy " << getEntropy();
            Policy::setPolicyInfo(ss.str());
        }
        double getEntropy();
        void Handoff(Car &, int, int, int, vector<vector<vector<double>>> &);
        void printPolicy();
    private:
        double _entropy;
};

//Threshold policy with policy number 2
class Threshold : virtual public Policy{
    public:
        Threshold(double thres) : _thres(thres){
            Policy::setPolicyID(2);
            stringstream ss;
            ss << "Threshold policy with threshold " << getThres();
            Policy::setPolicyInfo(ss.str());
        }
        double getThres();
        void Handoff(Car &, int, int, int, vector<vector<vector<double>>> &);
        void printPolicy();
    private:
        double _thres;
};

void policySelector(Policy *policy, Car &car, int max_BS, vector<vector<vector<double>>> &Power, const double BS_pos_arr[][2], int policy_index = 0);

//MyPolicy with policy number 3
class MyPolicy : public Threshold, public Entropy{
    public:
        MyPolicy(double thres, double entropy) : Entropy(entropy), Threshold(thres) {
            Policy::setPolicyID(3);
            stringstream ss;
            ss << "MyPolicy policy with entropy " << Entropy::getEntropy() << " threshold " << Threshold::getThres();
            Policy::setPolicyInfo(ss.str());
        }
        void Handoff(Car &, int, int, int, vector<vector<vector<double>>> &, const double BS_pos_arr[][2]);
        //compute the porb. of handoff with the distance from the car to origin BS and the distance from the car to max BS
        double handoffProb(double, double);
        void printPolicy();
};

inline void Policy::setPolicyID(int policy_id){_policy_id = policy_id;}
inline int Policy::getPolicyID(){return _policy_id;}
inline void Policy::setPolicyInfo(string policy_info){_policy_info = policy_info;}
inline void Policy::printPolicy(){
    cout << _policy_info << endl;
}
inline int Policy::getHandoff(){return _handoff;}
// inline void Policy::updateHandoff(){_handoff++;}
inline void Policy::updateBS_Handoff(Car &car, int new_BS, int policy_index){
    car.setBS(new_BS, policy_index);
    _handoff++;
}
// inline void Best::printPolicy(){cout << "Best policy\n";}
// inline void Entropy::printPolicy(){cout << "Entropy policy with entropy " << getEntropy() << endl;}
// inline void Threshold::printPolicy(){cout << "Threshold policy with threshold " << getThres() << endl;}
// inline void MyPolicy::printPolicy(){cout << "MyPolicy policy with entropy " << Entropy::getEntropy() << " threshold " << getThres() << endl;}
inline double Entropy::getEntropy(){return _entropy;}
inline double Threshold::getThres(){return _thres;}
inline double MyPolicy::handoffProb(double d_old, double d_new){return 1. - d_new / d_old;}

#endif // POLICY_H