/*
 * prebuild.js
 *
 * Copyright (c) 2022-2025 Xiongfei Shi
 *
 * Author: Xiongfei Shi <xiongfei.shi(a)icloud.com>
 * License: Apache-2.0
 *
 * https://github.com/shixiongfei/napi-ctp
 */

if (process.platform === "darwin") {
  const fs = require("node:fs");

  const symlinks = [
    [
      "./tradeapi/macos/thostmduserapi_se.framework/thostmduserapi_se",
      "./Versions/Current",
    ],
    [
      "./tradeapi/macos/thostmduserapi_se.framework/Versions/Current",
      "./A/thostmduserapi_se",
    ],
    [
      "./tradeapi/macos/thosttraderapi_se.framework/thosttraderapi_se",
      "./Versions/Current",
    ],
    [
      "./tradeapi/macos/thosttraderapi_se.framework/Versions/Current",
      "./A/thosttraderapi_se",
    ],
  ];

  symlinks.forEach(([symlink, target]) => {
    if (!fs.existsSync(symlink)) {
      fs.symlinkSync(target, symlink);
    }
  });
}
