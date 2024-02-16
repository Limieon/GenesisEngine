#include <iostream>

#include <Genesis/Core/Core.hpp>
#include <Genesis/Server/Server.hpp>
#include <Genesis/Client/Client.hpp>
#include <Runtime/Common/Common.hpp>

int main(int argc, char** argv) {
    std::cout<<"Starting Editor..."<<std::endl;

    ge::core::Core::init();
    ge::server::Server::init();
    ge::client::Client::init();
    rt::common::Common::init();

    std::cin.get();
}
