#pragma once

#include <GDK/GenericShader.hpp>

class SpriteFragmentShader final : public gamedevkit::shaders::GenericShader {
public:
    explicit SpriteFragmentShader();

private:
    auto shader_source() const -> std::string override;
};
