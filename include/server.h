#ifndef SERVER_H
#define SERVER_H


#include<iostream>
#include<memory>
#include<iomanip>
#include<map>
#include<vector>
#include<string>
#include "client.h"
#include "crypto.h"

class Client;




class Server
{
public:
	Server()=default;
	std::shared_ptr<Client> add_client(std::string id);
	std::shared_ptr<Client> get_client(std::string id) const;
	double get_wallet(std::string id) const;
	static bool parse_trx(std::string trx, std::string& sender, std::string& receiver, double& value) ;
	bool add_pending_trx(std::string trx, std::string signature) const;
	friend void  show_wallets(const  Server& server) ;
    friend void  show_pending_transactions();
	size_t mine();
private:
	std::map<std::shared_ptr<Client>, double> clients;
};

 
extern std::vector<std::string> pending_trxs;
#endif //SERVER_H