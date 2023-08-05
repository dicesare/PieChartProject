#include "pie_chart.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <gdfonts.h>
#include <libgen.h>

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
        double x_start, y_start, x_end, y_end;
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

PieChartSegment *parse_segments(char **input, int *length, int argc, bool output_file_name)
{
    // TODO: Parse percentages and labels from the input string
    // Store the total number of segments in *length
    // Return an array of PieChartSegments
    int segmentIndex = 1;
    int segmentLengh = 1;
    int i = 0;
    *length = 0;
    if (output_file_name)
    {
        segmentIndex++;
        segmentLengh++;
    }
    while (segmentLengh < argc && is_number(input[segmentLengh]) && (strcmp(input[segmentLengh], "-T") != 0 && strcmp(input[segmentLengh], "--titre") != 0))
    {
        (*length)++;
        segmentLengh++;
    }

    PieChartSegment *segments = malloc(*length * sizeof(PieChartSegment));
    if (segments == NULL)
        return NULL; // Stop processing if allocation error occurs

    while (i < *length)
    {
        int labelIndex = segmentLengh + i;
        segments[i].label = malloc(256 * sizeof(char));
        if (segments[i].label == NULL)
            exit(EXIT_FAILURE);
        sscanf(input[segmentIndex], "%lf", &(segments[i].percentage));

        if (labelIndex < argc && (strcmp(input[labelIndex], "-T") != 0 && strcmp(input[labelIndex], "--titre") != 0))
        {
            strncpy(segments[i].label, input[labelIndex], 255);
            segments[i].label[255] = '\0'; // Assure que la chaîne est terminée
        }
        else
        {
            segments[i].label[0] = '\0'; // Label vide si pas d'argument fourni
        }
        segmentIndex++;
        i++;
    }
    return segments;
}

char* generate_output_file(const char *executable_name)
{
    char *base_name = generate_base_name_from_executable(executable_name);
    size_t len = strlen(base_name) + 5; // Space for ".png" extension
    char* output_file = malloc(len * sizeof(char));
    if (output_file)
    {
        snprintf(output_file, len, "%s.png", base_name);
    }
    return output_file;
}

char* retrieve_title(int argc, char **argv, char *base_name)
{
    char *title = NULL;
    for (int i = 1; i < argc - 1; i++)
    {
        if (strcmp(argv[i], "-T") == 0 || strcmp(argv[i], "--titre") == 0)
        {
            title = argv[i + 1];
            break;
        }
    }
    // Use base name as title if no title provided
    if (title == NULL && base_name != NULL) title = base_name;
    return title;
}

char* generate_base_name_from_executable(const char *executable_name) {
    return basename(strdup(executable_name)); // Extrait le nom de base    
}

bool is_number(char *str)
{
    if (*str == '\0')
        return false;

    bool has_dot = false; // Pour vérifier qu'il y a au plus un point décimal

    if (*str == '-' || *str == '+') // Gérer un éventuel signe au début
        str++;

    while (*str)
    {
        if (*str == '.')
        {
            if (has_dot) // Si un point décimal a déjà été trouvé, retourner false
                return false;
            has_dot = true;
        }
        else if (!isdigit((unsigned char)*str))
            return false;

        str++;
    }

    return true;
}

bool has_arguments(int argc)
{
    return argc >= 2;
}

Color generate_random_color()
{
    Color color;
    color.r = rand() % 256;
    color.g = rand() % 256;
    color.b = rand() % 256;
    return color;
}