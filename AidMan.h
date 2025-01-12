
#ifndef AIDMAN_H
#define AIDMAN_H
#include <iostream>
#include <cstring>
#include <fstream>
#include "Menu.h"
#include "iProduct.h"

namespace sdds {

	// Define a constant for the maximum number of items
	const int sdds_max_num_items = 100;

	// Forward declaration of the iProduct class
	class iProduct;

	// Declaration of the Menu class
	class Menu;

	// Declaration of the AidMan class
	class AidMan {
		// Private members of the AidMan class
		char* fileName;
		Menu mainMenu;
		iProduct* iProductPointers[sdds_max_num_items];
		int numOfItems;

		// Private member functions of the AidMan class
		int menu() const;
		void saveData();
		void deallocateData();
		bool loadData();
		void allocateAndCopy(const char* file);
		int list(const char* sub_desc = nullptr);
		int search(int sku) const;
		void addItem();
		void remove(int index);
		void removeItem();
		void updateQuantity();
		void sort();
		void shipItems();

	public:
		// Public member functions of the AidMan class

		// Constructor with an optional file parameter
		AidMan(const char* file = nullptr);

		// Destructor
		~AidMan();

		// Run method to start the execution of the program
		void run();
	};
} 


#endif
