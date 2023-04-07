#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <math.h>
#include <time.h>

int main(int argc, char **argv)
{

    /* initialisation de generateur de nombres aleatoires*/
    srand(time(0));

    struct stat s;
    int fd;

    fd = open("bovary.txt", O_RDWR);

    if (stat("bovary.txt", &s) == -1)
    {
        perror("stat");
        exit(2);
    }
    /*calcule la taille de fichier et l'afficher*/
    printf("La taille de fichier bovary est : %lu.\n", s.st_size);

    /*la taille de la partie entiere de code secret >8 et <16 */
    int code_length = (rand() % (8) + 8);

    /*tirer une position aleatoire dans le fichier pour ecrire le code secret*/
    int pos = rand() % (s.st_size - (code_length + 4));

    /*la position de debut de la partie entiere de code secret*/
    int poscode = pos + 2;

    /*projection de fichier*/
    char *adr = mmap(NULL, s.st_size, PROT_WRITE, MAP_SHARED, fd, 0);

    adr[pos] = '0';
    adr[pos + 1] = 'x';
    char buf[2];

    for (int i = 0; i < code_length; i++)
    {
        int code = rand() % 9;

        /*conversion de chaque caractere a une chaine de caractere*/
        sprintf(buf, "%d", code);

        adr[poscode] = buf[0];

        /*avancer dans le fichier*/
        poscode++;
    }
    adr[poscode] = 'x';
    adr[poscode + 1] = '0';
}