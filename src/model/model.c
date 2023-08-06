/**
 * @file model.c
 * @author Antony COCO (antony.coco.pro@gmail.com)
 * @brief Program to generate a pie chart image based on input data.
 * @version 0.1
 * @date 2023-08-06
 *
 * @copyright Copyright (c) 2023
 */

#include "model.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <libgen.h>

void free_segments(PieChartSegment *segments, int length)
{
    for (int i = 0; i < length; i++)
    {
        free(segments[i].label);
    }
    free(segments);
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
        {
            free_segments(segments, i); // Libérer la mémoire pour les segments précédents
            return NULL;
        }
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

char *generate_output_file(int argc, char **argv)
{
    char *output_file;

    // Vérifier s'il y a des arguments et que le premier n'est pas un nombre
    if (argc > 1 && !is_number(argv[1]))
    {
        output_file = strdup(argv[1]); // Dupliquer la chaîne pour être cohérent avec le comportement de malloc plus loin
    }
    else
    {
        char *base_name = generate_base_name_from_executable(argv[0]);
        size_t len = strlen(base_name) + 5; // Espace pour l'extension ".png"
        output_file = malloc(len * sizeof(char));
        if (output_file)
        {
            snprintf(output_file, len, "%s.png", base_name);
        }
        free(base_name); // Libérer base_name après l'avoir utilisé
    }

    return output_file;
}


char *retrieve_title(int argc, char **argv, char *base_name)
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
    if (title == NULL && base_name != NULL)
        title = base_name;
    return title;
}

char *generate_base_name_from_executable(const char *executable_name)
{
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
