#include<iostream>
#include<string>
#include "client.h"
#include "crypto.h"




Client::Client(std::string _id,const Server& _server) : 
          id{_id},
          server{&_server}

  {
      //std::cout<<"constructor id&serv"<<std::endl;
      //this->id=id;
      
      crypto::generate_key(public_key, private_key);
    
      

  }
std::string Client::sign(std::string txt) const
{
    return crypto::signMessage( this -> private_key,  txt);

}
bool Client::transfer_money(std::string receiver, double value)
 {
   std::string transac{this -> id + "-" + receiver + "-" +std::to_string(value) };
   
   
   server->add_pending_trx(transac,sign(transac));
   return true;



 }
size_t Client::generate_nonce()
 {
   return rand();

 }
double Client::get_wallet()
 {  
     return server->get_wallet(this ->id);
 }





