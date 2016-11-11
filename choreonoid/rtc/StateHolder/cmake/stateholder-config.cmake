# StateHolder CMake config file
#
# This file sets the following variables:
# StateHolder_FOUND - Always TRUE.
# StateHolder_INCLUDE_DIRS - Directories containing the StateHolder include files.
# StateHolder_IDL_DIRS - Directories containing the StateHolder IDL files.
# StateHolder_LIBRARIES - Libraries needed to use StateHolder.
# StateHolder_DEFINITIONS - Compiler flags for StateHolder.
# StateHolder_VERSION - The version of StateHolder found.
# StateHolder_VERSION_MAJOR - The major version of StateHolder found.
# StateHolder_VERSION_MINOR - The minor version of StateHolder found.
# StateHolder_VERSION_REVISION - The revision version of StateHolder found.
# StateHolder_VERSION_CANDIDATE - The candidate version of StateHolder found.

message(STATUS "Found StateHolder-1.0.0")
set(StateHolder_FOUND TRUE)

find_package(<dependency> REQUIRED)

#set(StateHolder_INCLUDE_DIRS
#    "/usr/local/include/stateholder-1"
#    ${<dependency>_INCLUDE_DIRS}
#    )
#
#set(StateHolder_IDL_DIRS
#    "/usr/local/include/stateholder-1/idl")
set(StateHolder_INCLUDE_DIRS
    "/usr/local/include/"
    ${<dependency>_INCLUDE_DIRS}
    )
set(StateHolder_IDL_DIRS
    "/usr/local/include//idl")


if(WIN32)
    set(StateHolder_LIBRARIES
        "/usr/local/components/lib/libstateholder.a"
        ${<dependency>_LIBRARIES}
        )
else(WIN32)
    set(StateHolder_LIBRARIES
        "/usr/local/components/lib/libstateholder.so"
        ${<dependency>_LIBRARIES}
        )
endif(WIN32)

set(StateHolder_DEFINITIONS ${<dependency>_DEFINITIONS})

set(StateHolder_VERSION 1.0.0)
set(StateHolder_VERSION_MAJOR 1)
set(StateHolder_VERSION_MINOR 0)
set(StateHolder_VERSION_REVISION 0)
set(StateHolder_VERSION_CANDIDATE )

