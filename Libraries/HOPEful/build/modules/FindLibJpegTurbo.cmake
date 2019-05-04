
# - Try to find libjpeg-turbo
# Once done, this will define
#
#  JPEG_FOUND - system has libjpeg-turbo
#  JPEG_INCLUDE_DIRS - the libjpeg-turbo include directories
#  JPEG_LIBRARIES - link these to use libjpeg-turbo
#

include (FindPackageHandleStandardArgs)

find_path(JPEGTURBO_INCLUDE_DIR turbojpeg.h
          PATHS /opt/libjpeg-turbo/include
                /usr/include
                ${JPEGTURBO_PATH}/include
                NO_DEFAULT_PATH)

set(JPEGTURBO_NAMES ${JPEGTURBO_NAMES} libturbojpeg turbojpeg)
set(JPEG_NAMES ${JPEG_NAMES} libjpeg jpeg)

find_library(JPEGTURBO_LIBRARY NAMES ${JPEGTURBO_NAMES}
             PATHS ${JPEGTURBO_INCLUDE_DIR}/../lib
                   ${JPEGTURBO_PATH}/lib64
                   ${JPEGTURBO_PATH}/lib
                   /opt/libjpeg-turbo/lib64
                   NO_DEFAULT_PATH)

find_library(JPEG_LIBRARY NAMES ${JPEG_NAMES}
            PATHS ${JPEGTURBO_INCLUDE_DIR}/../lib
                  ${JPEGTURBO_PATH}/lib64
                  ${JPEGTURBO_PATH}/lib
                  /opt/libjpeg-turbo/lib64
                  NO_DEFAULT_PATH)

if (NOT JPEGTURBO_LIBRARY)
find_library(JPEGTURBO_LIBRARY NAMES ${JPEGTURBO_NAMES}
             PATHS ${JPEGTURBO_INCLUDE_DIR}/../lib
                   ${JPEGTURBO_INCLUDE_DIR}/../lib64
                   ${JPEGTURBO_PATH}/lib
                   ${JPEGTURBO_PATH}/lib64
                   /usr/lib
                   /usr/lib64
                   NO_DEFAULT_PATH)

find_library(JPEG_LIBRARY NAMES ${JPEG_NAMES}
           PATHS ${JPEGTURBO_INCLUDE_DIR}/../lib
                 ${JPEGTURBO_INCLUDE_DIR}/../lib64
                 ${JPEGTURBO_PATH}/lib
                 ${JPEGTURBO_PATH}/lib64
                 /usr/lib
                 /usr/lib64
                 NO_DEFAULT_PATH)
endif ()

# handle the QUIETLY and REQUIRED arguments and set JPEG_FOUND to TRUE if
# all listed variables are TRUE
FIND_PACKAGE_HANDLE_STANDARD_ARGS(JPEGTURBO DEFAULT_MSG JPEGTURBO_LIBRARY JPEG_LIBRARY JPEGTURBO_INCLUDE_DIR)

if(JPEGTURBO_FOUND)
  set(JPEGTURBO_LIBRARIES ${JPEGTURBO_LIBRARY})
  set(JPEG_LIBRARIES ${JPEG_LIBRARY})
endif()

mark_as_advanced(JPEGTURBO_LIBRARY JPEGTURBO_INCLUDE_DIR)
mark_as_advanced(JPEG_LIBRARY JPEGTURBO_INCLUDE_DIR)