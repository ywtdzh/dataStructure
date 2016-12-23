//
// Created by claim on 16-12-20.
//

#include <vector>

using std::vector;

template<typename D, typename E>
struct K_V {
    D key;
    E value;

    K_V (D key, E value) : key(key), value(value) {}
};

template<typename D>
vector<K_V<D, int>> createIndex (vector<D> source) {
    vector<K_V<D, int>> result;
    result.push_back(K_V<D, int>(source[0], 0));
    for (int i = 1; i < source.size(); ++i) {
        if (source[i] <= result.begin()->key) {
            result.insert(result.begin(), K_V<D, int>(source[i], i));
            continue;
        } else if (source[i] >= (result.end() - 1)->key) {
            result.insert(result.end(), K_V<D, int>(source[i], i));
            continue;
        }
        for (auto iter = result.begin() + 1; iter < result.end() - 1; iter++) {
            if (source[i] >= iter->key && source[i] <= (iter + 1)->key) {
                result.insert(iter + 1, K_V<D, int>(source[i], i));
                break;
            }
        }
    }
    return result;
}

int main () {
    int temp[] = {1, 4, 12, 4, 2354, 246, 5, 3, 4, 5, 9, 6, 23, 4, 78, 6, 34, 42, 34, 2, 4, 3, 52, 4, 98, 4, 3, 6, 3,
                  80, 4, 43, 4};
    auto container = vector<int>(temp, temp + 33);
    auto result_0 = createIndex<int>(container);
    return 0;
}