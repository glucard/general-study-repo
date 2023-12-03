"use client"

import { useContext, createContext, useState, useEffect } from "react"

const Context = createContext();

export const useDataContext = () => useContext(Context);

export const Provider = ({children}) => {
    const [currentPage, setCurrentPage] = useState('home');
    const [user, setUser] = useState()

    const data = {
        user,
        setUser,
        currentPage,
        setCurrentPage,
    };

    return <Context.Provider value={{ ...data }}>{children}</Context.Provider>;
}

export default Context;