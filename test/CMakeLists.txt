option(TEST_BENCHMARK "Enable the benchmark tests for ${projectName}" OFF)
option(TEST_UNIT_TESTS "Enable the unit tests for ${projectName}" ON)

if (TEST_BENCHMARK)
    # Add benchmark test executable
    add_executable(benchmarkTests)

    # Get benchmark framework
    handleExternals(NAME google_benchmark)

    # Link the benchmark test executable against the created libraries
    target_link_libraries(benchmarkTests gipoLibrary ${google_benchmark})
endif()

if (TEST_UNIT_TESTS)
    # Add unit test executable
    add_executable(i2cTest i2cTest.cpp)
    inhibit_target_warnings(i2cTest) # Needed for doctest to prevent parentheses warnings

    # Get unit testing framework
    handleExternals(NAME doctest)

    # Link the unit test executable against the created libraries
    target_link_libraries(i2cTest gipoLibrary doctest)

    # Enable testing and discover tests
    enable_testing()
    include(${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake)
    doctest_discover_tests(i2cTest)
endif()
