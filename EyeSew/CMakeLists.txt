# CMakeList.txt : CMake project for EyeSew, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (EyeSew 
"src/Main.cpp" "src/Instance.cpp" "src/Script.cpp" 
"src/Usertypes.cpp" "src/Game.cpp" "src/Color3.cpp" 
"src/Vec3.cpp" "src/Editor.cpp"

"${CMAKE_SOURCE_DIR}/imgui/imgui.cpp" "${CMAKE_SOURCE_DIR}/imgui/imgui_draw.cpp"
"${CMAKE_SOURCE_DIR}/imgui/imgui_demo.cpp" "${CMAKE_SOURCE_DIR}/imgui/imgui_tables.cpp"
"${CMAKE_SOURCE_DIR}/imgui/imgui_widgets.cpp" "${CMAKE_SOURCE_DIR}/imgui/misc/cpp/imgui_stdlib.cpp"

"${CMAKE_SOURCE_DIR}/rlImGui/rlImGui.cpp")

target_include_directories (${PROJECT_NAME} PRIVATE "include")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET EyeSew PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.

target_link_libraries (${PROJECT_NAME} Luau.Compiler Luau.VM Luau.CodeGen)
target_link_libraries (${PROJECT_NAME} raylib)
target_link_libraries (${PROJECT_NAME} Zep)

target_include_directories (${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/imgui)
target_include_directories (${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/imgui/misc/cpp)
target_include_directories (${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/rlImGui)
target_include_directories (${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/zep/include)
