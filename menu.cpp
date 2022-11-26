/**
 * Title:   Lab 3 - Menu class Implementation: menu.cpp
 *
 * Purpose: Menu_element.cpp defines the constructors, destructor, accessors, mutators, and other methods to create, modify, access, and run a menu object,
 * whose data members are _menuElements, _menuTitle, _numberOfOptions, _output, _errorStream, _input, _inputType, _errorMessage, _invalidMessage, and _menuOptionsWidth
 * Class:   CSC 2430 Winter 2022
 * Author:  Karena Qian
 */


#include "menu.h"
#include <cctype>
using std::isdigit;
using std::endl;

/**
 * The Menu constructor. Notice there is no default constructor. Notice that three streams can be sent to this
 * constructor, they will set _output, _input and _errorStream respectively. When you want to output something to
 * the screen you will use _output. For example:
 * _output << _menuTitle << endl;
 * That statement would send the title of the menu to whatever output stream has be set, by default cout.
 * @param numberOfOptions the number of options the menu will have, remember to include the separators
 * @param output the stream that will be used to send the normal output, by default cout
 * @param input the stream that will be used to receive the normal input, by default cin
 * @param errorStream the stream that will be used to send error output, by default cerr
 */
Menu::Menu(int numberOfOptions, ostream &output, istream &input, ostream &errorStream):
        _numberOfOptions(numberOfOptions),
        _output(output),
        _input(input),
        _errorStream(errorStream){

    _menuElements = new MenuElement[_numberOfOptions];
    _inputType = INT; // default
    _menuOptionsWidth = 0;

    // This method is incomplete, you still need to write some code here!
}
/**
 * Class destructor, in charge of cleaning the memory
 */
Menu::~Menu() {
    delete[] _menuElements;
}
/**
 * Finds the maximum length of all menu options, the purpose is to be able to find how many
 * characters are needed for the separators
 * @return the length of the largest menu option (includes option and text)
 */
size_t Menu::MaxMenuLength() const {
    size_t max = 0;
    for(int i = 0; i < _numberOfOptions; i++){
        if(_menuElements[i].MenuElementWidth() > max){
            max = _menuElements[i].MenuElementWidth();
        }
    }
    return max;
}

/**
 * Sets the error message
 * @param errorMessage The error message when the user inputs a string when a number is expected
 */
void Menu::SetErrorMessage(const string &errorMessage) {
    _errorMessage = errorMessage;
}

/**
 * Sets the invalid option error message
 * @param invalidMessage The error message when the user inputs an option that is not in the menu
 */
void Menu::SetInvalidOption(const string &invalidMessage) {
    _invalidMessage = invalidMessage;
}

/**
 * Sets the input type of the Menu
 * @param type What kind of input the Menu will have, see line 33 to see the available options
 */
void Menu::SetInputType(InputType type) {
    _inputType = type;
}

/**
 * Sets the title of the Menu
 * @param title menu title
 */
void Menu::SetTitle(const string &title) {
    _menuTitle = title;
}

/**
 * Gets the Error Message
 * @return The error message when the user inputs a string when a number is expected
 */
string Menu::GetErrorMessage() const {
    return _errorMessage;
}

/**
 * Gets the Invalid Option error Message
 * @return The error message when the user inputs an option that is not in the menu
 */
string Menu::GetInvalidOption() const {
    return _invalidMessage;
}

/**
 * Gets the input type
 * @return What kind of input the Menu will have, see line 33 to see the available options
 */
InputType Menu::GetInputType() const {
    return _inputType;
}

/**
 * Gets the title
 * @return menu title
 */
string Menu::GetTitle() const {
    return _menuTitle;
}

/**
 * This method is to add options to the menu. If the user sends an invalid optionNumber the method will return INVALID_MENU_INDEX. Users of this method
 * should never use as displayOption 99 or E, since they are reserved values for exiting.
 * @param optionNumber the slot where the menu is to be added. This represents the position in the array, the method needs to validate that it is a valid position 0<=optionNumber<_numberOfOptions
 * @param displayOption what the user needs to input to select a given menu option
 * @param menuOption the actual text that will be display as a menu option
 * @return INVALID_MENU_INDEX if optionNumber is greater than or equal than numberOfOptions, OVERWROTE_OPTION if there was something already in that array position, the optionNumber otherwise
 */
int Menu::AddMenuOption(unsigned int optionNumber, const string &displayOption, const string &menuOption) {
    if(optionNumber >= _numberOfOptions || optionNumber < 0){
        return INVALID_MENU_INDEX;
    }
    else{
        if(!_menuElements[optionNumber].GetMenuText().empty()){
            _menuElements[optionNumber].SetMenuElement(displayOption, menuOption);
            return OVERWROTE_OPTION;
        }
        else{
            _menuElements[optionNumber].SetMenuElement(displayOption, menuOption);
            return static_cast<int>(optionNumber);
        }
    }
}

