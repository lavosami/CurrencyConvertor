cmake_minimum_required(VERSION 3.10)

project(convert)

set(CXX_STANDARD 11)
set(CXX_STANDARD_REQUIRED ON)

set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

set(SOURCES
  ${SOURCE_DIR}/main.cpp
  ${SOURCE_DIR}/Currency.cpp
  ${INCLUDE_DIR}/Currency.hpp
  ${INCLUDE_DIR}/json.hpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR})
