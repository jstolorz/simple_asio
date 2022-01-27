#pragma once

#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>
#include <iostream>
#include <string>

void client(){
    asio::error_code ec;
    asio::io_context context;
    asio::ip::tcp::endpoint endpoint(asio::ip::make_address("127.0.0.1",ec), 17235);
    asio::ip::tcp::socket socket(context);
    socket.connect(endpoint,ec);

    if(!ec){
        std::cout << "Connected\n";
    }else{
        std::cout << "Failed to connect to address\n" << ec.message() << "\n";
    }

    if(socket.is_open()){
        //char s_request[25] = "WAVSTART cowbell.wav 0 0";
        //char s_request[25] = {'W','A','V','S','T','A','R','T','\t','c','o','w','b','e','l','l','.','w','a','v','\t','0','\t','0','\0'};
        //char s_request[26] = {'W','A','V','S','T','A','R','T',' ','c','o','w','b','e','l','l','.','w','a','v',' ','0',' ','0','\0'};
        std::string s_request = "WAVSTART cowbell.wav 0 0";
        //char s_request[10] = "WAVSTART ";
        socket.write_some(asio::buffer(s_request.data(),25),ec);
        //socket.write_some(asio::buffer(s_request, strlen(s_request)),ec);

        size_t bytes = socket.available();
        std::cout << "Bytes Available: " << bytes << "\n";
    }
}
