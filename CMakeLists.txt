cmake_minimum_required (VERSION 2.8)

#compiler options
if(NOT DEFINED ENV{CC})
set(ENV{CC} "/usr/bin/gcc")
message(STATUS "auto set GCC= " $ENV{CC} )
else()
message(STATUS "you have set CC= " $ENV{CC} )
endif()

set(CMAKE_C_COMPILER $ENV{CC})
#g++ options
if (NOT DEFINED ENV{CXX})
    set(ENV{CXX} "/usr/bin/g++")
    message(STATUS "auto set G++= " $ENV{CXX})
else ()
    message(STATUS "you have set CXX= " $ENV{CXX})
endif ()

# C++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set Optimization Flags
set(CMAKE_CXX_FLAGS "-std=c++20 -Wall -Werror=return-type -Werror=unused-variable -Werror=unused-parameter")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -DNO_RACE_CHECK -DADB_DEBUG_MODE=1")
set(CMAKE_CXX_FLAGS_RELEASE "-Wno-ignored-qualifiers -Wno-sign-compare -O3")


project (MYOPENCL)
#LIB OPTIONS
option(MAKE_LIB "make the library" OFF)
#set (LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/libbin)
#self
aux_source_directory (${PROJECT_SOURCE_DIR}/src/ MYOPENCL_BODY_LIST)
aux_source_directory (${PROJECT_SOURCE_DIR}/src/TonyFlowLib TFL_BODY_LIST)
include_directories  (${PROJECT_SOURCE_DIR}/include)
file(GLOB MYOPENCL_H_LIST ${PROJECT_SOURCE_DIR}/include/*.h)

aux_source_directory (${PROJECT_SOURCE_DIR}/example/ EXAMPLE_LIST)
#headers
set (HEADERS_SRC ${MYOPENCL_H_LIST})
#generate

add_executable (tcomp32_cl ${EXAMPLE_LIST} ${MYOPENCL_BODY_LIST} ${TFL_BODY_LIST})
target_link_libraries(tcomp32_cl OpenCL)

#set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/$ENV{CC}_build)
#set (LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/$ENV{CC}_build)

#install(DIRECTORY "include" DESTINATION "/aliancedb" COMPONENT aliancedb)
file(COPY ${PROJECT_SOURCE_DIR}/src/cl/
DESTINATION ${CMAKE_CURRENT_BINARY_DIR})