#pragma once

#include <asio.hpp>
#include <array>
#include <string>
#include <iostream>

using namespace asio;
using namespace asio::ip;

io_service ioservice;
tcp::resolver resolv{ioservice};
tcp::socket tcp_socket{ioservice};
std::array<char, 4096> bytes;

void read_handler(const asio::error_code& ec, std::size_t bytes_transferred){
   if(!ec){
       std::cout.write(bytes.data(), bytes_transferred);
       tcp_socket.async_read_some(buffer(bytes),read_handler);
   }
}

void connect_handler(const asio::error_code& ec){
    if(!ec){
        std::string str =  "GET / HTTP/1.1\r\nHost: theboostcpplibraries.com\r\n\r\n";
        write(tcp_socket, buffer(str));
        tcp_socket.async_read_some(buffer(bytes),read_handler);
    }
}

void resolve_handler(const asio::error_code& ec, tcp::resolver::iterator it) {
    if(!ec){
        tcp_socket.async_connect(*it, connect_handler);
    }
}

int run_example() {

    tcp::resolver::query q{"theboostcpplibraries.com", "80"};
    resolv.async_resolve(q, resolve_handler);
    ioservice.run();


    return 0;
}