import { useEffect, useState } from "react";

export default () => {
    const [items, setItems] = useState<any>([]);
    const [isLoaded, setIsLoaded] = useState(false);
    const [error, setError] = useState('');
    
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

    useEffect(()=> {
        handleGetItems()
    },[])

    const product_class = "flex flex-col h-56 bg-white text-black justify-between items-center rounded-lg p-5 outline outline-1 outline-gray-400"
    const lance_class = "bg-pink-400 rounded-md w-28"

    return (
        <div className="flex flex-col bg-white">
            <div className="flex flex-row justify-center gap-5 auto-cols-auto p-5">
                {
                    isLoaded ?
                        items.map((item:any) => (
                            <div key={item.id} className={product_class}>
                                <span className="outline outline-1 outline-gray-400 rounded-md p-1">inicio: {item.start_time}</span>
                                <span>{item.name}</span>
                                <span>{item.description}</span>
                                <span>00s</span>
                                <span>{item.posted_by}</span>
                                <span>R$ 0,00</span>
                                <button className={lance_class}>LANCE</button>
                            </div>
                        ))
                        : "Loading..."
                }
            </div>
        </div>
    )
}