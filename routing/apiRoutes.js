let direction = require("../direction/direction.js");

module.exports = function(app) {

    app.post("/direction", (req, res)=> {
        console.log(req.body);

        direction = req.body;  
        
        res.json(direction);
    })
};