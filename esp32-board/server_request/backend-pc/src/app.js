const express = require("express")
const app = express()

app.use(express.json())

app.post("/", (req,res) => {
    console.log(req.body)
    res.send({'status': "data comming"})
})

app.listen(1800, ()=>{
    console.log("server is running");
})