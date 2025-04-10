#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 3.17)
project(Simulation_of_a_calorimeter_cell)

set(CMAKE_MODULE_PATH
    ${Geant4_DIR}/Modules/
    ${CMAKE_MODULE_PATH}
)

# Uncomment these if you want to enforce C++17
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

#----------------------------------------------------------------------------
# Find ROOT and Geant4 packages
find_package(ROOT REQUIRED)
find_program(ROOT_rootcling_CMD rootcling)
if(NOT ROOT_rootcling_CMD)
    message(FATAL_ERROR "rootcling not found. Please ensure ROOT is installed correctly.")
endif()

option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
    find_package(Geant4 REQUIRED ui_all vis_all)
else()
    find_package(Geant4 REQUIRED)
endif()

#----------------------------------------------------------------------------
# ROOT Dictionary Generation
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Dict.cxx
    COMMAND ${ROOT_rootcling_CMD}
    ARGS -f ${CMAKE_CURRENT_BINARY_DIR}/Dict.cxx
         -c
         -I${CMAKE_SOURCE_DIR}/include
         ${CMAKE_SOURCE_DIR}/include/MyDict.h
         ${CMAKE_SOURCE_DIR}/include/LinkDef.h
    DEPENDS ${CMAKE_SOURCE_DIR}/include/MyDict.h
            ${CMAKE_SOURCE_DIR}/include/LinkDef.h
)

# Create shared library from dictionary
add_library(MyDict SHARED ${CMAKE_CURRENT_BINARY_DIR}/Dict.cxx)
target_include_directories(MyDict PRIVATE
    ${ROOT_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/include
)
target_link_libraries(MyDict PRIVATE ${ROOT_LIBRARIES})

#----------------------------------------------------------------------------
# Setup include directories
include(${Geant4_USE_FILE})
include_directories(${Geant4_INCLUDE_DIRS})  # Explicitly add Geant4 include dirs
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${ROOT_INCLUDE_DIRS})

# Note: ${AliEvent_INCLUDE_DIRS} is included but undefined; remove if not needed
# set(INCLUDE_DIRECTORIES
#     ${ROOT_INCLUDE_DIRS} ${AliEvent_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/include
# )
# include_directories(${INCLUDE_DIRECTORIES})

# set(LINK_DIRECTORIES ${ROOT_LIBRARY_DIR}) is unnecessary; target_link_libraries handles this

#----------------------------------------------------------------------------
# Locate sources and headers
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

#----------------------------------------------------------------------------
# Add the executable and link it to the libraries
add_executable(Simulation_of_a_calorimeter_cell.exe
    Simulation_of_a_calorimeter_cell.cpp
    ${sources}
    ${headers}
)

target_link_libraries(Simulation_of_a_calorimeter_cell.exe
    PRIVATE
    ${Geant4_LIBRARIES}
    ${ROOT_LIBRARIES}
    MyDict
)

# Optional: Print linked libraries for debugging
# get_target_property(LINKED_LIBS Simulation_of_a_calorimeter_cell.exe LINK_LIBRARIES)
# message(STATUS "Linked libraries: ${LINKED_LIBS}")