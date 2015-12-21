#include <stdlib.h>
#include <stdio.h>
#include "util.h"
#include <math.h>
#include <limits.h>

#define K 100
#define BAND_SIZE 25
#define HASH_SIZE 1040657

unsigned int hash_multipliers[BAND_SIZE];

struct bucket {	//Linked List Node Defining as bucket

	int key;
	struct bucket* next;
};

int lsh( int* arr, int start, int size) {

	int i;
	int sum = 0;
	for( i = 0; i < size; i++) {

		sum += arr[start + i] * hash_multipliers[i];
	}

	sum = sum % HASH_SIZE;
	if( sum < 0)
		sum += HASH_SIZE;
	return sum;
}

void insert( struct bucket** table, int position, int value) {


	struct bucket* bucket_added = malloc( sizeof(struct bucket));
	bucket_added->key = value;
	bucket_added->next = NULL;

	struct bucket* current = table[position];

	//If head is empty, make new node head.
	if( current == NULL) {
		table[position] = bucket_added;
		return;
	}
	while( current -> next != NULL) {

		current = current -> next;
	}

	current -> next = bucket_added;
}

int count( struct bucket* bucket) {

	if( bucket == NULL)
		return 0;

	int size = 0;
	while( bucket != NULL) {

		bucket = bucket -> next;
		size++;
	}

	return size;
}

int main( int argc, char* argv[]) {

	int** sign_matrix;
	FILE* sign_matrix_file;
	FILE* sim_file;
	int i, j, pos;
	int sign;
	struct bucket** hash_table;
	int counter = 0;

	hash_multipliers[0] = 1;
	for( i = 1; i < BAND_SIZE; i++) {

		hash_multipliers[i] = hash_multipliers[i - 1] * 103867;
	}

	//GET SIGNATURES
	sign_matrix = malloc( VERTEXSIZE * sizeof( int*));
	for( i = 0; i < VERTEXSIZE; i++) {

		sign_matrix[i] = malloc( K * sizeof( int));
	}

	sign_matrix_file = fopen (SIGNATUREPATH, "r");

	for( i = 0; i < VERTEXSIZE; i++) {

		for( j = 0; j < K; j++) {

			fscanf (sign_matrix_file, "%d", &sign);
			sign_matrix[i][j] = sign;
		}
	}

	fclose( sign_matrix_file);

	//LOCALITY SENSITIVE HASHING TO PUT NODES IN BUCKETS
	hash_table = malloc( HASH_SIZE * sizeof( struct bucket*));
	for( i = 0; i < HASH_SIZE; i++) {

		hash_table[i] = NULL;
	}
	
	for( i = 0; i < VERTEXSIZE; i++) {

		if( sign_matrix[i][0] == INT_MAX) {
			counter++;
			continue;
		}

		for( j = 0; j < 100; j += BAND_SIZE) {

			pos = lsh( sign_matrix[i], j, BAND_SIZE);
			if( pos < 0)
				continue;
			insert( hash_table, pos, i);
		}
	}

	//WRITE BUCKETS TO FILE
	sim_file = fopen( CANDIDATEPATH, "w");
	for( i = 0; i < HASH_SIZE; i++) {

		struct bucket* current = hash_table[i];

		int size = count( current);

		if( size == 0 || size == 1)
			continue;

		fprintf( sim_file, "%d ", size);
		while( current != NULL) {

			fprintf( sim_file, "%d ", current -> key);
			current = current -> next;
		}
		fprintf( sim_file, "\n");
	}

	fclose( sim_file);

	//DEALLOCATE RESOURCES
	for( i = 0; i < VERTEXSIZE; i++) {

		free( sign_matrix[i]);
	}
	free( sign_matrix);

	return 0;
}
