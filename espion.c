#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <wait.h>
#include <sys/mman.h>

int main(int argc, char **argv)
{
    struct stat s;
    int fd;
    if (stat("bovary.txt", &s) == -1)
    {
        perror("stat");
        exit(2);
    }
    fd = open("bovary.txt", O_RDWR);

    int file_length = s.st_size;

    char *adr = mmap(NULL, file_length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    for (int i = 0; i < file_length; i++)
    {
        if (adr[i] == '0' && adr[i + 1] == 'x')
        {
            printf("le code secret ecrit dans le fichier est ");
            for (int j = i; j < i + 20; j++)
            {
                if (adr[j] == 'x' && adr[j + 1] == '0' && j >= 10)
                {
                    printf("%c", adr[j]);
                    printf("%c\n", adr[j + 1]);
                    printf("\n");
                    exit(0);
                }
                else
                {
                    printf("%c", adr[j]);
                }
            }
        }
    }
    perror("code introuvable!");
    return 0;
}
