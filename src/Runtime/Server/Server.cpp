#include <iostream>

#include <Runtime/Common/Common.hpp>
#include <Genesis/Core/Core.hpp>
#include <Genesis/Server/Server.hpp>

int main(int argc, char** argv) {
    std::cout<<"Starting Server..."<<std::endl;

    ge::core::Core::init();
    rt::common::Common::init();
    ge::server::Server::init();

    std::cin.get();
}
