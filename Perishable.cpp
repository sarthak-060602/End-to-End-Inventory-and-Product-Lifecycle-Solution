
#include "Perishable.h"
#include "Utils.h"

namespace sdds {

	Perishable::Perishable() {
    m_handling = nullptr; // Initialize handling to nullptr
    new (&m_expiry) Date(); // Placement new for Date object
}

Perishable::~Perishable() {
    delete[] m_handling; // Release dynamic memory for handling
}

Perishable::Perishable(const Perishable& obj) : Item(obj) {
    if (obj) {
        m_expiry = obj.m_expiry; // Copy expiry date

        if (obj.m_handling != nullptr) {
            m_handling = new char[strlen(obj.m_handling) + 1]; // Allocate memory for handling
            strcpy(m_handling, obj.m_handling); // Copy handling information
        } else {
            m_handling = nullptr; // Set handling to nullptr
        }
    }
}

Perishable& Perishable::operator=(const Perishable& obj) {
    if (this != &obj) {
        m_expiry = obj.m_expiry; // Copy expiry date
        (Item&)*this = obj; // Copy base class part

        delete[] m_handling; // Release existing handling information

        if (obj.m_handling != nullptr) {
            m_handling = new char[strlen(obj.m_handling) + 1]; // Allocate memory for handling
            strcpy(m_handling, obj.m_handling); // Copy handling information
        } else {
            m_handling = nullptr; // Set handling to nullptr
        }
    }
    return *this;
}

Date& Perishable::expiry() {
    return m_expiry; // Return reference to expiry date
}

int Perishable::readSku(std::istream& istr) {
    m_sku = ut.getint(10000, 39999, "SKU: "); // Read and validate SKU
    return m_sku;
}

	std::ofstream& Perishable::save(std::ofstream& ofstr) const {
    const_cast<Date&>(m_expiry).formatted(false); // Set date format to non-linear
    Item::save(ofstr); // Call base class save function

    if (m_handling != nullptr) {
        ofstr << '\t' << m_handling << '\t'; // Save handling information if available
        m_expiry.write(ofstr); // Save expiry date
    } else {
        ofstr << '\t' << '\t'; // Save empty field for handling information
        m_expiry.write(ofstr); // Save expiry date
    }
    return ofstr;
}

std::ifstream& Perishable::load(std::ifstream& ifstr) {
    char newHandling[500];

    Item::load(ifstr); // Call base class load function

    if (ifstr.peek() != '\t') {
        ifstr.get(newHandling, 500, '\t'); // Read handling information if available
        delete[] m_handling;
        if (newHandling != nullptr) {
            m_handling = new char[strlen(newHandling) + 1];
            strcpy(m_handling, newHandling);
        }
    } else {
        delete[] m_handling;
        m_handling = nullptr;
    }

    if (ifstr.peek() != '\t') {
        m_state = "Input file stream read (perishable) failed!";
        ifstr.ignore(2000, '\n');
    } else {
        ifstr.ignore(); // Ignore the tab character
        m_expiry.read(ifstr); // Read expiry date
    }
    return ifstr;
}

std::ostream& Perishable::display(std::ostream& ostr) const {
    const_cast<Date&>(m_expiry).formatted(true); // Set date format to linear
    if (!this) {
        ostr << m_state; // Display error message if object is in an invalid state
    } else {
        if (m_linear == true) {
            Item::display(ostr); // Call base class display function
            if (m_handling != nullptr && m_handling[0] != '\0') {
                ostr << "*"; // Display asterisk if handling information is available
            } else {
                ostr << " "; // Display space if no handling information
            }
            m_expiry.write(ostr); // Display expiry date
        } else {
            ostr << "Perishable ";
            Item::display(ostr); // Call base class display function
            ostr << "Expiry date: ";
            ostr << m_expiry << std::endl; // Display expiry date
            if (m_handling != nullptr && m_handling[0] != '\0') {
                ostr << "Handling Instructions: " << m_handling << std::endl; // Display handling information
            }
        }
    }
    return ostr;
}

std::istream& Perishable::read(std::istream& istr) {
    char newHandling[500];

    Item::read(istr); // Call base class read function
    delete[] m_handling;
    m_handling = nullptr;

    istr.ignore(); // Ignore newline character
    std::cout << "Expiry date (YYMMDD): ";
    istr >> m_expiry; // Read and validate expiry date
    std::cout << "Handling Instructions, ENTER to skip: ";
    istr.get(newHandling, 500, '\n'); // Read handling information
    if (newHandling[0] != '\0') {
        if (newHandling != nullptr) {
            m_handling = new char[strlen(newHandling) + 1];
            strcpy(m_handling, newHandling); // Copy handling information
        }
    }
    if (!istr) {
        m_state = "Perishable console date entry failed!"; // Display error message if input fails
    }
    istr.ignore(2000, '\n'); // Ignore remaining characters in the input buffer
    return istr;
}

};