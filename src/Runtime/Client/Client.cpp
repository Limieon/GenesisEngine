#include <iostream>

#include <Runtime/Common/Common.hpp>
#include <Genesis/Core/Core.hpp>
#include <Genesis/Server/Server.hpp>
#include <Genesis/Client/Client.hpp>

int main(int argc, char** argv) {
    std::cout<<"Starting Client..."<<std::endl;

    ge::core::Core::init();
    rt::common::Common::init();
    ge::server::Server::init();
    ge::client::Client::init();

    std::cin.get();
}
