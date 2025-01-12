
#include <iostream>
#include <cstring>
#include <ctime>
#ifndef UTILS_H
#define UTILS_H

namespace sdds {
    
    const int sdds_testYear = 2023;
    const int sdds_testMon = 12;
    const int sdds_testDay = 9;
    class Utils {

        bool m_testMode = false;
    public:

        // Function to get the system date
        void getSystemDate(int* year = nullptr, int* mon = nullptr, int* day = nullptr);

        // Function to get the number of days in a given month of a year
        int daysOfMon(int mon, int year) const;

        // Function to set or unset the test mode
        void testMode(bool testmode = true);

        // Function to allocate memory and copy the content of a source string to a destination string
        void alocpy(char*& destination, const char* source);

        // Function to get an integer from the user with a given prompt
        int getint(const char* prompt = nullptr);

        // Function to get an integer within a specified range from the user with optional prompt and error message
        int getint(int min, int max, const char* prompt = nullptr, const char* errMes = nullptr);
    };

    // Declaration of the external object ut of type Utils
    extern Utils ut;
}

#endif 
