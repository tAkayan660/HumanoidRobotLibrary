cmake_minimum_required(VERSION 2.8)

#project(TestKinematics)

find_package(Boost COMPONENTS system thread filesystem)
find_package(Eigen3 REQUIRED)

include_directories(
	${BOOST_INCLUDE_DIRS}
	${Boost_INCLUDE_DIR}
	${EIGEN3_INCLUDE_DIR}
)

link_directories(
	${Boost_LIBRARY_DIRS}
	${Boost_LIBRARY_DIR}
)

add_executable(TestKinematics Kinematics.cpp Jacobian.cpp Link.cpp testKinematics.cpp Kinematics.h Link.h)
add_executable(testCheckCoM testCheckCom.cpp Kinematics.cpp Jacobian.cpp Link.cpp)

target_link_libraries(TestKinematics ${Boost_LIBRARIES})
target_link_libraries(testCheckCoM ${Boost_LIBRARIES})

install(TARGETS TestKinematics RUNTIME DESTINATION bin)
install(TARGETS testCheckCoM RUNTIME DESTINATION bin)
