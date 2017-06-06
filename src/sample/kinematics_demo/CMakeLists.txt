cmake_minimum_required(VERSION 2.8)

project(demoKinematicsGL)

set(DCMAKE_BUILD_TYPE Debug)

find_package(GLUT)
find_package(OpenGL)
find_package(Eigen3 REQUIRED)
find_package(Boost COMPONENTS system thread filesystem timer)

add_definitions(-lstdc++ -std=c++11)
add_definitions(-DEIGEN_DONT_ALIGN)
add_definitions(-lglut -lGLU -lGL -lm)

#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../kinematics ./kinematics)

include_directories(
	${Boost_INCLUDE_DIR}
	${BOOST_INCLUDE_DIRS}
	${EIGEN3_INCLUDE_DIR}
	../../kinematics/
)

add_executable(demoKinematicsGL main.cpp ../../kinematics/Link.cpp ../../kinematics/Kinematics.cpp ../../kinematics/Jacobian.cpp)

target_link_libraries(demoKinematicsGL ${Boost_LIBRARIES} ${GLUT_LIBRARY} ${OPENGL_LIBRARY})

install(TARGETS demoKinematicsGL RUNTIME DESTINATION bin)
