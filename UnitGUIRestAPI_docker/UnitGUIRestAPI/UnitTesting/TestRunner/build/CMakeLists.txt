cmake_minimum_required(VERSION 3.12.4)

if(NOT CMAKE_VERSION VERSION_LESS 3.0)
    cmake_policy(SET CMP0048 NEW)
endif()


project(DDS_Server)



# Set C++11
include(CheckCXXCompilerFlag)
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANG OR
        CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    check_cxx_compiler_flag(-std=c++11 SUPPORTS_CXX11)
    if(SUPPORTS_CXX11)
        add_compile_options(-std=c++11)
    else()
        message(FATAL_ERROR "Compiler doesn't support C++11")
    endif()
endif()

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

message(STATUS "Configuring DDS_Server publisher/subscriber example...")
file(GLOB DDS_Server_SOURCES_CXX "../dds/*.cxx")
file(GLOB DDS_Server_SOURCES_CPP "../dds/*.cpp")
file(GLOB LOGGER_SOURCES_CPP "../logger/*.cpp")
file(GLOB TESTSCRIPT_SOURCES_CPP "../test_scripts/*.cpp")
file(GLOB UTILITY_SOURCES_CPP "../utility/*.cpp")
file(GLOB LIBRARY_SOURCES_CPP "../test_library/*.cpp")
#file(GLOB XML_CONFIG_FILES "*.xml")
#message(STATUS "XML Files: " ${XML_CONFIG_FILES})
configure_file("DataPacketSubscriber.xml" "DataPacketSubscriber.xml" COPYONLY)
configure_file("DataPacketPublisher.xml" "DataPacketPublisher.xml" COPYONLY)
configure_file("dh2048.pem" "dh2048.pem" COPYONLY)
configure_file("server.pem" "server.pem" COPYONLY)
configure_file("ca.pem" "ca.pem" COPYONLY)
 
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
#include_directories("/home/bastin/.conan/data/poco/1.9.4/_/_/package/5b42a10c0c412cd0da6d8fcad2b82db24fc73c81/include")
#message (${GTEST_INCLUDE_DIRS})

#file(GLOB F /usr/local/lib)

add_executable(Gtest_Exec ${DDS_Server_SOURCES_CXX} ${DDS_Server_SOURCES_CPP} ${LOGGER_SOURCES_CPP} ${TESTSCRIPT_SOURCES_CPP} ${UTILITY_SOURCES_CPP} ${LIBRARY_SOURCES_CPP})
#target_link_libraries(Gtest_Exec libPocoZip.a libPocoNetSSL.a libPocoUtil.a libPocoDataSQLite.a libPocoRedis.a libPocoMongoDB.a libPocoNet.a libPocoEncodings.a libPocoXML.a libPocoData.a libPocoCrypto.a libPocoJSON.a libPocoFoundation.a)
target_link_libraries(Gtest_Exec fastrtps fastcdr foonathan_memory -L./bin/ ${GTEST_LIBRARIES} pthread)
