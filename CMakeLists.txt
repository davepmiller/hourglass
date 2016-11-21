project( hourglass )

cmake_minimum_required( VERSION 2.8.12 )

find_package( Threads REQUIRED )

include_directories( include )

aux_source_directory( src SRC )

add_executable( ${PROJECT_NAME}-test
    ${SRC}
    test/main.cpp
)

target_compile_options( ${PROJECT_NAME}-test
    PRIVATE
        -std=c++11
        -Wall
        -pthread
)

add_library( ${PROJECT_NAME}
    SHARED
        ${SRC}
)

target_compile_options( ${PROJECT_NAME}
    PRIVATE
        -std=c++11
        -Wall
        -pthread
)

install(
    TARGETS
        ${PROJECT_NAME}
    DESTINATION
        /usr/local/lib
)

file( GLOB INCLUDE include/*.hpp )

install(
    FILES
        ${INCLUDE}
    DESTINATION
        /usr/local/include/hourglass/
)
