cmake_minimum_required(VERSION 3.22.1)
project("casioemuandroid")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Thêm SDL2 và SDL2_image
add_subdirectory(sdl2)
add_subdirectory(sdl2_image)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/Chipset
        ${CMAKE_CURRENT_SOURCE_DIR}/Peripheral
        ${CMAKE_CURRENT_SOURCE_DIR}/Data
        ${CMAKE_CURRENT_SOURCE_DIR}/Gui
        ${CMAKE_CURRENT_SOURCE_DIR}/Gui/imgui
        ${CMAKE_CURRENT_SOURCE_DIR}/Gui/imgui/backends
        ${CMAKE_CURRENT_SOURCE_DIR}/sdl2/include
        ${CMAKE_CURRENT_SOURCE_DIR}/sdl2_image/include
)

# Gom toàn bộ file mã nguồn C++ của dự án
add_library(
        casioemuandroid
        SHARED
        native-lib.cpp
        Gui/imgui/imgui.cpp
        Gui/imgui/imgui_draw.cpp
        Gui/imgui/imgui_tables.cpp
        Gui/imgui/imgui_widgets.cpp
        Gui/imgui/backends/imgui_impl_android.cpp
        Gui/imgui/backends/imgui_impl_opengl3.cpp
)

find_library(log-lib log)

target_link_libraries(
        casioemuandroid
        ${log-lib}
        SDL2
        SDL2_image
        GLESv2
        GLESv3
        EGL
        android
)