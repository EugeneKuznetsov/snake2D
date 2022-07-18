function(add_test_suite)
    set(options)
    set(oneValueArgs TEST_SUITE_NAME TARGET_UNDER_TEST)
    set(multiValueArgs)
    cmake_parse_arguments(ARG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    set(MAIN_TARGET ${ARG_TEST_SUITE_NAME})
    set(SOURCES "${MAIN_TARGET}.cpp")
    set(TARGET_UNDER_TEST ${ARG_TARGET_UNDER_TEST})

    add_executable(${MAIN_TARGET} ${SOURCES} ${TARGET_UNDER_TEST_SOURCES})
    target_link_libraries(${MAIN_TARGET} PRIVATE GTest::gtest_main ${TARGET_UNDER_TEST})
    add_test(NAME ${MAIN_TARGET} COMMAND $<TARGET_FILE:${MAIN_TARGET}>)
endfunction()
