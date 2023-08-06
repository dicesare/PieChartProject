#ifndef VIEW_H
#define VIEW_H

#include <gd.h>
#include "model.h"
#include "utils.h"

#define FONT_PATH "/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf"

#define SIZE_TITLE 44
#define WIDTH 2400
#define HEIGHT 1600

/**
 * @brief Creates an image representing a pie chart based on the segments provided.
 * 
 * This function generates a pie chart image using the data provided through the segments.
 * It uses the gd library to draw the image. Diagram segments are drawn with random colors 
 labels corresponding to each segment are also drawn on the image, and a title is * added to the top of the image. 
 * added at the top of the image.
 * 
 * @param segments Pointer to an array of PieChartSegment structures containing the data for each segment of the diagram.
 * @param segments_count Number of segments in the array.
 * @param title Title of the pie chart to be displayed at the top of the image.
 * 
 * @return gdImagePtr Pointer to the created image. The user is responsible for destroying this image 
 * using gdImageDestroy() once he's finished with it.
 */
gdImagePtr create_pie_chart_image(PieChartSegment *segments, int segments_count, char *title);


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

#endif // VIEW_H
