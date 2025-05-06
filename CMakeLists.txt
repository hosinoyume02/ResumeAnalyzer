cmake_minimum_required(VERSION 3.25)
project(ResumeAnalyzer)

set(CMAKE_CXX_STANDARD 17)

# 设置 Qt 安装路径（你要根据自己的 Qt 安装路径修改）
set(CMAKE_PREFIX_PATH "E:/Qt/6.8.0/msvc2019_64/lib/cmake")

# 找 Qt 库
find_package(Qt6 REQUIRED COMPONENTS Core Sql Widgets)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
# 添加源文件
set(SOURCES
        main.cpp
        Resume.cpp
        resume_repository.cpp
        MainWindow.cpp
)

set(HEADERS
        Resume.h
        resume_repository.h
        MainWindow.h
        MainWindow.h
        MainWindow.cpp
        user_manager.cpp
        user_manager.h
        resume_parser.h
        resume_parser.cpp
        test_data_generator.h
        test_data_generator.cpp
        analyzer.h
        analyzer.cpp
        charts_widget.h
        charts_widget.cpp
)
target_link_libraries(ResumeAnalyzer PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::Sql
        Qt6::Charts
)
# Qt UI（暂时我们不使用 .ui 文件，可以忽略）
add_executable(ResumeAnalyzer ${SOURCES} ${HEADERS})

# 链接 Qt 库
target_link_libraries(ResumeAnalyzer Qt6::Core Qt6::Sql Qt6::Widgets)
