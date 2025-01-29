#!/bin/bash
set -e

# Update system and install dependencies
echo "=== Updating system and installing dependencies ==="
sudo apt update
sudo apt upgrade -y
sudo apt install -y build-essential cmake g++ libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libboost-test-dev pkg-config

# Set up SDL2_image and SDL2_ttf using pkg-config
echo "=== Setting up SDL2_image and SDL2_ttf paths for CMake ==="

# Fetch SDL2_image flags
SDL2_IMAGE_FLAGS=$(pkg-config --cflags --libs SDL2_image)
if [ -z "$SDL2_IMAGE_FLAGS" ]; then
    echo "SDL2_image not found! Please ensure SDL2_image is installed."
    exit 1
fi
echo "SDL2_image found using pkg-config"

# Fetch SDL2_ttf flags
SDL2_TTF_FLAGS=$(pkg-config --cflags --libs SDL2_ttf)
if [ -z "$SDL2_TTF_FLAGS" ]; then
    echo "SDL2_ttf not found! Please ensure SDL2_ttf is installed."
    exit 1
fi
echo "SDL2_ttf found using pkg-config"

# Export flags for CMake
export SDL2_IMAGE_FLAGS
export SDL2_TTF_FLAGS

# Create the build directory
echo "=== Creating build directory ==="
mkdir -p build
cd build

# Run CMake configuration
echo "=== Running CMake configuration ==="
cmake ..

# Build the project
echo "=== Building the project ==="
cmake --build .
cd ..

# Run the tests
echo "=== Running the Heroes_AI Tests ==="
./build/UnitTests
./build/HexTests
./build/HexMapTests
./build/HealthTests
./build/StatisticTests
./build/UnitClassTests
./build/FieldUnitTests
./build/FieldArmyTests
./build/InitiativeQueueTests

# Run the Heroes_AI application
echo "=== Running the Heroes_AI application ==="
./build/Heroes_AI
