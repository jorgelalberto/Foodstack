{
  "targets": [
    {
      "target_name": "greet",
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "sources": [
        "./src/greeting.cpp",
        "./src/index.cpp"
      ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")" 
      ],
      'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
    },
    {
      "target_name": "SPLAYTREE",
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "sources": [
        "./src/newSplayTree.cpp",
        "./src/indexSplayTree.cpp"
      ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")" 
      ],
      'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
    },
    {
      "target_name": "HASHMAP",
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "sources": [
        "./src/HashMap.cpp",
        "./src/indexHashMap.cpp"
      ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")" 
      ],
      'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
    }
  ]
}