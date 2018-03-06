#include <iostream>
#include <string>

#include "Typelist.h"

template <typename TList, template <typename> class Unit>
class GenScatterHierarchy;

template <typename T1, typename T2, template <typename> class Unit>
class GenScatterHierarchy<Typelist<T1, T2>, Unit>
    : public GenScatterHierarchy<T1, Unit>
    , public GenScatterHierarchy<T2, Unit> {
};

template <typename AtomicType, template <typename> class Unit>
class GenScatterHierarchy: public Unit<AtomicType> {
};

template <template <typename> class Unit>
class GenScatterHierarchy<NullType, Unit> {
};

template <typename T, typename TList, template <typename> class Unit>
Unit<T> &Field(GenScatterHierarchy<TList, Unit> &obj)
{
    return obj;
}

template <typename T>
struct Holder {
    T value_;
};

// typedef GenScatterHierarchy<TYPELIST_3(std::string, double, std::string), Holder> TestInfo;
// 当出现多个相同型别时, 会有二义性问题
typedef GenScatterHierarchy<TYPELIST_3(int, double, std::string), Holder> TestInfo;

int main(int argc, char *argv[])
{
    TestInfo obj;
    Field<std::string>(obj).value_ = "hello world";
    std::string name = Field<std::string>(obj).value_;
    std::cout << name << std::endl;
    return 0;
}
