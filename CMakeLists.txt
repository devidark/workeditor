cmake_minimum_required (VERSION 2.6)
project (WorkEditor)

set(WorkEditor_VERSION_MAJOR 0)
set(WorkEditor_VERSION_MINOR 1)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmakemods)

# - Find the curses include file and library
#
#  CURSES_FOUND - system has Curses
#  CURSES_INCLUDE_DIR - the Curses include directory
#  CURSES_LIBRARIES - The libraries needed to use Curses
#  CURSES_HAVE_CURSES_H - true if curses.h is available
#  CURSES_HAVE_NCURSES_H - true if ncurses.h is available
#  CURSES_HAVE_NCURSES_NCURSES_H - true if ncurses/ncurses.h is available
#  CURSES_HAVE_NCURSES_CURSES_H - true if ncurses/curses.h is available
#  CURSES_LIBRARY - set for backwards compatibility with 2.4 CMake
#
# Set CURSES_NEED_NCURSES to TRUE before the FIND_PACKAGE() command if NCurses
# functionality is required.
# Set CURSES_NEED_WIDE to TRUE before the FIND_PACKAGE() command if unicode
# functionality is required

# set(CURSES_NEED_WIDE TRUE)

set(CURSES_NEED_NCURSES TRUE)

find_package(Curses REQUIRED)
IF(CURSES_FOUND)
    MESSAGE(STATUS "    CURSES_INCLUDE_DIR = '${CURSES_INCLUDE_DIR}'")
    MESSAGE(STATUS "    CURSES_LIBRARIES = '${CURSES_LIBRARIES}'")
ELSE(CURSES_FOUND)
    MESSAGE(FATAL_ERROR "The curses package is required")
ENDIF(CURSES_FOUND)

include_directories(
    ${CMAKE_SOURCE_DIR}
)

add_subdirectory(vis)
# add_subdirectory(conf)
# add_subdirectory(app)
# add_subdirectory(editor)
