# Library Management System
## Overview
The Library Management System is a simple console-based application written in C++ that allows a library to manage its collection of books and its users. It provides functionality for adding books, borrowing books, returning books, and querying both books and users. The system is designed to be straightforward and easy to use, providing basic library operations.

## Features
### Book Management
Add Books: Allows the addition of books to the library's inventory with details like ID, name, and total quantity.
Borrow Books: Users can borrow books from the library as long as there are available copies.
Return Books: Users can return borrowed books, and the system tracks the number of books currently borrowed.
Book Lookup by Prefix: The system allows searching for books by name prefix, helping users find books more efficiently.
### User Management
Add Users: Allows new users to be added to the system, with unique IDs and names.
Borrowing Records: The system tracks how many books each user has borrowed.
Manage Borrowing: Users can borrow or return books, with borrowing limits enforced.
## System Constraints
Maximum number of books: 10
Maximum number of users: 10
These constraints are set for simplicity and can be adjusted by modifying the constant values in the code.

## Installation
To run this project, you will need the following:

C++ Compiler: Make sure you have a C++ compiler installed on your machine. You can use:

- GCC (g++): Commonly available on Linux or can be installed on Windows through MinGW or Cygwin.
- Clang: Available for macOS and Linux systems.
- Visual Studio: A good IDE for Windows that comes with MSVC (Microsoft C++ compiler).
- Terminal/Command Prompt: For compiling and running the program from the command line.

## User Input Format
- Adding Books: Input the book ID, name, and total quantity.
- Adding Users: Input the user ID and name.
- Borrowing Books: Users provide their ID and the book they wish to borrow.
- Returning Books: Users provide their ID and the book they wish to return.
  
## Code Structure
The project is structured around two main entities:
1. Book: Represents a book in the library, with properties like ID, name, total quantity, and borrowed count.
2. User: Represents a user who borrows books, tracking their ID, name, and the number of books they've borrowed.
## Key Functions
- read(): Reads input for books and users.
- borrow(): Manages book borrowing logic.
- return_copy(): Handles returning borrowed books.
- has_prefix(): Helps in searching books by name prefix.
- print(): Prints book details.
