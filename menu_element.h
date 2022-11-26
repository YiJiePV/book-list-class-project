/**
 * Title:   Lab 3 - Menu class Declaration: menu_element.h
 *
 * Purpose: declares the class MenuElement, this represents each of the menu elements in the menu
 * Class:   CSC 2430 Winter 2022
 * Author:  Carlos R. Arias
 *
 * ***************************************************************************************
 * You can ADD to the class, but you cannot change or remove anything that is already here
 * ***************************************************************************************
 */


#ifndef MENU_ELEMENT_H
#define MENU_ELEMENT_H

#include <string>
using std::string;

class MenuElement {
    /**
     * Each menu element has:
     * _selectionOption, the text that the user needs to input to select this item
     * _menuText, the text that describes this menu item
     * _isSeparator, to determine whether this item is a separator or a normal menu item
     * See the descriptions of the methods in the implementation file.
     */
    string _selectionOption;
    string _menuText;
    bool _isSeparator;
public:
    MenuElement();
    MenuElement(size_t length, char separator);
    MenuElement(const string& selectionOption, const string& menuText);
    void SetSeparator(size_t length, char separator);
    void SetMenuElement(const string& selectionOption, const string& menuText);
    string GetSelectionOption()const;
    string GetMenuText()const;
    string ToString()const;
    size_t MenuElementWidth()const;
    bool IsSeparator()const;
};


#endif //MENU_ELEMENT_H
