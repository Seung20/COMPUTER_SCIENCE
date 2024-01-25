#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SWAP(a, b) { EDGES tmp; tmp = a; a = b; b = tmp; }
#define MAX_VERTEX 10000
#define MAX_EDGE 50000000

typedef struct {
    int start;
    int end;
    int cost;
} EDGES;

typedef struct {
    int parent;
    int level;
} set;

set SET[MAX_VERTEX];
EDGES E[MAX_EDGE];

int find_parent(int point);
void connect_nodes(int src, int dest);
void MST_kruskal(FILE* fp_res, int vertex_num, int edge_num);

int main(int argc, char* argv[])
{
    double start, end;
    int edge_num, vertex_num;
    int i;

    start = (double)clock() / CLOCKS_PER_SEC;

    if (argc != 2) {
        printf("Usage: ./hw3 input_filename\n");
        exit(1);
    }

    FILE* fp = fopen(argv[1], "r");
    FILE* fp_res = fopen("aaa.txt", "w");

    if (fp == NULL) {
        printf("The input file does not exist.\n");
        exit(1);
    }

    fscanf(fp, "%d\n%d", &vertex_num, &edge_num);

    for (i = 0; i < edge_num; i++) {
        fscanf(fp, "%d %d", &E[i].start, &E[i].end);
        fscanf(fp, "%d", &E[i].cost);
    }

    for (i = 1; i < edge_num; i++) {
        int j = i;
        while (j > 0 && E[j - 1].cost > E[j].cost) {
            SWAP(E[j - 1], E[j]);
            j--;
        }
    }

    for (i = 0; i < vertex_num; i++) {
        SET[i].parent = i;
        SET[i].level = -1;
    }

    MST_kruskal(fp_res, vertex_num, edge_num);

    fclose(fp);
    fclose(fp_res);

    end = ((double)clock()) / CLOCKS_PER_SEC;
    printf("output written to hw3_result.txt\n");
    printf("running time: %lf seconds\n", (end - start));
    return 0;
}

int find_parent(int point) {
    int current = point;
    while (SET[current].parent != current) {
        current = SET[current].parent;
    }
    return current;
}

void connect_nodes(int src, int dest)
{
    int src_p = find_parent(src);
    int dest_p = find_parent(dest);

    if (SET[src_p].level > SET[dest_p].level) {
        SET[dest_p].parent = src_p;
    }
    else if (SET[src_p].level < SET[dest_p].level) {
        SET[src_p].parent = dest_p;
    }
    else {
        SET[src_p].parent = dest_p;
        SET[dest_p].level++;
    }
}

void MST_kruskal(FILE* fp_res, int vertex_num, int edge_num)
{
    int i;
    int total = 0;
    int count = 0;

    for (i = 0; i < edge_num; i++) {
        if (find_parent(E[i].start) != find_parent(E[i].end)) {
            connect_nodes(E[i].start, E[i].end);

            total += E[i].cost;
            count++;
            fprintf(fp_res, "%d %d %d\n", E[i].start, E[i].end, E[i].cost);
        }
    }

    fprintf(fp_res, "%d\n", total);
    if (count == vertex_num - 1)
        fprintf(fp_res, "CONNECTED\n");
    else
        fprintf(fp_res, "DISCONNECTED\n");
}

