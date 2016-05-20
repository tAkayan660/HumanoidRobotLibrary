cmake_minimum_required(VERSION 2.8)

project(FootSampleController)

include(FindPkgConfig)
pkg_check_modules(cnoid_plugin REQUIRED choreonoid-body-plugin)
pkg_check_modules(openrtm_aist REQUIRED	openrtm-aist)

add_subdirectory(/home/haze/github/HumanoidRobotLibrary/src/Kinematics ./Kinematics)

include_directories(
	${openrtm_aist_INCLUDE_DIRS}
	${cnoid_plugin_INCLUDE_DIRS}
	../../../src/Kinematics
)

link_directories(
	${openrtm_aist_LIBRARY_DIRS}
	${cnoid_plugin_LIBRARY_DIRS}
)

add_library(FootSampleController SHARED FootSampleController.cpp)
set_target_properties(FootSampleController PROPERTIES PREFIX "")

set(target FootSampleController)

add_dependencies(FootSampleController Kinematics)
target_link_libraries(FootSampleController
	${openrtm_aist_LIBRARIES}
	${cnoid_plugin_LIBRARIES}
	Kinematics
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

install(TARGETS FootSampleController LIBRARY DESTINATION /usr/lib/choreonoid-1.5/rtc)
