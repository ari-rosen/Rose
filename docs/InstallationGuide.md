# Installation Guide
Simple guide to installing Rose
## Prerequisites
**macOS**:
* XCode Command Line Tools
* Git
* CMake

## Using Rose as a Dependency (Recommended)
Best option for CMake, no need for manual compilation. This integrates the engine directly into your build system — no need to install anything separately.
### Step 1: Clone the Repository
```bash
git clone --recursive https://github.com/ari-rosen/Rose
```
### Step 2: Add Rose to Your Project
```
add_subdirectory(path/to/rose)
target_link_libraries(my_app PRIVATE RoseEngine)
```
## General Installation
Necessary if your project isn't a CMake project; You will have to manually link the library
### Step 1: Clone the Repository
```bash
git clone --recursive https://github.com/ari-rosen/Rose
cd Rose
```
### Step 2: Build the Engine
```bash
mkdir build
cd build
cmake ..
make
```
There should now be a ```libRoseEngine.dylib``` in Rose/build
