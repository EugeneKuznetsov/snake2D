#include "Snake2D/Renderer.hpp"

#include <GDK/GraphicsLibrary.hpp>

#include "Snake2D/Game.hpp"
#include "Snake2D/Snake.hpp"
#include "Snake2D/SpriteRenderer.hpp"
#include "Snake2D/Playfield.hpp"

Renderer::Renderer()
    : game_{nullptr}
    , sprite_renderer_{nullptr}
    , frame_buffer_size_{0, 0}
{
}

Renderer::~Renderer() = default;

auto Renderer::frame_buffer_size(const gamedevkit::windows::FrameBufferSize& new_frame_buffer_size) -> void
{
    frame_buffer_size_ = new_frame_buffer_size;
}

auto Renderer::setup(std::shared_ptr<gamedevkit::AbstractGame> game) -> void
{
    game_ = std::move(std::static_pointer_cast<Game>(game));

    const auto& playfield = game_->playfield();
    sprite_renderer_ = std::make_unique<SpriteRenderer>();
    sprite_renderer_->setup(frame_buffer_size_.width,
                            frame_buffer_size_.height,
                            frame_buffer_size_.width / playfield->rows,
                            frame_buffer_size_.height / playfield->cols);
}

auto Renderer::render() -> void
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    sprite_renderer_->render(game_->snake()->position());
}
