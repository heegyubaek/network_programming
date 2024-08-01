#include <iostream>

// 기본 컴포넌트
class Component {
public:
    virtual void operation() = 0;
    virtual ~Component() = default;
};

// 구체적인 컴포넌트
class ConcreteComponent : public Component {
public:
    void operation() override {
        std::cout << "ConcreteComponent operation" << std::endl;
    }
};

// 데코레이터 기본 클래스
class Decorator : public Component {
protected:
    Component* component;
public:
    Decorator(Component* comp) : component(comp) {}
    void operation() override {
        if (component) {
            component->operation();
        }
    }
};

// 구체적인 데코레이터
class ConcreteDecoratorA : public Decorator {
public:
    ConcreteDecoratorA(Component* comp) : Decorator(comp) {}
    void operation() override {
        Decorator::operation();
        std::cout << "ConcreteDecoratorA operation" << std::endl;
    }
};

class ConcreteDecoratorB : public Decorator {
public:
    ConcreteDecoratorB(Component* comp) : Decorator(comp) {}
    void operation() override {
        Decorator::operation();
        std::cout << "ConcreteDecoratorB operation" << std::endl;
    }
};

int main() {
    Component* component = new ConcreteComponent();
    Component* decoratorA = new ConcreteDecoratorA(component);
    Component* decoratorB = new ConcreteDecoratorB(decoratorA);

    decoratorB->operation();

    delete component;
    delete decoratorA;
    delete decoratorB;

    return 0;
}
