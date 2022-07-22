#include <gtest/gtest.h>

#include <Snake2D/Image.hpp>

TEST(the_image, can_load_existing_png_file)
{
    Image image(std::string(PATH_TO_RESOURCES) + "/resources/snake/head.png");

    EXPECT_EQ(image.width(), 62);
    EXPECT_EQ(image.height(), 62);
}
