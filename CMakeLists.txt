cmake_minimum_required(VERSION 3.9.1)

project(renderEngine)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

file(GLOB IMGUI_SOURCES "src/vendor/imgui/*.cpp")
file(GLOB RENDER_TEST_SOURCES "src/tests/*.cpp")

set(SOURCES
	src/main.cpp
	src/Renderer.cpp
	src/VertexBuffer.cpp
	src/IndexBuffer.cpp
	src/VertexArray.cpp
	src/VertexBufferLayout.cpp
	src/Shader.cpp
	src/Texture.cpp

	${RENDER_TEST_SOURCES}

	src/vendor/stb/stb_image.cpp
	${IMGUI_SOURCES}
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/vendor)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glfw/include)
add_executable(renderEngine ${SOURCES})
target_link_libraries(renderEngine ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glfw/lib-x86_64/libglfw.3.dylib)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res DESTINATION ${CMAKE_BINARY_DIR}/bin)

if (APPLE)
  target_link_libraries(renderEngine "-framework OpenGL")
endif()
