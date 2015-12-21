#include <stdlib.h>
#include <stdio.h>
#include "util.h"

bool seq_search( int* arr, int value, int size) {

	int i = 0;
	for(i = 0; i < size; i++)
		if( arr[i] == value)
			return true;

	return false;
}

int main( int argc, char* argv[]) {

	//PART - 1 - FETCH UNIQUE IDS FROM DATAPATH

	FILE* data_file = fopen (DATAPATH, "r");
	int temp;
	int number;
	int old_number;
	int counter = 0;
	int* arr;
	int i, j;

	arr = malloc( 28000 * sizeof( int));

	//Skip first 4 lines since they are just explanation about dataset
	char buffer[100];
	fgets(buffer, 100, data_file);
	fgets(buffer, 100, data_file);
	fgets(buffer, 100, data_file);
	fgets(buffer, 100, data_file);

	fscanf (data_file, "%d", &number);
	arr[0] = number;
	old_number = number;
	counter++;
	fscanf (data_file, "%d", &temp);

	while (!feof (data_file)) {

		fscanf (data_file, "%d", &number);
		if( old_number != number) {

			arr[counter] = number;
			old_number = number;
			counter++;
		}

		fscanf (data_file, "%d", &temp);
	}
	fclose (data_file);

	sort( arr, counter);
	
	int counter2 = 0;
	int* arr2 = malloc( 30000 * sizeof( int));

	//Skip first 4 lines since they are just explanation about dataset
	data_file = fopen (DATAPATH, "r");
	fgets(buffer, 100, data_file);
	fgets(buffer, 100, data_file);
	fgets(buffer, 100, data_file);
	fgets(buffer, 100, data_file);

	while (!feof (data_file)) {

		fscanf (data_file, "%d", &temp);
		fscanf (data_file, "%d", &number);

		if( qsearch( arr, number, 0, counter - 1) == -1) {

			if( !seq_search( arr2, number, counter2)) {

				arr2[counter2] = number;
				counter2++;
			}
		}
	}
	
	fclose (data_file);

	for( i = counter; i < counter2 + counter; i++) {
		arr[i] = arr2[i-counter];
	}

	sort(arr, counter + counter2);

	//All ids are fetched
	FILE* fp = fopen( MAPPATH, "w");

	for( i = 0; i < counter + counter2; i++)
		fprintf (fp, "%d\n", arr[i]);

	fclose( fp);
	
	free( arr2);

	//PART - 2 - MAP IDS

	int id;
	int** table = malloc( VERTEXSIZE * sizeof(int*));
	int* size = malloc( VERTEXSIZE * sizeof( int));
	int edge_buffer[1000];
	int edge_counter = 0;
	int current_vertex;

	for( i = 0; i < VERTEXSIZE; i++) {

		size[i] = 0;
	}

	FILE* old_data_file = fopen( DATAPATH, "r");

	//Skip comment lines in the raw data file
	fgets(buffer, 100, old_data_file);
	fgets(buffer, 100, old_data_file);
	fgets(buffer, 100, old_data_file);
	fgets(buffer, 100, old_data_file);

	fscanf (old_data_file, "%d", &current_vertex);
	fscanf (old_data_file, "%d", &number);
	edge_buffer[0] = search( arr, VERTEXSIZE, number);
	edge_counter++;

	while (!feof (old_data_file)) {

		fscanf (old_data_file, "%d", &number);

		if( current_vertex != number) {

			id = search( arr, VERTEXSIZE, current_vertex);

			table[id] = malloc( edge_counter * sizeof(int));
			for(i = 0; i < edge_counter; i++) {

				table[id][i] = edge_buffer[i];
			}
			if( id < 0 || id >= VERTEXSIZE) {
				printf( "%d - %d\n", id, current_vertex);
			}

			size[id] = edge_counter;

			edge_counter = 0;
			current_vertex = number;
		}

		fscanf (old_data_file, "%d", &number);
		edge_buffer[edge_counter] = search( arr, VERTEXSIZE, number);
		edge_counter++;
	}

	FILE* new_data_file = fopen( PREPROCESSPATH, "w");
	for( i = 0; i < VERTEXSIZE; i++) {
		fprintf( new_data_file, "%d", size[i]);
		for( j = 0; j < size[i]; j++) {
			fprintf(new_data_file, " %d", table[i][j]);
		}
		fprintf(new_data_file, "\n");

		if( size[i] > 0)
			free( table[i]);
	}

	free( size);
	free( table);

	fclose( new_data_file);
	fclose( old_data_file);
	free( arr);

	return 0;
}