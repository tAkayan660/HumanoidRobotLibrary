cmake_minimum_required(VERSION 2.8)

project(testFootStepPlanner)

set(DCMAKE_BUILD_TYPE Debug)
find_package(Eigen3 REQUIRED)
find_package(Boost COMPONENTS system thread filesystem timer)
add_definitions(-lstdc++ -std=c++11)
add_definitions(-DEIGEN_DONT_ALIGN)

include_directories(
	${Boost_INCLUDE_DIR}
	${BOOST_INCLUDE_DIRS}
	${EIGEN3_INCLUDE_DIR}
)

add_executable(testFootStepPlanner main.cpp FootStepPlanner.cpp)

target_link_libraries(testFootStepPlanner ${Boost_LIBRARIES})

install(TARGETS testFootStepPlanner RUNTIME DESTINATION bin)
