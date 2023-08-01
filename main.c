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
typedef struct Color
{
    int r;
    int g;
    int b;
} Color;
// Générer une couleur aléatoire
Color generate_random_color()
{
    Color color;
    color.r = rand() % 256;
    color.g = rand() % 256;
    color.b = rand() % 256;
    return color;
}

PieChartSegment *parse_segments(char **input, int *length);

void draw_pie_chart_segments(gdImagePtr img, PieChartSegment *segments, int length, int x, int y, int start_angle, int radius, int black);
void insert_segment_labels(gdImagePtr img, PieChartSegment *segments, int length, int x, int y, int start_angle, int radius, int color);

int main(int argc, char **argv)
{
    int width = 800;
    int height = 600;
    int start_angle = 0; // Définir l'angle de départ
    int end_angle = 60;  // Définir l'angle de fin
    int radius = 200;    // Définir le rayon
    int x = width / 2;   // Centrer le cercle en x
    int y = height / 2;  // Centrer le cercle en y
    int color;
    srand(time(NULL)); // Initialiser le générateur de nombres aléatoires

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

    // Couleur de fond
    int bg = gdImageColorAllocate(img, 255, 255, 255);
    int black = gdImageColorAllocate(img, 0, 0, 0); // Couleur de la bordure

    // Dessiner le graphique en camembert
    // Dessiner chaque segment
    draw_pie_chart_segments(img, segments, length, x, y, start_angle, radius, black);
    insert_segment_labels(img, segments, length, x, y, start_angle, radius, black);
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
// Insérer les étiquettes de segment
void insert_segment_labels(gdImagePtr img, PieChartSegment *segments, int length, int x, int y, int start_angle, int radius, int color) {
    // Définir les paramètres de la police de caractères
    char *fontPath = "/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf"; // Chemin vers le fichier de police, à adapter à votre système
    double fontSize = 12.0;                                                  // Taille de la police en points

    for (int i = 0; i < length; i++) {
        int end_angle = start_angle + segments[i].percentage * 3.6; // Multiplier par 3.6 pour convertir en degrés
        char *label = segments[i].label;

        // Calculer la position du texte
        int label_x = x + (radius * 1.2) * cos((start_angle + (end_angle - start_angle) / 2) * M_PI / 180);
        int label_y = y + (radius * 1.2) * sin((start_angle + (end_angle - start_angle) / 2) * M_PI / 180);

        // Écrire le texte
        int brect[8]; // Rectangle délimitant le texte
        gdImageStringFT(NULL, brect, color, fontPath, fontSize, 0, 0, 0, label);

        // // Si le texte est sur la partie gauche du diagramme, aligner à la fin de la chaîne
        // if(label_x < x) {
        //     label_x -= (brect[2] - brect[0]);
        // }
        // Ajuster la position du texte selon la taille de la boîte englobante
        int text_width = brect[2] - brect[0];
        int text_height = brect[3] - brect[5];
        label_x -= (brect[2] - brect[0]) / 2;
        label_y += (brect[3] - brect[5]) / 2;

        gdImageStringFT(img, brect, color, fontPath, fontSize, 0, label_x - (brect[2] - brect[0]) / 2, label_y + (brect[3] - brect[7]) / 2, label);
        
        // Calculer les coordonnées du point sur le bord du rectangle qui est le plus proche du centre du cercle
        int line_start_x = (start_angle + (end_angle - start_angle) / 2 > 180) ? brect[0] : brect[2];
        int line_start_y = (start_angle + (end_angle - start_angle) / 2 > 180) ? brect[1] : brect[3];

        // Calculer les coordonnées du point médian sur le contour du segment
        int mid_x = x + radius * cos((start_angle + (end_angle - start_angle) / 2) * M_PI / 180);
        int mid_y = y + radius * sin((start_angle + (end_angle - start_angle) / 2) * M_PI / 180);

        // Dessiner une ligne du point médian au texte
        gdImageLine(img, mid_x, mid_y, line_start_x, line_start_y, color);

        start_angle = end_angle;
        start_angle = end_angle;
    }
}

// Dessiner chaque segment du camembert
void draw_pie_chart_segments(gdImagePtr img, PieChartSegment *segments, int length, int x, int y, int start_angle, int radius, int black) {

    for (int i = 0; i < length; i++)
    {
        int end_angle = start_angle + segments[i].percentage * 3.6; // Multiplier par 3.6 pour convertir en degrés

        // Générer une couleur aléatoire
        Color color = generate_random_color();

        // Allouer la couleur dans l'image
        int img_color = gdImageColorAllocate(img, color.r, color.g, color.b);

        // Dessiner le segment du camembert
        gdImageFilledArc(img, x, y, 2 * radius, 2 * radius, start_angle, end_angle, img_color, gdPie);

        // Dessiner une bordure noire autour du segment
        gdImageArc(img, x, y, 2 * radius, 2 * radius, start_angle, end_angle, black);

        // Calculer les coordonnées du début et de la fin des lignes de séparation
        double rad_start = start_angle * M_PI / 180.0;
        double rad_end = end_angle * M_PI / 180.0;
        int x_start = x + radius * cos(rad_start);
        int y_start = y + radius * sin(rad_start);
        int x_end = x + radius * cos(rad_end);
        int y_end = y + radius * sin(rad_end);

        // Dessiner les lignes de séparation
        gdImageLine(img, x, y, x_start, y_start, black);
        gdImageLine(img, x, y, x_end, y_end, black);

        start_angle = end_angle;
    }
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
    char *saveptr1, *saveptr2;                                             // pointeurs de sauvegarde pour strtok_r
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
