cmake_minimum_required(VERSION 2.8)

project(LIP)

set(CMAKE_CXX_FLAGS_RELEASE)
find_package(Eigen3 REQUIRED)

include_directories(
	${EIGEN3_INCLUDE_DIR}
)

add_executable(LIP main.cpp LinearInvertedPendlum.cpp LinearInvertedPendlum.h)
