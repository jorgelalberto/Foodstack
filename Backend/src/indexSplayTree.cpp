#include <napi.h>
#include "SplayTree.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
    return SplayTree::Init(env, exports);
}

NODE_API_MODULE(SPLAYTREE, InitAll)