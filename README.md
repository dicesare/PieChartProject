# Generateur de Pie Chart

Ce projet contient un programme en C qui génère un graphique de type Pie Chart (ou camembert en français). 

Le code utilise la bibliothèque GD pour générer le graphique et il peut générer des graphiques avec des pourcentages et des étiquettes spécifiés par l'utilisateur.

## Installation

Assurez-vous que vous avez les bibliothèques gd et math.h installées sur votre système pour compiler et exécuter le programme.

Pour compiler le programme, utilisez la commande gcc:

```bash
gcc -o pie_chart pie_chart.c -lgd -lm
```

## Utilisation

Pour utiliser le programme, vous aurez besoin de fournir trois arguments sur la ligne de commande:

1. Le nom du fichier de sortie (par exemple, output.png)
2. Les pourcentages pour chaque segment du diagramme circulaire, séparés par des virgules (par exemple, 20,30,50)
3. Les étiquettes pour chaque segment, également séparées par des virgules (par exemple, label1,label2,label3)

Voici un exemple d'utilisation :

```bash
./pie_chart output.png "50,30,20" "Etiquette1,Etiquette2,Etiquette3"
```

Les arguments sont:

1. Le nom du fichier de sortie (ex: output.png)
2. Les pourcentages de chaque segment, séparés par des virgules (ex: "50,30,20")
3. Les étiquettes de chaque segment, séparées par des virgules (ex: "Etiquette1,Etiquette2,Etiquette3")

![Texte alternatif](images/output.png)

## Licence

Ce projet est sous licence MIT. Voir le fichier LICENSE pour plus de détails.

## Auteur

Antony Coco

Pour toute question ou demande de support, veuillez ouvrir un ticket dans l'onglet "Issues" de ce dépôt.
