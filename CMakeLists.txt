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

# NumbersReversed assignment
add_executable(NumbersReversed assignments/NumbersReversed/NumbersReversed.cpp)
target_include_directories(NumbersReversed PRIVATE include)

# IsPalindrome assignment
add_executable(IsPalindrome assignments/IsPalindrome/IsPalindrome.cpp)
target_include_directories(IsPalindrome PRIVATE include)

# Refactor IsPalindrome with class
add_executable(PalindromeChecker assignments/IsPalindromeRefactor/PalindromeChecker.cpp)
target_include_directories(PalindromeChecker PRIVATE include)

# TicTacToe two dimensional array example 
add_executable(TicTacToe samples/TwoDimensionalArrays/TicTacToe.cpp)
target_include_directories(TicTacToe PRIVATE include)

# SinglyLinkedList example
add_executable(SinglyLinkedList samples/SinglyLinkedList/SinglyLinkedList.cpp)
target_include_directories(SinglyLinkedList PRIVATE include)

# CircularlyLinkedList example 
add_executable(CircularlyLinkedList samples/CircularlyLinkedList/CircularlyLinkedList.cpp)
target_include_directories(CircularlyLinkedList PRIVATE include)

# CircularlyLinkedListSimple example
add_executable(CircularlyLinkedListSimple samples/CircularlyLinkedList/CircularlyLinkedListSimple.cpp)
target_include_directories(CircularlyLinkedListSimple PRIVATE include)

# DoublyLinkedList example
add_executable(DoublyLinkedList samples/DoublyLinkedList/DoublyLinkedList.cpp)
target_include_directories(DoublyLinkedList PRIVATE include)

# FactorialRecursion example 
add_executable(FactorialRecursion samples/Recursion/FactorialRecursion.cpp)
target_include_directories(FactorialRecursion PRIVATE include)

# EnglishRulerRecursion example
add_executable(EnglishRulerRecursion samples/Recursion/EnglishRulerRecursion.cpp)
target_include_directories(EnglishRulerRecursion PRIVATE include)

# BinarySearch example 
add_executable(BinarySearch samples/Recursion/BinarySearch.cpp)
target_include_directories(BinarySearch PRIVATE include)
