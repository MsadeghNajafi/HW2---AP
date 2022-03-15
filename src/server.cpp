#include<iostream>
#include<memory>
#include "server.h"
#include<string>
#include<map>
#include<stdlib.h>
#include<iomanip>

std::vector<std::string> pending_trxs;
std::shared_ptr<Client> Server:: add_client(std::string id)
 {
    int flag{0};
    std::shared_ptr<Client> p{new Client{id, *this}};
    for(auto client :clients)
     {
       if(client.first->get_id() ==(*p).get_id())
          flag+=1;
           
     }
    if (flag==0)
      {
      clients.insert(std::pair<std::shared_ptr<Client>, double>(p, 5));
      return p;
      }
    else
    {
       int num=rand()%1000+1000 ;
       id=id+std::to_string(num);
        std::shared_ptr<Client> p{new Client{id, *this}};
       clients.insert(std::pair<std::shared_ptr<Client>, double>(p, 5));
       return p;
    }
      

 }
std::shared_ptr<Client> Server:: get_client(std::string id) const
 {
  int flag{0};
  for(const auto& client: this->clients)
  {
    if(id == client.first->get_id())
      {
       flag+=1;
       return client.first;
      }
       
    
  }
  if (flag==0)
   return nullptr;
   
 }
bool Server:: parse_trx(std::string trx, std::string& sender, std::string& receiver, double& value) 
 {
   std::size_t co_1, co_2 , co_3  ;
   double nunval ;
   std::string nun{};
   co_1= trx.find("-");
   std::string trx2{trx.substr(co_1 +1)};
   co_2=trx2.find("-");
   std::string trx3{trx2.substr(co_2 +1)};
 
    
    if(trx.substr(0,co_1 ) != nun && trx2.substr(0,co_2 ) != nun  && trx3> "0.0"  && trx3<"10000.0")
      { 
        sender=trx.substr(0,co_1 );
        receiver=trx2.substr(0,co_2 );
        value =  std::stod(trx3);
        return true;
      }
  
    else
      {
       throw std::runtime_error("runtime_error !") ;
      }
   

 }

bool Server::add_pending_trx(std::string trx, std::string signature) const
 {  bool x;
    std::shared_ptr<Client> point;
     std::size_t co_1, co_2 , co_3 ;
   co_1= trx.find("-");
   std::string trx2{trx.substr(co_1 +1)};
   co_2=trx2.find("-");
   std::string trx3{trx2.substr(co_2 +1)};


   point=get_client(trx.substr(0,co_1 ));
   x=crypto::verifySignature((*point).get_publickey(),trx,(*point).sign(trx));
   if(std::stoi(trx3)<= (*point).get_wallet() && x==true)
         pending_trxs.push_back(trx);
 }

size_t Server::mine()
{
    std::string mempool{};
    
    std::string nonce{};
    std::string hash{};
 
 while(hash.substr(0, 10).find("000") )
 {
  
  for(  auto& client : clients)
   { 
     std::string mempool{};
     for(const auto& trx : pending_trxs)
        mempool += trx; 
     nonce=std::to_string(client.first -> generate_nonce());
     mempool+=nonce;
     hash=crypto::sha256(mempool);
     if(hash.substr(0, 10).find("000") != std::string::npos)
         
         {

         
          client.second +=6.25;
          std::cout<<client.first ->get_id()<<" ,"<<client.second<<std::endl;
  
            
          for(auto& clie : clients )
           {
            for(auto& tr :pending_trxs)
             {
              std::size_t co_1, co_2 , co_3 ;
              co_1= tr.find("-");
              std::string tr2{tr.substr(co_1 +1)};
              co_2=tr2.find("-");
              std::string tr3{tr2.substr(co_2 +1)};
              if(clie.first -> get_id() == tr.substr(0,co_1 ))
                  {
                    clie.second -=std::stod(tr3);
                  }
              else if(clie.first ->get_id()==tr2.substr(0,co_2))
                   clie.second +=std::stod(tr3);
              }  
           }
          pending_trxs.clear();
          return std::stoi(nonce);
          break;
         }

      }
  }
  
 }
double Server::get_wallet(std::string id) const
 {
   for( auto client: clients)
    {
      if(client.first->get_id()==id)
         return client.second;
    }
 }
void   show_wallets(const  Server& server)
 {
 	std::cout << std::string(20, '*') << std::endl;
 	for(const auto& client: server.clients)
 		std::cout << client.first->get_id() <<  " : "  << client.second << std::endl;
 	std::cout << std::string(20, '*') << std::endl;
 }
void  show_pending_transactions()
 {
 	std::cout  <<  std::string(20, '*') <<  std::endl;
 	for(const  auto& trx : pending_trxs)
 		std::cout << trx <<  std::endl;
 	std::cout  <<  std::string(20, '*') <<  std::endl;
 }

   


 


