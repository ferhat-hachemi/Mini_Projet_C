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

    srand(time(0));

    struct stat s;
    int fd;

    fd = open("bovary.txt", O_RDWR);

    if (stat("bovary.txt", &s) == -1)
    {
        perror("stat");
        exit(2);
    }

    printf("La taille de fichier bovary est : %lu.\n", s.st_size);

    int code_length = (rand() % (8) + 8);

    int pos = rand() % (s.st_size - (code_length + 4));

    int poscode = pos + 2;

    char *adr = mmap(NULL, s.st_size, PROT_WRITE, MAP_SHARED, fd, 0);

    adr[pos] = '0';
    adr[pos + 1] = 'x';
    char buf[2];

    for (int i = 0; i < code_length; i++)
    {
        int code = rand() % 9;

        sprintf(buf, "%d", code);

        adr[poscode] = buf[0];

        poscode++;
    }
    adr[poscode] = 'x';
    adr[poscode + 1] = '0';
    close(fd);
}
