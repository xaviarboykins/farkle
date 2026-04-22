#include "Dice.h"
#include <iostream>
#include <cstdlib>

using namespace std;

const string Dice::diceFaces[6] =
{
    // 1
    "+-------+\n"
    "|       |\n"
    "|   o   |\n"
    "|       |\n"
    "+-------+",

    // 2
    "+-------+\n"
    "| o     |\n"
    "|       |\n"
    "|     o |\n"
    "+-------+",

    // 3
    "+-------+\n"
    "| o     |\n"
    "|   o   |\n"
    "|     o |\n"
    "+-------+",

    // 4
    "+-------+\n"
    "| o   o |\n"
    "|       |\n"
    "| o   o |\n"
    "+-------+",

    // 5
    "+-------+\n"
    "| o   o |\n"
    "|   o   |\n"
    "| o   o |\n"
    "+-------+",

    // 6
    "+-------+\n"
    "| o   o |\n"
    "| o   o |\n"
    "| o   o |\n"
    "+-------+"
};

// Initializes all dice values to 0
Dice::Dice()
{
    for (int i = 0; i < 6; i++)
    {
        values[i] = 0;
    }
}

// Rolls a specified number of dice and assigns random values (1–6)
void Dice::Roll(int numDice)
{
    for (int i = 0; i < numDice; i++)
    {
        values[i] = rand() % 6 + 1;
    }
}

// Displays the rolled dice using ASCII art
void Dice::Display(int numDice) const
{
    cout << "\nYou rolled:\n\n";

    for (int i = 0; i < numDice; i++)
    {
        cout << diceFaces[values[i] - 1] << endl << endl;
    }
}

// Returns the current dice values
int* Dice::GetValues()
{
    return values;
}