cmake_minimum_required(VERSION 2.8)

project(testPreviewControl)

set(DCMAKE_BUILD_TYPE Debug)
find_package(Eigen3 REQUIRED)
find_package(PythonLibs REQUIRED)
add_definitions(-lstdc++ -std=c++11)

include_directories(
	${EIGEN3_INCLUDE_DIR}
	${PYTHON_INCLUDE_DIRS}
)

add_executable(testPreviewControl testPreviewControl.cpp PreviewControl.cpp PreviewControl.h)

target_link_libraries(testPreviewControl ${PYTHON_LIBRARIES})
