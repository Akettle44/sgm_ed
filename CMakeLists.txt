cmake_minimum_required(VERSION 3.0.0)
project(sgm_ed VERSION 0.1.0)
find_package( OpenCV REQUIRED )

include(CTest)
enable_testing()

include_directories("/usr/local/include/opencv4/opencv2")
include_directories("/usr/local/include/opencv4")

add_executable(sgm_ed main.cpp edge.cpp VideoCapture.cpp)
target_link_libraries( sgm_ed ${OpenCV_LIBS} )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

