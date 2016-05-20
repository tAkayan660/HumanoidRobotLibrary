cmake_minimum_required(VERSION 2.8)

project(TestKinematics)

find_package(Boost COMPONENTS system thread filesystem)
find_package(Eigen3 REQUIRED)

include_directories(
	${BOOST_INCLUDE_DIRS}
	${Boost_INCLUDE_DIR}
	${EIGEN3_INCLUDE_DIR}
)

add_library(Kinematics
	Kinematics.cpp
	Kinematics.h
	Link.cpp
	Link.h
	LinkParameter.h
)

link_directories(
	${Boost_LIBRARY_DIRS}
	${Boost_LIBRARY_DIR}
)

add_executable(TestKinematics Kinematics.cpp Link.cpp testKinematics.cpp Kinematics.h Link.h LinkParameter.h)
add_dependencies(TestKinematics Kinematics)
target_link_libraries(TestKinematics ${Boost_LIBRARIES} Kinematics)
