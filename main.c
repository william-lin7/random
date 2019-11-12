#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int randomNum(){
  int file = open("/dev/random", O_RDONLY);
  if (errno){
    printf("Error %d: %s\n", errno, strerror(errno));
  }
  int num;
  int rd = read(file, &num, sizeof(int));
  if (errno){
    printf("Error %d: %s\n", errno, strerror(errno));
  }
  close(file);
  return num;
}

int main(){
  printf("Generating random numbers:\n");
  int randNums[10];
  for (int i = 0; i < 10; i++){
    randNums[i] = randomNum();
    printf("\trandom %d: %d\n", i, randNums[i]);
  }

  printf("\nWriting numbers to file...\n");
  int fileout = open("nums.txt", O_RDWR|O_CREAT, 0644);
  write(fileout, randNums, sizeof(randNums));
  if (errno){
    printf("Error %d: %s\n", errno, strerror(errno));
  }
  close(fileout);

  printf("\nReading numbers from file...\n");
  int filein = open("nums.txt", O_RDONLY);
  int randCopy[10];
  read(filein, &randCopy, sizeof(randCopy));
  if (errno){
    printf("Error %d: %s\n", errno, strerror(errno));
  }
  close(filein);

  printf("\nVerification that written values were the same:\n");
  for (int i = 0; i < 10; i++){
    printf("\trandom %d: %d\n", i, randCopy[i]);
  }
  return 0;
}
