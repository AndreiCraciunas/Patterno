#include <catch2/catch.hpp>
#include <Patterno/singleton.hpp>

struct Object {
    Object(std::string&& ss, int ii) :
        s{ std::move(ss) },
        i{ ii }
    {}

    Object(std::string&& ss) :
        s{ std::move(ss) }
    {}

    std::string s{ "" };
    int i{ 0 };
};

TEST_CASE(
    "GIVEN" 
    "multiple objects of the same class as template arguments for the singleton template,"
    "THEN"
    "calling different constructors will result in different objects while calling the same constructor"
    "will fetch the originally created object") {

    auto& instance1 = pat::Singleton<Object, std::string, int>::GetInstance("some", 30);
    auto& instance2 = pat::Singleton<Object, std::string, int>::GetInstance("some", 30);
    auto& instance3 = pat::Singleton<Object, std::string>::GetInstance("some");

    REQUIRE(&instance1 == &instance2);
    REQUIRE(&instance1 != &instance3);
}