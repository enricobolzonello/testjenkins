const TSPModule = require('./build/Release/travelingsalesmanoptimization.node');
const express = require("express");
const cors = require("cors");

const PORT = process.env.PORT || 5050;
const app = express();

app.use(cors());
app.use(express.json());


console.log('exports : ', TSPModule);
console.log();

let obj = TSPModule.TSP_runner("../data/berlin52.tsp", 123, 1200, 2)

console.log('cost : ', obj['cost']);
console.log();

console.log('filename : ', obj['filename']);
console.log();

// start the Express server
app.listen(PORT, () => {
    console.log(`Server listening on port ${PORT}`);
  });
