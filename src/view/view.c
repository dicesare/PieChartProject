/**
 * @file view.c
 * @author Antony COCO (antony.coco.pro@gmail.com)
 * @brief Program to generate a pie chart image based on input data.
 * @version 0.1
 * @date 2023-08-06
 *
 * @copyright Copyright (c) 2023
 */
#include "view.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gdfonts.h>
#include <string.h>
#include <ctype.h>



gdImagePtr create_pie_chart_image(PieChartSegment *segments, int segments_count, char *title) {
    // Create a new image with predefined dimensions
    gdImagePtr img = gdImageCreate(WIDTH, HEIGHT);
    
    // Set a background color (adjust as required)
    int backgroundColor = gdImageColorAllocate(img, 255, 255, 255);  // Blanc
    gdImageFill(img, 0, 0, backgroundColor);

    //futur develloper border function

    // Draw the segments of the pie chart
    int black = gdImageColorAllocate(img, 0, 0, 0);  // Noir pour les bordures
    draw_pie_segments(img, segments, segments_count, WIDTH / 2, HEIGHT / 2, 0, MIN(WIDTH, HEIGHT) / 3, black);

   // Draw labels for the segments
    draw_label(img, segments, segments_count, WIDTH / 2, HEIGHT / 2, 0, MIN(WIDTH, HEIGHT) / 3, black);

    // Drawn the title
    draw_title(img, title, WIDTH / 2, HEIGHT / 10, black);

    return img;
}

void calculate_coordinates(int x, int y, int radius, int angle, int *coord_x, int *coord_y)
{
    *coord_x = x + radius * cos(angle * M_PI / 180);
    *coord_y = y + radius * sin(angle * M_PI / 180);
}

void draw_label(gdImagePtr img, PieChartSegment *segments, int length, int x, int y, int start_angle, int radius, int color)
{
    // Define the font parameters
    char *fontPath = FONT_PATH;      // Path to the font file, adjust for your system
    double fontSize = radius * 0.05; // Font size in points

    for (int i = 0; i < length; i++)
    {
        int end_angle = start_angle + segments[i].percentage * 3.6; // Multiply by 3.6 to convert to degrees
        char *label = segments[i].label;

        // Calculate the text position
        int label_x, label_y;
        calculate_coordinates(x, y, radius * 1.10, start_angle + (end_angle - start_angle) / 2, &label_x, &label_y);

        // Write the text
        int brect[8]; // Bounding rectangle of the text
        gdImageStringFT(NULL, brect, color, fontPath, fontSize, 0, 0, 0, label);

        // If the text is on the left part of the diagram, align to the end of the string
        if (label_x > x)
        {
            label_x += (brect[2] - brect[0]);
        }
        // Adjust the position of the text according to the size of the bounding box
        int text_width = brect[2] - brect[0];
        int text_height = brect[3] - brect[5];
        label_x -= (brect[2] - brect[0]) / 2;
        label_y += (brect[3] - brect[5]) / 2;

        gdImageStringFT(img, brect, color, fontPath, fontSize, 0, label_x - (brect[2] - brect[0]) / 2, label_y + (brect[3] - brect[7]) / 2, label);
        start_angle = end_angle;
    }
}

void draw_pie_segments(gdImagePtr img, PieChartSegment *segments, int length, int x, int y, double start_angle, int radius, int black)
{
    for (int i = 0; i < length; i++)
    {
        double end_angle = start_angle + segments[i].percentage * 3.6; // Multiply by 3.6 to convert to degrees

        // Generate a random color
        Color color = generate_random_color();

        // Allocate the color in the image
        int img_color = gdImageColorAllocate(img, color.r, color.g, color.b);

        // Draw the pie chart segment
        gdImageFilledArc(img, x, y, 2 * radius, 2 * radius, start_angle, end_angle, img_color, gdPie);

        // Draw a black border around the segment
        gdImageArc(img, x, y, 2 * radius, 2 * radius, start_angle, end_angle, black);

        // Calculate the coordinates of the start and end of the separation lines
        double rad_start = start_angle * M_PI / 180.0;
        double rad_end = end_angle * M_PI / 180.0;
        double median = (end_angle + start_angle) / 2.0 * M_PI / 180.0;
        int x_start, y_start, x_end, y_end;
        calculate_coordinates(x, y, radius, start_angle, &x_start, &y_start);
        calculate_coordinates(x, y, radius, end_angle, &x_end, &y_end);

        // Calculate the coordinates of the start of the median, at the edge of the circle
        int x_med_start = x + radius * cos(median);
        int y_med_start = y + radius * sin(median);

        // Calculate the coordinates of the end of the median, 10% beyond the edge of the circle
        int x_med_end = x + 1.05 * radius * cos(median);
        int y_med_end = y + 1.05 * radius * sin(median);

        // Draw the median
        gdImageLine(img, x_med_start, y_med_start, x_med_end, y_med_end, black);

        // Draw the separation lines
        gdImageLine(img, x, y, x_start, y_start, black);
        gdImageLine(img, x, y, x_end, y_end, black);

        start_angle = end_angle;
    }
}

void draw_title(gdImagePtr img, char *title, int x, int y, int color)
{
    int brect[8];
    double size = SIZE_TITLE;
    char *err;
    double angle = 0.0;
    int len = strlen(title);
    char string[len + 1];
    for (int i = 0; i < len; i++)
    {
        string[i] = toupper(title[i]);
    }
    string[len] = '\0';

    err = gdImageStringFT(NULL, &brect[0], color, FONT_PATH, size, angle, 0, 0, string);
    if (err)
    {
        fprintf(stderr, "Impossible de rendre le titre: %s\n", err);
        return;
    }

    gdImageStringFT(img, &brect[0], color, FONT_PATH, size, angle, x - brect[2] / 2, y, string);
}

