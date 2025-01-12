
#include "AidMan.h"
#include "Perishable.h"
#include "Item.h"
#include "Utils.h"

namespace sdds {

// Member function to display the main menu and return user selection
int AidMan::menu() const {
    std::cout << "Aid Management System" << std::endl;      
    std::cout << "Date: " << Date() << std::endl;           
    std::cout << "Data file: ";
    
    // Check if fileName is nullptr and display accordingly
    if (fileName == nullptr) {                    
        std::cout << "No file" << std::endl;                
    } else {
        std::cout << fileName << std::endl;                 
    }
    
    std::cout << "---------------------------------" << std::endl;

    // Return the user's menu selection
    return mainMenu.run();
}

// Constructor for the AidMan class
AidMan::AidMan(const char* file) {
    // Default menu options
    const char* m_default = "List Items\tAdd Item\tRemove Item\tUpdate Quantity\tSort\tShip Items\tNew/Open Aid Database";
    
    // Create a new Menu object with default options
    new (&mainMenu) Menu(m_default);
    
    // Check if the file parameter is not nullptr
    if (file != nullptr) {                        
        // Allocate memory for fileName and copy the provided file name
        fileName = new char[strlen(file) + 1];    
        strcpy(fileName, file);                   
    } else {
        fileName = nullptr;  // Set fileName to nullptr if no file name is provided                     
    }
}

// Destructor for the AidMan class
AidMan::~AidMan() {
    // Deallocate memory for fileName
    delete[] fileName;                            
    
    // Deallocate memory for each iProduct object in the array
    for (int i = 0; i < numOfItems; i++) {
        delete iProductPointers[i];
    }
}

// Member function to allocate memory for fileName and copy the provided name
void AidMan::allocateAndCopy(const char* name) {
    // Deallocate existing memory for fileName
    delete[] fileName;                            

    // Check if the provided name is not nullptr
    if (name != nullptr) {                        
        // Allocate memory for fileName and copy each character
        fileName = new char[strlen(name) + 1];    
        for (int i = 0; i < (int)strlen(name) + 1; i++)
            fileName[i] = name[i];                
    } else {
        fileName = nullptr;  // Set fileName to nullptr if no name is provided                     
    }
}

// Member function to save data to a file
void AidMan::saveData() {                         
    // Check if fileName is not nullptr
    if (fileName != nullptr) {
        std::ofstream ofstr;  // Create an output file stream
        ofstr.open(fileName);  // Open the file with the given file name
        
        // Loop through each iProduct object and save data to the file
        for (int i = 0; i < numOfItems; i++) {
            iProductPointers[i]->save(ofstr);     
            ofstr << std::endl;                        
        }
    }
}


