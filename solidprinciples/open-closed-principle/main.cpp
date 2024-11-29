#include <iostream>
#include "product.hpp"
#include "filter.hpp"

struct BetterFilter : Filter<Product>{
    std::vector<Product*> filter(std::vector<Product *> items,
    Specification<Product>& spec) override
    {
        std::vector<Product*> result;
        for(auto &p: items){
            if(spec.is_satisified(p))
            result.push_back(p);
        }
        return result;
    }


};

struct ColorSpecification:Specification<Product>{
    Color color;

    explicit ColorSpecification(const Color color):color(color){}
    bool is_satisified(Product *item) override {
        return item->color == color;
    }
};


struct SizeSpecification:Specification<Product>{
    Size size;
    explicit SizeSpecification(const Size size):size(size){}
    bool is_satisified(Product *item) override{
        return item->size == size;
    }
};

int main(){
    Product apple {"Apple", Color::Green, Size::Small};
    Product tree  {"Tree", Color::Green, Size::Large};
    Product house {"House",Color::Blue,Size::Large};
    std::vector<Product*> all {&apple,&tree,&house};
    BetterFilter bf;
    ColorSpecification green(Color::Green);

    auto green_things = bf.filter(all,green);
    for(auto &x : green_things){
        std::cout << x->name << "is green" << std::endl;
    }
    SizeSpecification large(Size::Large);
    AndSpecification<Product> green_and_large {large,green};
    auto big_and_green_things = bf.filter(all,green_and_large);

    for (auto &x:big_and_green_things){
        std::cout << x->name << "is large and gree" << std::endl;
    }

    /**
     * Now suppose we want this to work for two or more specification
     * template<typename T>  struct Specification{
     *  virtual bool is_satisified(T *item) = 0;
     *  AndSpefication<T> operator &&(Specification &&other){  
     *   return AndSpecification<T>(*this,other);
     *  }
     */
    
}