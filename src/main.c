#include "tsp.h"
#include "algorithms/heuristics.h"
#include "algorithms/metaheuristic.h"
#include "algorithms/cplex_model.h"

// TODO: better handling of errors

int main(int argc, char* argv[]){
    log_info("program started!");
    instance inst;
    ERROR_CODE e = tsp_parse_commandline(argc, argv, &inst);
    if(!err_ok(e)){
        log_error("error in command line parsing, error code: %d", e);
        tsp_free_instance(&inst);
        exit(0);
    }

    if(inst.options_t.graph_input){
        tsp_read_input(&inst);
    }
    if(inst.options_t.graph_random){
        tsp_generate_randompoints(&inst);
    }

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
    case ALG_CPLEX:
        log_info("running CPLEX");
        e = cx_TSPopt(&inst);
        if(!err_ok(e)){
            log_fatal("VNS did not finish correctly");
            tsp_handlefatal(&inst);
        } 
        printf("Optimal: %f\n", inst.best_solution.cost);
        tsp_plot_solution(&inst);
        break;
    default:
        log_error("cannot run any algorithm");
        break;
    }

    exit(0);
}
