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

var users = {};
var public_users = {};


io.on("connection", async(socket)=>{
    
    socket.on("join_room", (userName)=>{
        console.log(`Username: ${userName} - socket.id: ${socket.id}`)
        
        users[socket.id] = {
            name: userName,
            socket: socket,
        };
        
        public_users[socket.id] = {
            name: userName,
            is_typing: false,
        };
        
        msg = {
            user: "",
            msg: `${userName} has connected.`,
            time: new Date(Date.now()).getHours() + ":" + new Date(Date.now()).getMinutes()
        }
        //console.log(msg)
        io.emit("receive_message", msg)
        io.emit("update_users_client", public_users)
    });

    socket.on("send_message" , (msg) => {
        for (const id in users) {
            other_user = users[id];
            if (id === socket.id)
                continue;
            other_user.socket.emit("receive_message", msg); // send to all, except self
        }

        // io.emit("receive_message", msg);
    })
    
    socket.on("update_users", (n)=>{
        console.log("updating")
        io.emit("update_users_client", public_users);
    })

    socket.on("disconnect", ()=>{
        const user = users[socket.id];

        if (!user)
            return;

        msg = {
            user: "",
            msg: `${user.name} has disconnected.`,
            time: new Date(Date.now()).getHours() + ":" + new Date(Date.now()).getMinutes()
        }

        delete users[socket.id];
        delete public_users[socket.id];

        io.emit("receive_message", msg)
        io.emit("update_users_client", public_users)
    });
});

httpServer.listen(PORT, ()=>{
    console.log(`Socket.io is running on port ${PORT}`);
});