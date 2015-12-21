//MAIN FILES
#define DATAPATH "data/Cit-HepTh.txt"
#define PREPROCESSPATH "data/preprocess.txt"
#define SIGNATUREPATH "data/signatures.txt"
#define CANDIDATEPATH "data/candidates.txt"
#define SIMILARPATH "data/similar.txt"
#define FINALPATH "data/final.txt"
#define MAPPATH "data/map.txt"

//SIDE FILES
#define HASHPATH "data/hash_functions.txt"

//MINHASHING PARAMETERS
#define SIGNSIZE 100
#define P 27773

//LSH PARAMETERS

#define VERTEXSIZE 27770

typedef enum { false, true } bool;

int qsearch( int* arr, int value, int p, int r);

int cmpfunc (const void * a, const void * b);

void sort( int* arr, int size);

int search( int* arr, int size, int value);

void get_graph( int** table, int* size_arr);