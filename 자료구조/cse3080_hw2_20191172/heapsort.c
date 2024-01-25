#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ELEMENTS 1000000
#define HEAP_FULL(n) (n == MAX_ELEMENTS-1)
#define HEAP_EMPTY(n) (!n)

typedef struct {
  int key;
} element;

typedef struct {
	element heap[MAX_ELEMENTS];
	int size;
}Heap;

Heap max_heap;
Heap backup_max_heap;
Heap min_heap;
Heap backup_min_heap;


void insert_max_heap(Heap* h ,element item);
void insert_min_heap(Heap* h ,element item);

element result_max_heap(Heap* h);
element result_min_heap(Heap* h);


int main(int argc, char *argv[]){

	double start, end;
	int data;
	int max_count, min_count;
	char flags[10];
	element item;

	start = (double)clock() / CLOCKS_PER_SEC;

	if (argc != 2){
		printf("Usage: ./hw2 input_filename\n");
		exit(1);
		}
	FILE *fp = fopen(argv[1], "r");
	FILE *fp_res = fopen("hw2_result.txt", "w");

	if (fp == NULL){
			printf("The input file does not exist.\n");
			exit(1);
		}
	
	while(fscanf(fp, "%s %d", flags, &data) > 0) 
	{

		if (strcmp(flags, "INSERT") == 0) 
		{
			
			item.key = data;
			insert_max_heap(&max_heap,item);
			insert_min_heap(&min_heap,item);
			max_count = max_heap.size;
			min_count = min_heap.size;
		}
		
		if (strcmp(flags, "DESCEND") == 0)
		{	
			backup_max_heap = max_heap;
			for(int i =0; i <max_count; i++)
			{
				item = result_max_heap(&max_heap);
				fprintf(fp_res,"%d ", item.key);
			}
			fprintf(fp_res,"\n");
		}
		
		if (strcmp(flags, "ASCEND") == 0)
		{
			backup_min_heap = min_heap;
			for(int i =0; i <min_count; i++)
			{
				item = result_min_heap(&min_heap);
				fprintf(fp_res, "%d ", item.key);
			}
			fprintf(fp_res, "\n");
		}

	}

	

	fclose(fp);
	fclose(fp_res);

	end = (((double)clock()) / CLOCKS_PER_SEC);
	
	
	printf("output written to hw2_result.txt.\n");
	printf("running time: %lf seconds\n", (end - start));
	return 0;
}



void insert_max_heap(Heap* h ,element item) {
  int i;
  
  if(HEAP_FULL(h->size)) {
  fprintf(stderr, "The heap is full.\n");
  exit(1);
  }

  i = ++(h->size);
  while((i != 1) && (item.key > h->heap[i/2].key)) {
    h->heap[i] = h->heap[i/2];
    i /= 2;
  }
  h->heap[i] = item;
}

void insert_min_heap(Heap* h ,element item) {
	if(HEAP_FULL(h->size)) 
	{
 		fprintf(stderr, "The heap is full.\n");
 		exit(1);
  	}
	int i;
 	i = ++(h->size);
  	
	while((i != 1) && (item.key < h->heap[i/2].key)) {
   		 h->heap[i] = h->heap[i/2];
    		 i /= 2;
  }
  h->heap[i] = item;
}

element result_max_heap(Heap* h) {
  int parent, child;
  element item, temp;
  
  if(HEAP_EMPTY(h->size)) {
  fprintf(stderr, "The heap is empty.\n");
  exit(1);
  }

  item = h->heap[1];
  temp = h->heap[(h->size)--];
  parent = 1;
  child = 2;

  while(child <= h->size) {
    if((child < h->size) && (h->heap[child].key < h->heap[child+1].key)) child++;
    if(temp.key >= h->heap[child].key) break;
    h->heap[parent] = h->heap[child];
    parent = child;
    child *= 2;
  }
  h->heap[parent] = temp;
  return item;
}


element result_min_heap(Heap* h) {
  int parent, child;
  element item, temp;
  
  if(HEAP_EMPTY(h->size)) {
  fprintf(stderr, "The heap is empty.\n");
  exit(1);
  }

  item = h->heap[1];
  temp = h->heap[(h->size)--];
  parent = 1;
  child = 2;

  while(child <= h->size) {
    if((child < h->size) && (h->heap[child].key > h->heap[child+1].key)) child++;
    if(temp.key <= h->heap[child].key) break;
    h->heap[parent] = h->heap[child];
    parent = child;
    child *= 2;
  }
  h->heap[parent] = temp;
  return item;
}

