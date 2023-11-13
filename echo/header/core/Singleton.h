#ifndef __SINGLETON_H__
#define __SINGLETON_H__

namespace openge {
    // Implementação da classe Singleton
    template<typename T>
    class Singleton {
    public:
        static T& getInstance() {
            static T instance;
            return instance;
        }

    protected:
        Singleton() = default;
        ~Singleton() = default;

        Singleton(const Singleton&) = delete;
        Singleton& operator=(const Singleton&) = delete;
    };
}
#endif // !__SINGLETON_H__