cmake_minimum_required(VERSION 2.8)

project(testRiccatiEquation)

set(DCMAKE_BUILD_TYPE Debug)
find_package(Eigen3 REQUIRED)
add_definitions(-lstdc++ -std=c++11)

include_directories(
	${EIGEN3_INCLUDE_DIR}
)

add_executable(testRiccatiEquation testRiccatiEquation.cpp Riccati.h)
