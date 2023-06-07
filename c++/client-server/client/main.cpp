//
//  main.cpp
//  client
//
//  Created by Scott Gustafson on 7/1/16.
//  Copyright © 2016 Garlic Software LLC. All rights reserved.
//

// Simple networking code is adapted from the asio sample code for the simple echo tcp client and server code.
// blocking_tcp_echo_client.cpp

// I'm using ASIO as a standalone module and probably compiling under a modern version of g++
#define ASIO_STANDALONE

#include <iostream>
#include "asio.hpp"
#include "config.h"

using asio::ip::tcp;

int main(int argc, char* argv[]) {
	try {
		if (argc != 3){
			std::cerr << "Usage: client <host> value" << std::endl;
			return 1;
		}
		
		asio::io_service io_service;
		
		tcp::socket s(io_service);
		tcp::resolver resolver(io_service);
		asio::connect(s, resolver.resolve({argv[1], port_number.c_str()}));
		
		size_t request_length = std::strlen(argv[2]);
		asio::write(s, asio::buffer(argv[2], request_length));
		
		char reply[1];
		size_t reply_length = asio::read(s, asio::buffer(reply, 1));
		std::cout.write(reply, reply_length);
		std::cout << std::endl;
	}
	catch (std::exception& e) {
		std::cerr << "Exception: " << e.what() << "\n";
	}
	
	return 0;
}
