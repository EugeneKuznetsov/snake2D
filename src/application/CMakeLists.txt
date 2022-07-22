set(CURRENT_TARGET snake2d)

add_executable(${CURRENT_TARGET} main.cpp)
target_link_libraries(${CURRENT_TARGET} PRIVATE GameDevKit::Core Snake2D::Game Snake2D::Renderer)

file(GLOB GameResources snake)

add_custom_command(
    TARGET ${CURRENT_TARGET}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/resources
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources)
