// Our own dependency injection 

#include <iostream>
#include <memory>
#include <unordered_map>
#include <functional>
#include <string>
#include <typeindex>

// Interface
struct ILogger {
    virtual void log(const std::string& message) = 0;
    virtual ~ILogger() = default;
};

// Implementation
struct ConsoleLogger : ILogger {
    void log(const std::string& message) override {
        std::cout << "Log: " << message << std::endl;
    }
};

class DIContainer {
public:
    // Bind a type TInterface to a concrete implementation TImplementation
    template <typename TInterface, typename TImplementation>
    void bind() {
        creators[std::type_index(typeid(TInterface))] = []() {
            return std::make_shared<TImplementation>();
        };
    }

    // Bind a specific instance
    template <typename TInterface>
    void bind_instance(std::shared_ptr<TInterface> instance) {
        creators[std::type_index(typeid(TInterface))] = [instance]() { return instance; };
    }

    // Resolve a type and return the concrete instance
    template <typename TInterface>
    std::shared_ptr<TInterface> resolve() {
        auto it = creators.find(std::type_index(typeid(TInterface)));
        if (it != creators.end()) {
            return std::static_pointer_cast<TInterface>(it->second());
        }
        throw std::runtime_error("Type not bound to any implementation");
    }

private:
    std::unordered_map<std::type_index, std::function<std::shared_ptr<void>()>> creators;
};

int main() {
    DIContainer container;

    // Bind ILogger to ConsoleLogger
    container.bind<ILogger, ConsoleLogger>();

    // Resolve ILogger and use it
    auto logger = container.resolve<ILogger>();
    logger->log("Hello, Dependency Injection!");

    return 0;
}

/*
Benefits:

High-level modules (PaymentProcessor) depend only on the IPaymentService abstraction.
Low-level modules (CreditCardService, PayPalService) implement the abstraction.
New payment methods can be added without modifying PaymentProcessor.

Relation to Dependency Injection
DIP often works hand-in-hand with the Dependency Injection (DI) pattern.
In the second example, PaymentProcessor does not create its dependencies but receives them from an external source (via constructor injection).


Key Benefits of DIP
Reduced Coupling: High-level modules are not tied to specific implementations.
Flexibility: Easier to replace or add new low-level modules.
Testability: Mocks or stubs can be injected during testing.
Scalability: System design is open for extension and closed for modification (Open/Closed Principle).




*/