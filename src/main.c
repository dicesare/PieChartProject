/**
 * @file main.c
 * @author Antony COCO (antony.coco.pro@gmail.com)
 * @brief Entry point for the pie chart generation application.
 * @version 0.1
 * @date 2023-08-05
 *
 * @copyright Copyright (c) 2023
 */

#include "controller.h"

/**
 * Handle the input provided by the user (or any other source).
 * 
 * @param argc The count of command-line arguments.
 * @param argv The command-line arguments.
 */
int main(int argc, char **argv) 
{
    ControllerData controller_data;
    controller_init(&controller_data);
    int result = handle_input(argc, argv, &controller_data);
    controller_cleanup(&controller_data);
    return result;
}
