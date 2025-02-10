/*
 * test.js
 *
 * Copyright (c) 2022-2025 Xiongfei Shi
 *
 * Author: Xiongfei Shi <xiongfei.shi(a)icloud.com>
 * License: Apache-2.0
 *
 * https://github.com/shixiongfei/napi-ctp
 */

const ctp = require(".");
const fs = require("node:fs");

if (!fs.existsSync("./flow/")) {
  fs.mkdirSync("./flow/", { recursive: true });
}
const trader = ctp.createTrader("./flow/", "tcp://180.168.146.187:10202");

trader.on(ctp.TraderEvent.FrontConnected, (...args) => {
  console.log("Trader Connected:", ...args);
});

if (!fs.existsSync("./flowMd/")) {
  fs.mkdirSync("./flowMd/", { recursive: true });
}
const md = ctp.createMarketData("./flowMd/", "tcp://180.168.146.187:10212");

md.on(ctp.MarketDataEvent.FrontConnected, (...args) => {
  console.log("Market Data Connected:", ...args);
  md.reqUserLogin();
})
  .on(ctp.MarketDataEvent.RspUserLogin, (...args) => {
    console.log("Market Data Login:", ...args);
    md.subscribeMarketData(["rb2505"]);
  })
  .on(ctp.MarketDataEvent.RtnDepthMarketData, (...args) => {
    console.log("Market Data:", ...args);
  });

console.log(trader.getApiVersion());
console.log(md.getApiVersion());

console.log(trader.getTradingDay());
console.log(md.getTradingDay());

console.log(ctp.getLastRequestId());

console.log(ctp.ProductClassType.Futures);
