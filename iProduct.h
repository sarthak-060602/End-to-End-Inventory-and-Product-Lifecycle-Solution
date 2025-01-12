
#ifndef IPRODUCT_H
#define IPRODUCT_H
#include <iostream>
#include <cstring>

namespace sdds {
	
    // Abstract class representing an interface for a product
    class iProduct {
    public:
        virtual ~iProduct(); // Virtual destructor for proper polymorphic destruction

        // Reads the SKU (Stock Keeping Unit) from the input stream
        virtual int readSku(std::istream& istr) = 0;

        // Reduces the quantity on hand by the given quantity
        virtual int operator-=(int qty) = 0;

        // Increases the quantity on hand by the given quantity
        virtual int operator+=(int qty) = 0;

        // Converts the product to a double value (typically for total cost calculation)
        virtual operator double() const = 0;

        // Converts the product to a boolean value (true if it has a valid state)
        virtual operator bool() const = 0;

        // Returns the quantity needed of the product
        virtual int qtyNeeded() const = 0;

        // Returns the quantity on hand of the product
        virtual int qty() const = 0;

        // Sets the display format for the product (linear or non-linear)
        virtual void linear(bool isLinear) = 0;

        // Saves the product to an output file stream
        virtual std::ofstream& save(std::ofstream& ofstr) const = 0;

        // Loads the product from an input file stream
        virtual std::ifstream& load(std::ifstream& ifstr) = 0;

        // Displays the product on an output stream
        virtual std::ostream& display(std::ostream& ostr) const = 0;

        // Reads the product from an input stream
        virtual std::istream& read(std::istream& istr) = 0;

        // Checks if the product has the given SKU
        virtual bool operator==(int sku) const = 0;

        // Checks if the product has the given description
        virtual bool operator==(const char* description) const = 0;
    };

    // Overloaded stream insertion operator to write a product to an output stream
    std::ostream& operator<<(std::ostream& ostr, const iProduct& obj);

    // Overloaded stream extraction operator to read a product from an input stream
    std::istream& operator>>(std::istream& istr, iProduct& obj);
}


#endif
