#pragma once

#include <GDK/GenericShader.hpp>

class SpriteVertexShader final : public gamedevkit::shaders::GenericShader {
public:
    explicit SpriteVertexShader();

private:
    auto shader_source() const -> std::string override;
};
