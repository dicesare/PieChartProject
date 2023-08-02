#include "pie_chart.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>


/**
 * @brief Calculates the coordinates of a point on a circle's circumference.
 * 
 * This function takes the center (x, y), radius, and angle of a circle, and calculates
 * the coordinates of the corresponding point on the circle's circumference. The calculated
 * coordinates are stored in the addresses provided by coord_x and coord_y.
 *
 * @param x The x-coordinate of the circle's center.
 * @param y The y-coordinate of the circle's center.
 * @param radius The radius of the circle.
 * @param angle The angle in degrees from the positive x-axis to the point on the circle's circumference.
 * @param coord_x Pointer to an integer where the x-coordinate of the point on the circumference will be stored.
 * @param coord_y Pointer to an integer where the y-coordinate of the point on the circumference will be stored.
 */

void calculate_coordinates(int x, int y, int radius, int angle, int *coord_x, int *coord_y)
{
    *coord_x = x + radius * cos(angle * M_PI / 180);
    *coord_y = y + radius * sin(angle * M_PI / 180);
}

/**
 * @brief Draws labels for segments of a pie chart.
 *
 * This function iterates through the provided segments of a pie chart, calculates the position
 * for the label of each segment, and draws the label using the specified font settings. 
 * The labels are positioned near the outer edge of the segments.
 *
 * @param img Pointer to the image where the labels will be drawn.
 * @param segments Pointer to an array of PieChartSegment structures containing the label information.
 * @param length The number of segments in the pie chart.
 * @param x The x-coordinate of the pie chart's center.
 * @param y The y-coordinate of the pie chart's center.
 * @param start_angle The starting angle for drawing the first segment (in degrees).
 * @param radius The radius of the pie chart.
 * @param color The color used for drawing the text labels.
 */
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


/**
 * @brief Draws the segments of a pie chart.
 *
 * This function iterates through the provided segments of a pie chart, calculates the start and end angles for each segment,
 * and draws the segment using a randomly generated color. It also draws black borders around each segment and separating lines
 * between adjacent segments.
 *
 * @param img Pointer to the image where the segments will be drawn.
 * @param segments Pointer to an array of PieChartSegment structures containing the segment information.
 * @param length The number of segments in the pie chart.
 * @param x The x-coordinate of the pie chart's center.
 * @param y The y-coordinate of the pie chart's center.
 * @param start_angle The starting angle for drawing the first segment (in degrees).
 * @param radius The radius of the pie chart.
 * @param black The color used for drawing the borders and separating lines (usually black).
 */

void draw_pie_segments(gdImagePtr img, PieChartSegment *segments, int length, int x, int y, int start_angle, int radius, int black)
{
    for (int i = 0; i < length; i++)
    {
        int end_angle = start_angle + segments[i].percentage * 3.6; // Multiply by 3.6 to convert to degrees

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


/**
 * @brief Parses pie chart segments from input strings.
 *        This function extracts the percentages and labels from the command-line input
 *        and creates an array of PieChartSegment structures to represent each segment of a pie chart.
 * 
 * @param input  An array of strings, where input[2] contains the comma-separated percentages
 *               and input[3] contains the comma-separated labels for each pie chart segment.
 * @param length A pointer to an integer to store the total number of pie chart segments.
 * @return       A pointer to an array of PieChartSegment structures representing the segments of the pie chart,
 *               or NULL if an allocation error occurs.
 */

PieChartSegment *parse_segments(char **input, int *length)
{
    // TODO: Parse percentages and labels from the input string
    // Store the total number of segments in *length
    // Return an array of PieChartSegments
    char *input_percentages = input[2];
    char *input_labels = input[3];
    *length = 0;
    for (char *p = input_percentages; *p != '\0'; p++)
    {
        if (*p == ',')
            (*length)++;
    }
    (*length)++; // Add 1 because there's one more segment than commas, otherwise it returns 2
    PieChartSegment *segments = malloc(*length * sizeof(PieChartSegment));
    if (segments == NULL)
        return NULL; // Stop processing if allocation error occurs
    int i = 0;
    char *saveptr1, *saveptr2;                                             // Save pointers for strtok_r
    char *token_percentages = strtok_r(input_percentages, ",", &saveptr1); // Use ',' to separate our string into tokens
    char *token_labels = strtok_r(input_labels, ",", &saveptr2);           // Use ',' to separate our string into tokens
    while (token_percentages != NULL && token_labels != NULL)
    {
        segments[i].label = malloc(256 * sizeof(char));
        if (segments[i].label == NULL)
            exit(EXIT_FAILURE);
        sscanf(token_percentages, "%d", &(segments[i].percentage));
        strncpy(segments[i].label, token_labels, 256);
        token_percentages = strtok_r(NULL, ",", &saveptr1);
        token_labels = strtok_r(NULL, ",", &saveptr2);
        i++;
    }
    return segments;
}

/**
 * @brief Draws the title text at the specified position in an image.
 * 
 * @param img    A pointer to the image where the title will be drawn.
 * @param title  The title text to draw.
 * @param x      The x-coordinate of the position where the title will be centered.
 * @param y      The y-coordinate of the position where the title will be drawn.
 * @param color  The color value to use for the text.
 */
void draw_title(gdImagePtr img, char *title, int x, int y, int color)
{
    int brect[8];
    double size = SIZE_TITLE;
    char *err;
    double angle = 0.0;
    int len = strlen(title);
    char string[len+1];
    for(int i = 0; i < len; i++) {
        string[i] = toupper(title[i]);
    }
    string[len] = '\0';

    err = gdImageStringFT(NULL, &brect[0], color, FONT_PATH, size, angle, 0, 0, string);
    if (err) {
        fprintf(stderr, "Impossible de rendre le titre: %s\n", err);
        return;
    }
    
    gdImageStringFT(img, &brect[0], color, FONT_PATH, size, angle, x - brect[2] / 2, y, string);

}
/**
 * @brief Generates a random RGB color.
 * 
 * @return       A Color structure representing the randomly generated RGB color,
 *               with red, green, and blue components ranging from 0 to 255.
 */
Color generate_random_color()
{
    Color color;
    color.r = rand() % 256;
    color.g = rand() % 256;
    color.b = rand() % 256;
    return color;
}