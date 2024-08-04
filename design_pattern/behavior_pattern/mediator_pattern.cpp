#include <iostream>

class Colleague;

class Mediator {
public:
    virtual void notify(Colleague* sender, const std::string& event) = 0;
    virtual ~Mediator() = default;
};

class Colleague {
protected:
    Mediator* mediator_;
public:
    Colleague(Mediator* mediator) : mediator_(mediator) {}

    virtual void send(const std::string& message) = 0;
    virtual void receive(const std::string& message) = 0;
};

class ConcreteColleague1 : public Colleague {
public:
    ConcreteColleague1(Mediator* mediator) : Colleague(mediator) {}

    void send(const std::string& message) override {
        mediator_->notify(this, message);
    }

    void receive(const std::string& message) override {
        std::cout << "ConcreteColleague1 received: " << message << std::endl;
    }
};

class ConcreteColleague2 : public Colleague {
public:
    ConcreteColleague2(Mediator* mediator) : Colleague(mediator) {}

    void send(const std::string& message) override {
        mediator_->notify(this, message);
    }

    void receive(const std::string& message) override {
        std::cout << "ConcreteColleague2 received: " << message << std::endl;
    }
};

class ConcreteMediator : public Mediator {
private:
    ConcreteColleague1* colleague1_;
    ConcreteColleague2* colleague2_;

public:
    void setColleague1(ConcreteColleague1* colleague1) {
        colleague1_ = colleague1;
    }

    void setColleague2(ConcreteColleague2* colleague2) {
        colleague2_ = colleague2;
    }

    void notify(Colleague* sender, const std::string& event) override {
        if (sender == colleague1_) {
            colleague2_->receive(event);
        } else if (sender == colleague2_) {
            colleague1_->receive(event);
        }
    }
};

int main() {
    ConcreteMediator mediator;
    ConcreteColleague1 colleague1(&mediator);
    ConcreteColleague2 colleague2(&mediator);

    mediator.setColleague1(&colleague1);
    mediator.setColleague2(&colleague2);

    colleague1.send("Hello from Colleague1");
    colleague2.send("Hello from Colleague2");

    return 0;
}
