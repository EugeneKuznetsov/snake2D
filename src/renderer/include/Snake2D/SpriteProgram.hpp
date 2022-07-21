#pragma once

#include <GDK/GenericProgram.hpp>

class SpriteProgram final : public gamedevkit::shaders::GenericProgram {
private:
    auto vertex_shader() const -> std::unique_ptr<gamedevkit::shaders::GenericShader> override;
    auto fragment_shader() const -> std::unique_ptr<gamedevkit::shaders::GenericShader> override;
};
