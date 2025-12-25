# TestProgram

## Description
TestProgram is a console-based C++ application that simulates a school testing system.
An administrator can create categories and tests, while users can take tests from available categories.
The program saves test results for each user into separate files.

> Note: The project is Windows-specific due to console handling (WinAPI).

## Features
- Role-based access (Administrator / User)
- Creating and managing test categories
- Creating and managing tests
- Taking tests and saving results
- Console menu navigation using arrow keys and Enter
- File-based data storage

## Security Note
Passwords are hashed using MD5 for educational purposes.  
MD5 is not recommended for real-world password storage due to known vulnerabilities.  
In production systems, stronger algorithms such as bcrypt, Argon2 or PBKDF2 should be used.

## Technologies
- C++23
- STL (vector, map, string, algorithm)
- Object-Oriented Programming (OOP)
- WinAPI (console handling)

## Project Architecture
- `TestProgram` — main application controller
- `Admin` / `User` — user roles and logic
- `Category` — groups tests by subject
- `Test` — individual tests
- `Menu` — reusable console menu class

Architecture flow:  
`TestProgram → Admin/User → Category → Test`

## Build and Run

### Using PowerShell
1. Build the project in Visual Studio (Release | x64)
2. Open PowerShell in project folder
3. Run the executable: 
> x64\Release\TestProgram.exe


### Using Visual Studio
1. Open the project
2. Build the solution
3. Run in console

## Usage Example
1. Start the program
2. Enter login and password  
   (Default accounts: admin/admin, user/user.  
   User data can be reset by deleting `Users.txt`)
3. Administrator creates categories and tests
4. User selects a category and takes a test
5. Test results are saved automatically

## File Storage
- User credentials and test results are stored in local files
- Each user has a separate file with test results

## Future Improvements
- Add password salting
- Implement stronger hashing algorithms
- Add statistics and score analysis
- Add unit tests
- Add CMake build system

## Author
DeDarlin

