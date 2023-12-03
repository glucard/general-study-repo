"use client"
import AddItemPage from '@/components/Pages/AddItem/AddItemPage'
import BuyBidPage from '@/components/Pages/BuyBidPage/BuyBidPage'
import HomePage from '@/components/Pages/HomePage/HomePage'
import LoginPage from '@/components/Pages/LoginPage/LoginPage'
import RegisterUserPage from '@/components/Pages/RegisterUserPage/RegisterUserPage'
import TopBar from '@/components/Pages/TopBar/TopBar'
import SoldItemsPage from '@/components/Pages/SoldItemsPage/SoldItemsPage'
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
    case 'buy_bid':
      show_page = <BuyBidPage/>
      break
    case 'sold_to':
      show_page = <SoldItemsPage/>
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