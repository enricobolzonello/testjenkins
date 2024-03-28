#include "main.h"

// TODO: better handling of errors

void runTSP(const char* path, int seed, int time_limit, algorithms alg){
    log_info("program started!");
    instance inst;

    ERROR_CODE e;

    inst.options_t.tofile = true;
    inst.options_t.graph_input = true;

    if(!utils_file_exists(path)){
                log_fatal("file does not exist");
                tsp_handlefatal(&inst);
            }

    inst.options_t.inputfile = (char*) calloc(strlen(path), sizeof(char));
    strcpy(inst.options_t.inputfile, path);

    if(inst.options_t.graph_input){
        tsp_read_input(&inst);
    }

    if(seed != -1){
        inst.options_t.seed = seed;
    }

    if(time_limit > 0){
        inst.options_t.timelimit = time_limit;
    }

    inst.alg = alg;


    inst.best_solution.path = (int*) calloc(inst.nnodes, sizeof(int));

    switch (inst.alg)
    {
    case ALG_GREEDY:
        e = h_Greedy(&inst);
        if(!err_ok(e)){
            log_fatal("greedy did not finish correctly");
            tsp_handlefatal(&inst);
        }        
        printf("Greedy from 0: %f\n", inst.best_solution.cost);
        tsp_plot_solution(&inst);
        break;
    case ALG_GREEDY_ITER:
        log_info("running GREEDY-ITER");
        e = h_Greedy_iterative(&inst);
        if(!err_ok(e)){
            log_fatal("greedy iterative did not finish correctly");
            tsp_handlefatal(&inst);
        }  
        printf("Greedy from all nodes: %f\n", inst.best_solution.cost);
        log_info("Best starting node: %d", inst.starting_node);
        tsp_plot_solution(&inst);
        break;
    case ALG_2OPT_GREEDY:
        log_info("running 2OPT-GREEDY");
        e = h_greedy_2opt(&inst);
        if(!err_ok(e)){
            log_fatal("greedy did not finish correctly");
            tsp_handlefatal(&inst);
        } 
        printf("Greedy from %d + 2-opt: %f\n", inst.starting_node, inst.best_solution.cost);
        tsp_plot_solution(&inst);
        break;
    case ALG_TABU_SEARCH:
        log_info("running Tabu Search");
        e = mh_TabuSearch(&inst, POL_LINEAR);
        if(!err_ok(e)){
            log_fatal("tabu search did not finish correctly");
            tsp_handlefatal(&inst);
        } 
        printf("Tabu search: %f\n", inst.best_solution.cost);
        tsp_plot_solution(&inst);
        break;
    case ALG_VNS:
        log_info("running VNS");
        e = mh_VNS(&inst);
        if(!err_ok(e)){
            log_fatal("VNS did not finish correctly");
            tsp_handlefatal(&inst);
        } 
        printf("VNS: %f\n", inst.best_solution.cost);
        tsp_plot_solution(&inst);
        break;
    default:
        log_error("cannot run any algorithm");
        break;
    }

    rs.filename = (char*) malloc(strlen(inst.options_t.inputfile)+1);
    strcpy(rs.filename, inst.options_t.inputfile);
    rs.cost = inst.best_solution.cost;
}
