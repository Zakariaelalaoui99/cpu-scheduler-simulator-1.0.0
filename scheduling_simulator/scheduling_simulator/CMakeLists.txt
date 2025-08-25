cmake_minimum_required(VERSION 3.16)
project(SchedulerApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt codegen
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC OFF)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# IMPORTANT: tell uic where to search for .ui AND promoted widget headers
# (add BOTH folders!)
set(CMAKE_AUTOUIC_SEARCH_PATHS
    ${CMAKE_CURRENT_SOURCE_DIR}/ui
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(scheduler_app
    # Sources
    src/main.cpp
    src/mainwindow.cpp
    src/controller.cpp
    src/scheduler.cpp
    src/fcfs.cpp
    src/sjf.cpp
    src/rr.cpp
    src/rrp.cpp
    src/ganttchartwidget.cpp

    # UI (list it so CMake/UIC surely sees it)
    ui/mainwindow.ui

    # Headers with Q_OBJECT (helps AUTOMOC + IDEs)
    include/mainwindow.hpp
    include/controller.hpp
    include/ganttchartwidget.hpp

    # Other headers (optional for build, nice for IDEs)
    include/scheduler.hpp
    include/schedulingalgorithm.hpp
    include/fcfs.hpp
    include/sjf.hpp
    include/rr.hpp
    include/rrp.hpp
    include/process.hpp
    include/thread.hpp
    include/ganttentry.hpp
)

target_include_directories(scheduler_app PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(scheduler_app PRIVATE Qt6::Widgets)

if (MSVC)
    target_compile_options(scheduler_app PRIVATE /W3)
else()
    target_compile_options(scheduler_app PRIVATE -Wall -Wextra -Wpedantic)
endif()
