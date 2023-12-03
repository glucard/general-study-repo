const { TIMEOUT } = require('dns');
const http = require('http');
const { Server } = require('socket.io');

const httpServer = http.createServer();

const PORT = process.env.PORT || 3001

const START_TIME = 20

function delay(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}

const io = new Server(httpServer, {
    cors : {
        origin: "http://localhost:3000",
        methods: ["GET", "POST"],
        allowedHeaders: ["my-custom-header"],
        credentials: true,
    }
});

var items = {};

const handleTimer = async item_id =>{
    while (true){
        if (!items[item_id].is_active) break;
        await delay(1000);
        items[item_id].timer -= 1;

        if (items[item_id].timer <= 0) {
            items[item_id].is_active = false;

            const body = {
                id: item_id,
                sold_to_id: items[item_id].current_owner_id,
                sold_by_amout: items[item_id].current_bid, 
            };

            fetch(`http://localhost:3000/api/item/edit`, {
                method: "POST",
                headers: {"Content-Type": "application/json"},
                body: JSON.stringify(body),
            });
        }
        console.log(items[item_id].timer)
        
        io.emit("update_item", items);
    }
        
}

const handleStart = item_id => {
    
    console.log("starting item", item_id);
    var item = {
        item_id: item_id,
        current_bid: 0,
        timer: START_TIME,
        current_owner_id: undefined,
        current_owner_name: "seja o primeiro",
        is_active: true
    }
    items[item_id] = item;
    handleTimer(item_id)
}

io.on("connection", async(socket)=>{

    socket.on("bid_item", (bid_data) => {
        
        const { item_id, user_id, user_name } = bid_data;

        items[item_id].current_bid += 1;
        items[item_id].timer = START_TIME
        items[item_id].current_owner_id = user_id
        items[item_id].current_owner_name = user_name
        io.emit("update_item", items)
    })

    socket.on("new_item", ()=> {
        handleCountdown();
    })
    
    socket.on("start_item", (item_id)=>{
        handleStart(item_id)
    });
    
});



const handleCountdown = async ()=> {
    try {
        const res = await fetch(`http://localhost:3000/api/item/get_all`, {
            method: "GET",
            headers: {"Content-Type": "application/json"},
        });
        const res_json = await res.json();

        if (res_json == undefined) return

        res_json.forEach(item => {
            console.log(!item.sold_to_id)
            if (!item.sold_to_id) {
                const start_time = new Date(item.start_time);
                
                const remaining_time = start_time - Date.now()

                if (start_time < Date.now()){
                    handleStart(item.id)
                } else {
                    setTimeout(()=>{
                        console.log(item.id, "will start on", remaining_time / 1000, "seconds")
                        handleStart(item.id)
                    }, remaining_time)
                }
            }
        });
    } catch (error) {
        console.error(error);
    }
}
httpServer.listen(PORT, ()=>{
    console.log(`Socket.io is running on port ${PORT}`);
});


handleCountdown()