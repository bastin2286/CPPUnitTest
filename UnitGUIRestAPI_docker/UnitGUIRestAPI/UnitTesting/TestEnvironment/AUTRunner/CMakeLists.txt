cmake_minimum_required(VERSION 3.12.4)

if(NOT CMAKE_VERSION VERSION_LESS 3.0)
    cmake_policy(SET CMP0048 NEW)
endif()

project(AUT)

# Find requirements
if(NOT fastcdr_FOUND)
    find_package(fastcdr REQUIRED)
endif()

if(NOT foonathan_memory_FOUND)
    find_package(foonathan_memory REQUIRED)
endif()

if(NOT fastrtps_FOUND)
    find_package(fastrtps REQUIRED)
endif()

# Set C++11
include(CheckCXXCompilerFlag)
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANG OR
        CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    check_cxx_compiler_flag(-std=c++17 SUPPORTS_CXX11)
    if(SUPPORTS_CXX11)
        add_compile_options(-std=c++17)
    else()
        message(FATAL_ERROR "Compiler doesn't support C++11")
    endif()
endif()

message(STATUS "Configuring Application...")
file(GLOB AUT_SOURCES_CPP "*.cpp")

message(STATUS "Configuring BOT...")
file(GLOB APP_SOURCES_CPP "Application/*.cpp")
file(GLOB BOT_SOURCES_CPP "Api/*.cpp")
message(STATUS "Configuring DDS...")
file(GLOB DDS_SOURCES_CPP "Dds/*.cpp")
file(GLOB DDS_SOURCES_CXX "Dds/*.cxx")


#configure_file("DataPacketSubscriber.xml" "DataPacketSubscriber.xml" COPYONLY)
#configure_file("DataPacketPublisher.xml" "DataPacketPublisher.xml" COPYONLY)
configure_file("dh2048.pem" "dh2048.pem" COPYONLY)
configure_file("server.pem" "server.pem" COPYONLY)
configure_file("ca.pem" "ca.pem" COPYONLY)

add_executable(AUT_Exec ${APP_SOURCES_CPP} ${BOT_SOURCES_CPP} ${AUT_SOURCES_CPP} ${DDS_SOURCES_CPP} ${DDS_SOURCES_CXX})
target_link_libraries(AUT_Exec libmath.a)
target_link_libraries(AUT_Exec fastrtps fastcdr foonathan_memory -L./Lib/)
