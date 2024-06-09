/// @file project_utils.h
/// @author Adam T Koehler, PhD
/// @date January 12, 2024
/// @brief Provided utility functions to use during project implementation.

// Copyright Notice
// This document is protected by U.S. copyright law. Reproduction and
// distribution of this work, including posting or sharing through any medium,
// is explicitly prohibited by law, and also violates UIC's Student
// Disciplinary Policy (A2-c. Unauthorized Collaboration; and A2-e3.
// Participation in Academically Dishonest Activities: Material Distribution).

#pragma once

#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "project_values.h"

/// @brief Sleep for animation based on project animation setting value.
void animate(void)
{
    if (ANIMATE == 1)
    {
        usleep(SLEEP_USEC);
    }
}

/// @brief Clear the console screen or output two newlines based on
///        the project setting for clearing the screen.
void clearScreen(void)
{
    if (CLEAR_SCREEN == 1)
    {
        printf("\033[H");
    }
    else
    {
        printf("\n\n");
    }
}

/// @brief Print the specified value or convert it to a color block based
///        on the project setting for printing in color.
/// @param value the value to translate or output
void printCell(int value)
{
    if (IN_COLOR == 1)
    {
        switch(value)
        {
            case EMPTY:
                printf(RESET "  " RESET);
                break;
            case WATER:
                printf(BLUE "  " RESET);
                break;
            case FIRE:
                printf(RED "  " RESET);
                break;
            case GRASS:
                printf(GREEN "  " RESET);
                break;
            case WALL:
                printf(WHITE "  " RESET);
                break;
            default:
                printf(RESET "??" RESET);
        }
    }
    else
    {
        printf("%d ", value);
    }
}
