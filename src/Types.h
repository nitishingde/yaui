#ifndef YAUI_TYPES_H
#define YAUI_TYPES_H


#include <string>
#include <vector>
#include <unordered_map>

namespace yaui {
    using int8 = int8_t;
    using uint8 = uint8_t;
    using int16 = int16_t;
    using uint16 = uint16_t;
    using int32 = int32_t;
    using uint32 = uint32_t;
    using int64 = int64_t;
    using uint64 = uint64_t;

    template<typename Type, typename Alloc = std::allocator<Type>>
    using ArrayList = std::vector<Type, Alloc>;
    using String = std::string;
    template<typename key, typename value>
    using HashMap = std::unordered_map<key, value>;
}


#endif //YAUI_TYPES_H
