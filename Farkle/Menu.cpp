#include "Menu.h"
#include <iostream>

using namespace std;

void Menu::ShowMainMenu() const
{
    ShowTitle();
    cout << "\n=== MENU ===\n";
    cout << "1. Start Game\n";
    cout << "2. View Rules\n";
    cout << "Q. Quit\n";
    cout << "\n===================\n\n";
    cout << "Select an option: \n";
}

char Menu::GetUserChoice() const
{
    char choice;
    cin >> choice;
    return choice;
}
void Menu::ShowTitle() const
{
    cout << R"(

 ________  ______   _______   __    __  __        ________ 
/        |/      \ /       \ /  |  /  |/  |      /        |
$$$$$$$$//$$$$$$  |$$$$$$$  |$$ | /$$/ $$ |      $$$$$$$$/ 
$$ |__   $$ |__$$ |$$ |__$$ |$$ |/$$/  $$ |      $$ |__    
$$    |  $$    $$ |$$    $$< $$  $$<   $$ |      $$    |   
$$$$$/   $$$$$$$$ |$$$$$$$  |$$$$$  \  $$ |      $$$$$/    
$$ |     $$ |  $$ |$$ |  $$ |$$ |$$  \ $$ |_____ $$ |_____ 
$$ |     $$ |  $$ |$$ |  $$ |$$ | $$  |$$       |$$       |
$$/      $$/   $$/ $$/   $$/ $$/   $$/ $$$$$$$$/ $$$$$$$$/ 
                                                                                                                                                                          
)";
}