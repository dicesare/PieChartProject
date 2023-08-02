#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <gd.h>
#include <math.h>
#include <unistd.h> // Pour accéder à la fonction access()

#define FONT_PATH "/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf"
#define SIZE_TITLE 44
#define WIDTH 2400
#define HEIGTH 1600

/**
 * @brief Structure to represent a segment in a pie chart.
 * 
 * This structure is used to define a segment of a pie chart, including
 * its percentage representation, label, and color. 
 */
typedef struct PieChartSegment
{
    int percentage;      ///< The percentage that this segment represents in the pie chart.
    char *label;         ///< The label for this segment (e.g., the name of the category).
    gdImagePtr color;    ///< The color used to draw this segment in the pie chart.
} PieChartSegment;


/**
 * @brief Structure to represent a color in the RGB color space.
 * 
 * This structure is used to define a color using its red (r), green (g), and blue (b) components.
 * It can be used to represent a specific color for various graphical elements.
 */
typedef struct Color
{
    int r; ///< Red component of the color, in the range 0-255.
    int g; ///< Green component of the color, in the range 0-255.
    int b; ///< Blue component of the color, in the range 0-255.
} Color;

/**
 * @brief Generates a random color in the RGB color space.
 * 
 * This function creates a random color by selecting random values for the red, green, and blue components.
 * It can be used whenever a random color is required, such as for styling different segments of a chart.
 *
 * @return Color The randomly generated color, with each component in the range 0-255.
 */
Color generate_random_color();
/**
 * @brief Parses the input data to create an array of PieChartSegment structures.
 * 
 * This function takes an array of strings containing the input data and a pointer to an integer
 * to store the length of the array. It parses the data to create an array of PieChartSegment
 * structures, each representing a segment of a pie chart. The percentage, label, and color for each
 * segment are extracted from the input data.
 *
 * @param input Pointer to an array of strings containing the input data for the pie chart segments.
 * @param length Pointer to an integer where the length of the resulting array of PieChartSegment structures will be stored.
 * @return PieChartSegment* A dynamically allocated array of PieChartSegment structures representing the segments of the pie chart.
 *                          The caller is responsible for freeing this memory.
 */
PieChartSegment *parse_segments(char **input, int *length);

/**
 * @brief Calculates the coordinates of a point on a circle given its center, radius, and angle.
 * 
 * This function takes the x and y coordinates of the center of a circle, its radius, and an angle, and calculates
 * the x and y coordinates of the point on the circumference of the circle that corresponds to the given angle.
 * The results are stored in the pointers provided for `coord_x` and `coord_y`.
 *
 * @param x The x-coordinate of the center of the circle.
 * @param y The y-coordinate of the center of the circle.
 * @param radius The radius of the circle.
 * @param angle The angle in degrees, for which the coordinates are to be calculated.
 * @param coord_x Pointer to an integer where the calculated x-coordinate will be stored.
 * @param coord_y Pointer to an integer where the calculated y-coordinate will be stored.
 */
void calculate_coordinates(int x, int y, int radius, int angle, int *coord_x, int *coord_y);

/**
 * @brief Draws the segments of a pie chart on an image.
 * 
 * This function takes an image pointer, an array of segments representing the different parts of the pie chart,
 * the center coordinates of the pie, starting angle, radius, and the color for the border, and then draws each
 * segment of the pie chart on the given image.
 *
 * @param img Pointer to the image where the pie chart will be drawn.
 * @param segments Pointer to an array of PieChartSegment structures representing the segments of the pie chart.
 * @param length The number of segments in the pie chart.
 * @param x The x-coordinate of the center of the pie chart.
 * @param y The y-coordinate of the center of the pie chart.
 * @param start_angle The starting angle in degrees for the first segment of the pie chart.
 * @param radius The radius of the pie chart.
 * @param black The color to be used for the border of the segments (usually black).
 */
void draw_pie_segments(gdImagePtr img, PieChartSegment *segments, int length, int x, int y, int start_angle, int radius, int black);

/**
 * @brief Draws the labels for the segments of a pie chart on an image.
 * 
 * This function takes an image pointer, an array of segments representing the different parts of the pie chart,
 * the center coordinates of the pie, starting angle, radius, and the color for the labels, and then draws the labels
 * corresponding to each segment of the pie chart on the given image.
 *
 * @param img Pointer to the image where the labels will be drawn.
 * @param segments Pointer to an array of PieChartSegment structures representing the segments of the pie chart.
 * @param length The number of segments in the pie chart.
 * @param x The x-coordinate of the center of the pie chart.
 * @param y The y-coordinate of the center of the pie chart.
 * @param start_angle The starting angle in degrees for the first segment of the pie chart.
 * @param radius The radius of the pie chart.
 * @param color The color to be used for the labels.
 */
void draw_label(gdImagePtr img, PieChartSegment *segments, int length, int x, int y, int start_angle, int radius, int color);

/**
 * @brief Draws the title of the pie chart on an image.
 * 
 * This function takes an image pointer, a title string, the coordinates where the title should be drawn, and the color
 * for the title text, and then draws the title on the given image.
 *
 * @param img Pointer to the image where the title will be drawn.
 * @param title Pointer to a string containing the title text.
 * @param x The x-coordinate of where the title will be drawn.
 * @param y The y-coordinate of where the title will be drawn.
 * @param color The color to be used for the title text.
 */
void draw_title(gdImagePtr img, char *title, int x, int y, int color);
