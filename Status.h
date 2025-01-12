
#include <iostream>
#include <cstring>
#ifndef STATUS_H
#define STATUS_H

namespace sdds {
	
	class Status {
    char* objStatus;
    int statusCode;

public:
    // Default constructor
    Status();

    // Destructor
    ~Status();

    // Constructor with char pointer parameter
    Status(const char* obj);

    // Copy assignment operator
    Status& operator=(const Status&);

    // Assignment operator with integer parameter
    Status& operator=(int newValue);

    // Assignment operator with char pointer parameter
    Status& operator=(const char* newStatus);

    // Conversion operator to int
    operator int() const;

    // Conversion operator to const char*
    operator const char* () const;

    // Conversion operator to bool
    operator bool() const;

    // Clear the status
    Status& clear();
};

// Overloaded stream insertion operator
std::ostream& operator<<(std::ostream& os, const Status& obj);

};

#endif
