'client component'

import { useConnection } from "@/context/connect";
import { useState, useEffect } from "react"

interface IMSGDataTypes {
    user: String;
    msg: String;
    time: String;
    to: String;
}

export default function ChatPage({userName, connection} : any) {

    const [currentMessage, setCurrentMessage] = useState("")
    const [chatMessages, setChatMessages] = useState<IMSGDataTypes[]>([])
    const [users, setUsers] = useState<any[]>([])
    const [lastTyping, setLastTyping] = useState<any>({})

    const handleSend = async (e:React.FormEvent<HTMLFormElement>) => {
        e.preventDefault();
        if(currentMessage == ""){
            return;
        }


        var is_private = false;
        var receiver_id;
        var message = currentMessage;
        var title = userName;
        var to = "everyone";
        
        if (currentMessage.slice(0, 1) == "/"){
            switch(currentMessage.split(" ")[0]){
                case("/to"):
                    is_private = true;
                    const receiver_name = currentMessage.split(" ")[1];
                    users.forEach(u => {
                        if (receiver_name == u.name){
                            receiver_id = u.id;
                            to = receiver_id;
                            message = currentMessage.split(' ').slice(2).join(' ');
                        }
                    })
                    if(!receiver_id){
                        message = `Error: User ${receiver_name} not found.`
                    }
                    title = `from ${userName} to ${receiver_name}`
                    break
                default:
                    break;
            }
        }
        
        const newMsg: IMSGDataTypes = {
            user: title,
            msg: message,
            time: new Date(Date.now()).getHours() + ":" + new Date(Date.now()).getMinutes(),
            to: to
        };

        if (is_private) {
            if (receiver_id)
                connection.emit("send_private_message", newMsg)
        } else {
            connection.emit("send_message", newMsg);
        }
        setChatMessages((msgs) => [...msgs, newMsg]); // add before send
        setCurrentMessage("");
    }

    const handleTyping = async (e:any)=>{
        console.log("typing...");
        const wat = await connection.emit("typing", connection.id);
        console.log(wat);
        console.log("typing...2");
        setCurrentMessage(e.target.value);
    }

    useEffect(() => {
        if(connection) {
            connection.on("receive_message", (msg:IMSGDataTypes) => {
                setChatMessages((msgs) => [...msgs, msg]);
            })
            connection.on("update_users_client", (public_users:any) => {
                var new_users:any = []
                for (const id in public_users) {
                    new_users.push({
                        id: id,
                        name: public_users[id]['name']
                    })
                }
                setUsers(new_users);
            })
            connection.on("typing", (id:string) => {
                console.log("SIJDAISJDISAJ AQUIII")
                setLastTyping((e:any)=>{
                    e[id] = true;
                    return e;
                })
            })
        }
    }, [connection]);

    useEffect(()=>{
    }, [lastTyping]);
    return (
        <div className="flex">
            <div className="flex flex-col w-96 h-screen bg-green-300 p-3 gap-6 border-green-600">
                <div className="flex flex-col">
                    <span>online users</span>
                    {
                        users.map((u, key) => (
                            <div key={key}>
                                {u.name}{
                                    (!lastTyping) ? "" : (
                                        (!(u.id in lastTyping)) ? "" : (
                                            (lastTyping[u.id]) ? "is typing" : ""
                                        )
                                    )
                                }
                            </div>
                        ))
                    }
                </div>
            </div>

            <div className="flex flex-col w-full h-screen px-10 py-5 bg-yellow-100 justify-between">
                <div>
                    {
                        chatMessages.map(({user, msg, time}, key) => 
                            <div key={key} className="flex flex-row gap-2 p-5">
                                <div>
                                    {time}
                                </div>
                                <div className="font-bold">
                                    {user}:
                                </div>
                                <div>
                                    {msg}
                                </div>
                            </div>
                        )
                    }
                </div>
                <form onSubmit={handleSend} className="flex gap-2 w-full justify-center">
                    <input type="text" className='rounded px-2 py-3 text-gray-700 border border-gray-400 w-2/3' placeholder="enter message" value={currentMessage}
                        onChange={(e)=>{
                            setCurrentMessage(e.target.value);
                            console.log("test");
                            connection.emit("typing", connection.id);
                        }}/>
                    <button type="submit"
                        className='inline-flex items-center justify-content  px-4 py-2 text-base font-medium leading-6 text-white
                        whitespace-no-wrap bg-blue-600 border border-blue-700 rounded-md shadow-sm hover:bg-blue-700 focus:outline-none
                        focus:ring-2 focus:ring-offset-2 focus:ring-blue-500'
                        >send</button>
                </form>
            </div>
        </div>
    )
}