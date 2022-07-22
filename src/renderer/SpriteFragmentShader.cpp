#include "Snake2D/SpriteFragmentShader.hpp"

SpriteFragmentShader::SpriteFragmentShader()
    : gamedevkit::shaders::GenericShader{gamedevkit::shaders::Type::fragment}
{
}

auto SpriteFragmentShader::shader_source() const -> std::string
{
    return R"glsl(
        #version 400 core

        out vec4 color;

        void main()
        {
            color = vec4(1.0, 1.0, 1.0, 1.0);
        }
    )glsl";
}
