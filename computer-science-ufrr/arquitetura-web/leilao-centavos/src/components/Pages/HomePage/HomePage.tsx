import { useEffect, useState } from "react";
import { useConnection } from "@/context/connect";
import { useDataContext } from "@/context/data_context";

export default () => {
    const [items, setItems] = useState<any>([]);
    const [itemsSocket, setItemsSocket] = useState<any>({});
    
    const [isLoaded, setIsLoaded] = useState(false);
    const [error, setError] = useState('');

    const { connection } = useConnection();
    const { user, setUser, setCurrentPage } = useDataContext();

    const handleGetItems = async ()=>{
        try {
            const res = await fetch(`/api/item/get_all`, {
                method: "GET",
                headers: {"Content-Type": "application/json"},
            });
            console.log(res)
            const res_json = await res.json();

            if (res_json != undefined) {
                setItems(res_json)
            } else {
                setError("Não há produtos cadastrados.")
            }
            setIsLoaded(true);
        } catch (error) {
            console.error(error);
        }

    }

    const handleBid = (item_id:any) => {
        if (user == undefined){
            setCurrentPage('login')
            return
        }
        if (!itemsSocket[item_id]) return;
        if (!itemsSocket[item_id].is_active) return;

        if (user.remain_bids <= 0){
            setCurrentPage('buy_bid');
            return;
        };

        
        const bid_data = {
            item_id:item_id,
            user_id: user.id,
            user_name: user.name,
        }
        setUser((prev:any) => ({
            ...prev,
            remain_bids: prev.remain_bids-1,
        }));
        
        connection.emit("bid_item", bid_data)
    }

    useEffect(()=> {
        handleGetItems()
    },[])

    useEffect(() => {
        if(connection) {
            connection.on("update_item", (items:any) => {
                setItemsSocket(items);
            })
        }
    }, [connection]);

    const product_class = "flex flex-col bg-white text-black justify-between items-center rounded-lg p-5 outline outline-1 outline-purple-100 gap-1"
    const lance_class = ""


    return (
        <div className="flex flex-col bg-purple-50">
            <div className="flex flex-row justify-center gap-5 auto-cols-auto p-5">
                {
                    isLoaded ?
                        items.map((item:any) => ( item.sold_to_id ? "" :
                            <div key={item.id} className={product_class}>
                                {user == undefined ? "" : user.role == "admin" ? <button className="bg-black text-white p-2 rounded-xl" onClick={()=> connection.emit("start_item", item.id)}>start</button> : ""}
                                <span className="outline outline-1 outline-purple-50 rounded-md p-1">inicio: {item.start_time}</span>
                                <span>{item.name}</span>
                                <span>{item.description}</span>
                                <span>{itemsSocket[item.id] == undefined ? "00" : itemsSocket[item.id].timer}s</span>
                                <span>postado por: {item.posted_by.name}</span>
                                {itemsSocket[item.id] == undefined ? "" : <span>lance: {itemsSocket[item.id].current_owner_name}</span>}
                                <span>R$ {itemsSocket[item.id] == undefined ? "0.00" : itemsSocket[item.id].current_bid/100}</span>
                                <button onClick={()=>handleBid(item.id)}
                                    className={
                                        (itemsSocket[item.id] == undefined ? "bg-gray-400"
                                        : itemsSocket[item.id].is_active ? "bg-pink-400": "bg-gray-400")
                                        +" rounded-md w-28"
                                        }>LANCE</button>
                            </div>
                        ))
                        : "Loading..."
                }
            </div>
        </div>
    )
}