# raylib-cpp 環境構築ガイド（macOS）

## 構成

| 項目 | 内容 |
|------|------|
| OS | macOS（Apple Silicon / Intel 両対応） |
| ビルドシステム | CMake 3.20 以上 |
| エディタ | VS Code |
| ライブラリ | raylib 6.0 + raylib-cpp + Dear ImGui + rlImGui |

---

## 1. 前提ツールのインストール

```bash
# Homebrew（未インストールの場合）
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# CMake
brew install cmake
```

---

## 2. VS Code 拡張機能

以下の3つをインストールする。

| 拡張機能 | ID |
|----------|----|
| C/C++ | `ms-vscode.cpptools` |
| CMake Tools | `ms-vscode.cmake-tools` |
| CMake（シンタックスハイライト） | `twxs.cmake` |

---

## 3. raylib のインストール

### 3-A. Homebrew でインストール（推奨・6.0 対応後）

Homebrew の raylib が 6.0 以上になっていれば、こちらを使う。

```bash
brew install raylib

# バージョン確認
brew info raylib
```

### 3-B. ソースからビルド（Homebrew が 6.0 未満の場合）

Homebrew の raylib がまだ 5.x の場合は、ソースからビルドしてインストールする。

```bash
# 既存の Homebrew 版を削除
brew uninstall raylib

# ソースを取得（6.0 タグ指定）
git clone --depth 1 --branch 6.0 https://github.com/raysan5/raylib.git /tmp/raylib

# ビルド
cd /tmp/raylib
mkdir build && cd build

# Apple Silicon の場合
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/opt/homebrew

# Intel Mac の場合
# cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local

cmake --build . --config Release
sudo cmake --install .

# 後片付け（/tmp は再起動で消えるが手動でも削除可）
rm -rf /tmp/raylib
```

インストール確認：

```bash
pkg-config --modversion raylib
```

---

## 4. raylib-cpp のセットアップ

raylib-cpp はヘッダーオンリーのため、プロジェクトの `libs/` に置くだけでよい。

```bash
cd /path/to/your-project/libs
git clone https://github.com/RobLoach/raylib-cpp.git
```

---

## 5. Dear ImGui + rlImGui のセットアップ

raylib と ImGui を連携させるために **rlImGui** を使う。

### rlImGui とは

raylib 用の ImGui バックエンドで、raylib の描画ループに ImGui を組み込むためのグルーコードを提供するライブラリ。

### ダウンロード

```bash
cd /path/to/your-project/libs

# Dear ImGui 本体
git clone https://github.com/ocornut/imgui.git

# rlImGui（raylib 用バックエンド）
git clone https://github.com/raylib-extras/rlImGui.git
```

---

## 6. プロジェクト構成

```
geometry-app/
├── CMakeLists.txt
├── .vscode/
│   └── settings.json
├── libs/
│   ├── raylib-cpp/       ← git clone で配置
│   ├── imgui/            ← git clone で配置
│   └── rlImGui/          ← git clone で配置
└── src/
    └── main.cpp
```

---

## 7. CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.20)
project(GeometryApp CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(raylib REQUIRED)

# Dear ImGui のソースファイル
set(IMGUI_DIR libs/imgui)
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
)

# rlImGui のソースファイル
set(RLIMGUI_DIR libs/rlImGui)
set(RLIMGUI_SOURCES
    ${RLIMGUI_DIR}/rlImGui.cpp
)

add_executable(${PROJECT_NAME}
    src/main.cpp
    ${IMGUI_SOURCES}
    ${RLIMGUI_SOURCES}
)

target_include_directories(${PROJECT_NAME} PRIVATE
    libs/raylib-cpp/include
    libs/imgui
    libs/rlImGui
)

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

if(APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        "-framework Cocoa"
        "-framework IOKit"
        "-framework OpenGL"
    )
endif()
```

---

## 8. .vscode/settings.json

```json
{
    "cmake.buildDirectory": "${workspaceFolder}/build",
    "cmake.configureArgs": ["-DCMAKE_BUILD_TYPE=Debug"],
    "C_Cpp.default.configurationProvider": "ms-vscode.cmake-tools"
}
```

---

## 9. ImGui の基本的な使い方

```cpp
#include "raylib-cpp.hpp"
#include "rlImGui.h"
#include "imgui.h"