/**
 * This method adds a separator to the menu. The method will need to call MaxMenuLength to see how big the separator needs to be and set the separator character to '-'.
 * If the user sends an invalid separatorPosition the method will return INVALID_MENU_INDEX
 * @param separatorPosition the slot position where the separator is going to be stored. The method needs to validate that it is a valid position 0<=separatorPosition<numberOfOptions
 * @return INVALID_MENU_INDEX if separatorPosition >= _numberOfOptions, OVERWROTE_OPTION if the slot had something already in that position, separatorPosition otherwise
 */
int Menu::AddSeparator(unsigned int separatorPosition) {
    _menuOptionsWidth = MaxMenuLength();
    if(separatorPosition >= _numberOfOptions || separatorPosition < 0){
        return INVALID_MENU_INDEX;
    }
    else{
        if(!_menuElements[separatorPosition].GetMenuText().empty()){
            _menuElements[separatorPosition].SetSeparator(_menuOptionsWidth, '-');
            return OVERWROTE_OPTION;
        }
        else{
            _menuElements[separatorPosition].SetSeparator(_menuOptionsWidth, '-');
            return static_cast<int>(separatorPosition);
        }
    }
}

//Private helper method for Run()
/**
 * This method is to find the given string userInput in the _menuElements array.
 * The method will return the index of the appropriate menu element with the correct selection option, if it exists.
 * Otherwise, it will return -1 to indicate an error in the input.
 * @param userInput: a string inputted by the user representing a selection option
 * @return the index of the menu element corresponding to the user input if found, otherwise -1 to indicate error
 */
int Menu::findElementInArray(const string& userInput) const {
    for(int i = 0; i < _numberOfOptions; i++){
        if(_menuElements[i].GetSelectionOption() == userInput){
            return i;
        }
    }
    return -1;
}

/**
 * This is the main driver of the class! This method will do the following operations:
 * 1. Output the Title
 * 2. Show all the menu options and separators
 * 3. Wait for the user to input the selection
 * 4. Return the user selection, or error appropriately
 * Remember you are outputting to _output, you are reading from _input and you are sending errors to _errorStream!
 * Furthermore, you will need to check what type of input the menu has, depending on that you will read numbers, a character or string.
 *      If your _inputType is INT and the user inputs a letter (or something that is not a number) then Run will return INPUT_ERROR
 *      If your _inputType is INT and the user inputs a number that is not an available option then run will return INVALID_INPUT
 *      If your _inputType is CHAR and the user inputs a string of more than one letter then Run will return INPUT_ERROR
 *      If your _inputType is CHAR and the user inputs a letter that is not an available option then run will return INVALID_INPUT
 *      If your _inputType is STRING and the user inputs a string that is not an available option then run will return INVALID_INPUT
 * @return the slot where the option has been stored (see optionNumber in AddMenuOption), if there is an error it will return the error value as noted above.
 */
int Menu::Run() const {
    string userInput;
    int optionNumber;
    bool inputError = false;
    bool invalidInput = false;

    //output title
    _output << _menuTitle << "\n";

    //output menu
    for(int i = 0; i < _numberOfOptions; i++){
        _output << _menuElements[i].ToString() << "\n";
    }
    //output exit option
    if(_inputType == INT){
        _output << "99 Exit\n";
    }
    else{
        _output << "Type E to Exit\n";
    }

    //get user input
    _input >> userInput;
    optionNumber = findElementInArray(userInput);

    //check for exit first
    if((_inputType == INT && userInput == "99") || ((_inputType == STRING || _inputType == CHAR) && userInput == "E")){
        return EXIT;
    }

    //check for errors:
    //user entered a single char:
    if(userInput.length() == 1){
        char character = userInput[0];
        //If your _inputType is INT
        if(_inputType == INT){
            //and the user inputs a letter (or something that is not a number) then Run will return INPUT_ERROR
            if(!isdigit(character)){
                inputError = true;
            }
        }
    }
        //user entered a whole string:
    else{
        //If your _inputType is INT and the user inputs a letter (or something that is not a number) then Run will return INPUT_ERROR
        //If your _inputType is CHAR and the user inputs a string of more than one letter then Run will return INPUT_ERROR
        if(_inputType == INT || _inputType == CHAR){
            inputError = true;
        }
    }
    //if type of input is correct:
    //If your _inputType is INT and the user inputs a number that is not an available option then run will return INVALID_INPUT
    //If your _inputType is CHAR and the user inputs a letter that is not an available option then run will return INVALID_INPUT
    //If your _inputType is STRING and the user inputs a string that is not an available option then run will return INVALID_INPUT
    if(optionNumber == -1){
        invalidInput = true;
    }

    //output and return as needed
    if(inputError){
        _errorStream << _errorMessage << endl;
        return INPUT_ERROR;
    }
    else if(invalidInput){
        _errorStream << _invalidMessage << endl;
        return INVALID_INPUT;
    }

    return optionNumber;

// This method is the driver of your class!
}


