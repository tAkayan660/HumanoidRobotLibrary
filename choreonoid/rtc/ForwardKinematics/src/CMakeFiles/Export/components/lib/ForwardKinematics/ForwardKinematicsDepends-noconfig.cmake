#----------------------------------------------------------------
# Generated CMake target import file for configuration "".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "ForwardKinematics" for configuration ""
set_property(TARGET ForwardKinematics APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(ForwardKinematics PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_NOCONFIG "pthread;omniORB4;omnithread;omniDynamic4;RTC;coil"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/components/lib/ForwardKinematics.so"
  IMPORTED_SONAME_NOCONFIG "ForwardKinematics.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS ForwardKinematics )
list(APPEND _IMPORT_CHECK_FILES_FOR_ForwardKinematics "${_IMPORT_PREFIX}/components/lib/ForwardKinematics.so" )

# Import target "ForwardKinematicsComp" for configuration ""
set_property(TARGET ForwardKinematicsComp APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(ForwardKinematicsComp PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/components/bin/ForwardKinematicsComp"
  )

list(APPEND _IMPORT_CHECK_TARGETS ForwardKinematicsComp )
list(APPEND _IMPORT_CHECK_FILES_FOR_ForwardKinematicsComp "${_IMPORT_PREFIX}/components/bin/ForwardKinematicsComp" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
