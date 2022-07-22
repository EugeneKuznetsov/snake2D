#include "Snake2D/Image.hpp"

#include <sail-c++/sail-c++.h>

Image::Image(const std::string& path_to_image_file)
    : image_{std::make_unique<sail::image>(path_to_image_file)}
{
}

Image::~Image() = default;

auto Image::data() const -> const unsigned char*
{
    return static_cast<unsigned char*>(image_->pixels());
}

auto Image::width() const -> unsigned int
{
    return image_->width();
}

auto Image::height() const -> unsigned int
{
    return image_->height();
}
