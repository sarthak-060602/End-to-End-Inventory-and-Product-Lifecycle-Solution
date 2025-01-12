
#include "Item.h"
#include "Utils.h"

namespace sdds {

	bool Item::isLinear() {
    return m_linear; // Return the value of the m_linear flag
}

Item::Item() {
    m_price = 0;
    m_qty = 0;
    m_qtyNeeded = 0;
    m_description = nullptr;
    m_linear = false;
    m_sku = 0;
    m_state.clear(); // Clear the state of the item
}

Item::~Item() {
    delete[] m_description; // Release memory allocated for the description
}

Item::operator double() const {
    return m_price; // Conversion operator returning the price as a double
}

Item::operator bool() const {
    return bool(m_state); // Conversion operator returning true if the item has a state message
}

int Item::qtyNeeded() const {
    return m_qtyNeeded; // Return the quantity needed
}

int Item::qty() const {
    return m_qty; // Return the quantity on hand
}

int Item::operator-=(int qty) {
    return m_qty -= qty; // Subtract a quantity from the current quantity on hand
}

int Item::operator+=(int qty) {
    return m_qty += qty; // Add a quantity to the current quantity on hand
}

void Item::linear(bool isLinear) {
    m_linear = isLinear; // Set the display format to linear or non-linear
}

void Item::clear() {
    m_state.clear(); // Clear the state of the item
}

bool Item::operator==(int sku) const {
    return m_sku == sku; // Compare the SKU with an integer
}

bool Item::operator==(const char* description) const {
    bool result = false;
    if (description != nullptr || m_description != nullptr) { // Check if both descriptions are not null
        if (strstr(m_description, description) != nullptr) { // Check if the provided description is a substring
            result = true; // Set the result to true
        }
    }
    return result; // Return the result of the comparison
}

std::ofstream& Item::save(std::ofstream& ofstr) const {
    if (this) { // Check if the item is valid
        ofstr.precision(2); // Set precision for floating-point output
        ofstr.setf(std::ios::fixed); // Set fixed-point notation
        ofstr << m_sku << '\t' << m_description << '\t' << m_qty << '\t' << m_qtyNeeded << '\t' << m_price; // Save item data to the output stream
    }
    return ofstr; // Return the output stream
}

std::ifstream& Item::load(std::ifstream& ifstr) {
    char newDescription[500]; // Temporary array for reading a new description from the file

    if (!ifstr) { // Check if the input file stream is in a valid state
        m_state = "Input file stream read failed!"; // Set an error message in the item's state
    } else {
        ifstr >> m_sku; // Read SKU from the file
        ifstr.ignore();
        ifstr.get(newDescription, 500, '\t'); // Read description from the file
        delete[] m_description; // Release memory allocated for the current description
        if (newDescription != nullptr) {
            m_description = new char[strlen(newDescription) + 1]; // Allocate memory for the new description
            strcpy(m_description, newDescription); // Copy the new description
        }
        ifstr.ignore();
        ifstr >> m_qty; // Read quantity on hand from the file
        ifstr.ignore();
        ifstr >> m_qtyNeeded; // Read quantity needed from the file
        ifstr.ignore();
        ifstr >> m_price; // Read price from the file
        ifstr.ignore();
    }

    return ifstr; // Return the input stream
}


