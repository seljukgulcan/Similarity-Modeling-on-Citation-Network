RED='\033[0;31m'
GREEN='\33[0;32m'
NC='\033[0m' # No Color

gcc -g -Wall -o preprocess preprocess.c util.h util.c
gcc -g -Wall -o minhash minhash.c util.h util.c
gcc -g -Wall -o lsh lsh.c util.h util.c
gcc -g -Wall -o compare compare.c util.h util.c
gcc -g -Wall -o postprocess postprocess.c util.h util.c

printf "${GREEN}Compile completed${NC}\n"