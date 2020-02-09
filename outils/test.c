#include <stdio.h>

int main()
{
  FILE *fp;
  int write[5] = {0,1,2,3,4};
  int read[5];
  fp=fopen("file","w+");
  fwrite(write, sizeof(int), 5, fp);
  fseek(fp, 0, SEEK_SET);
  fread(read, sizeof(int), 5, fp);
  printf("%d %d %d %d %d\n", read[0], read[1], read[2], read[3], read[4]);
  fclose(fp);
}