	// Member function to deallocate memory for iProduct objects
void AidMan::deallocateData() {
    for (int i = 0; i < numOfItems; i++) {
        delete iProductPointers[i];
    }
    numOfItems = 0;
}

// Member function to load data from a file
bool AidMan::loadData() {
    int select;
    char firstDigit;
    char name[50];
    int i = 0;

    // Save existing data
    saveData();
    numOfItems = 0;

    // Deallocate existing data
    deallocateData();

    std::cout << "Enter file name: ";
    std::cin >> name;

    // Allocate memory for fileName and copy the provided name
    allocateAndCopy(name);

    std::ifstream file;
    file.open(fileName);

    if (!file.is_open()) {
        // Display an error message if the file fails to open
        std::cout << "Failed to open " << fileName << " for reading!" << std::endl;
        std::cout << "Would you like to create a new data file?" << std::endl;
        std::cout << "1- Yes!" << std::endl;
        std::cout << "0- Exit" << std::endl;
        std::cout << "> ";

        // Prompt user for action (create a new file or exit)
        select = ut.getint(0, 1);
        if (select == 1) {
            // Create a new file if user chooses to
            std::ofstream out(fileName);
        } else {
            // Clean up and exit if user chooses not to create a new file
            delete[] fileName;
            fileName = nullptr;
        }
    } else {
        // Read data from the file
        while (!file.eof()) {
            firstDigit = file.peek();
            if (firstDigit == '1' || firstDigit == '2' || firstDigit == '3') {
                iProductPointers[numOfItems] = new Perishable;
            } else if (firstDigit == '4' || firstDigit == '5' || firstDigit == '6' || firstDigit == '7' || firstDigit == '8' || firstDigit == '9') {
                iProductPointers[numOfItems] = new Item;
            } else {
                // Set the failbit if the first digit is not valid
                file.setstate(std::ios::failbit);
            }

            if (file.good()) {
                // Load data for iProduct object
                iProductPointers[numOfItems]->load(file);

                if (file.good()) {
                    // Increment the count of loaded items
                    numOfItems++;
                } else {
                    // Clean up and delete the partially loaded iProduct object
                    delete iProductPointers[i];
                }
            }
        }
    }
    // Return true if items were loaded, false otherwise
    return numOfItems > 0 ? true : false;
}

// Member function to list items based on description
int AidMan::list(const char* sub_desc) {
    int i = 0, num = 0;
    char select;

    if (sub_desc == nullptr) {
        // Display the entire list if no description is provided
        if (numOfItems != 0) {
            // Display header for the list
            std::cout << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << std::endl;
            std::cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << std::endl;

            // Display each item in the list
            for (i = 0; i < numOfItems; i++) {
                std::cout.width(4);
                std::cout << i + 1 << " | ";
                iProductPointers[i]->linear(true);
                iProductPointers[i]->display(std::cout);
                std::cout << std::endl;
            }

            // Display footer for the list
            std::cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << std::endl;
            std::cout << "Enter row number to display details or <ENTER> to continue:" << std::endl;
            std::cout << "> ";

            // Handle user input to display details of a specific item
            std::cin.ignore(2000, '\n');
            select = std::cin.get();
            if (select != '\n') {
                num = (int)select - 48;
                iProductPointers[num - 1]->linear(false);
                iProductPointers[num - 1]->display(std::cout);
                std::cout << std::endl;
            }
            std::cout << std::endl;
        } else {
            // Display a message if the list is empty
            std::cout << "The list is empty!" << std::endl;
        }
    } else {
        // Display the filtered list based on the provided description
        // Display header for the filtered list
        std::cout << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << std::endl;
        std::cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << std::endl;

        // Display items that match the provided description
        for (i = 0; i < numOfItems; i++) {
            if (*iProductPointers[i] == sub_desc) {
                std::cout.width(4);
                std::cout << i + 1 << " | ";
                iProductPointers[i]->linear(true);
                iProductPointers[i]->display(std::cout);
                std::cout << std::endl;
                num++;
            }
        }

        // Display footer for the filtered list
        std::cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << std::endl;
    }
    // Return the count of items displayed
    return num;
}


