include_directories(array_figures comparisons figure point rectangle rhombus trapezoied, exceptions)

add_library(figures figure/figure.cpp rectangle/rectangle.cpp rhombus/rhombus.cpp trapezoid/trapezoid.cpp)

add_library(array_figures array_figures/array_figures.cpp)
target_link_libraries(array_figures PRIVATE figures)

add_library(points point/point.cpp)

