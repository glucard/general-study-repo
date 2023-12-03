import { useDataContext } from "@/context/data_context";
import { useState } from "react"

export default () => {

    const { setCurrentPage, setUser } = useDataContext();

    const [email, setEmail] = useState('')
    const [name, setName] = useState('');
    const [password, setPassword] = useState('');
    const [error, setError] = useState('');

    const handleSubmit = async (e:any) => {
        e.preventDefault();
        console.log(email, password);
            
        if (email && password) {
            try {
                const body = { email, password };
                const res = await fetch(`/api/user/login`, {
                    method: "POST",
                    headers: {"Content-Type": "application/json"},
                    body: JSON.stringify(body),
                });
                console.log(res)
                const res_json = await res.json();

                if (res_json != undefined) {
                    setUser(res_json)
                    setCurrentPage('home')
                } else {
                    setError("Dados invalidos.")
                }
                
            } catch (error) {
                console.error(error);
            }
        } else {
            setError("All fields are required");
            return;
        }
    }

    return (
        <div className="flex flex-col p-5  bg-purple-50  text-black items-center gap-5">
            <form>
                <div className="flex flex-col gap-3 items-center p-5 rounded-lg bg-white">
                    <input onChange={e => setEmail(e.target.value)} className="bg-gray-100 rounded-md p-3" type='email' placeholder="E-mail"/>
                    <input onChange={e => setPassword(e.target.value)} className="bg-gray-100 rounded-md p-3" type='password' placeholder="senha"/>
                    <span className="text-red-500">{ error ? error : ""}</span>
                    <button onClick={(e) => handleSubmit(e)} className="bg-purple-100 p-1 rounded-md w-20" type="submit">Entrar</button>
                </div>
            </form>
        </div>
    )
}