# Heroes AI
Uproszczona wersja gry Heroes III z implementacją algorytmu min-max
##### Autorzy
Wojciech Sarwiński
Maciej Scheffer

# Specyfikacja
### Wymagane Biblioteki
- Boost
- SDL2,  SDL2_Image
### Skrypty budujące
- cmake

# Automatyczna kompilacja i uruchomienie
### Windows
Do automatycznej kompilacji i uruchomienia projektu służy plik **boot.bat**, który za argument przyjmuje
- **build**: buduje projekt w oparciu o sprecyzowany wewnątrz niego toolchain
- **main**: uruchamia plik wykonywalny Heroes_AI.exe
- **tests**: uruchamia testy jednostkowe UnitTests.exe
### Ubuntu 24.04 LTS
Do automatycznej kompilacji i uruchomienia projektu służy plik **boot.sh**, który automatycznie pobierze wymagane biblioteki, zbuduje projekt oraz kolejno uruchomi wszystkie testy, a następnie plik wykonywalny projektu.
## Ręczna kompilacja i uruchomienie
### Windows
``` 
mkdir build
cd ./build
cmake .. -DCMAKE_TOOLCHAIN_FILE=/path/to/toolchain.cmake
cmake --build .
./Debug/UnitTests.exe
./Debug/Heroes_AI.exe
```
### Ubuntu
``` 
sudo apt update
sudo apt upgrade -y
sudo apt install -y build-essential cmake g++ libsdl2-dev libsdl2-image-dev libboost-all-dev
mkdir -p build
cd build
cmake ..
cmake --build .
./UnitTests
./Heroes_AI
```