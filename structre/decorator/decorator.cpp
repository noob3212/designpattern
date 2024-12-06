/**
 * @file decorator.cpp
 * @author your name (you@domain.com)
 * @brief dynamic decroator.cpp
 * @version 0.1
 * @date 2024-12-06
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <cstdint>
#include <iostream>
#include <sstream>
#define pi 3.14
struct Shape{

    virtual std::string str() const = 0;
    virtual ~Shape() =default;
};


struct Circle : Shape {
    // explicit to stop conversion operation.
    explicit Circle(const float &radius) : radius{radius} {}
    float area() {
        return pi * radius * radius; 
    }
    std::string str() const override{
        std::ostringstream oss;
        oss << "Circle with radius " << radius;
        return  oss.str();
    }
    float radius;
};

struct ColorShape: Shape{
    Shape &shape;
    std::string color;
    ColorShape(Shape &shape,const std::string &color):shape{shape},color(color) {}
    std::string str() const override{
        std::ostringstream oss;
        oss << shape.str() << " has the color "<< color;
        return  oss.str();
    }

};

struct TransparentShape: Shape{
    Shape &shape;
    uint8_t transparency;
    TransparentShape(Shape &shape,uint8_t transparency):shape{shape},transparency{transparency} {}
    std::string str() const override{
        std::ostringstream oss;
        oss << shape.str() << " has the transparency "<< static_cast<float>(transparency)/255.f*100.f << "% transparency";
        return  oss.str();
    }

};


int main(){
    Circle circle{23};
    ColorShape coloredCircle{circle, "green"};
    TransparentShape myCircle{coloredCircle, 64};

    std::cout << myCircle.str() << std::endl;


    /**
     * @brief 
     * this cannnot be used 
     * because
     * Problem: The temporary objects ColorShape and Circle are destroyed at the end of the initializer list, leaving TransparentShape with dangling references.
     * Solution: To avoid this issue while storing by reference, you must use named variables (as shown above) to ensure the objects persist.
     * TransparentShape myCircle{ ColorShape{ Circle {23},"green" },64}; 
     */
    

}