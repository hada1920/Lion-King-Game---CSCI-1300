// Hannah Davisson
#include "Advisor.h"
#include <iostream>

// Default constructor
Advisor::Advisor()
{
    name = "";
    ability = "";
    id = 0;
    isSelected = false;
}

// Parameterized constructor
Advisor::Advisor(string name, string ability, int id)
{
    this->name = name;
    this->ability = ability;
    this->id = id;
    this->isSelected = false;
}

// Getters
string Advisor::getName() const
{
    return name;
}

string Advisor::getAbility() const
{
    return ability;
}

int Advisor::getId() const
{
    return id;
}

bool Advisor::getIsSelected() const
{
    return isSelected;
}

// Setters
void Advisor::setName(string name)
{
    this->name = name;
}

void Advisor::setAbility(string ability)
{
    this->ability = ability;
}

void Advisor::setId(int id)
{
    this->id = id;
}

void Advisor::setIsSelected(bool isSelected)
{
    this->isSelected = isSelected;
}

// Display advisor info
void Advisor::displayInfo() const
{
    cout << "Name: " << name << endl;
    cout << "Ability: " << ability << endl;
}