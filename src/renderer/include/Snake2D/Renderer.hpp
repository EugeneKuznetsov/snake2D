#pragma once

#include <GDK/AbstractRenderer.hpp>
#include <GDK/WindowProperties.hpp>

class Game;
class SpriteRenderer;

class Renderer : public gamedevkit::AbstractRenderer {
public:
    explicit Renderer();
    ~Renderer();

public:
    auto frame_buffer_size(const gamedevkit::windows::FrameBufferSize& new_frame_buffer_size) -> void override;
    auto setup(std::shared_ptr<gamedevkit::AbstractGame> game) -> void override;
    auto render() -> void override;

private:
    std::shared_ptr<Game> game_;
    std::unique_ptr<SpriteRenderer> sprite_renderer_;
    gamedevkit::windows::FrameBufferSize frame_buffer_size_;
};
