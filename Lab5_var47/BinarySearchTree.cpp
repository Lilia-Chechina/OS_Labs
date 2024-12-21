#include <zmq.hpp>
#include <queue>
class BinarySearchTree
{
private:
    int id_key;
    zmq::socket_t* socket;
    BinarySearchTree *left;
    BinarySearchTree *right;
    bool isKilled = false;

public:
    BinarySearchTree(int id_key)
    {
        this->id_key = id_key; 
        socket = nullptr;
        left = nullptr;
        right = nullptr;
    }

    zmq::socket_t* getSocket()
    {
        return socket;
    }

    BinarySearchTree *getLeft()
    {
        return left;
    }

    BinarySearchTree *getRight()
    {
        return right;
    }

    void setSocket(zmq::socket_t* socket)
    {
        this->socket = socket;
    }

    void setLeft(BinarySearchTree *left)
    {
        this->left = left;
    }

    void setRight(BinarySearchTree *right)
    {
        this->right = right;
    }

    ~BinarySearchTree()
    {
        if(socket != nullptr)
        {
            delete socket;
            socket = nullptr;
        }
        if (left != nullptr) {
            delete left;
            left = nullptr;
        }
        if (right != nullptr) {
            delete right;
            right = nullptr;
        }
    }

    void Insert(int data, zmq::socket_t* socket)
    {
        if (data < this->id_key) {
            if (left == nullptr) {
                left = new BinarySearchTree(data);
                left->setSocket(socket);
            } else {
                left->Insert(data, socket);
            }
        } else if (data > this->id_key) {
            if (right == nullptr) {
                right = new BinarySearchTree(data);
                right->setSocket(socket);
            } else {
                right->Insert(data, socket);
            }
        }
    }

    zmq::socket_t* Search(int id)
    {
        if (id == this->id_key && !isKilled) {
            return socket;
        } else if (id < this->id_key) {
            if (left == nullptr) {
                return nullptr;
            } else {
                return left->Search(id);
            }
        } else if (id > this->id_key) {
            if (right == nullptr) {
                return nullptr;
            } else {
                return right->Search(id);
            }
        }
        return nullptr;
    }

    void Kill(int id)
    {
        if (id < this->id_key) {
            if (left != nullptr) {
                left->Kill(id);
            }
        } else if (id > this->id_key) {
            if (right != nullptr) {
                right->Kill(id);
            }
        } else {
            if (left == nullptr && right == nullptr) {
                this->isKilled = true;
            } else if (left == nullptr) {
                BinarySearchTree* temp = right;
                this->isKilled = true;
                return;
            } else if (right == nullptr) {
                BinarySearchTree* temp = left;
                this->isKilled = true;
                return;
            } else {
                BinarySearchTree* temp = right;
                while (temp->left != nullptr) {
                    temp = temp->left;
                }
                this->id_key = temp->id_key;
                right->Kill(temp->id_key);
            }
        }
    }

    void InOrderTraversal(BinarySearchTree* tree, zmq::message_t& message)
    {
        if(tree != nullptr)
        {
            InOrderTraversal(tree->left, message);
            tree->socket->send(message, zmq::send_flags::none);
            InOrderTraversal(tree->right, message);
        }
    }

    std::queue<std::string> messageQueue;
    bool traversalDone = false;
    void InOrderTraversalPingall(BinarySearchTree* tree)
    {
        if(tree != nullptr)
        {
            InOrderTraversalPingall(tree->left);
            
            if(tree->isKilled)
            {
                messageQueue.emplace(std::to_string(tree->id_key));
            }
            InOrderTraversalPingall(tree->right);
        }
        else
        {
            traversalDone = true;
        }
    }
};
