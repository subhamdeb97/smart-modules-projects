const axios = require("axios")


const timeapi = async() =>{
    try{
      let response =await axios.get("http://worldtimeapi.org/api/timezone/Asia/Kolkata");
      return response
}catch(err){
    retrun ({"error" : "time API has problem"}) 
}
}


module.exports = timeapi