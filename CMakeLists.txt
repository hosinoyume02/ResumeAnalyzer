cmake_minimum_required(VERSION 3.25)
project(ResumeAnalyzer)

set(CMAKE_CXX_STANDARD 17)

# 设置 Qt 安装路径
set(CMAKE_PREFIX_PATH "E:/Qt/6.9.0/msvc2022_64/lib/cmake")

# 启用 Qt 自动功能
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# 查找 Qt 库组件
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Sql Charts)

# 添加 include 目录（如果你用了 include 文件夹）
include_directories(${CMAKE_SOURCE_DIR})

# 添加源文件
set(SOURCES
        Resume.cpp
        ResumeManager.cpp
        ResumeFilterWidget.cpp
        MainWindow.cpp
        main.cpp
        Job.cpp
        JobWidget.cpp
        ResumeWidget.cpp
        RecommendationWidget.cpp
        AdminWidget.cpp
        User.cpp
        LoginWindow.cpp
)

# 添加头文件（仅 .h/.hpp）
set(HEADERS
        Resume.h
        ResumeManager.h
        ResumeFilterWidget.h
        MainWindow.h
        Job.h
        JobWidget.h
        ResumeWidget.h
        RecommendationWidget.h
        AdminWidget.h
        User.h
        LoginWindow.h
)

# 创建可执行文件
add_executable(ResumeAnalyzer ${SOURCES} ${HEADERS})

# 链接 Qt 库
target_link_libraries(ResumeAnalyzer
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::Sql
        Qt6::Charts
)
