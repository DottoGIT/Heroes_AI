#!/bin/bash
set -e

echo "=== Updating system and installing dependencies ==="
sudo apt update
sudo apt upgrade -y
sudo apt install -y build-essential cmake g++ libsdl2-dev libsdl2-image-dev libboost-all-dev

echo "=== Creating build directory ==="
mkdir -p build
cd build

echo "=== Running CMake configuration ==="
cmake ..

echo "=== Building the project ==="
cmake --build .

echo "=== Running the Heroes_AI Tests ==="
./HexTests
./HexMapTests
./UnitTests

echo "=== Running the Heroes_AI application ==="
./Heroes_AI
