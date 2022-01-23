#include "server.h"


int main(){

    try{

        asio::io_context io_context;

        tcp::endpoint endpoint(tcp::v4(), 90000);

        chat_server s(io_context,endpoint);

        io_context.run();

    }catch (std::exception& e){
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}

