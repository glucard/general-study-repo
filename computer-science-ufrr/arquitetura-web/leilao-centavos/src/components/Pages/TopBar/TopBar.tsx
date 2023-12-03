import { useDataContext } from "@/context/data_context"
import { useEffect, useState } from "react";

export default () => {

    const { setCurrentPage, user} = useDataContext();
    const [ userSection, setUserSection ] = useState<JSX.Element>()

    useEffect(() => {
        const user_section = user == undefined ? (
            <div className="flex flex-row  gap-5">
                <button onClick={()=> setCurrentPage('register_user')}>cadastrar</button>
                <button onClick={()=> setCurrentPage('login')}>entrar</button>
            </div>
        ) : (
            <div className="flex flex-col  gap-5">
                <span>User: {user.name}</span>
                <span>Lances: {user.remain_bids}</span>
                {
                    user.role == 'admin' ?
                        <button onClick={()=>setCurrentPage('add_item')}>Adicionar Produto</button>
                        :
                        ""  
                }
            </div>
        )
        setUserSection(user_section);
        
        const body = user;
        fetch(`/api/user/edit_bids`, {
            method: "POST",
            headers: {"Content-Type": "application/json"},
            body: JSON.stringify(body),
        });
    },[user])


    
    return (
        <div className="flex flex-col bg-white text-black">
            <div className="flex flex-row justify-between p-5 items-center">
                <img src="./logo-leilao-legal.png" className="h-20" alt="leilao legal" />

                {
                    userSection
                }
            </div>
            <div className="flex flex-row gap-20 p-5 justify-center bg-purple-200">
                <button onClick={() => setCurrentPage('home')}>Home</button>
                <button onClick={() => setCurrentPage('sold_to')}>Leiloes Arrematados</button>
                <a>Perguntas frequentes</a>
                <a>Depoimentos</a>
                <button onClick={() => user ? setCurrentPage('buy_bid') : setCurrentPage('login')}>Comprar Lances</button>
            </div>
        </div>
    )
}