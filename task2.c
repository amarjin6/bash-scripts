#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>

int seek(char *dir)
{
  DIR *dp;
  dp = opendir(dir);
  if (dp == NULL)
  {
    printf("Error to open directory!\n");
    return 2;
  }

  struct dirent *dirp;
  while ((dirp = readdir(dp)) != NULL)
  {
    if (dirp->d_type == DT_DIR)
    {
      if ((strcmp(".", dirp->d_name) != 0) ||(strcmp("..", dirp->d_name) != 0))
      {
        char *newDir;
        newDir = (char*)malloc(strlen(dir) + strlen(dirp->d_name) + 2);
	strcpy(newDir, dir);
	strcat(newDir, "\0");
	strcat(newDir, dirp->d_name);
	strcat(newDir, "/");
	strcat(newDir, "\0");
	seek(newDir);
	free(newDir);
      }
    }
    else if (dirp->d_type == DT_REG)
    {
      struct stat buf;
      char *name = (char*)malloc(strlen(dir) + strlen(dirp->d_name) + 1);
      strcpy(name, dir);
      strcat(name, dirp->d_name);
      strcat(name, "\0");
      stat(name, &buf);
      if (buf.st_mode & S_IRUSR)
      {
	printf("%s\n", dirp->d_name);
      }
    }
  }
  return 0;
}

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
   printf("Not enough arguments!");
   return 2; 
  }
  char *dir = argv[1];
  seek(dir);
  return 0;
}
