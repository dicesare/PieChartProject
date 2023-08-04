/**
 * @file main.c
 * @author Antony COCO (antony.coco.pro@gmail.com)
 * @brief Program to generate a pie chart image based on input data.
 * @version 0.1
 * @date 2023-08-02
 *
 * @copyright Copyright (c) 2023
 */

#include "pie_chart.h" // Include necessary header(s)
#include <time.h>

// Other constants, function prototypes, etc.

/**
 * @brief The main function of a program that generates a pie chart image.
 *
 * @param argc The number of command-line arguments.
 * @param argv An array of command-line arguments.
 * @return int 0 if successful, 1 if an error occurs.
 */
int main(int argc, char **argv)
{
    // Define basic geometric properties of the pie chart
    int width = WIDTH, height = HEIGHT, radius = 600;
    int x = width / 2, y = height / 2; // Center the circle
    int start_angle = 0, end_angle = 360; // Full circle

    // Variables for title, output file name, and pie chart segments
    char *output_file = NULL, *title = NULL, *base_name = NULL;
    int length = 0;
    PieChartSegment *segments = NULL;

    srand(time(NULL)); // Seed the random number generator

    // Handle output file argument
    if (has_arguments(argc) && !is_number(argv[1]))
    {
        output_file = argv[1];
    }
    else
    {
        output_file = generate_output_file(argv[0]);
        if (!output_file)
        {
            fprintf(stderr, "Memory allocation error!\n");
            exit(EXIT_FAILURE);
        }
    }

    // Parse the pie chart segments
    if ((argc > 2 && is_number(argv[1])) || (argc > 3 && !is_number(argv[1])))
        segments = parse_segments(argv, &length, argc, !is_number(argv[1]));
    if (!segments)
    {
        printf("Error during segment analysis!\n");
        return 1;
    }

    // Create a new image
    gdImagePtr img = gdImageCreate(width, height);
    int bg = gdImageColorAllocate(img, 255, 255, 255); // Background color
    int black = gdImageColorAllocate(img, 0, 0, 0); // Border color

    // Retrieve title from command-line arguments or use base name
    title = retrieve_title(argc, argv, generate_base_name_from_executable(argv[0]));

    // Draw the title, pie chart segments, and labels
    draw_title(img, title, width / 2, 50, black);
    draw_pie_segments(img, segments, length, x, y, start_angle, radius, black);
    if (access(FONT_PATH, F_OK) == -1)
    {
        printf("The font file does not exist.\n");
        gdImageDestroy(img);
        free(segments);
        return 1;
    }
    draw_label(img, segments, length, x, y, start_angle, radius, black);

    // Save the image to a file
    FILE *out = fopen(output_file, "wb+");
    if (!out)
    {
        printf("Error while opening the output file!\n");
        gdImageDestroy(img);
        free(segments);
        return 1;
    }
    gdImagePng(img, out);
    fclose(out);

    // Clean up
    gdImageDestroy(img);
    for (int i = 0; i < length; i++) free(segments[i].label);
    free(segments);

    return 0;
}
