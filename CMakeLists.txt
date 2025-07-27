cmake_minimum_required (VERSION 3.11)
project(imtui_example)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Define where to store imgui content
set(THIRD_PARTY_DIR ${CMAKE_SOURCE_DIR}/third_party/imgui)

# Only download and zip file doesn't exist
if(NOT EXISTS ${THIRD_PARTY_DIR}/v1.90.zip)
  message(STATUS "Downloading imgui v1.90!")

  set(IMGUI_ZIP_PATH ${THIRD_PARTY_DIR}/v1.90.zip)

  file(DOWNLOAD
    https://github.com/ocornut/imgui/archive/refs/tags/v1.90.zip
    ${IMGUI_ZIP_PATH}
    EXPECTED_HASH SHA256=fbe086f5bfc631db509acea851734f6996d6d2ef8fdeacb3f097f6def21e8af8
    SHOW_PROGRESS
  )

endif()

# -- Fetch IMGUI
include(FetchContent)

function(fetch_project)
  cmake_parse_arguments(FETCH_SOURCE "" "NAME;URL;DESTINATION" "" ${ARGN})

  FetchContent_Populate(${FETCH_SOURCE_NAME}
    URL ${FETCH_SOURCE_URL}
    SOURCE_DIR ${CMAKE_BINARY_DIR}/${FETCH_SOURCE_DESTINATION}
  )

  set(
    "${FETCH_SOURCE_NAME}_LOCATION"
    ${CMAKE_BINARY_DIR}/${FETCH_SOURCE_DESTINATION}
    PARENT_SCOPE
  )
endfunction()

fetch_project(
  NAME imgui_src
  URL ${CMAKE_SOURCE_DIR}/third_party/imgui/v1.90.zip
  DESTINATION imgui
)

set(OpenGL_GL_PREFERENCE "LEGACY")
find_package(OpenGL 3 REQUIRED)
find_package(glfw3 REQUIRED)

add_library(imgui_glfw SHARED
  ${imgui_src_LOCATION}/imgui.cpp
  ${imgui_src_LOCATION}/imgui_draw.cpp
  ${imgui_src_LOCATION}/imgui_demo.cpp
  ${imgui_src_LOCATION}/imgui_tables.cpp
  ${imgui_src_LOCATION}/imgui_widgets.cpp

  ${imgui_src_LOCATION}/backends/imgui_impl_glfw.cpp
  ${imgui_src_LOCATION}/backends/imgui_impl_opengl3.cpp

  ${imgui_src_LOCATION}/misc/cpp/imgui_stdlib.cpp
)

target_link_libraries(imgui_glfw PUBLIC glfw OpenGL::GL)
target_compile_definitions(imgui_glfw PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLAD)

target_include_directories(imgui_glfw
PUBLIC
  ${imgui_src_LOCATION}
  ${imgui_src_LOCATION}/backends
  ${imgui_src_LOCATION}/misc/cpp
)
# ---

include_directories(
  include
  ${imgui_src_LOCATION}
  ${imgui_src_LOCATION}/backends
  ${imgui_src_LOCATION}/misc/cpp
)
add_library(imgui_handler SHARED
  ./src/imgui_handler.cpp
)
target_link_libraries(imgui_handler PUBLIC imgui_glfw glfw)

add_executable(imgui-example src/main.cpp)
target_link_libraries(imgui-example PRIVATE imgui_glfw)

add_executable(imgui-handler-example ./src/imgui_handler_example.cpp)
target_link_libraries(imgui-handler-example  PRIVATE imgui_handler)
