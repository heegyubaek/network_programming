#include <iostream>

class Singleton {
private:
    static Singleton* instance;
    Singleton() {} // 생성자를 private으로

public:
    static Singleton* getInstance() {
        if (instance == nullptr) {
            instance = new Singleton();
        }
        return instance;
    }
};

// Singleton의 인스턴스 포인터 초기화
Singleton* Singleton::instance = nullptr;

int main() {
    Singleton* s1 = Singleton::getInstance();
    Singleton* s2 = Singleton::getInstance();

    if (s1 == s2) {
        std::cout << "s1과 s2는 동일한 인스턴스입니다." << std::endl;
    }

    return 0;
}
