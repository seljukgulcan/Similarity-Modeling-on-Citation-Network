#include <stdlib.h>
#include <stdio.h>
#include "util.h"
#include <math.h>
#include <limits.h>
#include <time.h>

int main( int argc, char* argv[]) {

	int i,j;
	FILE* hash_func_file;
	FILE* sign_file;
	int* hash_funcs;
	time_t t;
	int** sign_matrix;
	int hash, hash_value;

	int** table;
	int* table_size_arr;

	//GET GRAPH
	table = malloc( VERTEXSIZE * sizeof( int*));
	table_size_arr = malloc( VERTEXSIZE * sizeof( int));
	get_graph( table, table_size_arr);

	//GENERATE HASH FUNCTIONS
	hash_func_file = fopen( HASHPATH, "w");
	srand((unsigned) time(&t));
	hash_funcs = malloc( SIGNSIZE * 2 * sizeof( int));
	for( i = 0; i < SIGNSIZE; i++) {

		hash_funcs[2*i] = rand() % 75000;
		hash_funcs[2*i+1] = rand() % 75000;
		fprintf( hash_func_file, "%d %d\n", hash_funcs[2*i], hash_funcs[2*i+1]);
	}
	fclose( hash_func_file);

	//CREATE SIGNATURE MATRIX
	sign_matrix = malloc( VERTEXSIZE * sizeof( int*));
	for( i = 0; i < VERTEXSIZE; i++) {

		sign_matrix[i] = malloc( SIGNSIZE * sizeof(int));
		for( j = 0; j < SIGNSIZE; j++) {

			sign_matrix[i][j] = INT_MAX;
		}
	}

	//MIN HASH
	for( i = 0; i < VERTEXSIZE; i++) {

		for( j = 0; j < table_size_arr[i]; j++) {

			for( hash = 0; hash < SIGNSIZE; hash++) {

				hash_value = ((hash_funcs[ hash * 2] * table[i][j] + hash_funcs[ hash * 2 + 1])%P)%VERTEXSIZE;

				if( sign_matrix[i][hash] > hash_value)
					sign_matrix[i][hash]=hash_value;
			}
		}
	}

	//WRITE TO FILE
	sign_file = fopen( SIGNATUREPATH, "w");

	for( i = 0; i < VERTEXSIZE; i++) {

		for( j = 0; j < SIGNSIZE; j++) {

			fprintf( sign_file, " %d", sign_matrix[i][j]);
		}
		fprintf( sign_file, "\n");
	}

	fclose( sign_file);

	//DEALLOCATE RESOURCES
	free( hash_funcs);
	for( i = 0; i < VERTEXSIZE; i++) {

		free( sign_matrix[i]);
	}
	free( sign_matrix);

	for( i = 0; i < VERTEXSIZE; i++) {

		if( table_size_arr[i] > 0)
			free( table[i]);
	}
	free( table);
	free( table_size_arr);

	return 0;
}
