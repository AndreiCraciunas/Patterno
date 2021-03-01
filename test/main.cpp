#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "singleton.hpp"

TEST_CASE("singleton")
{
    struct Object {
        Object(std::string &&ss, int ii) :
        s{std::move(ss)},
        i{ii}
        {}

        Object(std::string &&ss) :
        s{std::move(ss)}
        {}

        std::string s {""};
        int i {0};
    };

    auto &instance1 = pat::Singleton<Object, std::string, int>::GetInstance("some", 30);
    auto &instance2 = pat::Singleton<Object, std::string, int>::GetInstance("some", 30);
    auto &instance3 = pat::Singleton<Object, std::string>::GetInstance("some");

    REQUIRE(&instance1 == &instance2);
    REQUIRE(&instance1 != &instance3);
}