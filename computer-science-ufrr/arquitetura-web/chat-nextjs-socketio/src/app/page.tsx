'use client'

import ChatPage from "@/components/chat/ChatPage";
import { useConnection } from "@/context/connect";
import { useState } from "react";

export default function Home() {
  const [showSpinner, setShowSpinner] = useState(false)
  const [showChat, setShowChat] = useState(false)
  const [userName, setUserName] = useState("")

  const { connection } = useConnection();

  const handleJoin = async (e:React.FormEvent<HTMLFormElement>) => {
    e.preventDefault();
    
    if (userName !== "") {
      setShowSpinner(true);
      await connection.emit("join_room", userName);
      setShowChat(true);
      setShowSpinner(false);
    }

    setShowChat(true);
  }

  return (
    <main className="flex w-full h-screen">
      <div className="flex flex-col w-full h-full justify-center items-center gap-2" style={{display: !showChat ? "" : "none"}}>
        <div className="w-1/5">
          <h1 className='w-full h-full'>Chat SocketIO + NextJS</h1>
        </div>
        <div>
          <form onSubmit={handleJoin} className='flex gap-2'>
            <input type="text" className='rounded px-2 py-3 text-gray-700 border border-gray-400' placeholder="Enter username"value={userName} onChange={(e)=>setUserName(e.target.value)} required/>
            
            <button
                  type="submit"
                  className='inline-flex items-center justify-content  px-4 py-2 text-base font-medium leading-6 text-white
                  whitespace-no-wrap bg-blue-600 border border-blue-700 rounded-md shadow-sm hover:bg-blue-700 focus:outline-none
                  focus:ring-2 focus:ring-offset-2 focus:ring-blue-500'>
            {
              !showSpinner ? ("Join") : (
                <div className="border-gray-300 h-5 w-5 animate-spin rounded-full border-2 border-t-blue-600"/>
              )
            }
            
            </button>
          </form> 
        </div>
      </div>
      <div className="w-full" style={{display: showChat ? "" : "none"}}>
        <ChatPage userName={userName}/>
      </div>
    </main>
  )
}
