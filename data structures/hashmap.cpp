
//	https://github.com/the-tourist/algo/
//	https://github.com/p1k4-piyush/templates/


struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
typedef unordered_map<long long, int, custom_hash> safe_map;


// #include <ext/pb_ds/assoc_container.hpp>

// template <typename K, typename V, typename Hash = splitmix64_hash>
// using HashMap = __gnu_pbds::gp_hash_table<K, V, Hash>;

// template <typename K, typename Hash = splitmix64_hash>
// using HashSet = HashMap<K, __gnu_pbds::null_type, Hash>;


