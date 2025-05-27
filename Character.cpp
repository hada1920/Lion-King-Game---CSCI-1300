// Hannah Davisson
#include "Character.h"
#include <iostream>

// Default constructor
Character::Character()
{
    name = "";
    age = 0;
    strength = 0;
    stamina = 0;
    wisdom = 0;
    pridePoints = 0;
    isSelected = false;
}

// Parameterized constructor
Character::Character(string name, int age, int strength, int stamina, int wisdom, int pridePoints)
{
    this->name = name;
    this->age = age;
    this->strength = strength;
    this->stamina = stamina;
    this->wisdom = wisdom;
    this->pridePoints = pridePoints;
    this->isSelected = false;
}

// Getters
string Character::getName() const
{
    return name;
}

int Character::getAge() const
{
    return age;
}

int Character::getStrength() const
{
    return strength;
}

int Character::getStamina() const
{
    return stamina;
}

int Character::getWisdom() const
{
    return wisdom;
}

int Character::getPridePoints() const
{
    return pridePoints;
}

bool Character::getIsSelected() const
{
    return isSelected;
}

// Setters
void Character::setName(string name)
{
    this->name = name;
}

void Character::setAge(int age)
{
    this->age = age;
}

void Character::setStrength(int strength)
{
    this->strength = strength;
}

void Character::setStamina(int stamina)
{
    this->stamina = stamina;
}

void Character::setWisdom(int wisdom)
{
    this->wisdom = wisdom;
}

void Character::setPridePoints(int pridePoints)
{
    this->pridePoints = pridePoints; // differentiate from member var
}

void Character::setIsSelected(bool isSelected)
{
    this->isSelected = isSelected;
}

// Display character info
void Character::displayInfo() const
{
    cout << "Name: " << name << endl;
    cout << "Age: " << age << endl;
    cout << "Strength: " << strength << endl;
    cout << "Stamina: " << stamina << endl;
    cout << "Wisdom: " << wisdom << endl;
    cout << "Pride Points: " << pridePoints << endl;
}