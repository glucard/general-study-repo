import { useConnection } from "@/context/connect";
import { useDataContext } from "@/context/data_context";
import { useState } from "react"

export default () => {

    const { setCurrentPage, user } = useDataContext();
    const { connection } = useConnection();

    const [description, setDescription] = useState('');
    const [name, setName] = useState('');
    const [startTime, setStartTime] = useState<Date>();

    const [error, setError] = useState('');


    const handleSubmit = async (e:any) => {
        e.preventDefault();
        console.log(name, description, startTime);
            
        if (name && description && startTime) {
            try {
                const body = {
                    name: name,
                    description: description,
                    start_time: startTime,
                    posted_by_id: user.id,
                };

                const res = await fetch(`/api/item/create`, {
                    method: "POST",
                    headers: {"Content-Type": "application/json"},
                    body: JSON.stringify(body),
                });
                console.log(res)
                const res_json = await res.json();
                console.log(res_json);
                connection.emit("new_item");
                alert("Cadastrado com sucesso")
                setCurrentPage('home')
            } catch (error) {
                console.error(error);
            }
        } else {
            setError("All fields are required");
            return;
        }
    }

    return (
    <div className="flex flex-col p-5  bg-purple-50  text-black items-center gap-5 h-">
        <form>
            <div className="flex flex-col gap-3 items-center p-5 rounded-lg bg-white">
                <input onChange={e => setName(e.target.value)} className="bg-gray-100 rounded-md p-3" type='text' placeholder="Nome"/>
                <input onChange={e => setDescription(e.target.value)} className="bg-gray-100 rounded-md p-3" type='text' placeholder="Descrição"/>
                <input onChange={e => setStartTime(new Date(e.target.value))} className="bg-gray-100 rounded-md p-3" type='datetime-local' placeholder="cpf"/>
                <span className="text-red-500">{ error ? error : ""}</span>
                <button onClick={(e) => handleSubmit(e)} className="bg-purple-100 p-1 rounded-md w-28" type="submit">Cadastrar</button>
            </div>
        </form>
    </div>
    )
}