set(CURRENT_TARGET Renderer)

add_library(${CURRENT_TARGET} Renderer.cpp SpriteProgram.cpp SpriteVertexShader.cpp
                              SpriteFragmentShader.cpp)
add_library(Snake2D::${CURRENT_TARGET} ALIAS ${CURRENT_TARGET})
target_include_directories(${CURRENT_TARGET}
                           PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>)
target_link_libraries(${CURRENT_TARGET} PRIVATE GameDevKit::Core GameDevKit::Shaders Snake2D::Game)
