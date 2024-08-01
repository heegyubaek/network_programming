#include <iostream>
#include <string>

// 기존 인터페이스
class OldInterface {
public:
    void specificRequest() {
        std::cout << "Specific request" << std::endl;
    }
};

// 새로운 인터페이스
class NewInterface {
public:
    virtual void request() = 0;
};

// 어댑터 클래스
class Adapter : public NewInterface {
private:
    OldInterface* oldInterface;
public:
    Adapter(OldInterface* oi) : oldInterface(oi) {}
    void request() override {
        oldInterface->specificRequest();
    }
};

int main() {
    OldInterface* old = new OldInterface();
    NewInterface* adapter = new Adapter(old);
    adapter->request();

    delete old;
    delete adapter;
    return 0;
}
