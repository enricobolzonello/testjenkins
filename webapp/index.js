const TSPModule = require('./build/Release/travelingsalesmanoptimization.node');
const express = require("express");
const cors = require("cors");

const PORT = process.env.PORT || 5050;
const app = express();

app.use(cors());
app.use(express.json());
app.use(express.urlencoded({ extended: true }));

// use the “get” method of express to define the logic for the “/” route. 
// Inside this method, use res.sendFile() method which is used to send the HTML form we just created as a response.
app.get("/", (req, res) => {
    res.sendFile(__dirname + "/index.html");
});

app.post("/", (req, res) => {
    const algorithm = Number(req.body.algorithm);
    const seed = Number(req.body.seed);
    const timelimit = Number(req.body.timelimit);
    const dataset = req.body.dataset;

    res.send("Data received");

    let obj = TSPModule.TSP_runner(dataset, seed, timelimit, algorithm)

    console.log('cost : ', obj['cost']);
    console.log();

    console.log('filename : ', obj['filename']);
    console.log();
});

// start the Express server
app.listen(PORT, () => {
    console.log(`Server listening on port ${PORT}`);
});