int main() {
    raylib::Window window(1280, 720, "Geometry App");
    window.SetTargetFPS(60);

    // ImGui の初期化（raylib の InitWindow 後に呼ぶ）
    rlImGuiSetup(true);

    while (!window.ShouldClose()) {
        window.BeginDrawing();
        window.ClearBackground(raylib::Color(33, 33, 40));

        // raylib の描画
        DrawCircleV({640, 360}, 10, RED);

        // ImGui の描画
        rlImGuiBegin();

        ImGui::Begin("Controls");
        ImGui::Text("点の数: %d", pointCount);
        if (ImGui::Button("凸包を計算")) { /* 処理 */ }
        ImGui::SliderFloat("点のサイズ", &pointSize, 3.0f, 20.0f);
        ImGui::End();

        rlImGuiEnd();

        window.EndDrawing();
    }

    // ImGui の終了処理（CloseWindow 前に呼ぶ）
    rlImGuiShutdown();

    return 0;
}
```

### 呼び出し順序の注意

```
InitWindow()       ← raylib 初期化
rlImGuiSetup()     ← ImGui 初期化（必ず InitWindow の後）
─────────────────────────────────
ループ:
  BeginDrawing()
    raylib の描画
    rlImGuiBegin()
      ImGui::Begin() / End()
    rlImGuiEnd()
  EndDrawing()
─────────────────────────────────
rlImGuiShutdown()  ← ImGui 終了（必ず CloseWindow の前）
CloseWindow()
```

---

## 10. ビルドと実行

VS Code のステータスバーのボタン、またはコマンドパレット（`Cmd+Shift+P`）から：

```
CMake: Configure    ← 初回のみ
CMake: Build        ← F7 でも可
CMake: Run Without Debugging
```

ターミナルから実行する場合：

```bash
cmake -B build
cmake --build build
./build/GeometryApp
```

---

## 11. Homebrew 版への切り替え（ソースビルドから移行する場合）

Homebrew の raylib が 6.0 以上になったら、以下の手順で切り替える。

```bash
# ソースビルドでインストールしたファイルを削除
# Apple Silicon の場合
sudo rm /opt/homebrew/lib/libraylib*
sudo rm /opt/homebrew/include/raylib.h
sudo rm /opt/homebrew/include/rlgl.h
sudo rm /opt/homebrew/include/raymath.h

# Intel Mac の場合は /opt/homebrew を /usr/local に読み替える

# Homebrew 版をインストール
brew install raylib

# プロジェクトを再ビルド（CMakeLists.txt の変更は不要）
rm -rf build
cmake -B build && cmake --build build
```

Homebrew 版への切り替えが完了したかどうかの確認：

```bash
brew info raylib          # バージョン確認
which -a pkg-config       # pkg-config が通るか確認
pkg-config --modversion raylib
```

---

## 12. raylib のアップデート（ソースビルドの場合）

ソースビルドで管理している場合、新バージョンへの更新手順は以下の通り。

```bash
# 古いファイルを削除（Apple Silicon の場合）
sudo rm /opt/homebrew/lib/libraylib*
sudo rm /opt/homebrew/include/raylib.h
sudo rm /opt/homebrew/include/rlgl.h
sudo rm /opt/homebrew/include/raymath.h

# 新バージョンをクローン（例: 6.1 が出た場合）
git clone --depth 1 --branch 6.1 https://github.com/raysan5/raylib.git /tmp/raylib
cd /tmp/raylib
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/opt/homebrew
cmake --build . --config Release
sudo cmake --install .

rm -rf /tmp/raylib
```

---

## トラブルシューティング

### `find_package(raylib)` が失敗する

Homebrew のパスを明示する：

```bash
cmake -B build -DCMAKE_PREFIX_PATH=$(brew --prefix raylib)
```

### `raylib-cpp requires raylib >= 6` エラー

インストール済みの raylib が 5.x 以下。「3-B. ソースからビルド」の手順で 6.0 をインストールする。

### コメント行（`#`）が `zsh: command not found` になる

複数行のコマンドをターミナルに貼り付ける際、コメント行（`#` で始まる行）は除いて貼り付ける。

---

### git submodule

```bash
# 追加
git submodule add <URL> <ディレクトリ>

# 更新(一括)
git submodule update --remote --merge

# 更新(個別)
cd [サブモジュールへのパス]
git pull origin main # または該当ブランチ名

# 削除
git submodule                           
git submodule deinit sample/sample-submodules
git rm -f sample/sample-submodules
```


