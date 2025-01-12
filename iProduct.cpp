
#include "iProduct.h"
namespace sdds {
    // Destructor for the abstract iProduct class
    iProduct::~iProduct() {
    }

    // Overloaded stream insertion operator to write a product to an output stream
    std::ostream& operator<<(std::ostream& ostr, const iProduct& obj) {
        obj.display(ostr);      
        return ostr;
    }

    // Overloaded stream extraction operator to read a product from an input stream
    std::istream& operator>>(std::istream& istr, iProduct& obj) {
        obj.read(istr);         
        return istr;
    }
}
