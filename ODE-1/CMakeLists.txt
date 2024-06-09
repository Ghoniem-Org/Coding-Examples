cmake_minimum_required(VERSION 3.27)
project(ODE_1)

set(CMAKE_CXX_STANDARD 23)

# Specify the path to Boost
set(BOOST_ROOT "C:/Users/Owner/boost_1_85_0")  # Replace with your Boost installation path

find_package(Boost 1.85.0 REQUIRED)

if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(ode_solver main.cpp)
    target_link_libraries(ode_solver ${Boost_LIBRARIES})
else()
    message(FATAL_ERROR "Could not find Boost")
endif()

add_executable(ODE_1 main.cpp)

target_link_libraries(ODE_1 ${Boost_LIBRARIES})