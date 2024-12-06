#include <boost/signals2/signal_type.hpp>
#include <boost/signals2/variadic_signal.hpp>
#include <iostream>
#include <vector>
#include <boost/signals2.hpp>

struct Person;
template <typename  T>
struct Observer {
    /**
     * @brief 
     * why source  is used , from where it is trigger.
     * @param source : Name of source.
     * @param name : name of field
     */
    virtual void field_change(T& source ,const std::string &name) = 0;
};

template <typename T>
struct Observable{
    
 boost::signals2::signal<void(T&source,const std::string&name)> property_changed;   

};

struct Person: Observable<Person>{
    void set_age(const int &age){
        if (this->age == age) return;
        this->age = age;
        // similar to  emit property_changed 
        property_changed(*this,"age");
    }
    int  get_age(){
        return age;
    }
    Person (const int &age):age(age) {}
    private:
    int age;

};

struct ConsolePersonObserver : Observer<Person>{
    void field_change(Person &source , const std::string & name ){
        std::cout << "Person field name" << name  << "changed to "<< source.get_age() << std::endl;
    }

};


int main(){
    Person p{20};
    auto conn = p.property_changed.connect(
        [](Person &obj,const std::string &name){std::cout <<"Person field "<< name << " changed "<<obj.get_age();});
    p.set_age(21);
}