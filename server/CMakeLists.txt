cmake_minimum_required(VERSION 3.6)
project(server)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_PREFIX_PATH /home/sepehr007/Desktop/QT5.8/5.8/gcc_64/)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui Network Multimedia)


set(cmake_prefix_path ${qt5_base_dir}/lib/cmake)

set(SOURCE_FILES main.cpp sourc/head/server.h sourc/c++ha/server.cpp sourc/c++ha/timer.cpp sourc/head/timer.h sourc/c++ha/timemanage.cpp sourc/head/timemanage.h)#sources/headerfiles/sample.h sources/sourcesfiles/sample.cpp sources/headerfiles/chatdesign.h sources/sourcesfiles/chatdesign.cpp sources/headerfiles/loginmenu.h sources/sourcesfiles/loginmenu.cpp sources/headerfiles/connection.h sources/sourcesfiles/connection.cpp sources/headerfiles/interface.h sources/sourcesfiles/interface.cpp sources/headerfiles/client.h sources/sourcesfiles/client.cpp)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${CMAKE_PROJECT_NAME} Qt5::Core Qt5::Widgets Qt5::Gui Qt5::Network Qt5::Multimedia)