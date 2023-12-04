cmake_minimum_required (VERSION 2.8.12.2)
project (es2button)
set(CMAKE_INSTALL_PREFIX "/usr")
set(CMAKE_PROJECT_VERSION_MAJOR 0)
set(CMAKE_PROJECT_VERSION_MINOR 2)
set(CMAKE_PROJECT_VERSION_PATCH 1)
set(CMAKE_PROJECT_HOMEPAGE_URL "https://github.com/janrueth/es2button")

# download epson source
set(ESPONVERSION 6.7.43.0-1)
set(ESPONSHA1 0b4e4c2b43e1ef02bf593f3a108e0f78a3b59a0c)
set(EPSONPACKAGE epsonscan2-${ESPONVERSION})
set(EPSONFILENAME ${EPSONPACKAGE}.src.tar.gz)

set(CURRENT_EPSONSHA1 "DOES NOT EXIST")
if(EXISTS ${CMAKE_CURRENT_BINARY_DIR}/${EPSONFILENAME})
  message(" found ${EPSONFILENAME} checking SHA1")
  file(SHA1 ${CMAKE_CURRENT_BINARY_DIR}/${EPSONFILENAME} CURRENT_EPSONSHA1)
endif()

if(NOT ${CURRENT_EPSONSHA1} STREQUAL ${ESPONSHA1})
  message(" ${EPSONFILENAME} does not exist or has invalid sha1, downloading")
  file(DOWNLOAD
    https://support.epson.net/linux/src/scanner/epsonscan2/${EPSONFILENAME}
    ${CMAKE_CURRENT_BINARY_DIR}/${EPSONFILENAME}
    SHOW_PROGRESS
  )
endif()


set(ES2INCLUDE
  "${CMAKE_CURRENT_BINARY_DIR}/epsonscan2"
)
set(ES2MAINHEADER
  ${ES2INCLUDE}/Include/ES2Command/ES2CommandAPI.h
)
# we create a command that untar the epson source
add_custom_command(OUTPUT ${ES2MAINHEADER}
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  # untar
  COMMAND ${CMAKE_COMMAND} -E tar x ${CMAKE_CURRENT_BINARY_DIR}/${EPSONFILENAME} ${EPSONPACKAGE}/src
  # cmake's tar can't strip folders so we do that manually by renaming
  COMMAND ${CMAKE_COMMAND} -E rename ${EPSONPACKAGE}/src ${ES2INCLUDE}
  COMMAND ${CMAKE_COMMAND} -E rm -rf ${EPSONPACKAGE}
)
# we add a target that uses that command
add_custom_target(es2untar DEPENDS ${ES2MAINHEADER})


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

# We need to dynamically load libes2command.so but dlopen does not search subfolders
# as such, we just grab the install location that epsonscan2 uses
include(GNUInstallDirs)
set(EPSONSCAN2_LIB_PATH ${CMAKE_INSTALL_FULL_LIBDIR}/epsonscan2/)
message(" EPSONSCAN2_LIB_PATH: ${EPSONSCAN2_LIB_PATH}")
set(ES2CONF_DIR /etc/es2button)

# we template the config.h.in file to config.h
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/templates/config.h.in ${CMAKE_CURRENT_BINARY_DIR}/generated/config.h)

include_directories(
  ${ES2INCLUDE}
  ${Boost_INCLUDE_DIRS}
  ${LIBUSB_INCLUDE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}/generated
  nlohmann_json::nlohmann_json
)


add_executable(es2button
  ./src/main.cpp
)

# make sure we've got the epsonscan2 headers when we build es2button
add_dependencies(es2button es2untar)

target_link_libraries(es2button
  PRIVATE nlohmann_json::nlohmann_json # this is a header only library, so no actual linkage
  PRIVATE ${CMAKE_DL_LIBS}
  PRIVATE ${LIBUSB_LIBRARY}
)

# this installs es2button
install(TARGETS es2button)
# copy udev rule and make sure it is executed after epsonscan2.rules (60)
install(FILES resources/udev-es2button.rules DESTINATION /lib/udev/rules.d/ RENAME 61-es2button.rules)
# copy systemd rule which is activated by udev
install(FILES resources/systemd.service DESTINATION /lib/systemd/system/ RENAME es2button@.service)
# copy files to etc, there is a post install script that links default to entrypoint if not already exist
install(FILES resources/default.sh
  DESTINATION ${ES2CONF_DIR}
  RENAME default
  PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_WRITE GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
install(FILES resources/README.md DESTINATION ${ES2CONF_DIR} RENAME README.md)
# copy example folder to share
install(DIRECTORY example DESTINATION share/es2button/)

set(CPACK_GENERATOR DEB)
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Jan Rüth")
set(CPACK_PACKAGE_CONTACT "es2button@djiehmail.com")
set(CPACK_DEBIAN_FILE_NAME "DEB-DEFAULT")
set(CPACK_OUTPUT_FILE_PREFIX "./artifacts")
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS "YES")
# we'll run a script after installation to link default to entrypoint if required
set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "${CMAKE_CURRENT_SOURCE_DIR}/resources/preinst;${CMAKE_CURRENT_SOURCE_DIR}/resources/postinst;")
# since we dynamically load libes2command.so
# let's make sure the deb file depends on the corresponding package
# we also want udev and systemd
set(CPACK_DEBIAN_PACKAGE_DEPENDS "epsonscan2, udev, systemd")
include(CPack)