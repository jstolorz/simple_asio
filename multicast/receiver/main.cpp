#include <array>
#include <iostream>
#include <string>
#include <asio.hpp>

constexpr short multicast_port = 30001;

class receiver {
public:
    receiver(asio::io_context& io_context,
             const asio::ip::address& listen_address,
             const asio::ip::address& multicast_address)
            : socket_(io_context) {
        // Create the socket so that multiple may be bound to the same address.
        asio::ip::udp::endpoint listen_endpoint(listen_address, multicast_port);
        socket_.open(listen_endpoint.protocol());
        socket_.set_option(asio::ip::udp::socket::reuse_address(true));
        socket_.bind(listen_endpoint);

        // Join the multicast group.
        socket_.set_option(asio::ip::multicast::join_group(multicast_address));

        do_receive();

    }


private:

    void do_receive() {
        socket_.async_receive_from(
                asio::buffer(data_), sender_endpoint_,
                [this](asio::error_code ec, std::size_t length) {
                     if(!ec){
                         std::cout.write(data_.data(),length);
                         std::cout << "\n";

                         do_receive();
                     }
                }
        );
    }

private:
    asio::ip::udp::socket socket_;
    asio::ip::udp::endpoint sender_endpoint_;
    std::array<char, 1024> data_;
};

int main() {
    try{
        asio::io_context io_context;
        receiver r(io_context,
                   asio::ip::make_address("127.0.0.1"),
                   asio::ip::make_address("127.0.0.1"));
        io_context.run();

    }catch (std::exception& ex){
        std::cerr << "Exception " << ex.what() << "\n";
    }


    return 0;
}
