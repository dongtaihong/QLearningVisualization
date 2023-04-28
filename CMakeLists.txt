cmake_minimum_required(VERSION 2.6)
project(Qlearning)
# c++ 11
set(CMAKE_CXX_FLAGS "-std=c++11")
# 调试程序
set(CMAKE_BUILD_TYPE "Debug")
 
find_package(OpenCV 4.7.0 REQUIRED) 	# find opencv4.7 installed path
include_directories(OpenCV_INCLUDE_DIRS)	# load opencv header files
include_directories(include)
add_executable(Qlearning src/main.cpp src/Qlearning.cpp)	# create exe file
target_link_libraries(Qlearning ${OpenCV_LIBS})	# link llib files to exe