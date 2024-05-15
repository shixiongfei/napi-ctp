{
  "targets": [
    {
      "target_name": "napi_ctp",
      "sources": [
        "./src/binding.cpp",
        "./src/ctpmsg.cpp",
        "./src/mdapi.cpp",
        "./src/mdspi.cpp",
        "./src/mdmsg.cpp",
        "./src/guard.cpp",
        "./src/message_queue.cpp",
        "./src/napi_ctp.cpp",
        "./src/traderapi.cpp",
        "./src/traderspi.cpp",
        "./src/tradermsg.cpp"
      ],
      "include_dirs": [
        "./tradeapi"
      ],
      "conditions": [
        ['OS=="mac"', {
          "libraries": [
            "-Wl,-rpath,<(module_root_dir)/tradeapi/macos",
            "-F<(module_root_dir)/tradeapi/macos",
            "-framework thostmduserapi_se",
            "-framework thosttraderapi_se"
          ]
        }],
        ['OS=="win"', {
          "library_dirs": [
            "<(module_root_dir)/tradeapi/windows"
          ],
          "libraries": [
            "thostmduserapi_se.lib",
            "thosttraderapi_se.lib"
          ],
          "copies": [
            {
              "destination": "<(PRODUCT_DIR)",
              "files": [
                "<(module_root_dir)/tradeapi/windows/thostmduserapi_se.dll",
                "<(module_root_dir)/tradeapi/windows/thosttraderapi_se.dll"
              ]
            }
          ]
        }],
        ['OS=="linux"', {
          "libraries": [
            "<(module_root_dir)/tradeapi/linux/thostmduserapi_se.so",
            "<(module_root_dir)/tradeapi/linux/thosttraderapi_se.so"
          ]
        }]
      ]
    }
  ]
}
