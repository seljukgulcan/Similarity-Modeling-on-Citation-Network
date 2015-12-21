RED='\033[0;31m'
GREEN='\33[0;32m'
NC='\033[0m' # No Color

./preprocess
printf "${GREEN}Preprocessing step is completed${NC}\n"
./minhash
printf "${GREEN}minhash is completed${NC}\n"
./lsh
printf "${GREEN}LSH is completed${NC}\n"
./compare
printf "${GREEN}Comparing step is completed${NC}\n"
./postprocess
printf "${GREEN}Postprocessing step is completed${NC}\n"

printf "\n${GREEN}Similarity computed${NC}\n"