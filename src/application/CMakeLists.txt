set(CURRENT_TARGET snake2d)

add_executable(${CURRENT_TARGET} main.cpp)
target_link_libraries(${CURRENT_TARGET} PRIVATE GameDevKit::Core Snake2D::Game Snake2D::Renderer)
