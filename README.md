# 5607-hw2a-starter

## Note
This is the professor Victoria Interrante's code, not mine. I'm just posting this on github for students to download for their assignment.

## Installing + Configuring

Note: If you downloaded the ZIP file instead, just skip to the "mkdir build" step. Do note that the 2B files are on a different branch.


Configuring for HW2B:
```
git clone --recursive https://github.com/LiamTyler/5607-hw2a-starter.git
cd 5607-hw2a-starter
git checkout hw2b
mkdir build
cd build
cmake ..
```

Configuring for HW2A:
```
git clone --recursive https://github.com/LiamTyler/5607-hw2a-starter.git
cd 5607-hw2a-starter
mkdir build
cd build
cmake ..
```

## Building / Compiling

#### Linux/Mac
CMake should just generate a Makefile, so just do a `make` inside the build folder. 

#### Windows (Visual Studio)
Open up the solution file in the build folder and build it from there like normal. Note that with Visual Studio, you might want to do `cmake -G "Visual Studio 15 2017 Win64" ..` instead of `cmake ..` if you want to get the 64-bit version. You can change the '15' and '2017 'to be whatever your VS version is (command for VS 2016 would be `cmake -G "Visual Studio 16 2019" -Ax64 ..`, but I have only tested it on 2017. Also with Visual Studio, don't forget that it defaults to Debug mode (if you want to change it to Release)
