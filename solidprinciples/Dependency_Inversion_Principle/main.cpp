/*#include <iostream>
#include <memory>
#include <ostream>
#include "di.hpp"

struct Engine{
    float volume =5;
    int horse_power = 400;

    friend std::ostream& operator << (std::ostream &os,Engine &obj){
        
        return os
               << "volume:" << obj.volume
               << "horse_pwer:" << obj.horse_power;
    }
};

struct ILogger {
    virtual ~ILogger(){}
    virtual void Log(const std::string &s)=0;
 
};

struct ConsoleLogger : ILogger{
    ConsoleLogger() {}
    void Log(const std::string &s) override{
        std::cout << "LOG:" << s.c_str() << std::endl;
    }

};

struct Car{
    std::unique_ptr<Engine> engine;
    std::shared_ptr<ILogger> logger;

    Car(std::unique_ptr<Engine> engine,
        const std::shared_ptr<ILogger>& logger):
        engine{std::move(engine)},logger{logger}{
            logger->Log("making a car");
        }
    
    friend std::ostream& operator <<(std::ostream &os, Car &obj){
        return os<< "car with engine:" << *obj.engine;
    }


};

int main(){
    
    auto injector = boost::di::make_injector(boost::di::bind<ILogger>().to<ConsoleLogger>());
    auto car = injector.create<std::shared_ptr<Car>>();
}

*/


// Simple example 

// Without dependency inversion principle . 


/*

#include <iostream>
#include <string>

// Low-level module
class CreditCardService {
public:
    void processPayment(const std::string& amount) {
        std::cout << "Processing credit card payment of " << amount << std::endl;
    }
};

// High-level module depends directly on low-level module
class PaymentProcessor {
public:
    void process(const std::string& amount) {
        creditCardService.processPayment(amount);
    }

private:
    CreditCardService creditCardService;
};

//without dip

int main() {
    PaymentProcessor processor;
    processor.process("100 USD");
    return 0;
}
*/


#include <iostream>
#include <string>
#include <memory>

// Abstraction (interface)
class IPaymentService {
public:
    virtual void processPayment(const std::string& amount) = 0;
    virtual ~IPaymentService() = default;
};

// Low-level module 1
class CreditCardService : public IPaymentService {
public:
    void processPayment(const std::string& amount) override {
        std::cout << "Processing credit card payment of " << amount << std::endl;
    }
};

// Low-level module 2
class PayPalService : public IPaymentService {
public:
    void processPayment(const std::string& amount) override {
        std::cout << "Processing PayPal payment of " << amount << std::endl;
    }
};

// High-level module depends on abstraction
class PaymentProcessor {
public:
    PaymentProcessor(std::shared_ptr<IPaymentService> service) : paymentService(service) {}

    void process(const std::string& amount) {
        paymentService->processPayment(amount);
    }

private:
    std::shared_ptr<IPaymentService> paymentService;
};

int main() {
    // Use CreditCardService
    auto creditCardService = std::make_shared<CreditCardService>();
    PaymentProcessor processor1(creditCardService);
    processor1.process("100 USD");

    // Switch to PayPalService
    auto payPalService = std::make_shared<PayPalService>();
    PaymentProcessor processor2(payPalService);
    processor2.process("200 USD");

    return 0;
}
