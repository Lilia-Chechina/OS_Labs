#include <zmq.hpp>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <map>
#include <queue>
#include "BinarySearchTree.cpp"
int main() {
    
    zmq::context_t context(1);
    BinarySearchTree* tree = new BinarySearchTree(-1);

    int id{-1};
    std::string command_stroke, command, subcommand;
    
    while(true)
    {
        getline(std::cin, command_stroke);
        std::istringstream iss(command_stroke);
        
        iss >> command >> id >> subcommand;

        if (command == "Create") {

            if(id == -1)
            {
                std::cout << "Error: empty id" << std::endl;
                continue;
            }

            if(tree->Search(id))
            {
                std::cout << "Error: already exists" << std::endl;
            }
                
            pid_t pid = fork();
            if (pid == 0) {
                execl("./compute", "compute", std::to_string(id).c_str(), nullptr);
                exit(0);
            } 
            else if (pid > 0) {
                zmq::socket_t* newSocket = new zmq::socket_t(context, zmq::socket_type::pair);
                
                if(id % 100 > 9)
                {
                    newSocket->bind("tcp://*:55" + std::to_string(id));
                }
                else
                {
                    std::string addr = "tcp://*:550" + std::to_string(id);
                    newSocket->bind(addr);
                }
                tree->Insert(id, newSocket);
                std::cout << "OK: " << id << std::endl;
            }
        } 
        else if (command == "Exec") 
        {
            if(id == -1 || subcommand.empty())
            {
                std::cout << "Error: empty id or subcommand" << std::endl;
                continue;
            }
            auto socket = tree->Search(id);
            if(socket == nullptr)
            {
                std::cout << "Error: there is no such node" << std::endl;
            }
            zmq::message_t mes(10);
            memcpy(mes.data(), subcommand.c_str(), 10);
            socket->send(mes, zmq::send_flags::none);
            while(true)
            {
                auto a = socket->recv(mes, zmq::recv_flags::none);
                std::string str_mes = std::string(static_cast<char*>(mes.data()), mes.size());
                std::cout << str_mes << std::endl;
                if(!str_mes.empty())
                    break;
                sleep(1);
            }
        
        } 
        else if (command == "Kill") 
        {
        
            if(id == -1)
            {
                std::cout << "Error: empty id" << std::endl;
                continue;
            }
            auto socket = tree->Search(id);
            
            if(socket == nullptr)
            {
                std::cout << "Error: there is no such socket" << std::endl;
            }

            tree->Kill(id);
            socket->send(zmq::buffer("Stop"), zmq::send_flags::none);
            std::cout << "Killed: " << id << std::endl;
        
        } 
        else if(command == "Pingall")
        {
            tree->InOrderTraversalPingall(tree);
            std::queue<std::string> queue = tree->messageQueue;
            std::ostringstream stream;
            stream << "OK: ";
            if(queue.empty())
            {
                stream << "-1"; 
            }
            else
            {
                for(int i = 0; i < queue.size(); i++)
                {
                    stream << queue.front();
                    queue.pop();
                }
            }
            std::cout << stream.str() << std::endl;
        }


    }
 
    return 0;
}
