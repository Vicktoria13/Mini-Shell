## Bienvenue

# TP projet realisé par Victoria NGUYEN et Matthieu SYSOUVANH ROB4

# pour executer le code : 

taper make dans le terminal, puis ./main pour executer l'executable. Taper q pour quitter ou exit.
A savoir : les codes sont richement commentés, et une doc est disponible, dans le fichier doc (html ou latex).

# question 1.1 :
Pour les commandes simples sans arguments, on utilise la fonction strkok pour diviser, et execvp pour executer. On utilise des forks, car l'execvp entraine une mutation de processus.

# question 1.2 :
Pour cela, on utilise de meme la fonction strkok pour diviser selon les " ", et on place chaque mot dans un tableau de char**. Par la suite, on place un NULL a la fin du tableau, et on lance l'execvp dans un fork (processus fils)

# question 1.3 
Modifification de la structure du code : on test d'abord en premier lieu le contenu de buffer ( chaine de mots entrée par l'utilisateur) : Si on detecte un cd ou un pwd, alors on ne lance pas de fork, seulement une execution simple sans execvp, via chdir(), getcwd().



# question 2.1
Pour cela, on test avant d'entrer dans le traitement, si le buffer contient le caractere  & : si oui, alors le buffer sera divisé selon & , et le & sera remplacé par un NULL.

On lance ensuite un fork qui executera la premiere partie avant le &. La différence sera que le processus parent n'attendra pas (pas de wait) la fin du processus fils.


# principe de fonctionnement pour les pipes :
On split ce qui est lu et écris dans le buffer selon le caractère " ". Sauf que dès que l'on voit le caractère "|" , alors on crée un 2e tableau.
Attention les 2 tableaux doivent se finir par NULL.

Ensuite, dans  2 fork separés, on créera un appel exec pour chacun de ses 2 tableau, avec la sortie de l'un dirigé vers l'autre via le dup2.

# redirection de stdout
De meme, on teste la presence du caractere  > toujours via la fonction split.



 