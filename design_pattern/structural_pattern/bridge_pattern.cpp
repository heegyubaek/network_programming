#include <iostream>

// 구현 클래스 계층 구조
class Implementor {
public:
    virtual void operationImpl() = 0;
};

class ConcreteImplementorA : public Implementor {
public:
    void operationImpl() override {
        std::cout << "Implementation A" << std::endl;
    }
};

class ConcreteImplementorB : public Implementor {
public:
    void operationImpl() override {
        std::cout << "Implementation B" << std::endl;
    }
};

// 추상화 클래스 계층 구조
class Abstraction {
protected:
    Implementor* implementor;
public:
    Abstraction(Implementor* impl) : implementor(impl) {}
    virtual void operation() = 0;
};

class RefinedAbstraction : public Abstraction {
public:
    RefinedAbstraction(Implementor* impl) : Abstraction(impl) {}
    void operation() override {
        implementor->operationImpl();
    }
};

int main() {
    Implementor* implA = new ConcreteImplementorA();
    Implementor* implB = new ConcreteImplementorB();

    Abstraction* abs1 = new RefinedAbstraction(implA);
    Abstraction* abs2 = new RefinedAbstraction(implB);

    abs1->operation();
    abs2->operation();

    delete implA;
    delete implB;
    delete abs1;
    delete abs2;

    return 0;
}