	// Member function to search for an SKU and return its index in iProductPointers array
int AidMan::search(int sku) const {
    int i = 0;
    int index = -1;

    // Iterate through iProductPointers to find the SKU
    for (i = 0; i < numOfItems - 1; i++) {
        if (*iProductPointers[i] == sku) {
            index = i;
        }
    }
    return index;
}

// Member function to add a new item to the database
void AidMan::addItem() {
    int select, findSku;

    // Check if the database is full
    if (numOfItems >= sdds_max_num_items) {
        std::cout << "Database full!" << std::endl;
    } else {
        // Display menu for selecting item type
        std::cout << "1- Perishable" << std::endl;
        std::cout << "2- Non-Perishable" << std::endl;
        std::cout << "-----------------" << std::endl;
        std::cout << "0- Exit" << std::endl;
        std::cout << "> ";

        // Get user input for item selection
        std::cin >> select;

        if (select == 0) {
            // Exit if the user chooses to abort
            std::cout << "Aborted" << std::endl;
        } else if (select == 1) {
            // Create a new Perishable item
            iProductPointers[numOfItems] = new Perishable;
            findSku = iProductPointers[numOfItems]->readSku(std::cin);

            // Check if the SKU is already in the system
            if (search(findSku) == -1) {
                // Read data for the new item and increment the count
                iProductPointers[numOfItems]->read(std::cin);
                numOfItems++;
                saveData();
            } else {
                // Display a message if the SKU already exists and clean up
                std::cout << "Sku: " << findSku << " is already in the system, try updating quantity instead." << std::endl;
                delete iProductPointers[numOfItems];
            }
        } else if (select == 2) {
            // Create a new Non-Perishable item
            iProductPointers[numOfItems] = new Item;
            findSku = iProductPointers[numOfItems]->readSku(std::cin);

            // Check if the SKU is already in the system
            if (search(findSku) == -1) {
                // Read data for the new item and increment the count
                iProductPointers[numOfItems]->read(std::cin);
                numOfItems++;
                saveData();
            } else {
                // Display a message if the SKU already exists and clean up
                std::cout << "Sku: " << findSku << " is already in the system, try updating quantity instead." << std::endl;
                delete iProductPointers[numOfItems];
            }
        }
        std::cout << std::endl;
    }
}

// Member function to remove an item from the database
void AidMan::remove(int index) {
    int i, j = index + 1;

    // Delete the iProduct object at the specified index
    delete iProductPointers[index];

    // Shift the remaining items in the array to fill the gap
    for (i = index; i < numOfItems - 1; i++) {
        iProductPointers[i] = iProductPointers[j];
        j++;
    }

    // Decrement the count of items
    numOfItems--;
}

// Member function to remove an item interactively
void AidMan::removeItem() {
    char item[200];
    int sku, index, select;

    // Prompt user for item description
    std::cout << "Item description: ";
    std::cin >> item;

    // Check if any items match the description
    if (list(item) != 0) {
        // Prompt user for SKU
        std::cout << "Enter SKU: ";
        std::cin >> sku;

        // Search for the SKU in the database
        index = search(sku);

        if (index == -1) {
            // Display a message if SKU is not found
            std::cout << "SKU not found!";
        } else {
            // Display the item to be removed and confirm with the user
            std::cout << "Following item will be removed: " << std::endl;
            iProductPointers[index]->linear(false);
            iProductPointers[index]->display(std::cout);
            std::cout << std::endl;
            std::cout << "Are you sure?" << std::endl;
            std::cout << "1- Yes!" << std::endl;
            std::cout << "0- Exit" << std::endl;
            std::cout << "> ";

            // Get user confirmation
            select = ut.getint(0, 1);

            if (select == 1) {
                // Remove the item if the user confirms
                remove(index);
                saveData();
                std::cout << "Item removed!" << std::endl;
            } else {
                // Display an abort message if the user cancels
                std::cout << "Aborted!" << std::endl;
            }
            std::cout << std::endl;
        }
    }
}

// Member function to update the quantity of an item
void AidMan::updateQuantity() {
    char item[200];
    int sku, index, select, num;

    // Prompt user for item description
    std::cout << "Item description: ";
    std::cin >> item;

    // Check if any items match the description
    if (list(item) != 0) {
        // Prompt user for SKU
        std::cout << "Enter SKU: ";
        std::cin >> sku;

        // Search for the SKU in the database
        index = search(sku);

        if (index == -1) {
            // Display a message if SKU is not found
            std::cout << "SKU not found!";
        } else {
            // Display options for updating quantity
            std::cout << "1- Add" << std::endl;
            std::cout << "2- Reduce" << std::endl;
            std::cout << "0- Exit" << std::endl;
            std::cout << "> ";

            // Get user selection
            select = ut.getint(0, 2);

            if (select == 1) {
                // Add quantity if the user chooses option 1
                if (iProductPointers[index]->qtyNeeded() != iProductPointers[index]->qty()) {
                    num = ut.getint(1, iProductPointers[index]->qtyNeeded() - iProductPointers[index]->qty(), "Quantity to add: ");
                    *iProductPointers[index] += num;
                    saveData();
                    std::cout << num << " items added!" << std::endl;
                } else {
                    // Display a message if quantity needed is already fulfilled
                    std::cout << "Quantity Needed already fulfilled!" << std::endl;
                }
            } else if (select == 2) {
                // Reduce quantity if the user chooses option 2
                if (iProductPointers[index]->qty() != 0) {
                    num = ut.getint(1, iProductPointers[index]->qty(), "Quantity to reduce: ");
                    *iProductPointers[index] -= num;
                    saveData();
                    std::cout << num << " items removed!" << std::endl;
                } else {
                    // Display a message if quantity on hand is zero
                    std::cout << "Quantity on hand is zero!" << std::endl;
                }
            } else {
                // Display an abort message if the user cancels
                std::cout << "Aborted!" << std::endl;
            }
            std::cout << std::endl;
        }
    }
}


