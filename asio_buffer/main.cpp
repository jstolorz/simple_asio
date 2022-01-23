#include <asio.hpp>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>
#include <ctime>
#include <string>

using asio::ip::tcp;

class shared_const_buffer{
public:
   explicit shared_const_buffer(const std::string& data)
   : data_(new std::vector<char>(data.begin(),data.end())),
     buffer_(asio::buffer(*data_))
   {}

   // Implement the ConstBufferSequence requirements.
   typedef asio::const_buffer value_type;
   typedef const asio::const_buffer* const_iterator;

    const asio::const_buffer* begin() const {return &buffer_;}
    const asio::const_buffer* end() const {return &buffer_ + 1;}

private:
   std::shared_ptr<std::vector<char>> data_;
   asio::const_buffer buffer_;

};

class session : std::enable_shared_from_this<session>{
public:
    session(tcp::socket socket)
    : socket_(std::move(socket))
    {}

    void start(){
        do_write();
    }

private:

    void do_write() {
         std::time_t now = std::time(0);
         shared_const_buffer buffer(std::ctime(&now));

         //Ma to na celu upewnienie się, że obiekt połączenia
         // przetrwa operację asynchroniczną: dopóki lambda jest aktywne
         // (tj. operacja asynchroniczna jest w toku),
         // instancja połączenia również jest aktywna.
         auto self(shared_from_this());

         asio::async_write(socket_, buffer,
                           [self](std::error_code, std::size_t){});
    }

    tcp::socket socket_;
};

class server{

public:

    server(asio::io_context& io_context, short port)
    : acceptor_(io_context,tcp::endpoint(tcp::v4(),port))
    {
        do_accept();
    }

private:

     void do_accept() {
        acceptor_.async_accept(
                [this](std::error_code ec, tcp::socket socket){
            if(!ec){
                std::make_shared<session>(std::move(socket))->start();
            }
            do_accept();
        });
    }

    tcp::acceptor acceptor_;
};

int main(){

    try{
        asio::io_context io_context;

        server s(io_context, 90000);

        io_context.run();

    }catch (std::exception& e){
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}