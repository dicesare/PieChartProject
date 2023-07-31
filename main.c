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
}Color;
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


    // Dessiner le graphique en camembert
    // Dessiner chaque segment
    for (int i = 0; i < length; i++) {
        int end_angle = start_angle + segments[i].percentage * 3.6; // Multiplier par 3.6 pour convertir en degrés

        // Générer une couleur aléatoire
        Color color = generate_random_color();

        // Allouer la couleur dans l'image
        int img_color = gdImageColorAllocate(img, color.r, color.g, color.b);

        // Dessiner le segment du camembert
        gdImageFilledArc(img, x, y, 2 * radius, 2 * radius, start_angle, end_angle, img_color, gdPie);

        start_angle = end_angle;
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
