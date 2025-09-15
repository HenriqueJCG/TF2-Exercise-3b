# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_learning_tf2_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED learning_tf2_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(learning_tf2_FOUND FALSE)
  elseif(NOT learning_tf2_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(learning_tf2_FOUND FALSE)
  endif()
  return()
endif()
set(_learning_tf2_CONFIG_INCLUDED TRUE)

# output package information
if(NOT learning_tf2_FIND_QUIETLY)
  message(STATUS "Found learning_tf2: 0.2.0 (${learning_tf2_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'learning_tf2' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT learning_tf2_DEPRECATED_QUIET)
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(learning_tf2_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "ament_cmake_export_dependencies-extras.cmake")
foreach(_extra ${_extras})
  include("${learning_tf2_DIR}/${_extra}")
endforeach()
