#include <stdlib.h>
#include <stdio.h>
#include "util.h"

int main( int argc, char* argv[]) {

	int* arr = malloc( VERTEXSIZE * sizeof( int));
	FILE* id_file = fopen (MAPPATH, "r");
	int i;
	int number;
	float similarity;

	for( i = 0; i < VERTEXSIZE; i++)
		fscanf (id_file, "%d", &arr[i]);

	fclose( id_file);

	FILE* new_data_file = fopen( FINALPATH, "w");
	FILE* old_data_file = fopen( SIMILARPATH, "r");

	while (!feof (old_data_file)) {

		fscanf (old_data_file, "%d", &number);
		fprintf(new_data_file, "%d ", arr[number]);
		fscanf (old_data_file, "%d", &number);
		fprintf(new_data_file, "%d ", arr[number]);
		fscanf (old_data_file, "%f", &similarity);
		fprintf(new_data_file, "%f\n", similarity);
	}

	fclose( new_data_file);
	fclose( old_data_file);
	free( arr);

	return 0;
}