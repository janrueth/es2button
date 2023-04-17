cmake_minimum_required (VERSION 2.8.12.2)
project (es2button)
set(CMAKE_INSTALL_PREFIX "/usr")
set(CMAKE_PROJECT_VERSION_MAJOR 0)
set(CMAKE_PROJECT_VERSION_MINOR 1)
set(CMAKE_PROJECT_VERSION_PATCH 0)
set(CMAKE_PROJECT_HOMEPAGE_URL "https://github.com/janrueth/es2button")

# we only need some header definition
find_package(Boost 1.36.0 REQUIRED)
message(" Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")

find_package(nlohmann_json 3.9.1 REQUIRED)

find_path(LIBUSB_INCLUDE_DIR
  NAMES libusb.h
  PATH_SUFFIXES "include" "libusb" "libusb-1.0"
  REQUIRED
)

find_library(LIBUSB_LIBRARY
  usb-1.0
  REQUIRED
)

message(" LIBUSB_LIBRARY: ${LIBUSB_LIBRARY}")
message(" LIBUSB_INCLUDE_DIR: ${LIBUSB_INCLUDE_DIR}")

include_directories(
  ./include/
  ${Boost_INCLUDE_DIRS}
  ${LIBUSB_INCLUDE_DIR}
  nlohmann_json::nlohmann_json
)

# We need to dynamically load libes2command.so but dlopen does not search subfolders
# as such, we just grab the install location that epsonscan2 uses
include(GNUInstallDirs)
set(EPSONSCAN2_LIB_PATH ${CMAKE_INSTALL_FULL_LIBDIR}/epsonscan2/)
message(" EPSONSCAN2_LIB_PATH: ${EPSONSCAN2_LIB_PATH}")
# we template the config.h.in file to config.h
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/config.h)

add_executable(es2button
  ./main.cpp
)


target_link_libraries(es2button
  PRIVATE nlohmann_json::nlohmann_json # this is a header only library, so no actual linkage
  PRIVATE ${CMAKE_DL_LIBS}
  PRIVATE ${LIBUSB_LIBRARY}
)

# this installs es2button to /usr/bin/
install(TARGETS es2button)

set(CPACK_GENERATOR DEB)
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Jan Rüth")
set(CPACK_PACKAGE_CONTACT "es2button@djiehmail.com")
set(CPACK_DEBIAN_FILE_NAME "DEB-DEFAULT")
set(CPACK_OUTPUT_FILE_PREFIX "./artifacts")
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS "YES")
# since we dynamically load libes2command.so, let's make sure the deb file depends on the corresponding package
set(CPACK_DEBIAN_PACKAGE_DEPENDS "epsonscan2")
include(CPack)