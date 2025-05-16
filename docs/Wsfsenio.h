#include <iostream>
#include <string>

class IMessageReceiver {
public:
    virtual ~IMessageReceiver() = default;
    virtual void receive(const std::string& msg) = 0;
};

class Sender {
public:
    // 设置默认接收者
    void setDefaultReceiver(IMessageReceiver* receiver) {
        defaultReceiver_ = receiver;
    }
    
    // 向默认接收者发送
    void send(const std::string& msg) {
        if(defaultReceiver_) {
            defaultReceiver_->receive(msg);
        }
    }
    
    // 向指定接收者发送
    void send(IMessageReceiver* receiver, const std::string& msg) {
        if(receiver) {
            receiver->receive(msg);
        }
    }

private:
    IMessageReceiver* defaultReceiver_ = nullptr;
};

class Receiver : public IMessageReceiver {
public:
    void receive(const std::string& msg) override {
        std::cout << "Received: " << msg << std::endl;
    }
};

int main() {
    Sender sender;
    Receiver receiver1, receiver2;
    
    // 设置默认接收者
    sender.setDefaultReceiver(&receiver1);
    sender.send("Hello to default receiver");
    
    // 向指定接收者发送
    sender.send(&receiver2, "Hello to specific receiver");
    
    return 0;
}