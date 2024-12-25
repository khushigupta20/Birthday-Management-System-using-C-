# Birthday Manager System using c++

This is a C++ program designed to manage and organize birthday records. It allows users to add, view, delete, and modify birthdays in a structured and interactive manner.

## Features

1. **Add a New Birthday**  
   Users can input a name and birthday details, which are stored in a doubly linked list and saved to a file for persistence.

2. **View All Birthdays**  
   Displays a complete list of all birthdays in a sorted order (by date and name).

3. **Delete a Birthday**  
   Provides the option to search for a birthday and delete it from the records.

4. **Modify a Birthday**  
   Allows editing the details of an existing birthday.

5. **Data Persistence**  
   Uses binary file handling to save and retrieve birthday records from a file.

## How It Works

1. **Data Structure**  
   Birthdays are stored as nodes in a doubly linked list, with each node containing:
   - Name
   - Day
   - Month
   - Pointers to the next and previous nodes.

2. **File Handling**  
   Records are saved to and loaded from a binary file (`birthday.dat`) located in `C:\\TURBOC3\\Projects\\csc\\`.

3. **Interactive Menu**  
   - `1` - Add a new birthday  
   - `2` - Delete an existing birthday  
   - `3` - View all birthdays  
   - `4` - Modify a birthday  
   - `5` - Exit and save changes  

4. **Search Functionality**  
   Users can search for birthdays based on:
   - Specific date
   - Month
   - Name

## Compilation and Execution

1. Ensure Turbo C++ is set up and configured correctly.
2. Place the source file (`BIRTHDAY.CPP`) in the appropriate directory.
3. Compile and run the program in the Turbo C++ IDE.


