cmake_minimum_required(VERSION 3.14)

project(Week_1)
find_package(Boost 1.40.0 COMPONENTS filesystem system iostreams REQUIRED)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/externals/gnuplot-iostream")
set(CMAKE_CXX_STANDARD 14)
add_compile_options(-lboost_iostreams -lboost_system -lboost_filesystem)
add_executable(Week_1 main.cpp ArmSegment.cpp ArmSegment.h RobotArm.cpp RobotArm.h gnuplot-iostream.h)


target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})