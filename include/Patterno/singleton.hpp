#include <utility>

namespace pat {

    template <typename UnderlyingType, typename ... Args>
    struct Singleton {
        Singleton() = delete;
        Singleton(const Singleton &&) = delete;
        Singleton(Singleton &&) = delete;

        [[nodiscard]] static UnderlyingType&
        GetInstance(Args && ... args) noexcept {
            static UnderlyingType object(std::forward<Args>(args)...);
            return object;
        }
    };

}