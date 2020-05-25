#include <random>

template <class T>
void print_vector(const std::vector<T>& v) {
    for (T e : v) {
        std::cout << e << " ";
    }
    std::cout << std::endl;
}


template <class T>
T random(T i, T r) {
    std::random_device seeder;
    std::mt19937 rng(seeder());
    std::uniform_real_distribution<> gen(i, r);
    T x = gen(rng);

    return x;
}
