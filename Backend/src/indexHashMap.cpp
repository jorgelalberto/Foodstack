#include <napi.h>
#include "HashMap.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
    return HashMap::Init(env, exports);
}

NODE_API_MODULE(HASHMAP, InitAll)