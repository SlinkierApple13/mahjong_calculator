#ifndef __MAHJONG_UTILS_HPP__
#define __MAHJONG_UTILS_HPP__

#ifndef __MAHJONG_HPP__
#include "mahjong.hpp"
#endif

#include <bitset>

namespace mahjong {
    
    namespace utils {

        uint8_t popcount(uint32_t n) {
            return std::bitset<32>(n).count();
        }

        constexpr tile_t reflect_by(tile_t ti, num_t ref) {
            return (ti & 0b11110000u) | (ref - (ti & 0b00001111u));
        }

        constexpr meld_t reflect_by(meld_t m, num_t ref) {
            return (m & 0b1111111111110000u) | (ref - (m & 0b0000000000001111u));
        }

        constexpr bool is_equivalent(meld_t m1, meld_t m2) {
            return (m1 & 0b0000000111111111u) == (m2 & 0b0000000111111111u);
        }

        constexpr bool is_mixed_double_triplet(meld_t m1, meld_t m2) {
            if (!(m1 & 0b0000000100000000u) || !(m2 & 0b0000000100000000u)) return false;
            if (!(m1 & 0b0000000001000000u) || !(m2 & 0b0000000001000000u)) return false;
            return (m1 & 0b0000000000001111u) == (m2 & 0b0000000000001111u);
        }

        constexpr bool is_mixed_double_sequence(meld_t m1, meld_t m2) {
            if ((m1 & 0b0000000100000000u) || (m2 & 0b0000000100000000u)) return false;
            if (is_equivalent(m1, m2)) return false;
            return (m1 & 0b0000000000001111u) == (m2 & 0b0000000000001111u);
        }

        constexpr bool is_shifted_sequences(meld_t m1, meld_t m2, num_t inc) {
            if ((m1 & 0b0000000100000000u) || (m2 & 0b0000000100000000u)) return false;
            return std::abs((int32_t)(m1 & 0b0000000011111111u) - (int32_t)(m2 & 0b0000000011111111u)) == inc;
        }

        constexpr bool is_reflection(const hand::decomposition& d1, const hand::decomposition& d2, num_t ref) {
            if (reflect_by(d1.pair(), ref) != d2.pair()) return false;
            uint8_t paired = 0;
            for (const meld& m1 : d1.melds())
                for (uint8_t i = 0; i < d2.melds().size(); ++i) {
                    if (paired & (1 << i)) continue;
                    if (is_equivalent(m1, reflect_by(d2.melds()[i], ref))) {
                        paired |= 1 << i;
                        break;
                    }
                }
            return paired == (1 << d2.melds().size()) - 1;
        }

        template<typename T> requires std::is_constructible_v<tile, typename std::decay_t<T>::value_type>
        constexpr bool contains(const hand::decomposition& d, T&& m) {
            for (const meld_t& m2 : m) {
                bool found = false;
                for (const meld& m1 : d.melds())
                    if (is_equivalent(m1, m2)) {
                        found = true;
                        break;
                    }
                if (!found) return false;
            }
            return true;
        }

        template<typename T> requires std::is_constructible_v<tile, T>
        constexpr bool contains(const hand::decomposition& d, std::initializer_list<T> m) {
            for (const meld_t& m2 : m) {
                bool found = false;
                for (const meld& m1 : d.melds())
                    if (is_equivalent(m1, m2)) {
                        found = true;
                        break;
                    }
                if (!found) return false;
            }
            return true;
        }

        template<typename T> requires std::is_constructible_v<tile, typename std::decay_t<T>::value_type>
        constexpr bool contains_pair_of(const hand& d, T&& ti) {
            for (auto ti2 : ti)
                if (d.counter().count(ti2) != 2) return false;
            return true;
        }

        template<typename T> requires std::is_constructible_v<tile, T>
        constexpr bool contains_pair_of(const hand& d, std::initializer_list<T> ti) {
            for (auto ti2 : ti)
                if (d.counter().count(ti2) != 2) return false;
            return true;
        }

        std::vector<tile_t> all_waits(const hand& h, const verifier& v) {
            std::vector<tile_t> waits;
            const tile_counter counter = h.counter(false) - h.winning_tile();
            auto vt = counter.tiles();
            for (tile_t ti : tile_set::all_tiles) {
                auto h2 = hand(vt, h.melds(), ti);
                if (v(h2)) waits.push_back(ti);
            }
            return waits;
        }

    }

}

#endif