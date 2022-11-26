//
// Created by Carlos R. Arias on 1/13/22.
//
/**
 * Title:   Lab 3 - Menu class Implementation: menu_element.cpp
 *
 * Purpose: Menu_element.cpp defines the constructor, accessors, mutators, and other methods to create, modify, and access a menu_element object,
 * whose data members are _selectionOption, _menuText, and _isSeparator.
 * Class:   CSC 2430 Winter 2022
 * Author:  Karena Qian
 */
#include "menu_element.h"

#include <string>

using std::string;

/**
 * Default constructor, sets _selectionOption and _menuText to empty strings and _isSeparator to false
 */
MenuElement::MenuElement() {
    _selectionOption = "";
    _menuText = "";
    _isSeparator = false;
}
/**
 * Client program is responsible for setting the length of the selectionOption in such a way
 * that it is always aligned with the menuText??????
 * @param selectionOption
 * @param menuText
 */
MenuElement::MenuElement(const string &selectionOption, const string &menuText){
    _selectionOption = selectionOption;
    _menuText = menuText;
    _isSeparator = false;
}
/**
 * Client program should set the length to:
 * length = selection options space + max(menu text) + 1
 * selection options space is the the whole space that will be used for the selection
 * option of the menus, that is the width of the field.
 * @param length how many separator characters will be used for the separator
 * @param separator the character that will be used to separate the menus
 */
MenuElement::MenuElement(size_t length, char separator){
    _isSeparator = true;
    SetSeparator(length, separator);
}
/**
 * Sets isSeparator to true to remember that this item is an actual separator. Then the _menuText is going
 * to be length repetitions of separator. (5, '*') --> *****
 * @param length
 * @param separator
 */
void MenuElement::SetSeparator(size_t length, char separator) {
    _isSeparator = true;
    _menuText.append(length, separator);
}
/**
 * Sets the menu element, what do you think is going to be the value of _isSeparator?
 * @param selectionOption the option that will be input by the user to select this option
 * @param menuText the text that shows the description of the option
 */
void MenuElement::SetMenuElement(const string &selectionOption, const string &menuText) {
    _isSeparator = false;
    _selectionOption = selectionOption;
    _menuText = menuText;
}

/**
 * Will always append a single whitespace between selectionOption and menuText
 * @return the selection option a space and then the menu text
 */
string MenuElement::ToString() const {
    return _selectionOption + " " + _menuText;
}

/**
 * Accessor will return the value of the selection option data member
 * @return _selectionOption data member
 */
string MenuElement::GetSelectionOption() const {
    return _selectionOption;
}

/**
 * Accessor will return the value of the menu text data member
 * @return _menuText data member
 */
string MenuElement::GetMenuText() const {
    return _menuText;
}

/**
 * This method will return the length of _selectionOption and _menuText + 1
 * @return the length of _selectionOption + " " + _menuText
 */
size_t MenuElement::MenuElementWidth() const {
    return (_selectionOption + " " + _menuText).length();
}

/**
 * Accessor will return the value of the is separator data member
 * @return _isSeparator data member
 */
bool MenuElement::IsSeparator() const {
    return _isSeparator;
}
