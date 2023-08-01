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
// Structure pour stocker les informations sur un segment du graphique
typedef struct
{
    int percentage;
    char *label;
    gdImagePtr color;
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

void calculate_coordinates(int x, int y, int radius, int angle, int *coord_x, int *coord_y);
void draw_pie_segments(gdImagePtr img, PieChartSegment *segments, int length, int x, int y, int start_angle, int radius, int black);
void draw_label(gdImagePtr img, PieChartSegment *segments, int length, int x, int y, int start_angle, int radius, int color);
void draw_title(gdImagePtr img, char *title, int x, int y, int color);

int main(int argc, char **argv)
{
    int width = WIDTH;
    int height = HEIGTH;
    int start_angle = 0; // Définir l'angle de départ
    int end_angle = 60;  // Définir l'angle de fin
    int radius = 600;    // Définir le rayon
    int x = width / 2;   // Centrer le cercle en x
    int y = height / 2;  // Centrer le cercle en y
    int color;
    char *title = argv[4];
    char *output_file = argv[1];
    int length;

    srand(time(NULL)); // Initialiser le générateur de nombres aléatoires

    if (argc != 5)
    {
        fprintf(stderr, "Usage: %s <output_file> <data> <labels> <title>\n", argv[0]);
        return 1;
    }


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

    // Dessinez le titre
    draw_title(img, title, width / 2, 50, black);

    // Dessiner le graphique en camembert
    // Dessiner chaque segment
    draw_pie_segments(img, segments, length, x, y, start_angle, radius, black);

    // Avant de dessiner les étiquettes, vérifiez que le fichier de police existe et que la taille de la police n'est pas trop grande
    if (access(FONT_PATH, F_OK) == -1)
    {
        printf("Le fichier de police n'existe pas\n");
        gdImageDestroy(img);
        free(segments);
        return 1;
    }
    draw_label(img, segments, length, x, y, start_angle, radius, black);

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
    // Libérer la mémoire pour les étiquettes
    for (int i = 0; i < length; i++)
    {
        free(segments[i].label);
    }
    gdImageDestroy(img);
    free(segments);
    return 0;
}

void calculate_coordinates(int x, int y, int radius, int angle, int *coord_x, int *coord_y)
{
    *coord_x = x + radius * cos(angle * M_PI / 180);
    *coord_y = y + radius * sin(angle * M_PI / 180);
}

// Insérer les étiquettes de segment
void draw_label(gdImagePtr img, PieChartSegment *segments, int length, int x, int y, int start_angle, int radius, int color)
{
    // Définir les paramètres de la police de caractères
    char *fontPath = FONT_PATH;      // Chemin vers le fichier de police, à adapter à votre système
    double fontSize = radius * 0.05; // Taille de la police en points

    for (int i = 0; i < length; i++)
    {
        int end_angle = start_angle + segments[i].percentage * 3.6; // Multiplier par 3.6 pour convertir en degrés
        char *label = segments[i].label;

        // Calculer la position du texte
        int label_x, label_y;
        calculate_coordinates(x, y, radius * 1.10, start_angle + (end_angle - start_angle) / 2, &label_x, &label_y);

        // Écrire le texte
        int brect[8]; // Rectangle délimitant le texte
        gdImageStringFT(NULL, brect, color, fontPath, fontSize, 0, 0, 0, label);

        // Si le texte est sur la partie gauche du diagramme, aligner à la fin de la chaîne
        if (label_x > x)
        {
            label_x += (brect[2] - brect[0]);
        }
        // Ajuster la position du texte selon la taille de la boîte englobante
        int text_width = brect[2] - brect[0];
        int text_height = brect[3] - brect[5];
        label_x -= (brect[2] - brect[0]) / 2;
        label_y += (brect[3] - brect[5]) / 2;

        gdImageStringFT(img, brect, color, fontPath, fontSize, 0, label_x - (brect[2] - brect[0]) / 2, label_y + (brect[3] - brect[7]) / 2, label);
        start_angle = end_angle;
    }
}

// Dessiner chaque segment du camembert
void draw_pie_segments(gdImagePtr img, PieChartSegment *segments, int length, int x, int y, int start_angle, int radius, int black)
{

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
        double median = (end_angle + start_angle) / 2.0 * M_PI / 180.0;
        int x_start, y_start, x_end, y_end;
        calculate_coordinates(x, y, radius, start_angle, &x_start, &y_start);
        calculate_coordinates(x, y, radius, end_angle, &x_end, &y_end);

        // Calculer les coordonnées du début de la médiane, au bord du cercle
        int x_med_start = x + radius * cos(median);
        int y_med_start = y + radius * sin(median);

        // Calculer les coordonnées de la fin de la médiane, 10% au-delà du bord du cercle
        int x_med_end = x + 1.05 * radius * cos(median);
        int y_med_end = y + 1.05 * radius * sin(median);

        // Dessiner la médiane
        gdImageLine(img, x_med_start, y_med_start, x_med_end, y_med_end, black);

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