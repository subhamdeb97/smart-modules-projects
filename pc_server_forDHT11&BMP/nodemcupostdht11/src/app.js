const express = require("express")
const app = express()

const time = require("./functions/timecall")

const bodyParser = require('body-parser');
// app.use(bodyParser.urlencoded({ extended: true }));

app.use(express.json())

app.get("/", (req,res)=>{
    res.send("Hello From DHT11")
})
app.post("/esp8266", async (req, res)=>{
    // console.log(req.headers)
    let response = await time()
    console.log("Weather is:")
    console.log(response.data.datetime)
    console.log(req.body)
    res.send("OK")
})

app.listen(2000)