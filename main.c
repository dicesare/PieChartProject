#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <gd.h>
#include <math.h>

// Structure pour stocker les informations sur un segment du graphique
typedef struct
{
    int percentage;
    char *label;
} PieChartSegment;

// Définir une approximation de la palette "viridis"
struct Color {
    int r;
    int g;
    int b;
};
struct Color viridis[] = {
    {68, 1, 84}, {72, 15, 122}, {70, 29, 145},
    {64, 45, 155}, {58, 62, 163}, {51, 79, 168},
    {44, 97, 170}, {37, 116, 169}, {33, 136, 166},
    {31, 155, 162}, {34, 175, 154}, {51, 194, 143},
    {76, 210, 132}, {108, 225, 118}, {146, 238, 102},
    {189, 249, 87}, {237, 255, 69}, {255, 255, 21}
};

PieChartSegment *parse_segments(char **input, int *length);

int num_colors = sizeof(viridis) / sizeof(viridis[0]);

void draw_segments_recursive(gdImagePtr img, int x, int y, int radius, int start_angle, PieChartSegment *segments, int length, int index, int color);
void draw_segment(gdImagePtr im, int x, int y, int radius, int start_angle, int percentage, int color, char *label);


int main(int argc, char **argv)
{

    int width = 800;
    int height = 600;
    int start_angle = 0; // Définir l'angle de départ
    int end_angle = 60; // Définir l'angle de fin
    int radius = 200; // Définir le rayon
    int x = width / 2; // Centrer le cercle en x
    int y = height / 2; // Centrer le cercle en y
    int color; 
    if (argc < 4)
    {
        printf("Usage: %s <output file> <percentages> <labels>\n", argv[0]);
        return 1;
    }
    char *output_file = argv[1];
    int length;

    PieChartSegment *segments = parse_segments(argv, &length);

    if (!segments)
    {
        printf("Erreur lors de l'analyse des segments\n");
        return 1;
    }


    // Créer une nouvelle image
    gdImagePtr img = gdImageCreate(width, height);
    // Creer une couleur fixe rouge
    int red = gdImageColorAllocate(img, 255, 0, 0);

    draw_segments_recursive(img, x, y, radius, start_angle, segments, length, 0, red);

    if (!img)
    {
        free(segments);
        return 1;
    }
    // Dessiner le graphique en camembert
    for (int i = 0; i < length; i++)
    {
        // TODO: Dessiner le segment i
        // TODO: Écrire le label pour le segment i
    }
    // Enregistrer l'image
    FILE *out = fopen(output_file, "wb+");
    if (!out)
    {
        printf("Erreur lors de l'ouverture du fichier de sortie\n");
        gdImageDestroy(img);
        free(segments);
        return 1;
    }
    gdImagePng(img, out);
    fclose(out);

    // Nettoyer
    gdImageDestroy(img);
    free(segments);
    return 0;
}

void draw_segments_recursive(gdImagePtr img, int x, int y, int radius, int start_angle, PieChartSegment *segments, int length, int index, int color) {
    if (index >= length)
        return;

    draw_segment(img, x, y, radius, start_angle, segments[index].percentage, color, segments[index].label);

    int next_start_angle = start_angle + (segments[index].percentage * 360) / 100;

    draw_segments_recursive(img, x, y, radius, next_start_angle, segments, length, index + 1, color);
}

void draw_segment(gdImagePtr im, int x, int y, int radius, int start_angle, int percentage, int color, char *label) {
    int end_angle = start_angle + (percentage * 360) / 100; // Calculer l'angle de fin

    // Dessiner le segment de cercle
    gdImageFilledArc(im, x, y, radius * 2, radius * 2, start_angle, end_angle, color, gdPie);

    // Écrire le label
    // Définir les paramètres de la police de caractères
    char *fontPath = "/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf"; // Chemin vers le fichier de police, à adapter à votre système
    double fontSize = 12.0; // Taille de la police en points

    // Calculer la position du texte
    int label_x = x + (radius / 2) * cos((start_angle + (end_angle - start_angle) / 2) * M_PI / 180);
    int label_y = y + (radius / 2) * sin((start_angle + (end_angle - start_angle) / 2) * M_PI / 180);

    // Écrire le texte
    int brect[8]; // Rectangle délimitant le texte
    gdImageStringFT(NULL, brect, color, fontPath, fontSize, 0, 0, 0, label);
    gdImageStringFT(im, brect, color, fontPath, fontSize, 0, label_x - (brect[2] - brect[0]) / 2, label_y + (brect[3] - brect[7]) / 2, label);
}


// Analyse les pourcentages et les étiquettes depuis la ligne de commande
PieChartSegment *parse_segments(char **input, int *length)
{
    // TODO: Parsez les pourcentages et les étiquettes depuis la chaîne d'entrée
    // Stockez le nombre total de segments dans *length
    // Retournez un tableau de PieChartSegments
    char *input_percentages = input[2];
    char *input_labels = input[3];
    *length = 0;
    for (char *p = input_percentages; *p != '\0'; p++)
    {
        if (*p == ',')
            (*length)++;
    }
    (*length)++; // Ajouter 1 car il y a un segment de plus que de virgules sans ça retourne 2
    PieChartSegment *segments = malloc(*length * sizeof(PieChartSegment));
    if (segments == NULL)
        return NULL; // si errreur allocation on arrete le traitement
    int i = 0;
    char *saveptr1, *saveptr2; // pointeurs de sauvegarde pour strtok_r
    char *token_percentages = strtok_r(input_percentages, ",", &saveptr1); // on utilise la ',' pour separer notre chaine en tokens
    char *token_labels = strtok_r(input_labels, ",", &saveptr2);           // on utilise la ',' pour separer notre chaine en tokens
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
//     // TODO: Définir la palette de couleurs "viridis"



//     // Enregistrer l'image
//     FILE *out = fopen(output_file, "wb+");
//     if (!out)
//     {
//         printf("Erreur lors de l'ouverture du fichier de sortie\n");
//         gdImageDestroy(img);
//         free(segments);
//         return 1;
//     }
//     gdImagePng(img, out);
//     fclose(out);

//     // Nettoyer
//     gdImageDestroy(img);
//     free(segments);
//     return 0;
//}

// int main()
// {
//     printf("Hello Nino!\n");
//     gdImagePtr img = gdImageCreate(100, 100);
//     if (!img)
//     {
//         return 1;
//     }
//     gdImageDestroy(img);
//     return 0;
// }

// // Parse les pourcentages depuis la ligne de commande
// int *parse_percentages(char *input, int *length) {
//     // TODO: Parsez les pourcentages depuis la chaîne d'entrée
//     // Stockez le nombre total de pourcentages dans *length
//     // Retournez un tableau d'entiers contenant les pourcentages
//     return NULL;
// }

// int main(int argc, char **argv) {
//     if (argc < 3) {
//         printf("Usage: %s <output file> <percentages>\n", argv[0]);
//         return 1;
//     }

//     char *output_file = argv[1];
//     int length;
//     int *percentages = parse_percentages(argv[2], &length);

//     if (!percentages) {
//         printf("Erreur lors de l'analyse des pourcentages\n");
//         return 1;
//     }

//     // TODO: Générez le Pie Chart

//     free(percentages);
//     return 0;
// }
