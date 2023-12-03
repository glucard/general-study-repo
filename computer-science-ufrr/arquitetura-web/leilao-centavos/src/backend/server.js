const http = require('http');
const { Server } = require('socket.io');

const httpServer = http.createServer();

const PORT = process.env.PORT || 3001

const io = new Server(httpServer, {
    cors : {
        origin: "http://localhost:3000",
        methods: ["GET", "POST"],
        allowedHeaders: ["my-custom-header"],
        credentials: true,
    }
});

var items = {};

const handleBid = item => {
    item.current_bid += 1;
}

const handleTimer = async item_id =>{
    while (true){
        items[item_id].timer -= 1;
        await setTimeout(()=>"", 1000);
        if (!is_active) break;
        io.emit("update_item", items[item_id]);
    }
}

const handleItem = item => {
    items[item_id] = item;
    handleTimer(item_id)
}

io.on("connection", async(socket)=>{
    
    socket.on("start_item", (item_id)=>{
        item = {
            item_id: item_id,
            current_bid: 0,
            timer: 20,
            is_active: false
        }
        handleItem(item_id)
    });
});

httpServer.listen(PORT, ()=>{
    console.log(`Socket.io is running on port ${PORT}`);
});