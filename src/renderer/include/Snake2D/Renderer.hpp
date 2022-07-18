#pragma once

#include <GDK/AbstractRenderer.hpp>

class Renderer : public gamedevkit::AbstractRenderer {
public:
    auto setup(std::shared_ptr<gamedevkit::AbstractGame> game) -> void override;
    auto render() -> void override;
};
