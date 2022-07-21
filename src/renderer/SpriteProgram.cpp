#include "Snake2D/SpriteProgram.hpp"

#include "Snake2D/SpriteFragmentShader.hpp"
#include "Snake2D/SpriteVertexShader.hpp"

auto SpriteProgram::vertex_shader() const -> std::unique_ptr<gamedevkit::shaders::GenericShader>
{
    return std::make_unique<SpriteVertexShader>();
}

auto SpriteProgram::fragment_shader() const -> std::unique_ptr<gamedevkit::shaders::GenericShader>
{
    return std::make_unique<SpriteFragmentShader>();
}
