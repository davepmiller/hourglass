project( hourglass )

cmake_minimum_required( VERSION 2.8.12 )

find_package( Threads REQUIRED )

# Compiler-specific C++11 activation.
if( "${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU" )
    execute_process(
        COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
    if( NOT ( GCC_VERSION VERSION_GREATER 4.7 OR
              GCC_VERSION VERSION_EQUAL 4.7 ) )
        message( FATAL_ERROR "${PROJECT_NAME} requires g++ 4.7 or greater." )
    endif ()
elseif ( "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang" )
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++" )
else ()
    message( FATAL_ERROR "Your C++ compiler does not support C++11." )
endif ()

include_directories( include )

aux_source_directory( src SRC_LIST )

add_executable( ${PROJECT_NAME}-test
    ${SRC_LIST}
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
        ${SRC_LIST}
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
