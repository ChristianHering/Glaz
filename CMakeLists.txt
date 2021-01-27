cmake_minimum_required(VERSION 3.13)
 
project(
    Glass
    VERSION 0.0.1
    LANGUAGES C)
 
file(GLOB SOURCES "./*.c" "./utils/*.c")
add_executable(${PROJECT_NAME})
 
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(Glass PRIVATE Threads::Threads)
