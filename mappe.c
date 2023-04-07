#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <wait.h>
#include <math.h>

int main(int argc, char **argv)
{
  int fd;
  char *adr;
  int n = atoi(argv[2]);
  int pid;

  if ((fd = open(argv[1], O_RDWR | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO)) == -1)
  {
    perror(argv[1]);
    exit(2);
  }

  adr = (char *)mmap(NULL, 1024, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

  if (adr == MAP_FAILED)
  {
    perror("mmap1");
    exit(2);
  }

  int pid_parent = getppid();
  int taille = sizeof(int);
  /*redimensionner le fichier */
  ftruncate(fd, taille + 1);
  char buf[taille];
  sprintf(buf, "%d", pid_parent);
  for (int i = 0; i <= taille; i++)
  {
    adr[i] = buf[i];
  }

  for (int i = 0; i < n; i++)
  {
    pid = fork();

    if (pid == 0)
    {
      /*lire le pid ecrit dans le fichier*/
      sscanf(buf, "%d", &pid_parent);
      printf("je suis le fils %d et je lis mon pere : %d\n", getpid(), pid_parent);
      exit(0);
    }
    else
    {
      wait(NULL);
    }
  }
  return 0;
}