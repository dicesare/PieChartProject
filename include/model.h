#ifndef MODEL_H
#define MODEL_H

#include <stdbool.h>


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
 * @brief Structure to represent a segment in a pie chart.
 * 
 * This structure is used to define a segment of a pie chart, including
 * its percentage representation, label, and color. 
 */
typedef struct PieChartSegment
{
    double percentage;      ///< The percentage that this segment represents in the pie chart.
    char *label;         ///< The label for this segment (e.g., the name of the category).
    Color color;    ///< The color used to draw this segment in the pie chart.
} PieChartSegment;

/**
 * @brief Frees the memory associated with pie chart segments.
 *
 * @param segments A pointer to an array of PieChartSegments.
 * @param length The total number of pie chart segments.
 */
void free_segments(PieChartSegment *segments, int length);


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
 * @brief Generates the output file name based on provided arguments or executable name.
 *        If the first argument is provided and is not a number, it's used as the file name.
 *        Otherwise, the file name will have the format "executable_name.png".
 * 
 * @param argc Count of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return char* A dynamically allocated string containing the output file name, 
 *               or NULL if allocation fails.
 */
char *generate_output_file(int argc, char **argv);


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
 * @brief Extracts the base name (file name without path) from the given executable name.
 *        This can be useful to create names based on the current executable.
 * 
 * @param executable_name The full path or name of the executable.
 * @return char* A dynamically allocated string containing the base name of the executable.
 */
char* generate_base_name_from_executable(const char *executable_name);

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
 * @brief Generates a random RGB color.
 * 
 * @return       A Color structure representing the randomly generated RGB color,
 *               with red, green, and blue components ranging from 0 to 255.
 */
Color generate_random_color();

#endif // MODEL_H
