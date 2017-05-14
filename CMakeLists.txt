cmake_minimum_required( VERSION 2.8.12 FATAL_ERROR )

project( hourglass )

find_package( Threads REQUIRED )

aux_source_directory( src SRC )

file( GLOB INCLUDE include/*.hpp )

add_library( 
    hourglass
        SHARED
            ${SRC}
)

target_compile_options( 
    hourglass
        PRIVATE
            -pthread
            -std=c++11
            -Wall
            -Wextra
            -Wshadow
)

target_include_directories(
    hourglass
        PUBLIC
            include
)

target_link_libraries( 
    hourglass
        pthread
)

set( GOOGLETEST_ROOT 
    external/googletest/googletest CACHE STRING "Google Test source root"
)

set( GOOGLETEST_SOURCES
    ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/src/gtest-all.cc
    ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/src/gtest_main.cc
)

foreach( _source ${GOOGLETEST_SOURCES} )
    set_source_files_properties( ${_source} PROPERTIES GENERATED 1 )
endforeach()

add_library( 
    googletest 
        ${GOOGLETEST_SOURCES} 
)

target_include_directories(
    googletest
        PUBLIC
            ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}
            ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/include
)

add_executable(
    unit_tests
        test/main.cpp
)

add_dependencies( 
    unit_tests 
        googletest
)

target_include_directories(
    unit_tests
        PUBLIC
            ../include
            ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}
            ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/include
)

target_compile_options( 
    unit_tests
        PRIVATE
            -std=c++11
            -Wall
            -Wextra
            -Wshadow
)

target_link_libraries(
    unit_tests
        googletest
        hourglass
        pthread
)

include( CTest )

enable_testing()

add_test( unit 
    ${PROJECT_BINARY_DIR}/unit_tests 
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
