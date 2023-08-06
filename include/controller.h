#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <unistd.h> // Pour accéder à la fonction access()
#include <stdbool.h>
#include "model.h"
#include "view.h"

/**
 * @brief Structure representing the data required by the controller.
 * 
 * This structure contains all the information needed to operate the controller. 
 * of the controller. It includes an image, an array of pie chart segments, 
 * and the number of these segments.
 */
typedef struct {
    gdImagePtr img;
    PieChartSegment *segments;
    int segments_count;
} ControllerData;

/**
 * @brief Controller initialization.
 * 
 * This function initializes controller data by setting pointers to NULL and integers to zero.
 * @param data Pointer to a ControllerData structure to be initialized.
 */
void controller_init(ControllerData *data);

/**
 * @brief Handles user-supplied input.
 * 
 * This function analyzes the command line arguments to determine the name of the output file, 
 * title and pie chart segments. It then generates the image and saves it.
 * 
 * @param argc The number of command line arguments.
 * @param argv Command line arguments.
 * @param data Pointer to a ControllerData structure containing the data to be filled in.
 * @return 0 on success, 1 on error.
 */
int handle_input(int argc, char **argv, ControllerData *data);

/**
 * @brief Cleans up resources or status associated with the controller.
 * 
 * This function frees all memory allocated while the application is running.
 * 
 * @param data Pointer to the ControllerData structure to be cleaned up.
 */
void controller_cleanup(ControllerData *data);

#endif // CONTROLLER_H
