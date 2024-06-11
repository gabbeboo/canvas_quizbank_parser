// Komp: gcc -std=c99 -Wall -o assignments assignments.c -I ../datastructures-v1.0.8.2/include
// queue komp: gcc -std=c99 -Wall -o assignments assignments.c ../datastructures-v1.0.8.2/src/queue/queue.c ../datastructures-v1.0.8.2/src/list/list.c -I ../datastructures-v1.0.8.2/include
// dlist komp: gcc -std=c99 -Wall -o assignments assignments.c ../datastructures-v1.0.8.2/src/dlist/dlist.c -I ../datastructures-v1.0.8.2/include

// Valgrind: valgrind --leak-check=full --show-reachable=yes ./assignments

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "queue.h"
#include "dlist.h"

#define MAX_LINE 1024

typedef struct {
  int x;
  int y;
  int z;
} coord;

// Varning: Denna lösning ingen felhantering
int main(void) {
/*
  // Övning 1
  FILE *file = fopen("readme.txt", "w");
  fprintf(file, "Hello World!\n");
  fclose(file);
*/
/*
  // Övning 2
  FILE *file = fopen("readme.txt", "r");
  char string[MAX_LINE];
  fgets(string, MAX_LINE, file);
  fprintf(stdout, "%s", string);
  fclose(file);
*/
/*
  // Övning 3
  FILE *file = fopen("data.txt", "w");
  int tal;
  while(true) {
    scanf("%d", &tal);
    if (tal < 0) {
      break;
    }
    fprintf(file, "%d\n", tal);
  }
  fclose(file);
*/
/*
  // Övning 4
  FILE *file = fopen("data.txt", "r");
  queue *queue = queue_empty(free);
  int *val = malloc(sizeof(int));
  while (fscanf(file, "%d", val) != EOF) {
    queue = queue_enqueue(queue, val);
    val = malloc(sizeof(int));
  }
  free(val);
  fclose(file);
  while (!queue_is_empty(queue)) {
    val = queue_front(queue);
    printf("%d\n", *val);
    queue = queue_dequeue(queue);
  }
  queue_kill(queue);
*/
/*
  // Övning 5
  coord coords[3];
  srand(time(NULL));
  for (int i = 0; i < 3; i++) {
    coord tmp = {(int) rand(), (int) rand(), (int) rand()};
    coords[i] = tmp;
  }
  FILE *bin = fopen("binary.bin", "wb");
  for (int i = 0; i < 3; i++) {
    coord tmp = coords[i];
    fprintf(bin, "%d %d %d\n", tmp.x, tmp.y, tmp.z);
  }
  fclose(bin);
*/
/*
  // Övning 6
  FILE *bin = fopen("binary.bin", "rb");
  dlist *dlist = dlist_empty(free);
  dlist_pos pos = dlist_first(dlist);
  char buf[MAX_LINE];
  while (fgets(buf, MAX_LINE, bin)) {
    coord *tmp = malloc(sizeof(coord));
    sscanf(buf, "%d %d %d", &(tmp->x), &(tmp->y), &(tmp->z));
    pos = dlist_insert(dlist, tmp, pos);
    pos = dlist_next(dlist, pos);
  }
  fclose(bin);
  pos = dlist_first(dlist);
  while (!dlist_is_end(dlist, pos)) {
    coord *tmp = dlist_inspect(dlist, pos);
    printf("%d %d %d\n", tmp->x, tmp->y, tmp->z);
    pos = dlist_next(dlist, pos);
  }
  dlist_kill(dlist);
*/

  return 0;
}
