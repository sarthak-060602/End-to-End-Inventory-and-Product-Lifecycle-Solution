
#ifndef ITEM_H
#define ITEM_H
#include <iostream>
#include <fstream>
#include <cstring>
#include "Status.h"
#include "iProduct.h"

namespace sdds {
	class Item : public iProduct {
	public:
        double m_price;         // Price of the item
        int m_qty;              // Quantity on hand
        int m_qtyNeeded;        // Quantity needed
        char* m_description;    // Description of the item
        bool m_linear;          // Flag indicating linear/non-linear display

	protected:
        Status m_state;         // State of the item (error message if any)
        int m_sku;              // SKU (Stock Keeping Unit) of the item
		bool isLinear();

	public:
        // Default constructor
        Item();

        // Destructor
        ~Item();

        // Copy constructor
        Item(const Item&);

        // Copy assignment operator
        Item& operator=(const Item&);

        // Conversion operator to double (returns the price)
        operator double() const;

        // Conversion operator to bool (checks if the item is valid)
        operator bool() const;

        // Returns the quantity needed
        int qtyNeeded() const;

        // Returns the quantity on hand
        int qty() const;

        // Overloaded subtraction-assignment operator (decreases quantity on hand)
        int operator-=(int qty);

        // Overloaded addition-assignment operator (increases quantity on hand)
        int operator+=(int qty);

        // Set the display format to linear or non-linear
        void linear(bool isLinear);

        // Clear the item's content
        void clear();

        // Overloaded equality operator (compares SKU with an integer)
        bool operator==(int sku) const;

        // Overloaded equality operator (compares description with a C-style string)
        bool operator==(const char* description) const;

        // Save the item to a file stream
        std::ofstream& save(std::ofstream& ofstr) const;

        // Load the item from a file stream
        std::ifstream& load(std::ifstream& ifstr);

        // Display the item on an output stream
        std::ostream& display(std::ostream& ostr) const;

        // Read the item from an input stream
        std::istream& read(std::istream& istr);

        // Read the SKU from an input stream
        int readSku(std::istream& istr);
    };
}

#endif
