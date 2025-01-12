
#include "Menu.h"
#include "Utils.h"

namespace sdds {

	Menu::Menu(const char* options) {
    int count = 0;

    // Check if options are provided
    if (options != nullptr) {
        // Count the number of tabs to determine the number of menu options
        for (int i = 0; i < (int)strlen(options) + 1; i++) {
            if (options[i] == '\t') {
                count++;
            }
        }

        // If the number of options is within the allowed limit, allocate memory and copy options
        if (count + 1 <= maxOptions) {
            menuContent = new char[strlen(options) + 1];
            strcpy(menuContent, options);
        } else {
            menuContent = nullptr;
        }
    } else {
        menuContent = nullptr;
    }
}

Menu::~Menu() {
    // Deallocate memory used for menu content
    delete[] menuContent;
}

int Menu::run() const {
    int selection, i, count = 1;

    // Check if menu content is valid
    if (menuContent != nullptr) {
        std::cout << count << "- ";

        // Display menu options
        for (i = 0; i <= (int)strlen(menuContent); i++) {
            if (menuContent[i] == '\0') {
                std::cout << std::endl << "---------------------------------" << std::endl;
                std::cout << "0- Exit" << std::endl;
            } else if (menuContent[i] != '\t') {
                std::cout << menuContent[i];
            } else {
                std::cout << std::endl;
                std::cout << ++count << "- ";
            }
        }

        // Get user selection
        std::cout << "> ";
        selection = ut.getint(0, count);
    } else {
        // Display error for invalid menu
        std::cout << "Invalid Menu!" << std::endl;
        selection = 0;
    }

    return selection;
}

}