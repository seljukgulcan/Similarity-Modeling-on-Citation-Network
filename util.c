#include "util.h"
#include <stdlib.h>
#include <stdio.h>

int qsearch( int* arr, int value, int p, int r) {

	int size = r - p + 1;

	if( size <= 0)
		return -1;

	if( size == 1) {
		if( arr[p] == value)
			return p;

		return -1;
	}

	int pos = (p+r)/2;
	int pivot = arr[pos];

	if( pivot < value)
		return qsearch( arr, value, pos+1, r);

	return qsearch( arr, value, p,pos);
}

int cmpfunc (const void * a, const void * b) {

	return ( *(int*)a - *(int*)b );
}

void sort( int* arr, int size) {

	qsort(arr, size, sizeof(int), cmpfunc);
}

int search( int* arr, int size, int value) {

	return qsearch( arr, value, 0, size - 1);
}

void get_graph( int** table, int* size_arr) {

	FILE* fd = fopen( PREPROCESSPATH, "r");
	int i, j;
	int size;
	for( i = 0; i < VERTEXSIZE; i++) {

		fscanf (fd, "%d", &size);
		size_arr[i] = size;
		table[i] = malloc( size * sizeof(int));

		for( j = 0; j < size; j++) {

			fscanf (fd, "%d", &table[i][j]);
		}
	}

	fclose( fd);
}