#pragma once

#include <GDK/GenericProgram.hpp>

#include <glm/mat4x4.hpp>

class SpriteProgram final : public gamedevkit::shaders::GenericProgram {
public:
    auto matrix4_uniform(const std::string& uniform_variable, const glm::mat4& matrix) -> SpriteProgram&;

private:
    auto vertex_shader() const -> std::unique_ptr<gamedevkit::shaders::GenericShader> override;
    auto fragment_shader() const -> std::unique_ptr<gamedevkit::shaders::GenericShader> override;
};
