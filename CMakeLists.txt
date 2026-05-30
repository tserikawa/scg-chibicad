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
    ${IMGUI_SOURCES}
    ${RLIMGUI_SOURCES}
)

target_include_directories(${PROJECT_NAME} PRIVATE
    libs/raylib-cpp/include
    libs/imgui
    libs/rlImGui
    libs/scg-core/include
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

# FetchContentモジュールを読み込む（外部ライブラリの自動取得に使用）
include(FetchContent)

# GoogleTestをGitHubから取得する設定
# バージョンを変更する場合はURLのタグ（v1.14.0）を変更する
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

# GoogleTestをビルド対象に追加する
FetchContent_MakeAvailable(googletest)

# CMakeのテスト機能を有効化（add_testが使えるようになる）
enable_testing()

# Testsディレクトリのビルド設定を読み込む
# ※ Testsフォルダ内にCMakeLists.txtが必要
add_subdirectory(test)