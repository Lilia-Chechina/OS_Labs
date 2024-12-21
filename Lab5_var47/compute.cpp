#include <zmq.hpp>
#include "Stopwatch.cpp"
#include <iostream>
#include <sys/wait.h>

int main( int argc, char *argv[] ) {
    
    int currentId = atoi(argv[1]);
    zmq::context_t context(1);

    zmq::socket_t socket(context, zmq::socket_type::pair);
    if(currentId % 100 > 9)
    {
        socket.connect("tcp://localhost:55" + std::to_string(currentId));
    }
    else
    {
        std::string addr = "tcp://localhost:550" + std::to_string(currentId);
        socket.connect(addr);
    }
    

    Stopwatch sw;
    while(true)
    {
        zmq::message_t message;
        auto a = socket.recv(message, zmq::recv_flags::none);
        std::string msg = std::string(static_cast<char*>(message.data()), message.size());
        std::string sendMessage = "OK: " + std::to_string(currentId);
        if(msg.find("Start") != std::string::npos)
        {
            sw.Start();
            socket.send(zmq::buffer(sendMessage), zmq::send_flags::none);
            std::cout << "sendedMessage" << std::endl;
        }
        else if(msg.find("Stop") != std::string::npos)
        {
            sw.Stop();
            socket.send(zmq::buffer(sendMessage), zmq::send_flags::none);
        }
        else if(msg.find("Time") != std::string::npos)
        {
            sendMessage += " " + std::to_string(sw.Time());
            socket.send(zmq::buffer(sendMessage), zmq::send_flags::none);
        }
        
    }

    return 0;
}