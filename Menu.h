
#include <iostream>
#include <cstring>
#ifndef MENU_H
#define MENU_H

namespace sdds {
    const int maxOptions = 15;

    // Represents a simple text-based menu.
    class Menu {
        char* menuContent; // Pointer to the menu content

    public:
        // Constructor that initializes the menu with the given options.
        // If options are not provided (nullptr), the menu is considered empty.
        Menu(const char* options = nullptr);

        // Destructor to deallocate memory used for the menu content.
        ~Menu();

        // Displays the menu options and waits for the user to input a selection.
        int run() const;
    };
}


#endif
