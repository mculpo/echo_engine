#ifndef __RANDOM_H__
#define __RANDOM_H__

#include <core/core.h>

namespace openge {
    class Random {
    private:
        static std::random_device rd;
        static std::mt19937 gen;

    public:

        static void setSeed(unsigned int seed) {
            gen.seed(seed);
        }

        static int Range(int min, int max) {
            std::uniform_int_distribution<int> distribution(min, max);
            return distribution(gen);
        }

        static float Range(float min, float max) {
            std::uniform_real_distribution<float> distribution(min, max);
            return distribution(gen);
        }
    };

    // Inicializar as variáveis estáticas fora da definição da classe
    std::random_device Random::rd;
    std::mt19937 Random::gen(Random::rd());
}

#endif // __RANDOM_H__

