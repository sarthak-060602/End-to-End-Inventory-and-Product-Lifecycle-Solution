
#ifndef DATE_H
#define DATE_H
#include "Status.h"
#include <iostream>
#include <cstring>

namespace sdds {

	// Maximum valid year for the Date class
	const int maxYear = 2030;

	// Class representing a Date
	class Date {
		int year;           // Year of the date
		int month;          // Month of the date
		int day;            // Day of the date
		Status m_state;     // Status of the date (Valid, Invalid, Error)
		bool format;        // Flag indicating the display format

		// Private member functions
		bool validate();            // Validates the date
		int unique() const;         // Generates a unique integer based on the date
		int stringToInt(char* str); // Converts a string to an integer
		bool validDigit(char* str); // Checks if the characters in a string are valid digits

	public:
		// Constructors and Destructor
		Date();                                // Default constructor
		Date(int newYear, int newMonth, int newDay); // Parameterized constructor
		~Date();                               // Destructor
		Date(const Date&);                     // Copy constructor
		Date& operator=(const Date&);          // Copy assignment operator

		// Comparison operators
		bool operator==(const Date& obj) const;
		bool operator!=(const Date& obj) const;
		bool operator<(const Date& obj) const;
		bool operator>(const Date& obj) const;
		bool operator<=(const Date& obj) const;
		bool operator>=(const Date& obj) const;

		// Member functions
		Status& state();                    // Accessor for the date's status
		Date& formatted(bool format);      // Setter for the display format
		operator bool() const;             // Conversion operator to bool
		std::ostream& write(std::ostream& os) const; // Writes the date to an output stream
		std::istream& read(std::istream& is);        // Reads the date from an input stream
	};

	// Non-member functions
	std::ostream& operator<<(std::ostream& os, const Date& obj); // Overloaded insertion operator
	std::istream& operator>>(std::istream& is, Date& obj);       // Overloaded extraction operator

};


#endif
