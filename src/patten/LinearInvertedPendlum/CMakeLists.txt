cmake_minimum_required(VERSION 2.8)

project(LIP)

set(CMAKE_CXX_FLAGS_RELEASE)
find_package(Eigen3 REQUIRED)
find_package(PythonLibs REQUIRED)
add_definitions(-lstdc++ -std=c++11)

include_directories(
	${EIGEN3_INCLUDE_DIR}
	${PYTHON_INCLUDE_DIRS}
)

add_executable(LIP main.cpp LinearInvertedPendlum.cpp LinearInvertedPendlum.h)

target_link_libraries(LIP ${PYTHON_LIBRARIES})

install(TARGETS LIP RUNTIME DESTINATION bin)
