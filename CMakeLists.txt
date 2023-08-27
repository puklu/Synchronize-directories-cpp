cmake_minimum_required(VERSION 3.16.3)
set(CMAKE_BUILD_TYPE "Debug")

project(synchronize-directories-cpp)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")

# include_directories(include)
find_package(OpenSSL REQUIRED)

set(SOURCES
    src/main.cpp
    src/synchronize.cpp
    src/helpers.cpp
)

# add_library(sync src/synchronize.cpp)

add_executable(main ${SOURCES})

target_include_directories(main PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(main PRIVATE OpenSSL::Crypto)    

