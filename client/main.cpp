#include "client.h"


int main(){

    try{

        asio::io_context io_context;

        tcp::resolver resolver(io_context);
        auto endpoints = resolver.resolve("127.0.0.1","90000");
        chat_client c(io_context,endpoints);

        std::thread t([&io_context](){ io_context.run(); });

        char line[chat_message::max_body_length + 1];

        while(std::cin.getline(line, chat_message::max_body_length + 1)){
            chat_message msg;
            msg.body_length(std::strlen(line));
            std::memcpy(msg.body(),line,msg.body_length());
            msg.encode_header();
            c.write(msg);
        }

        c.close();
        t.join();
    }catch (std::exception& e){
      std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
