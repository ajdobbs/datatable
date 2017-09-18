# DataTable top level CMake build script - A. J. Dobbs
cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(datatable VERSION 0.1.0 LANGUAGES CXX)
set (CMAKE_CXX_STANDARD 11)

# Specify where build output should go
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

# Specify include locations
include_directories(include)

# Build the DataTable library
add_library(DataTableCore SHARED src/PropertyBase.cc
                                 src/Property.cc
                                 src/Table.cc)


# Build the app
link_directories(${CMAKE_BINARY_DIR})
add_executable(datatable app/datatable.cc)
target_link_libraries(datatable DataTableCore)

# Specify where installing will place the output
install(TARGETS datatable DataTableCore
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
