{
    "targets": [
        {
            "target_name": "napi_ctp",
            "sources": [
                "./src/is_utf8.cpp",
                "./src/binding.cpp",
                "./src/spievent.cpp",
                "./src/ctpmsg.cpp",
                "./src/mdapi.cpp",
                "./src/mdspi.cpp",
                "./src/mdmsg.cpp",
                "./src/guard.cpp",
                "./src/message_buffer.cpp",
                "./src/napi_ctp.cpp",
                "./src/traderapi.cpp",
                "./src/traderspi.cpp",
                "./src/tradermsg.cpp"
            ],
            "conditions": [
                ['OS=="mac"', {
                    "include_dirs": [
                        "<(module_root_dir)/tradeapi/macos/thostmduserapi_se.framework/Versions/A/Headers",
                        "<(module_root_dir)/tradeapi/macos/thosttraderapi_se.framework/Versions/A/Headers"
                    ],
                    "libraries": [
                        "-Wl,-rpath,<(module_root_dir)/tradeapi/macos",
                        "-F<(module_root_dir)/tradeapi/macos",
                        "-framework thostmduserapi_se",
                        "-framework thosttraderapi_se"
                    ]
                }],
                ['OS=="win"', {
                    "include_dirs": [
                        "<(module_root_dir)/tradeapi"
                    ],
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
                    "include_dirs": [
                        "<(module_root_dir)/tradeapi"
                    ],
                    "libraries": [
                        "<(module_root_dir)/tradeapi/linux/thostmduserapi_se.so",
                        "<(module_root_dir)/tradeapi/linux/thosttraderapi_se.so"
                    ]
                }]
            ]
        }
    ]
}
