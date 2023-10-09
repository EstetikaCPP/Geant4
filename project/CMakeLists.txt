cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(Test)

find_package(Geant4 REQUIRED ui_all vis_all)
find_package(Qt5 COMPONENTS Widgets Core REQUIRED)


include(${Geant4_USE_FILE})

file(GLOB sources ${PROJECT_SOURCE_DIR}/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/*.hh)

add_executable(test main.cc ${sources} ${headers})

target_link_libraries(test ${Geant4_LIBRARIES})
target_link_libraries(test Qt5::Widgets)


add_custom_target(Test DEPENDS test)
