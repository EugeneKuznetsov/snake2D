#pragma once

#include <memory>

struct Position;
class SpriteProgram;

class SpriteRenderer {
public:
    explicit SpriteRenderer();
    ~SpriteRenderer();

public:
    auto setup(const int viewport_width, const int viewport_height, const int sprite_width, const int sprite_height) -> void;
    auto render(const Position& position) -> void;

private:
    auto setup_data_layout() -> void;

private:
    std::unique_ptr<SpriteProgram> sprite_program_;
    unsigned int vertex_array_object_;
    int viewport_width_;
    int viewport_height_;
    int sprite_width_;
    int sprite_height_;
};
