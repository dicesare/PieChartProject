#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <gd.h>

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


// Parse les pourcentages depuis la ligne de commande
int *parse_percentages(char *input, int *length) {
    // TODO: Parsez les pourcentages depuis la chaîne d'entrée
    // Stockez le nombre total de pourcentages dans *length
    // Retournez un tableau d'entiers contenant les pourcentages
    return NULL;
}

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Usage: %s <output file> <percentages>\n", argv[0]);
        return 1;
    }

    char *output_file = argv[1];
    int length;
    int *percentages = parse_percentages(argv[2], &length);

    if (!percentages) {
        printf("Erreur lors de l'analyse des pourcentages\n");
        return 1;
    }

    // TODO: Générez le Pie Chart

    free(percentages);
    return 0;
}
