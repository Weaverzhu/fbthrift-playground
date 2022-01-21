include(${CMAKE_SOURCE_DIR}/external/fbthrift/ThriftLibrary.cmake)


thrift_library(
    echo
    EchoService
    cpp2
    ""
    ${CMAKE_SOURCE_DIR}/playground/idl
    ${CMAKE_BINARY_DIR}/playground/idl
    playground/idl
)