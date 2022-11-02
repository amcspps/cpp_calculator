cmake_minimum_required (VERSION 3.8)

project ("cpp_calc")

add_executable (cpp_calc "main.cpp" "calc.cpp"  "parser.cpp" "solver.cpp" "token.cpp" "function.cpp")

include_directories("cpp_calc")

set (BOOST_ROOT "C:/Boost/boost_1_79_0/") 
set (CMAKE_CXX_STANDARD 20) 
set (Boost_NO_SYSTEM_PATHS ON)
set (Boost_USE_MULTITHREADED ON)
set (Boost_USE_STATIC_LIBS ON)
set (Boost_USE_STATIC_RUNTIME OFF)
set (BOOST_ALL_DYN_LINK OFF)
  
find_package (Boost REQUIRED COMPONENTS program_options REQUIRED) 
  
if (Boost_FOUND)
    include_directories (SYSTEM ${Boost_INCLUDE_DIR})
    add_executable (Boost_test "main.cpp" "solver.cpp" "token.cpp" "function.cpp")
    target_link_libraries (Boost_test ${Boost_LIBRARIES})
endif ()