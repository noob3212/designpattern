#include "specification.hpp"
#include <vector>
template <typename  T>
struct Filter{
    virtual std::vector<T*> filter(std::vector<T*> items,Specification<T> &spec) =0;

};