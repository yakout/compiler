#!/bin/bash

# Checks if "build" directory exists or not. If it exists then it will 
# not create another one to avoid unnecessary warning messages else it will create one.
if [ ! -d "build" ]; then
    mkdir build
fi

cd build/

# Checks if "CMakeCache.txt" file exists or not. If it exists then it will remove it
# to avoid confusion between multiple building modes.
#if [ -f "CMakeCache.txt" ]; then
#    rm CMakeCache.txt
#fi

# Running cmake on the CMakeLists.txt in the "compiler" (Root) directory.

# 1- With the option of building regression tests turned ON
#    and the option of building unit tests truned ON also.
#cmake -DBUILD_REG_TEST=ON -DBUILD_UNIT_TEST=ON ..

# 2- With the option of building unit tests turned OFF explicitly.
cmake -DBUILD_REG_TEST=ON -DBUILD_UNIT_TEST=ON ..

# 3- With both options (Building unit tests as well as regression tests) turned off
#    implicitly. NOTING that this option will work correctly as long as we remove 
#    CMakeCache.txt everytime because if we build this module with -DBUILD_UNIT_TEST=ON
#    for example this value will be cached and if we didn't turn this option off 
#    explicity using -DBUILD_UNIT_TEST=OFF cmake will use the cached value and will 
#    build the tests accordingly even if we don't need them in our build.
#cmake ..

make

# "ctest" or "make test" can be used and both will work correctly as long as we remove
# CMakeCache.txt but "make test" will work correctly either we remove it or not as it
# doesn't use cached test results (Dangerous! maybe misleading) as ctest; It re-builds 
# modified tests individually so their results are always up-to-date.
make test

#ctest