#include <iostream>
class Rectangle{
    protected:
    int width,height;
    public:
    Rectangle(const int width,const int height): width(width),height(height){}

    int get_width() const {return width;}
    virtual void set_width(const int width) {this->width = width;}
    int get_height() const {return height;}
    virtual void set_height(const int height) { this->height = height;}
    int area() const {return width*height;}
};

class Square : public Rectangle{
    public:
    Square(int size):Rectangle(size, size) {}
    void set_width(const int width) override {
        this->width = height = width;
    }
    void set_height(const int height) override {
        this->height = width = height;
    }
};

void process(Rectangle &r){
    int w = r.get_width();
    r.set_height(10);
    std::cout << "expected area = " << (w*10) << ", got" << r.area() << std::endl;
}

int main(){
    Square s{5};
    process(s); // expected area = 50 got 25
    /**
     * process breaks ths lsp by being throughly unable to take
     * a derived type Square instead of type Rectangle. 
     * 
     *Solution is factory method
     *
     * struct RectangleFactory{ static Rectangle create_rectangle(int w,int h);
     *  static Rectangle create_square(int size);}
     */
}