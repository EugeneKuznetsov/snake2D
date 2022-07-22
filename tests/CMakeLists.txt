include(TestUtils)

add_test_suite(TEST_SUITE_NAME test_Game TARGET_UNDER_TEST Snake2D::Game)
add_test_suite(TEST_SUITE_NAME test_Image TARGET_UNDER_TEST Snake2D::Resources)

add_compile_definitions(test_Image PATH_TO_RESOURCES="${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
