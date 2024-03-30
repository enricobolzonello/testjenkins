{
    "targets": [
        {
            "target_name" : "travelingsalesmanoptimization",
            "cflags!" : [ "-std=gnu99 -fno-exceptions -O3 -fstack-protector-all -Wstack-protector" ],
            "cflags_cc!" : [ "-std=gnu99 -fno-exceptions -O3 -fstack-protector-all -Wstack-protector" ],
            "sources" : [
                "index.cpp",
                "../src/tsp.c",
                "../src/main.c",
                "../src/algorithms/heuristics.c",
                "../src/algorithms/metaheuristic.c",
                "../src/algorithms/refinment.c",
                "../src/utils/errors.c",
                "../src/utils/plot.c",
                "../src/utils/utils.c"
            ],
            "include_dirs" : [
                "node_modules/node-addon-api"
            ], # where sources should look for header files if the compiler could not locate them
            "defines": ['NAPI_DISABLE_CPP_EXCEPTIONS'],
        }
    ]
}