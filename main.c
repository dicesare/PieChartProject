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
    // Define dimensions and geometric properties of the pie chart
    int width = WIDTH;
    int height = HEIGTH;
    int start_angle = 0; // Define the start angle
    int end_angle = 360;  // Define the end angle
    int radius = 600;    // Define the radius
    int x = width / 2;   // Center the circle in x
    int y = height / 2;  // Center the circle in y

    // Variables for color, title, and file name
    int color;
    char *title = argv[4];
    char *output_file = argv[1];
    int length;

    srand(time(NULL)); // Initialize the random number generator

    // Check for the correct number of command-line arguments
    if (argc != 5)
    {
        fprintf(stderr, "Usage: %s <output_file> <data> <labels> <title>\n", argv[0]);
        return 1;
    }

    // Parse the segments from the command-line arguments
    PieChartSegment *segments = parse_segments(argv, &length);
    if (!segments)
    {
        printf("Error during segment analysis!\n");
        return 1;
    }

    // Create a new image
    gdImagePtr img = gdImageCreate(width, height);

    // Background color
    int bg = gdImageColorAllocate(img, 255, 255, 255);
    int black = gdImageColorAllocate(img, 0, 0, 0); // Border color

    // Draw the title
    draw_title(img, title, width / 2, 50, black);

    // Draw the pie chart
    // Draw each segment
    draw_pie_segments(img, segments, length, x, y, start_angle, radius, black);

    // Check for the existence of the font file before drawing labels
    if (access(FONT_PATH, F_OK) == -1)
    {
        printf("The font file does not exist.\n");
        gdImageDestroy(img);
        free(segments);
        return 1;
    }

    // Draw labels
    draw_label(img, segments, length, x, y, start_angle, radius, black);

    // Save the image
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
    // Free memory for labels
    for (int i = 0; i < length; i++)
    {
        free(segments[i].label);
    }
    gdImageDestroy(img);
    free(segments);

    return 0;
}