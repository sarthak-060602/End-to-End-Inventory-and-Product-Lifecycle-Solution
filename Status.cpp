
#include "Status.h"

namespace sdds {

    Status::Status() {
    // Initialize objStatus to nullptr
    objStatus = nullptr;
    // Initialize statusCode to 0
    statusCode = 0;
}

Status::Status(const char* obj) {
    // Initialize statusCode to 0
    statusCode = 0;

    if (obj != nullptr) {
        // Allocate memory for objStatus and copy the content of obj
        objStatus = new char[strlen(obj) + 1];
        strcpy(objStatus, obj);
    }
}

Status::~Status() {
    // Deallocate memory for objStatus
    delete[] objStatus;
}

Status& Status::operator=(const Status& source) {
    if (this != &source) {
        // Copy statusCode from the source
        statusCode = source.statusCode;

        // Deallocate existing memory for objStatus
        delete[] objStatus;

        if (source.objStatus != nullptr) {
            // Allocate memory for objStatus and copy the content from source
            objStatus = new char[strlen(source.objStatus) + 1];
            strcpy(objStatus, source.objStatus);
        } else {
            // If source.objStatus is nullptr, set objStatus to nullptr
            objStatus = nullptr;
        }
    }
    return *this;
}


    Status& Status::operator=(int newValue) {
    // Assign the new value to statusCode
    statusCode = newValue;
    return *this;
}

Status& Status::operator=(const char* newStatus) {
    if (newStatus != nullptr) {
        // Allocate memory for objStatus and copy the content from newStatus
        objStatus = new char[strlen(newStatus) + 1];
        strcpy(objStatus, newStatus);
    }
    return *this;
}

Status::operator int() const {
    // Return the statusCode
    return statusCode;
}

Status::operator const char* () const {
    // Return the objStatus
    return objStatus;
}

Status::operator bool() const {
    // Return true if objStatus is nullptr, otherwise false
    return objStatus == nullptr;
}

Status& Status::clear() {
    // Reset statusCode to 0
    statusCode = 0;
    if (objStatus != nullptr) {
        // Deallocate memory for objStatus and set it to nullptr
        delete[] objStatus;
        objStatus = nullptr;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Status& obj) {
    if (obj || int(obj) != 0) {
        // If obj is not empty or has a non-zero status code, display error message
        os << "ERR#" << int(obj) << ": " << (const char*)(obj);
    } else {
        // Display the content of objStatus
        os << (const char*)(obj);
    }
    return os;
}

};