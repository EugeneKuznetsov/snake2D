#include "Snake2D/SpriteRenderer.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include <GDK/GraphicsLibrary.hpp>

#include "Snake2D/Position.hpp"
#include "Snake2D/SpriteProgram.hpp"

SpriteRenderer::SpriteRenderer()
    : sprite_program_{nullptr}
    , vertex_array_object_{GL_NONE}
    , viewport_width_{0}
    , viewport_height_{0}
    , sprite_width_{0}
    , sprite_height_{0}
{
    glGenVertexArrays(1, &vertex_array_object_);
}

SpriteRenderer::~SpriteRenderer()
{
    glDeleteVertexArrays(1, &vertex_array_object_);
}

auto SpriteRenderer::setup(const int viewport_width, const int viewport_height, const int sprite_width, const int sprite_height) -> void
{
    viewport_width_ = viewport_width;
    viewport_height_ = viewport_height;
    sprite_width_ = sprite_width;
    sprite_height_ = sprite_height;

    const auto projection = glm::ortho(0.0f, static_cast<float>(viewport_width_), static_cast<float>(viewport_height_), 0.0f, -1.0f, 1.0f);
    sprite_program_ = std::make_unique<SpriteProgram>();
    sprite_program_->build().activate();
    sprite_program_->matrix4_uniform("projection", projection);

    setup_data_layout();
}

auto SpriteRenderer::render(const Position& position) -> void
{
    const auto sprite_object_x = (position.row * sprite_width_) - sprite_width_;
    const auto sprite_object_y = (position.col * sprite_height_) - sprite_height_;

    glm::mat4 sprite_position{1.0f};
    sprite_position = glm::translate(sprite_position, glm::vec3{sprite_object_x, sprite_object_y, 0.0f});
    sprite_position = glm::translate(sprite_position, glm::vec3{0.5f * sprite_width_, 0.5f * sprite_height_, 0.0f});
    sprite_position = glm::rotate(sprite_position, glm::radians(0.0f), glm::vec3{0.0f, 0.0f, 1.0f});
    sprite_position = glm::translate(sprite_position, glm::vec3{-0.5f * sprite_width_, -0.5f * sprite_height_, 0.0f});
    sprite_position = glm::scale(sprite_position, glm::vec3{sprite_width_, sprite_height_, 1.0f});

    sprite_program_->activate();
    sprite_program_->matrix4_uniform("position", sprite_position);

    glBindVertexArray(vertex_array_object_);
    // TODO: switch to glDrawElements and use buffer indices accordingly...
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0u);
}

auto SpriteRenderer::setup_data_layout() -> void
{
    unsigned int vertex_buffer_object;
    glGenBuffers(1, &vertex_buffer_object);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);

    const float rectangle[] = {0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f};
    glBufferData(GL_ARRAY_BUFFER, sizeof(rectangle), rectangle, GL_STATIC_DRAW);

    glBindVertexArray(vertex_array_object_);
    const auto origin_attribute = glGetAttribLocation(sprite_program_->object_id(), "origin");
    glEnableVertexAttribArray(origin_attribute);
    glVertexAttribPointer(origin_attribute, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);
    glBindVertexArray(GL_NONE);
}
