cmake_minimum_required(VERSION 3.20)
project(GeometryApp CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(raylib REQUIRED)

set(IMGUI_DIR libs/imgui)
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
)

set(RLIMGUI_DIR libs/rlImGui)
set(RLIMGUI_SOURCES
    ${RLIMGUI_DIR}/rlImGui.cpp
)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/ui/MenuBar.cpp
    src/ui/ControlPanel.cpp
    src/core/AppState.cpp
    src/core/Renderer.cpp
    src/geometry/Point2f.cpp
    src/collection/PointCollection.cpp
    ${IMGUI_SOURCES}
    ${RLIMGUI_SOURCES}
)

target_include_directories(${PROJECT_NAME} PRIVATE
    libs/raylib-cpp/include
    libs/imgui
    libs/rlImGui
    src
)

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

if(APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        "-framework Cocoa"
        "-framework IOKit"
        "-framework OpenGL"
    )
endif()