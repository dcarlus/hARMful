if (UNIX)
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/modules/")

    find_package(LibJpegTurbo REQUIRED)
    if (JPEGTURBO_FOUND)
        include_directories(${JPEGTURBO_INCLUDE_DIRS})
        target_link_libraries(${PROJECT_NAME} ${JPEGTURBO_LIBRARIES})
        target_link_libraries(${PROJECT_NAME} ${JPEG_LIBRARIES})
    endif()

    find_package(PNG REQUIRED)
    if (PNG_FOUND)
        include_directories(${PNG_INCLUDE_DIRS})
        target_link_libraries(${PROJECT_NAME} ${PNG_LIBRARIES})
    endif()
endif()
