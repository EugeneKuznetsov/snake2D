include(TestUtils)

add_test_suite(TEST_SUITE_NAME test_Game TARGET_UNDER_TEST Snake2D::Game)
add_test_suite(TEST_SUITE_NAME test_Snake TARGET_UNDER_TEST Snake2D::Game)
