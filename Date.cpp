
#include "Date.h"
#include "Status.h"
#include "Utils.h"

namespace sdds {

	bool Date::validate() {
    // Function to validate the date components (year, month, day)
    // Returns true if the date is valid, false otherwise
    bool result = false;

    // Check if the year is within a valid range
    if (year < 2023 || year > maxYear) { 
        m_state = "Invalid year in date";
        m_state = 1;
    } 
    // Check if the month is within a valid range
    else if (month < 1 || month > 12) {  
        m_state = "Invalid month in date";
        m_state = 2;
    } 
    // Check if the day is within a valid range for the given month and year
    else if (day < 1 || day > ut.daysOfMon(month, year)) { 
        m_state = "Invalid day in date";
        m_state = 3;
    } 
    // If all components are valid, clear the status and set the result to true
    else {
        m_state.clear();
        result = true;
    }

    return result;
}

int Date::unique() const {
    // Function to generate a unique integer based on the date components
    // Uses a simple calculation to create a unique value
    return year * 372 + month * 31 + day; 
}

Date::Date() {
    // Default constructor
    // Initializes the date with the current system date and sets the format to true
    ut.getSystemDate(&year, &month, &day);
    validate();
    format = true;
}

Date::Date(int newYear, int newMonth, int newDay) {
    // Parameterized constructor
    // Initializes the date with the specified year, month, and day, and sets the format to true
    year = newYear;
    month = newMonth;
    day = newDay;
    validate();
    format = true;
}


	Date::~Date() {
    // Destructor to clear the status
    m_state.clear();                  
}

bool Date::operator==(const Date& obj) const {
    // Equality operator to compare the unique values of two dates
    return unique() == obj.unique();  
}

bool Date::operator!=(const Date& obj) const {
    // Inequality operator to compare the unique values of two dates
    return unique() != obj.unique();  
}

bool Date::operator<(const Date& obj) const {
    // Less than operator to compare the unique values of two dates
    return unique() < obj.unique();   
}

bool Date::operator>(const Date& obj) const {
    // Greater than operator to compare the unique values of two dates
    return unique() > obj.unique();   
}

bool Date::operator<=(const Date& obj) const {
    // Less than or equal to operator to compare the unique values of two dates
    return unique() <= obj.unique();  
}

bool Date::operator>=(const Date& obj) const {
    // Greater than or equal to operator to compare the unique values of two dates
    return unique() >= obj.unique();  
}

Status& Date::state() {
    // Accessor function to retrieve the status of the date
    return m_state;
}

Date& Date::formatted(bool newFormat) {
    // Function to set the date format
    format = newFormat;               
    return *this;
}

Date::operator bool() const {
    // Conversion operator to check the validity of the date
    return (const char*)(m_state);
}

std::ostream& Date::write(std::ostream& os) const {
    // Function to write the date to an output stream based on the selected format
    if (format == true) {
        os << year << "/";
        os.width(2);
        os.fill('0');
        os << month << "/";
        os.width(2);
        os.fill('0');
        os << day;
    } else {
        os << year - 2000;
        os.width(2);
        os.fill('0');
        os << month;
        os.width(2);
        os.fill('0');
        os << day;
    }
    os.fill(' ');

    return os;
}

int Date::stringToInt(char* str) {
    // Function to convert a C-string to an integer
    int result = 0, i;

    for (i = 0; str[i] != '\0'; ++i) {
        result = result * 10 + str[i] - '0';   
    }
    return result;
}

bool Date::validDigit(char* str) {
    // Function to check if all characters in a C-string are valid digits (0-9)
    bool result = true;
    for (int i = 0; i < (int)(strlen(str)); i++) {
        if (!(str[i] >= 48 && str[i] <= 57)) { 
            result = false;
        }
    }
    return result;
}


	std::istream& Date::read(std::istream& is) {
    // Function to read a date from an input stream
    char yearString[5] = {'2', '0'};
    char string1[3] = {}, string2[3] = {}, string3[3] = {};

    is.get(string1, 3);      
    if (is.peek() != '\n') { 
        is.get(string2, 3);  
    }
    if (is.peek() != '\n') { 
        is.get(string3, 3);  
    }
    if (validDigit(string1) && validDigit(string2) && validDigit(string3)) { 
        if (strlen(string1) + strlen(string2) + strlen(string3) == 6) {      
            strcat(yearString, string1);                                     
            year = stringToInt(yearString);                                  
            month = stringToInt(string2);                                    
            day = stringToInt(string3);                                      
        } else if (strlen(string1) + strlen(string2) + strlen(string3) == 4) { 
            month = stringToInt(string1);                                    
            day = stringToInt(string2);                                      
        } else if (strlen(string1) + strlen(string2) + strlen(string3) == 2) { 
            day = stringToInt(string1);                                      
            month = stringToInt(string2);                                    
        }
    } else {
        m_state = "Invalid date value"; 
        m_state = 0;                    
        is.setstate(std::ios::badbit);       
    }
    if (is) {
        if (!validate()) {             
            is.setstate(std::ios::badbit);  
        }
    }
    is.ignore(2000, '\n');             
    return is;
}

Date& Date::operator=(const Date& obj) {
    // Assignment operator to copy the content of another date
    if (this != &obj) {                
        year = obj.year;               
        month = obj.month;
        day = obj.day;
        format = obj.format;
        m_state.clear();               
        m_state = obj.m_state;
    }
    return *this;
}

Date::Date(const Date& obj) {
    // Copy constructor to copy the content of another date
    if (obj) {
        year = obj.year;               
        month = obj.month;
        day = obj.day;
        format = obj.format;
        m_state.clear();               
        m_state = obj.m_state;
    }
}

std::ostream& operator<<(std::ostream& os, const Date& obj) {
    // Overloaded stream insertion operator to write a date to an output stream
    obj.write(os);                     
    return os;
}

std::istream& operator>>(std::istream& is, Date& obj) {
    // Overloaded stream extraction operator to read a date from an input stream
    obj.read(is);                      
    return is;
}
}