	std::ostream& Item::display(std::ostream& ostr) const {
    int i;
    double neededAmount = 0.00;

    if (m_description != nullptr) { // Check if the item has a valid description
        if (m_linear == true) { // Display in linear format
            ostr.width(4);
            ostr << m_sku << " | ";
            if (strlen(m_description) > 35) { // Truncate long descriptions
                for (i = 0; i < 35; i++) {
                    ostr << m_description[i];
                }
                ostr << " | ";
            } else {
                ostr.setf(std::ios::left);
                ostr.width(35);
                ostr << m_description << " | ";
            }
            ostr.unsetf(std::ios::left);
            ostr.width(4);
            ostr << m_qty << " | ";
            ostr.width(4);
            ostr << m_qtyNeeded << " | ";
            ostr.width(7);
            ostr.precision(2);
            ostr.setf(std::ios::fixed);
            ostr << m_price << " |";
        } else { // Display in non-linear format
            ostr << "AMA Item:" << std::endl;
            ostr << m_sku << ": " << m_description << std::endl;
            ostr << "Quantity Needed: " << m_qtyNeeded << std::endl;
            ostr << "Quantity Available: " << m_qty << std::endl;
            ostr.precision(2);
            ostr.setf(std::ios::fixed);
            ostr << "Unit Price: $" << m_price << std::endl;
            if (m_qtyNeeded > m_qty) {
                neededAmount = (m_qtyNeeded - m_qty) * m_price;
            }
            ostr.precision(2);
            ostr.setf(std::ios::fixed);
            ostr << "Needed Purchase Fund: $" << neededAmount << std::endl;
        }
    } else {
        ostr << m_state; // Display the item's state if description is invalid
    }
    return ostr;
}

std::istream& Item::read(std::istream& istr) {
    char newDescription1[500];
    char newDescription2[500];
    double num;
    bool valid = false;

    delete[] m_description; // Release memory for the current description
    clear(); // Clear the item's state

    std::cout << "AMA Item:" << std::endl;
    std::cout << "SKU: " << m_sku << std::endl;

    std::cout << "Description: ";
    istr >> newDescription1;
    istr.getline(newDescription2, 500);
    strcat(newDescription1, newDescription2);
    if (newDescription1 != nullptr) {
        m_description = new char[strlen(newDescription1) + 1]; // Allocate memory for the new description
        strcpy(m_description, newDescription1); // Copy the new description
    }

    m_qtyNeeded = ut.getint(1, 9999, "Quantity Needed: "); // Read and validate the quantity needed
    m_qty = ut.getint(0, m_qtyNeeded, "Quantity On Hand: "); // Read and validate the quantity on hand
    std::cout << "Unit Price: $";

    do {
        while (!valid) {
            istr >> num;
            if (istr.fail()) {
                std::cout << "Invalid number, retry: ";
                istr.clear();
                istr.ignore(2000, '\n');
            } else {
                valid = true;
            }
        }
        if (num < 0.0 || num > 9999.0) {
            std::cout << "Value out of range [" << "0.00" << "<=val<=" << "9999.00" << "]: ";
            valid = false;
        }
    } while (num < 0.0 || num > 9999.0);
    m_price = num; // Read and validate the price
    if (!istr) {
        m_state = "Console entry failed!"; // Set an error message in the item's state if console entry fails
    }
    return istr;
}


	int Item::readSku(std::istream& istr) {
    m_sku = ut.getint(40000, 99999, "SKU: "); // Read and validate the SKU
    return m_sku;
}

Item& Item::operator=(const Item& obj) {
    if (this != &obj) { // Check for self-assignment
        m_price = obj.m_price; // Copy price
        m_qty = obj.m_qty; // Copy quantity
        m_qtyNeeded = obj.m_qtyNeeded; // Copy quantity needed
        m_linear = obj.m_linear; // Copy linearity
        m_state = obj.m_state; // Copy item state
        m_sku = obj.m_sku; // Copy SKU

        delete[]  m_description; // Deallocate memory for the current description
        if (obj.m_description != nullptr) { // Check if the source object has a valid description
            m_description = new char[strlen(obj.m_description) + 1]; // Allocate memory for the new description
            for (int i = 0; i < (int)strlen(obj.m_description) + 1; i++)
                m_description[i] = obj.m_description[i]; // Copy the new description
        } else {
            m_description = nullptr; // Set the description to nullptr if the source object has an invalid description
        }
    }
    return *this;
}

Item::Item(const Item& obj) {
    if (obj) { // Check if the source object is valid
        m_price = obj.m_price; // Copy price
        m_qty = obj.m_qty; // Copy quantity
        m_qtyNeeded = obj.m_qtyNeeded; // Copy quantity needed
        m_linear = obj.m_linear; // Copy linearity
        m_state = obj.m_state; // Copy item state
        m_sku = obj.m_sku; // Copy SKU

        if (obj.m_description != nullptr) { // Check if the source object has a valid description
            m_description = new char[strlen(obj.m_description) + 1]; // Allocate memory for the new description
            for (int i = 0; i < (int)strlen(obj.m_description) + 1; i++)
                m_description[i] = obj.m_description[i]; // Copy the new description
        } else {
            m_state = "Input file stream read failed!"; // Set an error message if the source object has an invalid description
            m_description = nullptr; // Set the description to nullptr
        }
    }
}
}