# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\ResumeAnalyzer_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\ResumeAnalyzer_autogen.dir\\ParseCache.txt"
  "ResumeAnalyzer_autogen"
  )
endif()
