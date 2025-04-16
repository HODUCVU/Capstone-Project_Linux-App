cmake_minimum_required(VERSION 3.16)

project(IVI-System-App LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Network)

add_executable(IVI-System-App
  main.cpp
  testing.h testing.cpp

  utils/commands.h utils/commands.cpp
  DeviceStats/SystemStats/systemcpu.h DeviceStats/SystemStats/systemcpu.cpp
  DeviceStats/SystemStats/cpucore.h DeviceStats/SystemStats/cpucore.cpp
  utils/processcommand.h utils/processcommand.cpp
  DeviceStats/SystemStats/systemmem.h DeviceStats/SystemStats/systemmem.cpp
  DeviceStats/SystemStats/systemstats.h DeviceStats/SystemStats/systemstats.cpp


  DeviceStats/ProcessesStats/processesstats.h DeviceStats/ProcessesStats/processesstats.cpp
  DeviceStats/ProcessesStats/processstats.h DeviceStats/ProcessesStats/processstats.cpp
  OverloadSolution/terminateprocesses.h OverloadSolution/terminateprocesses.cpp
  DeviceStats/SystemStats/cpugeneral.h DeviceStats/SystemStats/cpugeneral.cpp
  utils/installlinuxapi.h utils/installlinuxapi.cpp
  TCPService/tcpservice.h TCPService/tcpservice.cpp
  TCPService/receiverworker.h TCPService/receiverworker.cpp
  TCPService/senderworker.h TCPService/senderworker.cpp
  utils/hostIPAddress.h
  OverloadSolution/devicespeaker.h OverloadSolution/devicespeaker.cpp
  OverloadSolution/stresstestsystem.h OverloadSolution/stresstestsystem.cpp
)
target_link_libraries(IVI-System-App Qt${QT_VERSION_MAJOR}::Core
    Qt6::Network)

include(GNUInstallDirs)
install(TARGETS IVI-System-App
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
