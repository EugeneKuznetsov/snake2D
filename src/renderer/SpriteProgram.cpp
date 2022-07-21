#include "Snake2D/SpriteProgram.hpp"

#include <glm/gtc/type_ptr.hpp>

#include <GDK/GraphicsLibrary.hpp>

#include "Snake2D/SpriteFragmentShader.hpp"
#include "Snake2D/SpriteVertexShader.hpp"

auto SpriteProgram::matrix4_uniform(const std::string& uniform_variable, const glm::mat4& matrix) -> SpriteProgram&
{
    const auto uniform_location = glGetUniformLocation(object_id(), uniform_variable.c_str());
    glUniformMatrix4fv(uniform_location, 1, false, glm::value_ptr(matrix));

    return *this;
}

auto SpriteProgram::vertex_shader() const -> std::unique_ptr<gamedevkit::shaders::GenericShader>
{
    return std::make_unique<SpriteVertexShader>();
}

auto SpriteProgram::fragment_shader() const -> std::unique_ptr<gamedevkit::shaders::GenericShader>
{
    return std::make_unique<SpriteFragmentShader>();
}
