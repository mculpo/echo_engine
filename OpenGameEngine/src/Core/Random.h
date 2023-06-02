#ifndef __RANDOM_H__
#define __RANDOM_H__

#include <Core/tspch.h>
#include <Core/Singleton.h>

namespace openge {
    class Random : public Singleton<Random> {
    private:
        std::random_device rd;
        std::mt19937 gen;

    public:
        Random() : gen(rd()) {}

        int Range(int min, int max) {
            std::uniform_int_distribution<int> distribution(min, max);
            return distribution(gen);
        }

        float Range(float min, float max) {
            std::uniform_real_distribution<float> distribution(min, max);
            return distribution(gen);
        }
    };
}

#endif // __RANDOM_H__

