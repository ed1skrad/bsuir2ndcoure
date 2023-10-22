# Install script for directory: C:/Users/atema/CLionProjects/CourseWork/lib/libpqxx-7.8.1

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/CourseWork")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "C:/Users/atema/CLion 2022.3.3/bin/mingw/bin/objdump.exe")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/libpqxx" TYPE FILE FILES
    "C:/Users/atema/CLionProjects/CourseWork/lib/libpqxx-7.8.1/cmake/libpqxx-config.cmake"
    "C:/Users/atema/CLionProjects/CourseWork/cmake-build-debug/lib/libpqxx-7.8.1/libpqxx-config-version.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/libpqxx/libpqxx-targets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/libpqxx/libpqxx-targets.cmake"
         "C:/Users/atema/CLionProjects/CourseWork/cmake-build-debug/lib/libpqxx-7.8.1/CMakeFiles/Export/d6b66e93f8212dd1f00debf9f6654819/libpqxx-targets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/libpqxx/libpqxx-targets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/libpqxx/libpqxx-targets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/libpqxx" TYPE FILE FILES "C:/Users/atema/CLionProjects/CourseWork/cmake-build-debug/lib/libpqxx-7.8.1/CMakeFiles/Export/d6b66e93f8212dd1f00debf9f6654819/libpqxx-targets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/libpqxx" TYPE FILE FILES "C:/Users/atema/CLionProjects/CourseWork/cmake-build-debug/lib/libpqxx-7.8.1/CMakeFiles/Export/d6b66e93f8212dd1f00debf9f6654819/libpqxx-targets-debug.cmake")
  endif()
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/atema/CLionProjects/CourseWork/cmake-build-debug/lib/libpqxx-7.8.1/src/cmake_install.cmake")
  include("C:/Users/atema/CLionProjects/CourseWork/cmake-build-debug/lib/libpqxx-7.8.1/include/cmake_install.cmake")
  include("C:/Users/atema/CLionProjects/CourseWork/cmake-build-debug/lib/libpqxx-7.8.1/test/cmake_install.cmake")

endif()

