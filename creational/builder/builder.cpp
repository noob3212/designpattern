#include <iostream>
#include <vector>

struct HtmlBuilder;
struct HtmlElement{
    std::string name;
    std::string text;
    std::vector<HtmlElement> element;
    // static std::unique_ptr<HtmlBuilder> build(const std::string &root_name){
    //     return std::make_unique<HtmlBuilder>(root_name);
    // }

    static HtmlBuilder build(const std::string &root_name);


    std::string str(){
        std::string finalstring;
        finalstring+="<"+name+" "+ text+">"+'\n';
        for(auto &x: element){
            finalstring+="<"+x.name+" "+ x.text+">"+'\n';
        

        }
        finalstring+="<\\"+name+" "+text+">"+'\n';
        return finalstring;
    }

    HtmlElement()=default;

    HtmlElement(std::string &name, std::string &text):name(name),text(text) {}
    
};


struct HtmlBuilder{
    HtmlElement root;
    HtmlBuilder(std::string root_name) {root.name = root_name;}

    HtmlBuilder& add_child(std::string child_name,std::string text_name){
        HtmlElement e {child_name,text_name};
        root.element.emplace_back(e);
        return *this;

    }
    std::string str(){ return root.str();}
    operator HtmlElement() const { return  root;}

};

HtmlBuilder HtmlElement::build(const std::string &root_name){
    return HtmlBuilder(root_name);
}


int main(){
    HtmlElement e = HtmlElement::build("ul").add_child("li","Hello").add_child("li", "hi");
    std::cout << e.str(); 

}