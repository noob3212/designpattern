#include <vector>
#include "product.hpp"

struct ProductFilter{
    typedef std::vector<Product*> Items;
    Items by_color(Items items, Color color);
    Items by_color_and_size(Items items, Color color, Size size);
};

ProductFilter::Items ProductFilter::by_color(Items items, Color color){
    Items result;
    for(auto &i:items){
        if(i->color == color){
            result.push_back(i);
        }
    }
    return result;
}

/*
* Now we want to filter by both color and size
* We are 
*/ 

ProductFilter::Items ProductFilter::by_color_and_size(Items items, Color color,Size size){
    Items result;
    for(auto &i:items){
        if(i->color == color && i->size == size){
            result.push_back(i);
        }
    }
    return result;
}

