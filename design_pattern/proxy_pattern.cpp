#include <iostream>
#include <string>

// Subject 인터페이스 정의
class Subject {
public:
    virtual void request() = 0;
    virtual ~Subject() = default;
};

// RealSubject 클래스 정의
class RealSubject : public Subject {
public:
    void request() override {
        std::cout << "RealSubject: Handling request." << std::endl;
    }
};

// Proxy 클래스 정의
class Proxy : public Subject {
private:
    RealSubject* real_subject_;
    bool access_granted_;

    bool checkAccess() {
        // 실제로는 사용자 인증 등의 작업을 수행할 수 있습니다.
        std::cout << "Proxy: Checking access before firing a real request." << std::endl;
        return access_granted_;
    }

    void logAccess() {
        std::cout << "Proxy: Logging the time of request." << std::endl;
    }

public:
    Proxy(RealSubject* real_subject, bool access_granted) 
        : real_subject_(real_subject), access_granted_(access_granted) {}

    void request() override {
        if (checkAccess()) {
            real_subject_->request();
            logAccess();
        } else {
            std::cout << "Proxy: Access denied." << std::endl;
        }
    }

    ~Proxy() {
        delete real_subject_;
    }
};

// 클라이언트 코드
void clientCode(Subject* subject) {
    subject->request();
}

int main() {
    std::cout << "Client: Executing the client code with a real subject:\n";
    RealSubject* real_subject = new RealSubject();
    clientCode(real_subject);

    std::cout << "\nClient: Executing the same client code with a proxy:\n";
    Proxy* proxy = new Proxy(real_subject, true); // Access granted
    clientCode(proxy);

    Proxy* proxyDenied = new Proxy(new RealSubject(), false); // Access denied
    clientCode(proxyDenied);

    delete proxy;
    delete proxyDenied;

    return 0;
}
