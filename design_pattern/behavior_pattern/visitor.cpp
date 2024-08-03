#include <iostream>

class Visitor;

class Element {
public:
    virtual void accept(Visitor& visitor) const = 0;
    virtual ~Element() = default;
};

class ConcreteElementA : public Element {
public:
    void accept(Visitor& visitor) const override;
    void operationA() const {
        std::cout << "ConcreteElementA operationA" << std::endl;
    }
};

class ConcreteElementB : public Element {
public:
    void accept(Visitor& visitor) const override;
    void operationB() const {
        std::cout << "ConcreteElementB operationB" << std::endl;
    }
};

class Visitor {
public:
    virtual void visit(const ConcreteElementA& element) = 0;
    virtual void visit(const ConcreteElementB& element) = 0;
    virtual ~Visitor() = default;
};

class ConcreteVisitor1 : public Visitor {
public:
    void visit(const ConcreteElementA& element) override {
        element.operationA();
    }
    void visit(const ConcreteElementB& element) override {
        element.operationB();
    }
};

void ConcreteElementA::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

void ConcreteElementB::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

int main() {
    ConcreteElementA elementA;
    ConcreteElementB elementB;
    ConcreteVisitor1 visitor;

    elementA.accept(visitor);
    elementB.accept(visitor);

    return 0;
}
