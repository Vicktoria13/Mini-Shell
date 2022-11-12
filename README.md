#Bienvenue

#principe de fonctionnement pour les pipes :
On split ce qui est lu et écris dans le buffer selon le caractère " ". Sauf que dès que l'on voit le caractère "|" , alors on crée un 2e tableau.
Attention les 2 tableaux doivent se finir par NULL.

Ensuite, dans  2 fork separés, on créera un appel exec pour chacun de ses 2 tableau, avec la sortie de l'un dirigé vers l'autre via le dup2.

