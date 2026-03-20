# C++ Vending Machine Simulator

A fully functional, console-based Vending Machine simulator written in C++.

## Features

* **File-Based Persistence**: Loads products, their quantities, and the machine's initial cash float (banknotes) directly from `.txt` files.
* **Dynamic Inventory Management**: Tracks the exact quantity of each product. Prevents purchasing if an item is out of stock.
* **Intelligent Change Calculation**: Automatically calculates the exact change to return to the user using a greedy algorithm, prioritizing the largest available denominations.
* **Virtual Credit System**: Users can deposit multiple banknotes to build a "virtual balance" before making a purchase.
* **Error Handling**: Custom exception classes handle edge cases like insufficient funds, out-of-stock items, invalid inputs, and missing files.
* **Comprehensive Test Suite**: Includes automated unit tests for Repositories, Services, and Controllers to ensure reliability.

## Architecture

The application is structured using a strict layered architecture:

* **Domain Layer**: Contains the core business entities (`Product`, `GenericProduct`) and their validation rules (`GenericProductValidator`).
* **Repository Layer**: Handles data storage and retrieval. Includes an `InMemoryRepository` for fast access and a `FileRepository` that automatically syncs changes to the text files.
* **Service Layer (`VendingMachineService`)**: Contains the core business logic, bridging the Controller and the Repository.
* **Controller Layer (`VendingMachineController`)**: Manages the machine's state, tracking the physical inventory quantities and the available banknotes. Handles the complex logic of purchasing and calculating change.
* **UI Layer (`VendingMachineUI`)**: A console-based interface that interacts with the user and delegates commands to the Controller.

## Build & Run Instructions

This project requires a modern C++ compiler (C++17 or higher recommended due to the use of structured bindings and smart pointers).

### Prerequisites

* Ensure you have `CMake` or a standard C++ compiler (like `g++` or `clang++`) installed.
* Make sure the required text files are present in the same directory as your executable:
  * `products.txt`: Contains product definitions (ID, Name, Price).
  * `quantities.txt`: Contains inventory levels (ID, Quantity).
  * `banknotes.txt`: Contains the machine's cash float (Denomination, Quantity).

### Compilation (using g++)

You can compile the project from the terminal. Ensure you include all `.cpp` files in your command. For example:

\`\`\`bash
g++ -std=c++17 main.cpp domain/*.cpp repository/*.cpp service/*.cpp controller/*.cpp ui/*.cpp -o VendingMachine
\`\`\`

### Execution

Run the compiled executable:

\`\`\`bash
./VendingMachine
\`\`\`

## How to Use

Upon running the application, you will see the main menu:

\`\`\`text
=== Vending Machine ===
1. View products
2. Deposit money
3. Buy product
4. Get change
0. Exit
\`\`\`

1. **View products**: Displays all available items, their prices, and current stock.
2. **Deposit money**: Insert cash into the machine. The machine tracks this as your virtual balance.
3. **Buy product**: Enter the ID of the product you wish to purchase. If your balance covers the price, the item is dispensed, and exact change is calculated and returned.
4. **Get change**: Cancels your transaction and returns your deposited money.
5. **Exit**: Closes the application (automatically returning any unspent balance).

## Testing

The project includes built-in test suites that run automatically when the application starts. These cover:

* **Domain Validation**: Ensures products cannot have negative prices or empty names.
* **Repository Tests**: Verifies adding, finding, updating, and removing items in both memory and file-based repositories.
* **Service Tests**: Validates business logic, such as checking if a product is available.
* **Controller Tests**: Rigorously tests the purchasing logic, inventory updates, and the change calculation algorithm.
