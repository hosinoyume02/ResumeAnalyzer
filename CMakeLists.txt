cmake_minimum_required(VERSION 3.21)
project(ResumeAnalyzer)

set(CMAKE_CXX_STANDARD 17)

if (MSVC)
    add_compile_options(/Zc:__cplusplus)
endif()

find_package(Qt6 REQUIRED COMPONENTS Core Sql)

add_executable(ResumeAnalyzer
        main.cpp
        resume.h
        Resume.cpp
        resume_repository.h
        resume_repository.cpp
)

target_link_libraries(ResumeAnalyzer
        Qt6::Core
        Qt6::Sql

)