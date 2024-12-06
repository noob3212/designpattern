#include <iostream>
#include <mutex>
#include <vector>

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
    
    void notify(T &source ,const std::string &name){
        std::scoped_lock<std::mutex> lock(mtx);
        for (auto &x : observers){
            x->field_change(source,name);
        }

    }
    void subscribe(Observer<T> * obj){
        std::scoped_lock<std::mutex> lock(mtx);
        observers.push_back(obj);

    }
    void unsubsribe(Observer<T> *obj){
        std::scoped_lock<std::mutex> lock(mtx);
        erase(std::remove(observers.begin(),observers.end(),obj),observers.end());
    }

    private:
    std::vector<Observer<T>*> observers;
    std::mutex mtx;

};

struct Person: Observable<Person>{
    void set_age(const int &age){
        if (this->age == age) return;
        this->age = age;
        notify(*this,"age");
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

}





