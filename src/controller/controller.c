/**
 * @file controller.c
 * @author Antony COCO (antony.coco.pro@gmail.com)
 * @brief Orchestrates the main logic for pie chart creation, rendering, and saving.
 * @version 0.1
 * @date 2023-08-05
 *
 * @copyright Copyright (c) 2023
 */

// Include necessary header(s)
#include "controller.h"
#include <time.h>
#include <stdio.h>
#include <stdbool.h>

void controller_init(ControllerData *data)
{
    srand(time(NULL)); // Seed the random number generator
    data->img = NULL;
    data->segments = NULL;
    data->segments_count = 0;
}

int handle_input(int argc, char **argv, ControllerData *data)
{

    // Extract necessary information from command-line arguments (this is part of the Model)
    char *output_file = generate_output_file(argc, argv);
    char *base_name = generate_base_name_from_executable(argv[0]);
    char *title = retrieve_title(argc, argv, base_name);
    int segments_count = 0;
    data->segments = parse_segments(argv, &segments_count, argc, !is_number(argv[1]));

    if (!data->segments)
    {
        printf("Error during segment analysis!\n");
        return 1;
    }

    // Create and render the pie chart (this is the View)
    data->img = create_pie_chart_image(data->segments, segments_count, title);

    // Save the pie chart image to the output file
    FILE *fp = fopen(output_file, "wb+");
    if (!fp)
    {
        perror("Error opening output file for writing");
        return 1;
    }
    gdImagePng(data->img, fp);
    fclose(fp);

    return 0;
}

void controller_cleanup(ControllerData *data)
{
    if (data->img)
    {
        gdImageDestroy(data->img);
    }

    if (data->segments)
    {
        free_segments(data->segments, data->segments_count);
    }
}
