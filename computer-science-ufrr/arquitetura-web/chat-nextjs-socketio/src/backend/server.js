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

io.on("connection", async(socket)=>{
    
    socket.on("join_room", (userName)=>{
        console.log(`Username: ${userName} - socket.id: ${socket.id}`)
    });

    socket.on("send_message" , (msg) => {
        console.log(msg);

        io.emit("receive_message", msg);
    })
});

httpServer.listen(PORT, ()=>{
    console.log(`Socket.io is running on port ${PORT}`);
});