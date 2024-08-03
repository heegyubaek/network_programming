#include <iostream>
#include <vector>
#include <memory>

// 명령 인터페이스
class Command {
public:
    virtual void execute() const = 0;
    virtual ~Command() = default;
};

// 구체적인 명령
class ConcreteCommand : public Command {
private:
    std::string payload_;

public:
    explicit ConcreteCommand(std::string payload) : payload_(std::move(payload)) {}
    
    void execute() const override {
        std::cout << "Executing command with payload: " << payload_ << std::endl;
    }
};

// 호출자
class Invoker {
private:
    std::vector<std::unique_ptr<Command>> commands_;

public:
    void add_command(std::unique_ptr<Command> command) {
        commands_.push_back(std::move(command));
    }

    void execute_commands() {
        for (const auto& command : commands_) {
            command->execute();
        }
    }
};

int main() {
    Invoker invoker;
    invoker.add_command(std::make_unique<ConcreteCommand>("Payload 1"));
    invoker.add_command(std::make_unique<ConcreteCommand>("Payload 2"));
    
    invoker.execute_commands();
    
    return 0;
}
