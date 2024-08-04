#include <iostream>
#include <string>
#include <map>
#include <sstream>

// 표현식 인터페이스
class Expression {
public:
    virtual int interpret(const std::map<std::string, int>& context) const = 0;
    virtual ~Expression() = default;
};

// 변수 표현식
class VariableExpression : public Expression {
private:
    std::string name_;

public:
    explicit VariableExpression(std::string name) : name_(std::move(name)) {}

    int interpret(const std::map<std::string, int>& context) const override {
        auto it = context.find(name_);
        if (it != context.end()) {
            return it->second;
        }
        throw std::runtime_error("Variable not found");
    }
};

// 숫자 표현식
class NumberExpression : public Expression {
private:
    int number_;

public:
    explicit NumberExpression(int number) : number_(number) {}

    int interpret(const std::map<std::string, int>& context) const override {
        return number_;
    }
};

// 덧셈 표현식
class AddExpression : public Expression {
private:
    std::shared_ptr<Expression> left_;
    std::shared_ptr<Expression> right_;

public:
    AddExpression(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right)
        : left_(std::move(left)), right_(std::move(right)) {}

    int interpret(const std::map<std::string, int>& context) const override {
        return left_->interpret(context) + right_->interpret(context);
    }
};

// 해석기 사용 예제
int main() {
    std::map<std::string, int> context = { {"x", 10}, {"y", 20} };

    std::shared_ptr<Expression> expr1 = std::make_shared<AddExpression>(
        std::make_shared<VariableExpression>("x"),
        std::make_shared<NumberExpression>(5)
    );

    std::shared_ptr<Expression> expr2 = std::make_shared<AddExpression>(
        expr1,
        std::make_shared<VariableExpression>("y")
    );

    std::cout << "Result: " << expr2->interpret(context) << std::endl;

    return 0;
}