	// Member function to sort items based on quantity needed
void AidMan::sort() {
    iProduct* temp[1];
    int i, j;

    // Nested loops to perform bubble sort based on quantity needed
    for (i = 0; i < numOfItems; i++) {
        for (j = i + 1; j < numOfItems; j++) {
            // Compare items based on the difference between quantity needed and quantity on hand
            if (iProductPointers[i]->qtyNeeded() - iProductPointers[i]->qty() <
                iProductPointers[j]->qtyNeeded() - iProductPointers[j]->qty()) {
                // Swap pointers if the condition is met
                temp[0] = iProductPointers[i];
                iProductPointers[i] = iProductPointers[j];
                iProductPointers[j] = temp[0];
            }
        }
    }

    // Output a completion message and save data after sorting
    std::cout << "Sort completed!\n" << std::endl;
    saveData();
}

// Member function to generate a shipping order
void AidMan::shipItems() {
    int i, num = 0;

    // Open a file for writing the shipping order
    std::ofstream file;
    file.open("shippingOrder.txt");

    if (file.is_open()) {
        // Write header information to the file
        file << "Shipping Order, Date: " << Date() << std::endl;
        file << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << std::endl;
        file << "-----+-------+-------------------------------------+------+------+---------+-----------" << std::endl;

        // Iterate through items and create the shipping order
        for (i = 0; i < numOfItems; i++) {
            if (iProductPointers[i]->qtyNeeded() == iProductPointers[i]->qty()) {
                // Write item details to the file, increment counter, and remove item from the database
                file.width(4);
                file << num + 1 << " | ";
                iProductPointers[i]->linear(true);
                iProductPointers[i]->display(file);
                file << std::endl;
                num++;
                remove(i);
            }
        }

        // Write footer information to the file
        file << "-----+-------+-------------------------------------+------+------+---------+-----------" << std::endl;
        std::cout << "Shipping Order for " << num << " times saved!" << std::endl;
        std::cout << std::endl;

        // Save data and close the file
        saveData();
        file.close();
    }
}

// Member function to run the Aid Management System
void AidMan::run() {
    int selection = -1;

    // Main loop for user interaction
    while (selection != 0) {
        selection = menu();

        // Handle special case where the user tries to perform an operation without opening a database
        if (selection != 0 && selection != 7 && fileName == nullptr) {
            selection = 7;
        }

        // Switch statement to perform actions based on user selection
        switch (selection) {
            case 0:
                std::cout << "Exiting Program!" << std::endl;
                break;
            case 1:
                std::cout << std::endl << "****List Items****" << std::endl;
                list();
                break;
            case 2:
                std::cout << std::endl << "****Add Item****" << std::endl;
                addItem();
                break;
            case 3:
                std::cout << std::endl << "****Remove Item****" << std::endl;
                removeItem();
                break;
            case 4:
                std::cout << std::endl << "****Update Quantity****" << std::endl;
                updateQuantity();
                break;
            case 5:
                std::cout << std::endl << "****Sort****" << std::endl;
                sort();
                break;
            case 6:
                std::cout << std::endl << "****Ship Items****" << std::endl;
                shipItems();
                break;
            case 7:
                std::cout << std::endl << "****New/Open Aid Database****" << std::endl;
                if (loadData() == true) {
                    std::cout << numOfItems << " records loaded!" << std::endl << std::endl;
                }
                break;
        }
    }
}

}