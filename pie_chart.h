#ifndef PIE_CHART_H
#define PIE_CHART_H

#include <gd.h>
#include <unistd.h> // Pour accéder à la fonction access()
#include <stdbool.h>

#define FONT_PATH "/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf"
#define SIZE_TITLE 44
#define WIDTH 2400
#define HEIGHT 1600

/**
 * @brief Structure to represent a segment in a pie chart.
 * 
 * This structure is used to define a segment of a pie chart, including
 * its percentage representation, label, and color. 
 */
typedef struct PieChartSegment
{
    double percentage;      ///< The percentage that this segment represents in the pie chart.
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
 * @brief Generates a random RGB color.
 * 
 * @return       A Color structure representing the randomly generated RGB color,
 *               with red, green, and blue components ranging from 0 to 255.
 */
Color generate_random_color();

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

PieChartSegment *parse_segments(char **input, int *length, int argc, bool output_file_name);

/**
 * @brief Extracts the base name (file name without path) from the given executable name.
 *        This can be useful to create names based on the current executable.
 * 
 * @param executable_name The full path or name of the executable.
 * @return char* A dynamically allocated string containing the base name of the executable.
 */
char* generate_base_name_from_executable(const char *executable_name);


/**
 * @brief Generates the output file name based on the executable name.
 *        The file name will have the format "executable_name.png".
 * 
 * @param executable_name The name of the executable from which the output file name is derived.
 * @return char* A dynamically allocated string containing the output file name, or NULL if allocation fails.
 */
char* generate_output_file(const char *executable_name);

/**
 * @brief Retrieves the title from the command-line arguments if present. If no title is provided and a base name is given, it returns the base name as the title.
 *
 * @param argc The number of command-line arguments.
 * @param argv An array of command-line arguments.
 * @param base_name The base name (usually extracted from the executable name), which will be used as the title if no title is provided in the command-line arguments.
 * @return char* A pointer to the title string, or the base name if no title is provided in the command-line arguments.
 */
char* retrieve_title(int argc, char **argv, char *base_name);


/**
 * @brief Determines if a given string represents a valid number.
 *
 * @param str The string to check.
 * @return true If the string represents a number.
 * @return false If the string does not represent a number.
 */
bool is_number(char *str);

/**
 * @brief Checks if the program has been called with command-line arguments.
 *
 * @param argc The number of command-line arguments.
 * @return true If there are command-line arguments besides the program name.
 * @return false If there are no additional command-line arguments.
 */
bool has_arguments(int argc);


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
void calculate_coordinates(int x, int y, int radius, int angle, int *coord_x, int *coord_y);

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

void draw_pie_segments(gdImagePtr img, PieChartSegment *segments, int length, int x, int y, double start_angle, int radius, int black);

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
void draw_label(gdImagePtr img, PieChartSegment *segments, int length, int x, int y, int start_angle, int radius, int color);

/**
 * @brief Draws the title text at the specified position in an image.
 * 
 * @param img    A pointer to the image where the title will be drawn.
 * @param title  The title text to draw.
 * @param x      The x-coordinate of the position where the title will be centered.
 * @param y      The y-coordinate of the position where the title will be drawn.
 * @param color  The color value to use for the text.
 */
void draw_title(gdImagePtr img, char *title, int x, int y, int color);

#endif // PIE_CHART_H