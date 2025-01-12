
#include "Utils.h"

namespace sdds {

    Utils ut;

void Utils::testMode(bool testmode) {
    // Set or unset the test mode
    m_testMode = testmode;
}

void Utils::getSystemDate(int* year, int* mon, int* day) {
    if (m_testMode) {
        // If in test mode, use predefined test date
        if (day) *day = sdds_testDay;
        if (mon) *mon = sdds_testMon;
        if (year) *year = sdds_testYear;
    } else {
        // Get the current system date
        time_t t = std::time(NULL);
        tm lt = *localtime(&t);
        if (day) *day = lt.tm_mday;
        if (mon) *mon = lt.tm_mon + 1;  // Months are 0-indexed
        if (year) *year = lt.tm_year + 1900;  // Years since 1900
    }
}

int Utils::daysOfMon(int month, int year) const {
    // Calculate the number of days in a given month of a year
    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1};
    int mon = (month >= 1 && month <= 12 ? month : 13) - 1;
    return days[mon] + int((mon == 1) * ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
}

void Utils::alocpy(char*& destination, const char* source) {
    // Allocate memory and copy the content of a source string to a destination string
    if (destination != nullptr) {
        delete[] destination;
        destination = nullptr;
    }
    if (source != nullptr) {
        destination = new char[strlen(source) + 1];
        strcpy(destination, source);
    }
}

int Utils::getint(const char* prompt) {
    // Get an integer from the user with optional prompt
    int num;
    bool valid = false;

    if (prompt != nullptr) {
        std::cout << prompt;
    }

    while (!valid) {
        std::cin.clear();
        std::cin >> num;

        if (std::cin.fail()) {
            std::cout << "Invalid Integer, retry: ";
            std::cin.clear();
            std::cin.ignore(2000, '\n');
        } else {
            valid = true;
        }
    }

    return num;
}

int Utils::getint(int min, int max, const char* prompt, const char* errMes) {
    // Get an integer within a specified range from the user with optional prompt and error message
    int num;

    do {
        num = getint(prompt);

        if (num < min || num > max) {
            if (errMes != nullptr) {
                std::cout << errMes << ", retry: ";
            } else {
                std::cout << "Value out of range [" << min << "<=val<=" << max << "]: ";
            }

            prompt = nullptr;
        }
    } while (num < min || num > max);

    return num;
}

}