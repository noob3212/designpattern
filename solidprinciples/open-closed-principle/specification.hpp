/**
 * @brief 
 * From product.cpp we understand that
 * when we are adding and filtering mechanism that
 * is based on both by size and color
 * We are breaking srp(single responsibility principle)
 * and also we want to force open-close priniciple
 * that is classes should be open for extension
 * but close for modification.
 */
template <typename T>
struct Specification{
    virtual bool is_satisified(T *item) = 0;
};

template<typename T>
struct AndSpecification:Specification<T>{
    Specification<T> &first;
    Specification<T> &second;

    AndSpecification(Specification<T> &first, Specification<T> &second):first(first),second(second) {}

    bool is_satisified(T *item) override {
        return first.is_satisified(item) && second.is_satisified(item);
    }

};