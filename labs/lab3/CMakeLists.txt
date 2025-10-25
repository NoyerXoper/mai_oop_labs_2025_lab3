add_subdirectory(lib)
include(GoogleTest)

include_directories(lib/figure lib/point lib/array_figures lib/rectangle lib/rhombus lib/trapezoid lib/exceptions lib/comparisons)

add_executable(test tests/tests.cpp)
target_link_libraries(test PRIVATE array_figures points figures gtest gtest_main)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE array_figures points figures gtest gtest_main)
