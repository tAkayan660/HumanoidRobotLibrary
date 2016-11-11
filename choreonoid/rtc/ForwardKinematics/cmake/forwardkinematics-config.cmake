# ForwardKinematics CMake config file
#
# This file sets the following variables:
# ForwardKinematics_FOUND - Always TRUE.
# ForwardKinematics_INCLUDE_DIRS - Directories containing the ForwardKinematics include files.
# ForwardKinematics_IDL_DIRS - Directories containing the ForwardKinematics IDL files.
# ForwardKinematics_LIBRARIES - Libraries needed to use ForwardKinematics.
# ForwardKinematics_DEFINITIONS - Compiler flags for ForwardKinematics.
# ForwardKinematics_VERSION - The version of ForwardKinematics found.
# ForwardKinematics_VERSION_MAJOR - The major version of ForwardKinematics found.
# ForwardKinematics_VERSION_MINOR - The minor version of ForwardKinematics found.
# ForwardKinematics_VERSION_REVISION - The revision version of ForwardKinematics found.
# ForwardKinematics_VERSION_CANDIDATE - The candidate version of ForwardKinematics found.

message(STATUS "Found ForwardKinematics-1.0.0")
set(ForwardKinematics_FOUND TRUE)

find_package(<dependency> REQUIRED)

#set(ForwardKinematics_INCLUDE_DIRS
#    "/usr/local/include/forwardkinematics-1"
#    ${<dependency>_INCLUDE_DIRS}
#    )
#
#set(ForwardKinematics_IDL_DIRS
#    "/usr/local/include/forwardkinematics-1/idl")
set(ForwardKinematics_INCLUDE_DIRS
    "/usr/local/include/"
    ${<dependency>_INCLUDE_DIRS}
    )
set(ForwardKinematics_IDL_DIRS
    "/usr/local/include//idl")


if(WIN32)
    set(ForwardKinematics_LIBRARIES
        "/usr/local/components/lib/libforwardkinematics.a"
        ${<dependency>_LIBRARIES}
        )
else(WIN32)
    set(ForwardKinematics_LIBRARIES
        "/usr/local/components/lib/libforwardkinematics.so"
        ${<dependency>_LIBRARIES}
        )
endif(WIN32)

set(ForwardKinematics_DEFINITIONS ${<dependency>_DEFINITIONS})

set(ForwardKinematics_VERSION 1.0.0)
set(ForwardKinematics_VERSION_MAJOR 1)
set(ForwardKinematics_VERSION_MINOR 0)
set(ForwardKinematics_VERSION_REVISION 0)
set(ForwardKinematics_VERSION_CANDIDATE )

