#include "tsp.h"
#include "algorithms/heuristics.h"
#include "algorithms/metaheuristic.h"

typedef struct {
    char* filename;
    double cost;
} return_struct;

return_struct rs;

void runTSP(char* path, int seed, int time_limit, algorithms alg);
