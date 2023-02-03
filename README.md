# Cy-meteo-
Ce code est une compilation de différents scripts qui vont prendre les données d'un fichier de banque de données et afficher différents graphiques en fonction des options choisies. Il utilise deux langages de programmation différents, d'abord bash pour prendre les arguments et couper les données, puis il utilisera le langage C pour trier les données filtrées et réutilisera bash avec la bibliothèque gnuplot pour imprimer un graphique.

##UTILISATION
Pour compiler les algorithmes de tri, mettez tous les fichiers du github dans le même répertoire puis utilisez la commande :

```c
  $ make
```  
  
###Pour utiliser le programme :
```bash
  $ bash meteo.sh --help
```  
###Découvrir l'outil
Pour découvrir l'outil, utilisez cette commande dans le terminal linux :

```bash
  $ bash meteo.sh --help
  ```
