#pragma once

#include <string>
#include <memory>

namespace sail {
class image;
}  // namespace sail

class Image {
public:
    explicit Image(const std::string& path_to_image_file);
    ~Image();

    auto data() const -> const unsigned char*;
    auto width() const -> unsigned int;
    auto height() const -> unsigned int;

private:
    std::unique_ptr<sail::image> image_;
};
