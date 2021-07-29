cmake_minimum_required(VERSION 3.17)
project(rtsp_streamer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(GStreamer 1.0 REQUIRED)


#set(SRC ${PROJECT_SOURCE_DIR}/src/rtsp_meta_factory.cpp
#        ${PROJECT_SOURCE_DIR}/src/rtsp_meta_factory.h
#        ${PROJECT_SOURCE_DIR}/src/rtsp_streamer.cpp
#        ${PROJECT_SOURCE_DIR}/src/rtsp_streamer.h
#        ${PROJECT_SOURCE_DIR}/src/data_sources/source_blank.cpp
#        ${PROJECT_SOURCE_DIR}/src/data_sources/source_blank.h
#        ${PROJECT_SOURCE_DIR}/src/data_sources/source_random_test_pattern.cpp
#        ${PROJECT_SOURCE_DIR}/src/data_sources/source_random_test_pattern.h
#        ${PROJECT_SOURCE_DIR}/src/data_sources/source_file.cpp
#        ${PROJECT_SOURCE_DIR}/src/data_sources/source_file.h
#        ${PROJECT_SOURCE_DIR}/src/data_sources/source_rtsp_stream.cpp
#        ${PROJECT_SOURCE_DIR}/src/data_sources/source_rtsp_stream.h
#        ${PROJECT_SOURCE_DIR}/src/hikvision_camera_manager.cpp
#        ${PROJECT_SOURCE_DIR}/src/hikvision_camera_manager.h)


set(GSTREAMER_LIBS
        /usr/lib/x86_64-linux-gnu/libgstrtspserver-1.0.so
        /usr/lib/x86_64-linux-gnu/libgstrtsp-1.0.so
        gstreamer-1.0
        gstbase-1.0
        gstrtp-1.0
        gstsdp-1.0
        gstrtsp-1.0
        gstapp-1.0
        gstnet-1.0
        gobject-2.0
        gmodule-2.0
        gthread-2.0
        glib-2.0
        gio-2.0)


#add_library(${PROJECT_NAME} SHARED ${SRC})

#target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC
#        ${GSTREAMER_INCLUDE_DIRS}
#        ${PROJECT_SOURCE_DIR}/src
#        ${PROJECT_SOURCE_DIR}/src/data_sources
#        ${HCNETSDK_INCLUDE_DIR})
#
#target_link_libraries(${PROJECT_NAME}
#        ${GSTREAMER_LIBS}
#        CONAN_PKG::spdlog
#        CONAN_PKG::nlohmann_json
#        CONAN_PKG::opencv
#        ${HCNETSDK_LIBRARY})



add_executable(rtsp_streamer test.cpp)
target_include_directories(rtsp_streamer SYSTEM PUBLIC
        ${GSTREAMER_INCLUDE_DIRS})

target_link_libraries(rtsp_streamer
        ${GSTREAMER_LIBS})
