import { useDataContext } from "@/context/data_context"
import { useEffect } from "react";


export default () => {
    const { setUser } = useDataContext();

    const handleBuy = async (how_many:any) => {
        await setUser((prev:any)=> ({...prev, remain_bids: prev.remain_bids+how_many}))
    }

    return (
        <div className="flex flex-col bg-purple-50 text-black items-center gap-5 p-5">
            <h2>Comprar lances</h2>
            <div className="flex flex-row justify-center gap-5">
                <button onClick={()=> handleBuy(10)} className="bg-purple-200 p-2 rounded-md">comprar 10 lances</button>
                <button onClick={()=> handleBuy(20)}  className="bg-purple-500 p-2 rounded-md text-gray-900">comprar 20 lances</button>
                <button onClick={()=> handleBuy(50)}  className="bg-purple-800 p-2 rounded-md text-white">comprar 50 lances</button>
            </div>

        </div>
    )
}