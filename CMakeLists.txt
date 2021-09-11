cmake_minimum_required(VERSION 3.8)
project(EyeDetect)

set(CMAKE_CXX_STANDARD 17)

# Include a library search using find_package() 
# via REQUIRED, specify that libraries are required
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Charts REQUIRED)

add_subdirectory(3rdparty/gflags)
add_subdirectory(3rdparty/glog)
add_subdirectory(3rdparty/json)


set(JSON_BuildTests OFF CACHE INTERNAL "")

set(SOURCE_FILES main.cpp config.cpp config.h dashboard.cpp dashboard.h ipaddr.h ipaddr.cpp)
add_executable(EyeDetect ${SOURCE_FILES})

include_directories("${CMAKE_SOURCE_DIR}/3rdparty/ed/include")
find_library(ED_LIB ed "${CMAKE_SOURCE_DIR}/3rdparty/ed/bin")

# specify which libraries to connect
target_link_libraries(${PROJECT_NAME} Qt5::Core)
target_link_libraries(${PROJECT_NAME} Qt5::Gui)
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
target_link_libraries(${PROJECT_NAME} Qt5::Charts)

target_link_libraries(${PROJECT_NAME} gflags::gflags)
target_link_libraries(${PROJECT_NAME} glog::glog)
target_link_libraries(${PROJECT_NAME} nlohmann_json::nlohmann_json)
target_link_libraries(${PROJECT_NAME} ${ED_LIB})
