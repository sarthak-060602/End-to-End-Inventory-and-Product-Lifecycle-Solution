# End-to-End-Inventory-and-Product-Lifecycle-Solution

# Comprehensive Product and Inventory Management System

A robust inventory management system designed for handling products and their life cycles, with a special emphasis on managing perishable goods. The system supports tracking product details, managing stock levels, and processing expiry dates, ensuring seamless inventory management for businesses.

---

## Key Features

- **Inventory Management**: Maintain product details, track stock levels, and categorize products.
- **Expiry Date Handling**: Manage perishable products by tracking expiry dates and issuing appropriate warnings.
- **Handling Instructions**: Store and display handling instructions for perishable items.
- **Custom Status Management**: Easily handle the state of products with detailed status codes and messages.
- **Streamlined Input/Output**: Load and save product data through file operations for persistent storage.
- **User-Friendly Console Interface**: Simple console-based operations for product entry, display, and updates.

---

## Example Implementations and Use Cases

### Adding a Perishable Product
```cpp
#include "Perishable.h"
#include <iostream>

int main() {
    sdds::Perishable p;
    std::cout << "Enter product details:" << std::endl;
    p.read(std::cin);

    std::ofstream file("inventory.txt");
    p.save(file);
    file.close();

    std::cout << "Product added successfully!" << std::endl;
    return 0;
}
```

### Loading and Displaying Inventory
```cpp
#include "Perishable.h"
#include <iostream>
#include <fstream>

int main() {
    sdds::Perishable p;
    std::ifstream file("inventory.txt");
    
    if (file) {
        p.load(file);
        p.display(std::cout);
    } else {
        std::cerr << "Error loading inventory." << std::endl;
    }

    return 0;
}
```

---

## Explanation of Files and Methods

### Core Files

#### **`Item.h` / `Item.cpp`**
- Base class for managing general product attributes like SKU, price, quantity, etc.
- Methods:
  - `display()`: Outputs item details.
  - `read()`: Reads item details from the user.
  - `save()` and `load()`: File operations for persistence.

#### **`Perishable.h` / `Perishable.cpp`**
- Inherits from `Item` and adds specific functionalities for perishable products.
- Additional Attributes:
  - `m_expiry`: Tracks the expiry date of the product.
  - `m_handling`: Stores handling instructions for sensitive items.
- Methods:
  - `expiry()`: Accessor for expiry date.
  - `read()`: Reads expiry date and handling instructions.
  - `save()` and `load()`: Specialized file operations for perishables.

#### **`Status.h` / `Status.cpp`**
- Manages the state of items with status codes and messages.
- Methods:
  - Conversion operators for `int` and `const char*`.
  - `clear()`: Resets the status to a neutral state.

#### **`Utils.h` / `Utils.cpp`**
- Utility functions for common tasks like input validation, date calculations, and string operations.
- Methods:
  - `getint()`: Validates integer input within a range.
  - `getSystemDate()`: Retrieves the current date or a test date in test mode.
  - `alocpy()`: Allocates and copies strings.

#### **`Date.h` / `Date.cpp`**
- Handles date-related operations.
- Attributes:
  - `m_year`, `m_month`, `m_day`: Store date components.
- Methods:
  - `read()` and `write()`: Input and output operations.
  - Validation for date ranges.

#### **`POS.h`**
- Contains constants and macros for the project.
- Used for SKU ranges, formatting options, and project settings.

---

## Example Use Cases

1. **Retail Store Inventory**: Track and manage products, ensuring that perishable goods are handled properly and expired items are flagged.
2. **Warehouse Management**: Maintain records of product stock levels, expiry dates, and special handling requirements.
3. **E-commerce Platforms**: Streamline product inventory processes with file-based storage and retrieval.

---

This project demonstrates strong object-oriented programming principles, with features like inheritance, polymorphism, and modularity. It is suitable for various business applications requiring reliable inventory and product lifecycle management.
