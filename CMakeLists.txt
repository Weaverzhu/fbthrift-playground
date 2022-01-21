project(playground)

cmake_minimum_required(VERSION 3.18)
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)

option(ASAN "santiizer" OFF)

if (ASAN)
    add_compile_options(-fsanitize=address -g -O0)
    add_link_options(-fsanitize=address)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS on)

find_package(Threads REQUIRED)
set(OPT_PATH ${CMAKE_BINARY_DIR}/opt/playground)
include_directories(${OPT_PATH}/include)
include_directories(${CMAKE_BINARY_DIR})
include_directories(${CMAKE_SOURCE_DIR})



if (CMAKE_BUILD_TYPE EQUAL "DEBUG")
    message("debug mode")
endif (CMAKE_BUILD_TYPE EQUAL "DEBUG")

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} 
    ${CMAKE_BINARY_DIR}/opt/playground
    ${CMAKE_BINARY_DIR}/opt/playground/lib
    ${CMAKE_BINARY_DIR}/opt/playground/lib/cmake
)
set(PKG_CONFIG_PATH ${PKG_CONFIG_PATH}
    ${CMAKE_BINARY_DIR}/opt/playground/lib/pkgconfig
    /usr/lib/x86_64-linux-gnu/pkgconfig
)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
    ${CMAKE_SOURCE_DIR}/cmake
    ${CMAKE_SOURCE_DIR}/external/folly/CMake
)

set(CMAKE_INSTALL_PREFIX ${OPT_PATH})
set(CMAKE_CXX_STANDARD 20)
add_compile_options(-Wno-deprecated)

set(THRIFT1 ${OPT_PATH}/bin/thrift1)
set(THRIFTCPP2 ${OPT_PATH}/lib/libthriftcpp2.a)


find_package(gflags REQUIRED)
find_package(glog REQUIRED)
find_package(folly REQUIRED)
find_package(wangle REQUIRED)
find_package(PkgConfig)
find_package(Boost  COMPONENTS ALL)
find_package(FBThrift REQUIRED)
pkg_check_modules(Sodium REQUIRED libsodium)
find_package(fizz REQUIRED)


pkg_check_modules(libunwind REQUIRED libunwind)
pkg_check_modules(libevent REQUIRED libevent)
pkg_check_modules(fmt REQUIRED fmt)

add_library(rpc_bundle INTERFACE)
target_link_libraries(rpc_bundle INTERFACE
    Folly::folly
    FBThrift::thriftcpp2
    FBThrift::concurrency
    FBThrift::transport
    FBThrift::thrift-core
    gflags
    glog
    ${Boost_LIBRARIES}
    wangle::wangle
)
link_libraries(rpc_bundle)

add_subdirectory(playground)
