cmake_minimum_required (VERSION 3.8)

project ("cpp_calc")

add_executable (cpp_calc "cpp_calc.cpp" "cpp_calc.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET cpp_calc PROPERTY CXX_STANDARD 20)
endif()

