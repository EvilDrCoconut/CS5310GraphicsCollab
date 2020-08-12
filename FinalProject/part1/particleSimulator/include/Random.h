//
// Created by Evil Dr Coconut on 8/10/2020.
//

#ifndef LUKE_S_PARTICLE_SIM_RANDOM_H
#define LUKE_S_PARTICLE_SIM_RANDOM_H

# include <random>

class Random
{
public:
    static void Init()
    {
        randomEngine.seed(std::random_device()());
    }

    static float Float()
    {
        return (float)distribution(randomEngine) / (float)std::numeric_limits<uint32_t>::max();
    }

private:
    static std::mt19937 randomEngine;
    static std::uniform_int_distribution<std::mt19937::result_type> distribution;
};


#endif //LUKE_S_PARTICLE_SIM_RANDOM_H
