'client component'

import { useConnection } from "@/context/connect";
import { useState, useEffect } from "react"

interface IMSGDataTypes {
    user: String;
    msg: String;
    time: String;
}

export default function ChatPage({userName} : any) {

    const [currentMessage, setCurrentMessage] = useState("")
    const [chatMessages, setChatMessages] = useState<IMSGDataTypes[]>([])
    
    const { connection } = useConnection();

    const handleSend = async (e:React.FormEvent<HTMLFormElement>) => {
        e.preventDefault();
        if(currentMessage !== ""){
            const newMsg: IMSGDataTypes = {
                user: userName,
                msg: currentMessage,
                time: new Date(Date.now()).getHours() + ":" + new Date(Date.now()).getMinutes()
            };

            connection.emit("send_message", newMsg);
            setCurrentMessage("");
        }
    }

    useEffect(() => {
        if(connection) {
            connection.on("receive_message", (msg:IMSGDataTypes) => {
                setChatMessages((msgs) => [...msgs, msg]);
            })
        }
    }, [connection]);
    return (
        <div className="flex">
            <div className="flex flex-col w-96 h-screen bg-green-300 p-3 gap-6 border-green-600">
                <div className="flex flex-col">
                    <span>online users</span>
                    <span>...</span>
                    <span>{userName}</span>
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
                    <input type="text" className='rounded px-2 py-3 text-gray-700 border border-gray-400 w-2/3' placeholder="enter message" value={currentMessage} onChange={(e)=>setCurrentMessage(e.target.value)}/>
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