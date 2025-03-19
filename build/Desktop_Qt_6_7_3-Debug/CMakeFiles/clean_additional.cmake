# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/IVI-System-App_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/IVI-System-App_autogen.dir/ParseCache.txt"
  "IVI-System-App_autogen"
  )
endif()
