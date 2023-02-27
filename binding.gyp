{
  "targets": [
    {
      "target_name": "napi_ctp",
      "sources": [
        "<(module_root_dir)/src/napi_ctp.cpp",
        "<(module_root_dir)/src/mdspi.cpp",
        "<(module_root_dir)/src/mdapi.cpp",
        "<(module_root_dir)/src/traderspi.cpp",
        "<(module_root_dir)/src/traderapi.cpp"
      ],
      "include_dirs": [
        "<(module_root_dir)/tradeapi"
      ],
      "conditions": [
        ['OS=="mac"', {
          "library_dirs": [
            "<(module_root_dir)/tradeapi/macos",
            "<(module_root_dir)/tradeapi/macos/libs"
          ],
          "libraries": [
            "libthostmduserapi_v6.6.7_MacOS_20220302.a",
            "libthosttraderapi-v6.6.7_MacOS_20220302.a"
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
              "destination": "<(module_root_dir)/build/Release/",
              "files": [
                "<(module_root_dir)/tradeapi/windows/thostmduserapi_se.dll",
                "<(module_root_dir)/tradeapi/windows/thosttraderapi_se.dll"
              ]
            }
          ]
        }],
        ['OS=="linux"', {
          "library_dirs": [
            "<(module_root_dir)/tradeapi/linux"
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
