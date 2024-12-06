#include <iostream>
#include <string>
#include <utility>

struct PersonBuilderBase;
class PersonBuilder;
struct Person {
    // Address
    std::string street_address, post_code, city;

    // Employment
    std::string company_name, poistion;
    int annual_income = 0;

    static PersonBuilder build();
    Person() {}
};

struct PersonAddressBuilder;
struct PersonJobBuilder;

struct PersonBuilderBase {
protected:
    Person& person;

    explicit PersonBuilderBase(Person& person) : person(person) {}

public:
    operator Person() {
        return std::move(person);
    }

    // Builder facets
    PersonAddressBuilder lives();
    PersonJobBuilder works();
};

class PersonBuilder : public PersonBuilderBase {
    Person p;

public:
    PersonBuilder() : PersonBuilderBase(p) {}
};

struct PersonAddressBuilder : public PersonBuilderBase {
    typedef PersonAddressBuilder self;

public:
    explicit PersonAddressBuilder(Person& person) : PersonBuilderBase(person) {}

    self& at(const std::string& street_address) {
        person.street_address = street_address;
        return *this;
    }

    self& with_postcode(const std::string& postcode) {
        person.post_code = postcode;
        return *this;
    }

    self& in(const std::string& city) {
        person.city = city;
        return *this;
    }
};

struct PersonJobBuilder : public PersonBuilderBase {
    typedef PersonJobBuilder self;

public:
    explicit PersonJobBuilder(Person& person) : PersonBuilderBase(person) {}

    self& company_name(const std::string& company_name) {
        person.company_name = company_name;
        return *this;
    }

    self& poistion(const std::string& poistion) {
        person.poistion = poistion;
        return *this;
    }
};

// Define `lives` and `works` methods
PersonAddressBuilder PersonBuilderBase::lives() {
    return PersonAddressBuilder(person);
}

PersonJobBuilder PersonBuilderBase::works() {
    return PersonJobBuilder(person);
}

PersonBuilder Person::build() {
    return PersonBuilder();
}

int main() {
    Person p = Person::build().lives().at("123 Main Street").with_postcode("12345").in("Metropolis");
    std::cout << "Address: " << p.street_address << ", " << p.post_code << ", " << p.city << std::endl;

    return 0;
}

