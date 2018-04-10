cmake_minimum_required(VERSION 3.0)
set(PROJECT_NAME "python_extension")
project(${PROJECT_NAME})

set(SHARED_LIB "pyextension")

# Add src code.
aux_source_directory(${CMAKE_SOURCE_DIR} SRC)

# Include headers in below directory.
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_SOURCE_DIR})

# Use c++11.
set(CMAKE_CXX_FLAGS "-g -fPIC -std=c++11 -I/usr/include/python2.7/ -pipe -Wno-deprecated-declarations")

# Build shared library.
ADD_LIBRARY(${SHARED_LIB} SHARED ${SRC})
target_link_libraries(${SHARED_LIB} libboost_python.a)

# Copy shared lib.
add_custom_command(TARGET ${SHARED_LIB} POST_BUILD
    COMMAND cp ${CMAKE_CURRENT_BINARY_DIR}/lib${SHARED_LIB}.so ${CMAKE_SOURCE_DIR}/test/
)
