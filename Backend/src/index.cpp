#include <napi.h>
#include <string>
#include "greeting.h"

// native C++ func assigned to 'greetHello' property on 'exports' object
Napi::String greetHello(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    // call 'helloUser' func from 'greeting.cpp' file
    // WARNING: We are passing hardcoded 'JORGE' value for now
    std::string result = helloUser("JORGE");
    
    // return new 'Napi::String' value
    return Napi::String::New(env, result);
}

// callback method when module is registered w/Node.js
// invoked when Node.js starts registration process of greet module
Napi::Object Init(Napi::Env env, Napi::Object exports) {

    // set a key on 'exports' object
    exports.Set(
        Napi::String::New(env, "greetHello"), // property name => "greetHello"
        Napi::Function::New(env, greetHello) // property value => 'greetHello' function
    );

    // return 'exports' object (always)
    return exports;
}

// register 'greet' module which calls 'Init' method
// wraps NAPI_MODULE provided by node_api.h (N-API)
// invoked when imprting Native Addon in JS program using require func
// greet - unique name specified as target_name in binding.gyp (should be label not string)
// Init - above function
NODE_API_MODULE(greet, Init)