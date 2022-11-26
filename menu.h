/**
 * Title:   Lab 3 - Menu class Declaration: menu.h
 *
 * Purpose: declares the class Menu and some constants necessary for the program
 * Class:   CSC 2430 Winter 2022
 * Author:  Carlos R. Arias
 *
 * ***************************************************************************************
 * You can ADD to the class, but you cannot change or remove anything that is already here
 * ***************************************************************************************
 */



#ifndef MENU_H
#define MENU_H

#include "menu_element.h"

#include <string>
#include <iostream>
using std::string;
using std::ostream;
using std::istream;
using std::cin;
using std::cout;
using std::cerr;

// Constants used for the Menu workings
const int EXIT = -1;                // Run returns this when the user wants to exit
const int INPUT_ERROR = -2;         // Run returns this when the user inputs a string when a number is expected
const int INVALID_INPUT = -3;       // Run returns this when the user inputs an option that is not in the menu
const int ERROR = -4;               // Run returns this when the optionType is neither INT, CHAR or STRING (not needed)
const int OVERWROTE_OPTION = -5;    // AddSeparator or AddMenuOption return this when overwriting on a given position
const int INVALID_MENU_INDEX = -6;  // AddSeparator or AddMenuOption return this when the slot is not a valid array index

enum InputType {CHAR, INT, STRING}; // Creates a type InputType to define the kind of input the menu will have

class Menu {
private:
    MenuElement* _menuElements;     // The pointer to point to the array of MenuElements
    string _menuTitle;              // Menu Title
    int _numberOfOptions;           // Number of Options, remember that separators count as options
    ostream& _output;               // The output stream, by default is cout, but it could be something else (see test)
    ostream& _errorStream;          // The error stream, by default is cerr, but it could be something else (see test)
    istream& _input;                // The input stream, by default is cin, but it could be something else (see test)
    InputType _inputType;           // What kind of input the Menu will have, see line 33 to see the available options
    string _errorMessage;           // The error message when the user inputs a string when a number is expected
    string _invalidMessage;         // The error message when the user inputs an option that is not in the menu
    size_t _menuOptionsWidth;       // remembers the max width to be used for the menu options
    size_t MaxMenuLength()const;    // Checks all the MenuElements that are not separators and gets the maximum length
    int findElementInArray(const string& userInput)const; //Finds the given user selection option in _menuElements
public:

    Menu(int numberOfOptions, ostream& output = cout, istream& input = cin, ostream& errorStream = cerr);

    ~Menu();
    void SetErrorMessage(const string& errorMessage);
    void SetInvalidOption(const string& invalidMessage);
    void SetInputType(InputType type);
    void SetTitle(const string& title);
    string GetErrorMessage()const;
    string GetInvalidOption()const;
    InputType GetInputType()const;
    string GetTitle()const;
    int AddMenuOption(unsigned int optionNumber, const string& displayOption, const string& menuOption);
    int AddSeparator(unsigned int separatorPosition);
    int Run()const;

};


#endif //MENU_H
