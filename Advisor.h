// Hannah Davisson
#ifndef ADVISOR_H
#define ADVISOR_H

#include <string>
using namespace std;

class Advisor
{
private:
    string name;
    string ability;
    int id; // 1 = Rafiki, 2 = Nala, etc.
    bool isSelected;

public:
    // Constructors
    Advisor();
    Advisor(string name, string ability, int id);

    // Getters
    string getName() const;
    string getAbility() const;
    int getId() const;
    bool getIsSelected() const;

    // Setters
    void setName(string name);
    void setAbility(string ability);
    void setId(int id);
    void setIsSelected(bool isSelected);

    // Display advisor info
    void displayInfo() const;
};

#endif