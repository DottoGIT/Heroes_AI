#!/bin/bash
set -e

echo "=== Updating system and installing dependencies ==="
sudo apt update
sudo apt upgrade -y
sudo apt install -y build-essential cmake g++ libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libboost-test-dev

echo "=== Creating build directory ==="
mkdir -p build
cd build

echo "=== Running CMake configuration ==="
cmake ..

echo "=== Building the project ==="
cmake --build .
cd ..

echo "=== Running the Heroes_AI Tests ==="
./build/HexTests
./build/HexMapTests
./build/UnitTests

echo "=== Running the Heroes_AI application ==="
./build/Heroes_AI
