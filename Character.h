// Hannah Davisson
#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
using namespace std;

class Character {
private:
    string name;
    int age;
    int strength;
    int stamina;
    int wisdom;
    int pridePoints;
    bool isSelected;

public:
    // Constructors
    Character();
    Character(string name, int age, int strength, int stamina, int wisdom, int pridePoints);
    
    // Getters
    string getName() const;
    int getAge() const;
    int getStrength() const;
    int getStamina() const;
    int getWisdom() const;
    int getPridePoints() const;
    bool getIsSelected() const;
    
    // Setters
    void setName(string name);
    void setAge(int age);
    void setStrength(int strength);
    void setStamina(int stamina);
    void setWisdom(int wisdom);
    void setPridePoints(int pridePoints);
    void setIsSelected(bool isSelected);
    
    // Display character info
    void displayInfo() const;
};

#endif