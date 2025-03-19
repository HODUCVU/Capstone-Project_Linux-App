cmake_minimum_required(VERSION 3.16)

project(IVI-System-App LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_executable(IVI-System-App
  main.cpp

  utils/commands.h utils/commands.cpp
  DeviceStats/SystemStats/systemcpu.h DeviceStats/SystemStats/systemcpu.cpp
  DeviceStats/SystemStats/cpucore.h DeviceStats/SystemStats/cpucore.cpp
  utils/processcommand.h utils/processcommand.cpp


)
target_link_libraries(IVI-System-App Qt${QT_VERSION_MAJOR}::Core)

include(GNUInstallDirs)
install(TARGETS IVI-System-App
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
