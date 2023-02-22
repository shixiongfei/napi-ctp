{
  "targets": [
    {
      "target_name": "napi_ctp",
      "sources": [
        "./src/napi_ctp.cpp",
        "./src/mdspi.cpp",
        "./src/mdapi.cpp",
        "./src/traderspi.cpp",
        "./src/traderapi.cpp"
      ],
      "include_dirs": [
        "./tradeapi"
      ],
      "conditions": [
        ['OS=="mac"', {
          "library_dirs": [
            "./tradeapi/macos",
            "./tradeapi/macos/libs"
          ],
          "libraries": [
            "libthostmduserapi_v6.6.7_MacOS_20220302.a",
            "libthosttraderapi-v6.6.7_MacOS_20220302.a"
          ]
        }],
        ['OS=="win"', {
          "library_dirs": [
            "./tradeapi/windows"
          ],
          "libraries": [
            "thostmduserapi_se.lib",
            "thosttraderapi_se.lib"
          ]
        }],
        ['OS=="linux"', {
          "library_dirs": [
            "./tradeapi/linux"
          ],
          "libraries": [
            "thostmduserapi_se.so",
            "thosttraderapi_se.so"
          ]
        }]
      ]
    }
  ]
}
