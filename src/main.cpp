#include <iostream>
#include <gtest/gtest.h>
#include "server.h"


int main(int argc, char **argv)
{
    if (false) // make false to run unit-tests
    {
       Server server{};
    pending_trxs.clear();
    auto bryan{server.add_client("bryan")};
    auto clint{server.add_client("clint")};
    auto sarah{server.add_client("sarah")};
     std::string mempool{};
    for(const auto& trx : pending_trxs)
        mempool += trx;
        
    show_wallets(server);
    size_t nonce{server.mine()};
    show_wallets(server);
    std::string hash = crypto::sha256(mempool + std::to_string(nonce));
    std::cout<<bryan->get_wallet()<<std::endl;
    std::cout<<clint->get_wallet()<<std::endl;
    std::cout<<sarah->get_wallet()<<std::endl;
    std::cout<<sarah->generate_nonce()<<std::endl;
    std::cout<<sarah->generate_nonce()<<std::endl;
    //server.show_pending_transactions();
     
    }  
     
    else
    {
        ::testing::InitGoogleTest(&argc, argv);
        std::cout << "RUNNING TESTS ..." << std::endl;
        int ret{RUN_ALL_TESTS()};
        if (!ret)
            std::cout << "<<<SUCCESS>>>" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    return 0;   
} 