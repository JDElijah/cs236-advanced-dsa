cmake_minimum_required(VERSION 3.20)
project(cs236_advanced_dsa LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Starter program
add_executable(cs236 src/main.cpp "assignments/NumbersReversed/NumbersReversed.cpp")
target_include_directories(cs236 PRIVATE include)

# Add one executable per assignment below.
# Example (we'll add the file in step 6):
# add_executable(NumbersReversed assignments/NumbersReversed/NumbersReversed.cpp)
# target_include_directories(NumbersReversed PRIVATE include)
add_executable(NumbersReversed assignments/NumbersReversed/NumbersReversed.cpp)
target_include_directories(NumbersReversed PRIVATE include)

add_executable(IsPalindrome assignments/IsPalindrome/IsPalindrome.cpp)
target_include_directories(IsPalindrome PRIVATE include)