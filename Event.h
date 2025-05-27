// Hannah Davisson
#ifndef EVENT_H
#define EVENT_H

#include <string>
using namespace std;

struct Event
{
    string description;
    int pathType;          // 0 = cubTraining, 1 = straight to pride lands, 2 = either path
    int advisorProtection; // 0 = none, 1 = Rafiki, 2 = Nala, 3 = Sarabi, 4 = Zazu, 5 = Sarafina
    int pridePointsEffect;
};

#endif