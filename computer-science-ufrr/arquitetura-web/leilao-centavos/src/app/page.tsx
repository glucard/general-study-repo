"use client"
import AddItemPage from '@/components/Pages/AddItem/AddItemPage'
import HomePage from '@/components/Pages/HomePage/HomePage'
import LoginPage from '@/components/Pages/LoginPage/LoginPage'
import RegisterUserPage from '@/components/Pages/RegisterUserPage/RegisterUserPage'
import TopBar from '@/components/Pages/TopBar/TopBar'
import { useDataContext } from '@/context/data_context'
export default function Home() {

  const { currentPage, setCurrentPage } = useDataContext()

  var show_page
  switch(currentPage){
    case 'login':
      show_page = <LoginPage/>
      break
    case 'register_user':
      show_page = <RegisterUserPage/>
      break
    case 'add_item':
      show_page = <AddItemPage/>
      break
    case 'home':
    default:
      show_page = <HomePage/>
      break
  }

  return (
    <main>
      <TopBar/>
      {show_page}
    </main>
  )
}