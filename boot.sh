#!/bin/bash
set -e

echo "=== Updating system and installing dependencies ==="
sudo apt update
sudo apt upgrade -y
sudo apt install -y build-essential cmake g++ libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libboost-test-dev pkg-config

echo "=== Setting up SDL2_image and SDL2_ttf paths for CMake ==="
# Find SDL2_image paths
SDL2_IMAGE_INCLUDE_DIR=$(pkg-config --cflags-only-I SDL2_image | sed 's/-I//g')
SDL2_IMAGE_LIBRARY=$(pkg-config --libs-only-l SDL2_image | sed 's/-l//g')

# Find SDL2_ttf paths
SDL2_TTF_INCLUDE_DIR=$(pkg-config --cflags-only-I SDL2_ttf | sed 's/-I//g')
SDL2_TTF_LIBRARY=$(pkg-config --libs-only-l SDL2_ttf | sed 's/-l//g')

# Export the paths to environment variables or directly add them in CMake
export SDL2_IMAGE_INCLUDE_DIR
export SDL2_IMAGE_LIBRARY
export SDL2_TTF_INCLUDE_DIR
export SDL2_TTF_LIBRARY

echo "SDL2_image include dir: $SDL2_IMAGE_INCLUDE_DIR"
echo "SDL2_image library: $SDL2_IMAGE_LIBRARY"
echo "SDL2_ttf include dir: $SDL2_TTF_INCLUDE_DIR"
echo "SDL2_ttf library: $SDL2_TTF_LIBRARY"

echo "=== Creating build directory ==="
mkdir -p build
cd build

echo "=== Running CMake configuration ==="
# Pass the paths to CMake as arguments if needed
cmake -DSDL2_IMAGE_INCLUDE_DIR=$SDL2_IMAGE_INCLUDE_DIR \
      -DSDL2_IMAGE_LIBRARY=$SDL2_IMAGE_LIBRARY \
      -DSDL2_TTF_INCLUDE_DIR=$SDL2_TTF_INCLUDE_DIR \
      -DSDL2_TTF_LIBRARY=$SDL2_TTF_LIBRARY ..

echo "=== Building the project ==="
cmake --build .
cd ..

echo "=== Running the Heroes_AI Tests ==="
./build/HexTests
./build/HexMapTests
./build/UnitTests

echo "=== Running the Heroes_AI application ==="
./build/Heroes_AI