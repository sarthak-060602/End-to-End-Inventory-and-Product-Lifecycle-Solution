
#include <iostream>
#include <fstream>
#include <cstring>
#ifndef PERISHABLE_H
#define PERISHABLE_H
#include "Item.h"
#include "Date.h"

namespace sdds {

	class Perishable : public Item {
    char* m_handling;
    Date m_expiry;

public:
    // Default constructor
    Perishable();

    // Destructor
    ~Perishable();

    // Copy constructor
    Perishable(const Perishable&);

    // Copy assignment operator
    Perishable& operator=(const Perishable&);

    // Accessor function for the expiry date
    Date& expiry();

    // Read SKU from input stream
    int readSku(std::istream& istr);

    // Save object to output stream
    std::ofstream& save(std::ofstream& ofstr) const;

    // Load object from input stream
    std::ifstream& load(std::ifstream& ifstr);

    // Display object on output stream
    std::ostream& display(std::ostream& ostr) const;

    // Read object from input stream
    std::istream& read(std::istream& istr);
};

}

#endif
