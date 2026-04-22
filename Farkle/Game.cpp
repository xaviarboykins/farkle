#include "Game.h"
#include "Menu.h"
#include "Dice.h"
#include <iostream>
#include <fstream>

using namespace std;

void ClearErrors()
{
    cin.clear();
    cin.ignore(1000, '\n');
}

void Game::Greet()
{
    cout << "\n===================\n\n";
    cout << "Grab your dice!" << endl << endl;
    cout << "What is your name?" << endl << endl;

    // Register player name
    string name;
    cin >> name;
    player.SetName(name);

    cout << endl << "Hello " << player.GetName() << endl;
    cout << "Let's Play!" << endl << endl;
}

void Game::ShowRules()
{
    cout << "\n===================\n\n";

    string file = "farklerules.txt";
    ifstream inFile(file);
    string line;

    if (!inFile.is_open())
    {
        cout << "Error: Could not open rules file.\n";
        return;
    }

    // Output each line of the rules file to the console
    while (getline(inFile, line))
    {
        cout << line << endl;
    }

    inFile.close();
}

// Calculates the score for a roll of dice.
// Applies Farkle rules:
// - 1 = 100 points
// - 5 = 50 points
// - Three of a kind = face * 100 (except 1 = 1000)
// Also tracks how many dice contributed to scoring.
int CalculateScore(const int diceValues[], int numDice, int& scoringDiceUsed)
{
    int counts[7] = { 0 };
    int score = 0;
    scoringDiceUsed = 0;

    for (int i = 0; i < numDice; i++)
    {
        counts[diceValues[i]]++;
    }

    // Three of a kind
    for (int face = 1; face <= 6; face++)
    {
        if (counts[face] >= 3)
        {
            if (face == 1)
            {
                score += 1000;
            }
            else
            {
                score += face * 100;
            }

            counts[face] -= 3;
            scoringDiceUsed += 3;
        }
    }

    // Single 1s
    score += counts[1] * 100;
    scoringDiceUsed += counts[1];

    // Single 5s
    score += counts[5] * 50;
    scoringDiceUsed += counts[5];

    return score;
}

// Runs the main Farkle game loop.
// Handles player turns, dice rolling, scoring, banking decisions,
// and win condition (10,000 points).
void Game::Farkle()
{
    Dice dice;
    bool isPlaying = true;

    while (isPlaying)
    {
        int turnScore = 0;
        int remainingDice = 6;
        bool turnOver = false;

        cout << "\n=========================\n\n";
        cout << player.GetName() << "'s Turn\n";
        cout << "Total Score: " << player.GetScore() << endl;
        cout << "=========================\n\n";

        cout << "\nPress R to roll or Q to quit: "; // prompts first roll or exit

        char input;
        cin >> input;
        input = toupper(input);
        
        ClearErrors(); // clears any error messages incase of invalid input

        if (input == 'Q')
        {
            cout << "Exiting game...\n";
            return;
        }

        
        // Handle turns
        // Roll remaining dice and evaluate result
        while (!turnOver) 
        {
            if (input != 'R')
            {
                cout << "Invalid input.\n";
                cout << "Press R to roll or Q to quit: ";
                cin >> input;
                input = toupper(input);
                
                ClearErrors(); // clears any error messages incase of invalid input

                if (input == 'Q')
                {
                    cout << "Exiting game...\n";
                    return;
                }

                continue;
            }

            // Handle rolling phase
            dice.Roll(remainingDice);
            dice.Display(remainingDice);

            int scoringDiceUsed = 0;
            int rollScore = CalculateScore(dice.GetValues(), remainingDice, scoringDiceUsed);

            // Check for Farkle (no scoring dice)
            if (rollScore == 0)
            {
                cout << "\nFARKLE! No scoring dice.\n";
                cout << "You lose all points from this turn.\n";
                turnScore = 0;
                turnOver = true;

                cout << "\nPress any key to continue...";
                cin >> input;
            }
            else
            {
                turnScore += rollScore;

                cout << "\nRoll Score: " << rollScore << endl;
                cout << "Turn Score: " << turnScore << endl;

                remainingDice -= scoringDiceUsed;

                if (remainingDice < 0)
                {
                    remainingDice = 0;
                }

                if (remainingDice == 0)
                {
                    cout << "\nAll six dice scored!\n";
                    cout << "You must roll all six dice again.\n";
                    remainingDice = 6; // reset dice count
                    continue;
                }

                // Bank phase
                // Player chooses whether to bank points or continue rolling.
                // Banking adds turnScore to total score (if eligible)
                char choice;
                cout << "\nBank points or roll again? (B/R): ";
                cin >> choice;
                choice = toupper(choice);

                if (choice == 'B')
                {
                    if (!player.HasEnteredGame())
                    {
                        if (turnScore >= 1000)
                        {
                            player.SetEnteredGame(true);
                            player.AddScore(turnScore);

                            cout << "\nYou have entered the game!\n";
                            cout << "Total Score: " << player.GetScore() << endl;
                        }
                        else
                        {
                            cout << "\nYou need at least 1000 points in one turn to enter the game.\n";
                            cout << "No points were banked.\n";
                        }
                    }
                    else
                    {
                        player.AddScore(turnScore);
                        cout << "\nPoints banked!\n";
                        cout << "Total Score: " << player.GetScore() << endl;
                    }

                    turnOver = true;
                }
                else if (choice == 'R') // re roll
                {
                    input = 'R';
                }
                else
                {
                    cout << "Invalid choice. Turn continues.\n";
                    input = 'R';
                }
            }
        }

        if (player.GetScore() >= 10000)
        {
            cout << "\nCongratulations, " << player.GetName() << "!\n";
            cout << "You reached 10,000 points and won the game!\n";

            isPlaying = false;

            return;
        }
    }
}

void Game::LoadMenu() // triggers basic actions farkle, rules and quiting
{
	Menu menu;
	char choice;

	do
	{
        menu.ShowMainMenu();
        choice = menu.GetUserChoice();

        switch (toupper(choice))
        {
        case '1':
            // Start game
            Greet();
            Farkle();

            return;
            break;
        case '2':
            // Show rules
            ShowRules();
            break;
        case 'Q':
            cout << "Exiting game...\n";
            break;
        default:
            cout << "Invalid option.\n";
        }
	} 
	while (toupper(choice) != 'Q');

}

void Game::Launch()
{
	LoadMenu();
}

