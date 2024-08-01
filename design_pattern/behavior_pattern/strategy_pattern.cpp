#include <iostream>
#include <memory>

// 전략 인터페이스
class Strategy {
public:
    virtual void execute() const = 0;
    virtual ~Strategy() = default;
};

// 구체적인 전략 1
class ConcreteStrategyA : public Strategy {
public:
    void execute() const override {
        std::cout << "ConcreteStrategyA: 실행 중" << std::endl;
    }
};

// 구체적인 전략 2
class ConcreteStrategyB : public Strategy {
public:
    void execute() const override {
        std::cout << "ConcreteStrategyB: 실행 중" << std::endl;
    }
};

// 컨텍스트
class Context {
private:
    std::unique_ptr<Strategy> strategy_;

public:
    void set_strategy(std::unique_ptr<Strategy> strategy) {
        strategy_ = std::move(strategy);
    }

    void execute_strategy() const {
        strategy_->execute();
    }
};

int main() {
    Context context;

    context.set_strategy(std::make_unique<ConcreteStrategyA>());
    context.execute_strategy();

    context.set_strategy(std::make_unique<ConcreteStrategyB>());
    context.execute_strategy();

    return 0;
}
