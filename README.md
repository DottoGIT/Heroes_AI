# Heroes_AI

**Heroes_AI** is a reconstruction of the classic **Heroes III** game with an AI-powered enemy movement system. The enemy logic is implemented using the **Minimax algorithm**.

## Compilation Instructions

### Windows

1. **Prepare the Environment:**
   - Rename `CMakeLists-Windows.txt` to `CMakeLists.txt`.
   - Install **vcpkg** (a package manager for C++).
   - Using **vcpkg**, install the required dependencies:
     ```
     vcpkg install sdl2 sdl2-image sdl2-ttf boost-test
     ```
   - After successful installation, update the `VCPKG` variable in `boot.bat` to point to the correct `vcpkg.cmake` path.

2. **Build the Project:**
   - Open the project folder in the terminal and run:
     ```
     ./boot.bat build
     ```
   - This will generate the necessary executable files.

3. **Run the Game:**
   - To launch the compiled game, execute:
     ```
     ./boot.bat main
     ```

4. **Run Tests:**
   - To execute tests, run:
     ```
     ./boot.bat tests
     ```

### Ubuntu (Linux)

1. **Prepare the Script:**
   - Rename `CMakeLists-Linux.txt` to `CMakeLists.txt`.
   - Ensure the script has execution permissions:
     ```
     chmod +x boot.sh
     ```

2. **Build & Run the Project:**
   - Execute the script:
     ```
     sh boot.sh
     ```
   - This will:
     - Install necessary dependencies.
     - Build the main executable and test files.
     - Automatically run the compiled game and tests.