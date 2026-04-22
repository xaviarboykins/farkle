#pragma once
#include <string>

class Dice
{
private:
    int values[6];
    static const std::string diceFaces[6];

public:
    Dice();

    void Roll(int numDice); 
    void Display(int numDice) const;
    int* GetValues(); 

};

