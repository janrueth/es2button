cmake_minimum_required (VERSION 2.8.12.2)
project (es2button)
set (CMAKE_INSTALL_PREFIX "/usr")

set(Boost_USE_STATIC_LIBS        OFF)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME     OFF)
find_package(Boost 1.36.0 REQUIRED)
message(" Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}") 
message(" Boost_LIBRARIES: ${Boost_LIBRARIES}")  
message(" Boost_LIBRARY_DIRS: ${Boost_LIBRARY_DIRS}") 

find_library(ES2COMMAND_LIBRARY 
es2command
PATH_SUFFIXES "epsonscan2"
)
message(" ES2COMMAND_LIBRARY: ${ES2COMMAND_LIBRARY}") 

find_package(nlohmann_json 3.9.1 REQUIRED)

find_path(LIBUSB_INCLUDE_DIR
  NAMES libusb.h
  PATH_SUFFIXES "include" "libusb" "libusb-1.0" 
  REQUIRED)

find_library(LIBUSB_LIBRARY
  usb-1.0
  REQUIRED)

  message(" LIBUSB_LIBRARY: ${LIBUSB_LIBRARY}") 
  message(" LIBUSB_INCLUDE_DIR: ${LIBUSB_INCLUDE_DIR}") 

include_directories(
    ./include/
    ${Boost_INCLUDE_DIRS}
    ${LIBUSB_INCLUDE_DIR}
    nlohmann_json::nlohmann_json
)

add_executable(ess2devstate
./main.cpp
)


target_link_libraries(ess2devstate 
${ES2COMMAND_LIBRARY}
nlohmann_json::nlohmann_json
${LIBUSB_LIBRARY}
)

