#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int patrol(char maze[150][150], int a, int b, int max);

int main(int argc, char *argv[]) {
  char *filename = "input.txt";
  long result = 0;
  int part = 2;
  char buf[145];
  char maze[150][150] = {0};
  char mazea[150][150] = {0};
  char mazeb[150][150] = {0};
  int size;
  int startx, starty, x, y, i = 1;
  FILE *fp;
  if (argc > 1)
    part = atoi(argv[1]);
  if (argc > 2)
    filename = argv[2];
  if ((fp = fopen(filename, "r")) == NULL) {
    printf("error opening file %s\n", filename);
    return 1;
  }
  while (fgets(buf, 145, fp) != NULL) {
    size = strlen(buf) - 1;
    memcpy(maze[size - (i++)], buf, size);
  }
  for (x = 0; x < size; x++)
    for (y = 0; y < size; y++)
      if (maze[x][y] == '^') {
        startx = x;
        starty = y;
      }
  memcpy(mazea, maze, sizeof(maze));
  patrol(mazea, startx, starty, size);
  if (part == 1) {
    for (x = (150 - 1); x >= 0; x--)
      for (y = 0; y < 150; y++)
        if (mazea[x][y] == 'X')
          result++;
  } else {
    for (x = 0; x < 150; x++)
      for (y = 0; y < 150; y++)
        if (mazea[x][y] == 'X' && !(x == startx && y == starty)) {
          memcpy(mazeb, maze, sizeof(maze));
          mazeb[x][y] = '#';
          if (!patrol(mazeb, startx, starty, size)) {
            printf("%i %i\n", startx, starty);
            result++;
          }
        }
  }
  printf("%ld\n", result);
  return 0;
}

int patrol(char maze[150][150], int a, int b, int max) {
  int x, y, startx, starty, steps = 0, dir = 0;
  x = startx = a;
  y = starty = b;
  maze[x][y] = 'X';
  while (x >= 0 && y >= 0 && x < max && y < max && steps < (max * max)) {
    if (maze[x][y] == '#') {
      dir++;
      dir %= 4;
      x = startx;
      y = starty;
    } else {
      startx = x;
      starty = y;
      maze[x][y] = 'X';
      steps++;
    }
    switch (dir) {
    case 0:
      x++;
      break;
    case 1:
      y++;
      break;
    case 2:
      x--;
      break;
    case 3:
      y--;
      break;
    }
  }
  if (steps == (max * max))
    return 0;
  return 1;
}
