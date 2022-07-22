#include "Snake2D/SpriteVertexShader.hpp"

SpriteVertexShader::SpriteVertexShader()
    : gamedevkit::shaders::GenericShader{gamedevkit::shaders::Type::vertex}
{
}

auto SpriteVertexShader::shader_source() const -> std::string
{
    return R"glsl(
        #version 400 core

        in vec2 origin;

        uniform mat4 projection;
        uniform mat4 position;

        void main()
        {
            gl_Position = projection * position * vec4(origin, 0.0, 1.0);
        }
    )glsl";
}
