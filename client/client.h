#pragma once

#include <cstdlib>
#include <deque>
#include <iostream>
#include <thread>
#include <asio.hpp>
#include "../common/chat_message.h"

using asio::ip::tcp;

typedef std::deque<chat_message> chat_message_queue;

class chat_client{



private:
    asio::io_context& io_context_;
    tcp::socket socket_;
    chat_message read_msg_;
    chat_message_queue write_msgs_;
};

