add_library(term_driver
    ncurs.cpp
)

target_link_libraries(term_driver
    ${CURSES_LIBRARIES}
)

add_subdirectory(test)
