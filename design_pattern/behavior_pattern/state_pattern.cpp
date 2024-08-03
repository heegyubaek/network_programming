#include <iostream>
#include <memory>

class Context;

class State {
public:
    virtual void handle(Context& context) = 0;
    virtual ~State() = default;
};

class ConcreteStateA : public State {
public:
    void handle(Context& context) override;
};

class ConcreteStateB : public State {
public:
    void handle(Context& context) override;
};

class Context {
private:
    std::unique_ptr<State> state_;

public:
    explicit Context(std::unique_ptr<State> state) : state_(std::move(state)) {}

    void set_state(std::unique_ptr<State> state) {
        state_ = std::move(state);
    }

    void request() {
        state_->handle(*this);
    }
};

void ConcreteStateA::handle(Context& context) {
    std::cout << "ConcreteStateA handling request." << std::endl;
    context.set_state(std::make_unique<ConcreteStateB>());
}

void ConcreteStateB::handle(Context& context) {
    std::cout << "ConcreteStateB handling request." << std::endl;
    context.set_state(std::make_unique<ConcreteStateA>());
}

int main() {
    Context context(std::make_unique<ConcreteStateA>());
    context.request();
    context.request();
    context.request();
		context.request();
    context.request();


    return 0;
}
