project( hourglass )

cmake_minimum_required( VERSION 2.8.12 )

find_package( Threads REQUIRED )

include_directories( include )

aux_source_directory( src SRC )

file( GLOB INCLUDE include/*.hpp )

add_executable( ${PROJECT_NAME}-test
    ${SRC}
    test/main.cpp
)

target_compile_options( ${PROJECT_NAME}-test
    PRIVATE
        -pthread
        -std=c++11
        -Wall
        -Wextra
        -Wshadow
)

target_link_libraries( ${PROJECT_NAME}-test
    pthread
)

add_library( ${PROJECT_NAME}
    SHARED
        ${SRC}
)

target_compile_options( ${PROJECT_NAME}
    PRIVATE
        -pthread
        -std=c++11
        -Wall
        -Wextra
        -Wshadow
)

target_link_libraries( ${PROJECT_NAME}
    pthread
)

install(
    TARGETS
        ${PROJECT_NAME}
    DESTINATION
        /usr/local/lib
)

install(
    FILES
        ${INCLUDE}
    DESTINATION
        /usr/local/include/hourglass/
)
