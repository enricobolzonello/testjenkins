#include <napi.h>
#include <string>
#include <unordered_map>

extern "C" {
    #include "../src/main.h"
}

 std::unordered_map<int, algorithms> index_algs =
    {
        {0, ALG_GREEDY},
        {1, ALG_GREEDY_ITER},
        {2, ALG_2OPT_GREEDY}
    };

Napi::Object TSP_runner(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();

    std::string temp = (std::string) info[0].ToString();
    char* filename = temp.data();
    int seed = (int) info[1].As<Napi::Number>();
    int time_limit = (int) info[2].As<Napi::Number>();
    int alg = (int) info[3].As<Napi::Number>();
    runTSP(filename, seed, time_limit, index_algs[alg]);

    // javascript object
    Napi::Object ret = Napi::Object::New(env);
    ret.Set("cost", Napi::Number::New(env, (double)rs.cost));
    ret.Set("filename", Napi::String::New(env, (std::string)rs.filename));

    return ret;
}

Napi::Object Init(Napi::Env env, Napi::Object exports){
    exports.Set(
        Napi::String::New(env, "TSP_runner"),
        Napi::Function::New(env, TSP_runner)
    );

    return exports;
}

NODE_API_MODULE(TSP, Init);
