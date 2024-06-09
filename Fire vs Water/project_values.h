/// @file project_values.h
/// @author Adam T Koehler, PhD
/// @date January 12, 2024
/// @brief Header file containing useful project settings and values.

// Copyright Notice
// This document is protected by U.S. copyright law. Reproduction and
// distribution of this work, including posting or sharing through any medium,
// is explicitly prohibited by law, and also violates UIC's Student
// Disciplinary Policy (A2-c. Unauthorized Collaboration; and A2-e3.
// Participation in Academically Dishonest Activities: Material Distribution).

#pragma once

enum STATES {EMPTY, WALL, GRASS, FIRE, WATER};
enum DIRECTIONS {NORTH, SOUTH, EAST, WEST};

#ifndef COLORS
    #define COLORS
    #define RED     "\x1B[41m"
    #define GREEN   "\x1B[42m"
    #define BLUE    "\x1B[44m"
    #define WHITE   "\x1B[47m"
    #define RESET   "\033[0m"
#endif

#ifndef PROJECT_SETTINGS
    #define PROJECT_SETTINGS
    #define ANIMATE 1
    #define CLEAR_SCREEN 1
    #define IN_COLOR 1
    #define SLEEP_USEC 250000
    #define RAND_SEED 1000
#endif
