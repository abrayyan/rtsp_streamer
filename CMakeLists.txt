cmake_minimum_required(VERSION 3.17)
project(rtsp_streamer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(GStreamer 1.0 REQUIRED)


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

add_executable(rtsp_streamer streamer.cpp)
target_include_directories(rtsp_streamer SYSTEM PUBLIC
        ${GSTREAMER_INCLUDE_DIRS})

target_link_libraries(rtsp_streamer
        ${GSTREAMER_LIBS})
