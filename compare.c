#include <stdlib.h>
#include <stdio.h>
#include "util.h"
#include <math.h>
#include <limits.h>
#include <time.h>

bool seq_search( int* arr, int value, int size) {

	int i;
	for(i = 0; i < size; i++)
		if( arr[i] == value)
			return true;

	return false;
}

bool check_arr( int* arr, int value) {

	int i;
	for( i = 0; arr[i] != -1; i++) {

		if( arr[i] == value)
			return true;
	}

	arr[i] = value;
	return false;
}

double find_similarity( int id1, int id2, int** table, int* table_size_arr) {

	int size1 = table_size_arr[id1];
	int size2 = table_size_arr[id2];

	if( size1 == 0 || size2 == 0)
		return 0;

	int common = 0;
	int i;
	for( i = 0; i < size1; i++) {

		if( seq_search( table[id2], table[id1][i], size2))
			common++;
	}

	int total = size1 + size2 - common;

	return ((double)common) / total;
}

bool checked_before( int id1, int id2, int** hist) {

	int small = id1 < id2 ? id1 : id2;
	int big = id1 > id2 ? id1 : id2;

	return check_arr( hist[small], big);
}

int main( int argc, char* argv[]) {

	int i, j;
	FILE* candidate_file;
	FILE* final_file;
	int** table;
	int* table_size_arr;
	int size;
	double threshold = 0.8;
	int candidate_buffer[20];
	double similarity;
	int false_positive, true_positive;

	int** hist = malloc( VERTEXSIZE * sizeof( int*));
	for( i = 0; i < VERTEXSIZE; i++) {

		hist[i] = malloc( 30 * sizeof( int));
		for( j = 0; j < 30; j++)
			hist[i][j] = -1;
	}

	//GET GRAPH
	table = malloc( VERTEXSIZE * sizeof( int*));
	table_size_arr = malloc( VERTEXSIZE * sizeof( int));
	get_graph( table, table_size_arr);

	final_file = fopen( SIMILARPATH, "w");
	candidate_file = fopen( CANDIDATEPATH, "r");
	false_positive = 0;
	true_positive = 0;
	while (!feof (candidate_file)) {

		fscanf (candidate_file, "%d", &size);

		for( i = 0; i < size; i++) {

			fscanf (candidate_file, "%d", &candidate_buffer[i]);
		}

		for( i = 0; i < size; i++) {

			for( j = i + 1; j < size; j++) {

				if( checked_before( candidate_buffer[i], candidate_buffer[j], hist))
					continue;

				similarity = find_similarity( candidate_buffer[i], candidate_buffer[j], table, table_size_arr);
				if( similarity >= threshold) {

					fprintf( final_file, "%d %d %f\n", candidate_buffer[i], candidate_buffer[j], similarity);
					true_positive++;
				}

				else {

					false_positive++;
				}
			}
		}
	}

	fclose( candidate_file);
	fclose( final_file);

	/*printf( "--RESULT--\n");
	printf( "%d candidate pairs are examined\n", true_positive + false_positive);
	printf( "FALSE POSITIVES : %d\n", false_positive);*/


	//DEALLOCATE RESOURCES
	for( i = 0; i < VERTEXSIZE; i++) {

		if( table_size_arr[i] > 0)
			free( table[i]);
		free( hist[i]);
	}
	free( hist);
	free( table);
	free( table_size_arr);

	return 0;
}
