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
#include <wait.h>
#include <stdbool.h>

int main(int argc, char **argv)
{

    srand(time(0));
    int n = atoi(argv[1]);
    int pid;

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

    char *adr = mmap(NULL, s.st_size, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);

    char buf[code_length];
    char buf2[code_length];

    adr[pos] = '0';
    adr[pos + 1] = 'x';

    for (int i = 0; i < code_length + 2; i++)
    {

        int code = rand() % 9;
        sprintf(buf, "%d", code);
        adr[poscode] = buf[0];
        poscode++;
    }

    adr[poscode] = 'x';
    adr[poscode + 1] = '0';

    for (int j = 0; j < n; j++)
    {
        pid = fork();
        if (pid == 0)
        {
            int lecture = pos;
            lseek(fd, lecture, SEEK_SET);
            while (lecture < s.st_size)
            {
                read(fd, buf2, code_length + 8);

                for (int x = 0; x < s.st_size - (code_length + 4); x++)
                {
                    adr[poscode + 1] = '0';

                    printf("je suis %d et le code secret est : \n", getpid());
                    write(1, buf2, code_length + 6);
                    printf("\n\n");
                    exit(0);
                }
            }
        }
        else
        {
            wait(NULL);
        }
    }
}