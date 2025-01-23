#ifndef MCR_MAHJONG_HPP
#define MCR_MAHJONG_HPP

#include <math.h>
#include <bitset>

#define MAHJONG_KNITTED_STRAIGHT
#include "../basic/mahjong.hpp"
#include "../basic/mahjong_utils.hpp"

namespace mcr_mahjong {

    using namespace mahjong;

    namespace patterns {

        constexpr uint64_t nine_gates_m_s = 0b011001001001001001001001011000ull;
        constexpr uint64_t nine_gates_p = 0b011001001001001001001001011000ull << 32;

        using namespace tile_literals;
        using enum meld_type;

        constexpr std::initializer_list<std::initializer_list<meld_t>> mixed_shifted_triplets = {
            {triplet | 1_m, triplet | 2_p, triplet | 3_s}, {triplet | 2_m, triplet | 3_p, triplet | 4_s}, {triplet | 3_m, triplet | 4_p, triplet | 5_s}, {triplet | 4_m, triplet | 5_p, triplet | 6_s},
            {triplet | 5_m, triplet | 6_p, triplet | 7_s}, {triplet | 6_m, triplet | 7_p, triplet | 8_s}, {triplet | 7_m, triplet | 8_p, triplet | 9_s},
            {triplet | 1_p, triplet | 2_s, triplet | 3_m}, {triplet | 2_p, triplet | 3_s, triplet | 4_m}, {triplet | 3_p, triplet | 4_s, triplet | 5_m}, {triplet | 4_p, triplet | 5_s, triplet | 6_m},
            {triplet | 5_p, triplet | 6_s, triplet | 7_m}, {triplet | 6_p, triplet | 7_s, triplet | 8_m}, {triplet | 7_p, triplet | 8_s, triplet | 9_m},
            {triplet | 1_s, triplet | 2_m, triplet | 3_p}, {triplet | 2_s, triplet | 3_m, triplet | 4_p}, {triplet | 3_s, triplet | 4_m, triplet | 5_p}, {triplet | 4_s, triplet | 5_m, triplet | 6_p},
            {triplet | 5_s, triplet | 6_m, triplet | 7_p}, {triplet | 6_s, triplet | 7_m, triplet | 8_p}, {triplet | 7_s, triplet | 8_m, triplet | 9_p},
            {triplet | 1_m, triplet | 2_s, triplet | 3_p}, {triplet | 2_m, triplet | 3_s, triplet | 4_p}, {triplet | 3_m, triplet | 4_s, triplet | 5_p}, {triplet | 4_m, triplet | 5_s, triplet | 6_p},
            {triplet | 5_m, triplet | 6_s, triplet | 7_p}, {triplet | 6_m, triplet | 7_s, triplet | 8_p}, {triplet | 7_m, triplet | 8_s, triplet | 9_p},
            {triplet | 1_p, triplet | 2_m, triplet | 3_s}, {triplet | 2_p, triplet | 3_m, triplet | 4_s}, {triplet | 3_p, triplet | 4_m, triplet | 5_s}, {triplet | 4_p, triplet | 5_m, triplet | 6_s},
            {triplet | 5_p, triplet | 6_m, triplet | 7_s}, {triplet | 6_p, triplet | 7_m, triplet | 8_s}, {triplet | 7_p, triplet | 8_m, triplet | 9_s},
            {triplet | 1_s, triplet | 2_p, triplet | 3_m}, {triplet | 2_s, triplet | 3_p, triplet | 4_m}, {triplet | 3_s, triplet | 4_p, triplet | 5_m}, {triplet | 4_s, triplet | 5_p, triplet | 6_m},
            {triplet | 5_s, triplet | 6_p, triplet | 7_m}, {triplet | 6_s, triplet | 7_p, triplet | 8_m}, {triplet | 7_s, triplet | 8_p, triplet | 9_m}
        };

        constexpr std::initializer_list<std::initializer_list<meld_t>> mixed_shifted_sequences = {
            {2_m, 3_p, 4_s}, {3_m, 4_p, 5_s}, {4_m, 5_p, 6_s}, {5_m, 6_p, 7_s}, {6_m, 7_p, 8_s},
            {2_p, 3_s, 4_m}, {3_p, 4_s, 5_m}, {4_p, 5_s, 6_m}, {5_p, 6_s, 7_m}, {6_p, 7_s, 8_m},
            {2_s, 3_m, 4_p}, {3_s, 4_m, 5_p}, {4_s, 5_m, 6_p}, {5_s, 6_m, 7_p}, {6_s, 7_m, 8_p},
            {2_m, 3_s, 4_p}, {3_m, 4_s, 5_p}, {4_m, 5_s, 6_p}, {5_m, 6_s, 7_p}, {6_m, 7_s, 8_p},
            {2_p, 3_m, 4_s}, {3_p, 4_m, 5_s}, {4_p, 5_m, 6_s}, {5_p, 6_m, 7_s}, {6_p, 7_m, 8_s},
            {2_s, 3_p, 4_m}, {3_s, 4_p, 5_m}, {4_s, 5_p, 6_m}, {5_s, 6_p, 7_m}, {6_s, 7_p, 8_m}
        };

        constexpr std::initializer_list<std::initializer_list<meld_t>> mixed_chained_sequences = {
            {2_m, 4_p, 6_s}, {3_m, 5_p, 7_s}, {4_m, 6_p, 8_s},
            {2_p, 4_s, 6_m}, {3_p, 5_s, 7_m}, {4_p, 6_s, 8_m},
            {2_s, 4_m, 6_p}, {3_s, 5_m, 7_p}, {4_s, 6_m, 8_p},
            {2_m, 4_s, 6_p}, {3_m, 5_s, 7_p}, {4_m, 6_s, 8_p},
            {2_p, 4_m, 6_s}, {3_p, 5_m, 7_s}, {4_p, 6_m, 8_s},
            {2_s, 4_p, 6_m}, {3_s, 5_p, 7_m}, {4_s, 6_p, 8_m}
        };

        constexpr std::initializer_list<std::initializer_list<meld_t>> mixed_straight = {
            {2_m, 5_p, 8_s}, {2_p, 5_s, 8_m}, {2_s, 5_m, 8_p},
            {2_m, 5_s, 8_p}, {2_p, 5_m, 8_s}, {2_s, 5_p, 8_m}
        };

        constexpr std::initializer_list<std::initializer_list<meld_t>> mirrored_short_straights = {
            {2_m, 5_m, 2_p, 5_p}, {3_m, 6_m, 3_p, 6_p}, {4_m, 7_m, 4_p, 7_p}, {5_m, 8_m, 5_p, 8_p}, {2_m, 8_m, 2_p, 8_p},
            {2_p, 5_p, 2_s, 5_s}, {3_p, 6_p, 3_s, 6_s}, {4_p, 7_p, 4_s, 7_s}, {5_p, 8_p, 5_s, 8_s}, {2_p, 8_p, 2_s, 8_s},
            {2_s, 5_s, 2_m, 5_m}, {3_s, 6_s, 3_m, 6_m}, {4_s, 7_s, 4_m, 7_m}, {5_s, 8_s, 5_m, 8_m}, {2_s, 8_s, 2_m, 8_m}
        };

        constexpr uint64_t knitted_tiles = 0b001000000001000000001ull;
        constexpr uint64_t honours = 0b001001001001001001001000ull << 32;

        const std::initializer_list<tile_counter> honours_and_knitted_tiles = {
            tile_counter((knitted_tiles << 3) + (knitted_tiles << (32 + 6)), honours + (knitted_tiles << 9)),
            tile_counter((knitted_tiles << 6) + (knitted_tiles << (32 + 9)), honours + (knitted_tiles << 3)),
            tile_counter((knitted_tiles << 9) + (knitted_tiles << (32 + 3)), honours + (knitted_tiles << 6)),
            tile_counter((knitted_tiles << 3) + (knitted_tiles << (32 + 9)), honours + (knitted_tiles << 6)),
            tile_counter((knitted_tiles << 6) + (knitted_tiles << (32 + 3)), honours + (knitted_tiles << 9)),
            tile_counter((knitted_tiles << 9) + (knitted_tiles << (32 + 6)), honours + (knitted_tiles << 3))
        };

        const std::initializer_list<tile_counter> pure_terminal_sequences = {
            tile_counter({1_m, 1_m, 2_m, 2_m, 3_m, 3_m, 5_m, 5_m, 7_m, 7_m, 8_m, 8_m, 9_m, 9_m}),
            tile_counter({1_p, 1_p, 2_p, 2_p, 3_p, 3_p, 5_p, 5_p, 7_p, 7_p, 8_p, 8_p, 9_p, 9_p}),
            tile_counter({1_s, 1_s, 2_s, 2_s, 3_s, 3_s, 5_s, 5_s, 7_s, 7_s, 8_s, 8_s, 9_s, 9_s})
        };

        const std::initializer_list<tile_counter> mixed_terminal_sequences = {
            tile_counter({1_m, 2_m, 3_m, 7_m, 8_m, 9_m, 1_p, 2_p, 3_p, 7_p, 8_p, 9_p, 5_s, 5_s}),
            tile_counter({1_m, 2_m, 3_m, 7_m, 8_m, 9_m, 1_s, 2_s, 3_s, 7_s, 8_s, 9_s, 5_p, 5_p}),
            tile_counter({1_p, 2_p, 3_p, 7_p, 8_p, 9_p, 1_s, 2_s, 3_s, 7_s, 8_s, 9_s, 5_m, 5_m}),
            tile_counter({1_p, 2_p, 3_p, 7_p, 8_p, 9_p, 1_m, 2_m, 3_m, 7_m, 8_m, 9_m, 5_s, 5_s}),
            tile_counter({1_s, 2_s, 3_s, 7_s, 8_s, 9_s, 1_m, 2_m, 3_m, 7_m, 8_m, 9_m, 5_p, 5_p}),
            tile_counter({1_s, 2_s, 3_s, 7_s, 8_s, 9_s, 1_p, 2_p, 3_p, 7_p, 8_p, 9_p, 5_m, 5_m})
        };

        constexpr std::array<tile_t, 12> even_tiles = {2_m, 4_m, 6_m, 8_m, 2_p, 4_p, 6_p, 8_p, 2_s, 4_s, 6_s, 8_s};

        constexpr std::array<tile_t, 14> reversible_tiles = {1_p, 2_p, 3_p, 4_p, 5_p, 8_p, 9_p, 2_s, 4_s, 5_s, 6_s, 8_s, 9_s, honours::P};

        constexpr std::array<tile_t, 6> green_tiles = {2_s, 3_s, 4_s, 6_s, 8_s, honours::F};

    }

    struct tag {
        uint16_t value;
        bool special_compatible = false;
        bool is_special = false;
    };

    using fan = scoring_element<uint8_t, tag>;
    using scorer = scoring_system<uint16_t, uint8_t, tag, std::string>;

    const verifier is_seven_pairs([](const hand& h) {
        if (h.melds().size()) return false;
        for (tile_t ti : tile_set::all_tiles)
            if (h.counter().count(ti) & 1) return false;
        return true;
    });

    const verifier is_thirteen_orphans([](const hand& h) {
        if (h.melds().size()) return false;
        for (tile_t ti : tile_set::terminal_honour_tiles)
            if (!h.counter().count(ti)) return false;
        for (tile_t ti : tile_set::simple_tiles)
            if (h.counter().count(ti)) return false;
        return true;
    });

    const verifier is_honours_and_knitted_tiles([](const hand& h) {
        if (h.melds().size()) return false;
        for (const auto& p : patterns::honours_and_knitted_tiles)
            if (h.counter() <= p) return true;
        return false;
    });
    
    const verifier input_verifier([](const hand& h) {
        if (!h.is_valid()) return false;
        uint8_t kong_count = 0;
        for (const auto& m : h.melds())
            if (m.type() == meld_type::kong) ++kong_count;
        if (kong_count == 0 && h.winning_type()(win_type::kong_related | win_type::self_drawn)) return false;
        if (h.counter(false).count(h.winning_tile()) > 1 && h.winning_type()(win_type::heavenly_or_earthly_hand)) return false;
        if (h.counter().count(h.winning_tile()) > 1 && h.winning_type()(win_type::kong_related, win_type::self_drawn)) return false;
        return true;
    });

    const verifier is_winning_hand([](const hand& h) {
        if (!input_verifier(h)) return false;
        if (h.decompose().size()) return true;
        if (is_seven_pairs(h) || is_thirteen_orphans(h) || is_honours_and_knitted_tiles(h)) return true;
        return false;
    });

    const verifier is_5tile_winning_hand([](const hand& h) { // fifth tile allowed; used for wait checking
        if (!h.is_valid(false)) return false;
        if (h.decompose().size()) return true;
        if (is_seven_pairs(h) || is_thirteen_orphans(h) || is_honours_and_knitted_tiles(h)) return true;
        return false;
    });

    namespace criteria {

        using namespace tile_literals;
        
        using res_t = uint8_t;
        using res_v = std::vector<uint8_t>;

        constexpr res_t out_with_replacement_tile(const hand& h) {
            return h.winning_type()(win_type::kong_related | win_type::self_drawn);
        }

        constexpr res_t last_tile_draw(const hand& h) {
            return h.winning_type()(win_type::final_tile | win_type::self_drawn);
        }

        constexpr res_t last_tile_claim(const hand& h) {
            return h.winning_type()(win_type::final_tile, win_type::self_drawn);
        }

        constexpr res_t robbing_the_kong(const hand& h) {
            return h.winning_type()(win_type::kong_related, win_type::self_drawn);
        }

        constexpr res_t self_drawn(const hand& h) {
            return h.winning_type()(win_type::self_drawn);
        }

        constexpr res_t concealed_hand(const hand& h) {
            if (self_drawn(h)) return false;
            for (const auto& m : h.melds())
                if (!m.concealed()) return false;
            return true;
        }

        constexpr res_t four_kongs(const hand& h) {
            return h.counter().count() == 18;
        }

        constexpr res_t three_kongs(const hand& h) {
            return h.counter().count() == 17;
        }

        constexpr res_t two_melded_kongs(const hand& h) {
            if (h.counter().count() != 16) return false;
            uint8_t count = 0;
            for (const auto& m : h.melds())
                if (m.type() == meld_type::kong && !m.concealed()) ++count;
            return count == 2;
        }

        constexpr res_t two_concealed_kongs(const hand& h) {
            if (h.counter().count() != 16) return false;
            uint8_t count = 0;
            for (const auto& m : h.melds())
                if (m.type() == meld_type::kong && m.concealed()) ++count;
            return count == 2;
        }

        constexpr res_t melded_and_concealed_kongs(const hand& h) {
            if (h.counter().count() != 16) return false;
            uint8_t count = 0;
            for (const auto& m : h.melds())
                if (m.type() == meld_type::kong && m.concealed()) ++count;
            return count == 1;
        }

        constexpr res_t melded_kong(const hand& h) {
            if (h.counter().count() != 15) return false;
            for (const auto& m : h.melds())
                if (m.type() == meld_type::kong && !m.concealed()) return true;
            return false;
        }

        constexpr res_t concealed_kong(const hand& h) {
            if (h.counter().count() != 15) return false;
            for (const auto& m : h.melds())
                if (m.type() == meld_type::kong && m.concealed()) return true;
            return false;
        }

        res_v four_concealed_triplets(const hand& h) {
            return utils::for_all_decompositions<res_t>(h, [](const hand::decomposition& d) {
                uint8_t counter = 0;
                for (const meld& m : d.melds())
                    if (m.concealed() && m.type() > meld_type::sequence) ++counter;
                return counter == 4;
            });
        }

        res_v three_concealed_triplets(const hand& h) {
            return utils::for_all_decompositions<res_t>(h, [](const hand::decomposition& d) {
                uint8_t counter = 0;
                for (const meld& m : d.melds())
                    if (m.concealed() && m.type() > meld_type::sequence) ++counter;
                return counter == 3;
            });
        }

        res_v two_concealed_triplets(const hand& h) {
            return utils::for_all_decompositions<res_t>(h, [](const hand::decomposition& d) {
                uint8_t counter = 0;
                for (const meld& m : d.melds())
                    if (m.concealed() && m.type() > meld_type::sequence) ++counter;
                return counter == 2;
            });
        }

        res_v all_triplets(const hand& h) {
            return utils::for_all_decompositions<res_t>(h, [](const hand::decomposition& d) {
                uint8_t counter = 0;
                for (const meld& m : d.melds())
                    if (m.type() > meld_type::sequence) ++counter;
                return counter == 4;
            });
        }

        constexpr res_t tile_hog(const hand& h) {
            uint8_t count = 0u;
            for (tile_t ti : tile_set::all_tiles)
                if (h.counter().count(ti) >= 4) ++count;
            count -= (h.counter().count() - 14);
            return count;
        }

        constexpr res_t all_honours(const hand& h) {
            for (tile_t ti : tile_set::numbered_tiles)
            if (h.counter().count(ti)) return false;
            return true;
        }

        constexpr res_t big_four_winds(const hand& h) {
            for (tile_t ti : tile_set::wind_tiles)
            if (h.counter().count(ti) < 3) return false;
            return true;
        }

        constexpr res_t little_four_winds(const hand& h) {
            uint8_t count = 0u;
            for (tile_t ti : tile_set::wind_tiles)
            count += (h.counter().count(ti) >= 3) + (h.counter().count(ti) >= 2);
            return count == 7;
        }

        constexpr res_t big_three_dragons(const hand& h) {
            for (tile_t ti : tile_set::dragon_tiles)
            if (h.counter().count(ti) < 3) return false;
            return true;
        }

        constexpr res_t little_three_dragons(const hand& h) {
            uint8_t count = 0u;
            for (tile_t ti : tile_set::dragon_tiles)
            count += (h.counter().count(ti) >= 3) + (h.counter().count(ti) >= 2);
            return count == 5;
        }

        constexpr res_t seat_wind(const hand& h) {
            return h.counter().count(h.winning_type().seat_wind()) >= 3;
        }

        constexpr res_t prevalent_wind(const hand& h) {
            return h.counter().count(h.winning_type().prevalent_wind()) >= 3;
        }

        constexpr res_t dragon_triplet(const hand& h) {
            return (h.counter().count(honours::C) >= 3) + (h.counter().count(honours::F) >= 3) + (h.counter().count(honours::P) >= 3) == 1;
        }

        constexpr res_t two_dragon_triplets(const hand& h) {
            return (h.counter().count(honours::C) >= 3) + (h.counter().count(honours::F) >= 3) + (h.counter().count(honours::P) >= 3) == 2;
        }

        constexpr res_t three_wind_triplets(const hand& h) {
            uint8_t count = 0u;
            for (tile_t ti : tile_set::wind_tiles)
                count += h.counter().count(ti) >= 3;
            return count == 3;
        }

        constexpr res_t all_terminals(const hand& h) {
            for (tile_t ti : tile_set::all_tiles)
            if (h.counter().count(ti) && tile(ti).num() != 1 && tile(ti).num() != 9) return false;
            return true;
        }

        constexpr res_t all_terminals_and_honours(const hand& h) {
            return !h.counter().count(tile_set::simple_tiles);
        }

        res_v outside_hand(const hand& h) {
            return utils::for_all_decompositions<res_t>(h, [](const hand::decomposition& d) {
                if (d.is_knitted_straight()) return false;
                if (!d.pair().is_in(tile_set::terminal_honour_tiles)) return false;
                for (const meld& m : d.melds())
                    if (!m.contains(tile_set::terminal_honour_tiles)) return false;
                return true;
            });
        }

        res_v terminal_triplet(const hand& h) {
            return utils::for_all_decompositions<res_t>(h, [](const hand::decomposition& d) {
                uint8_t count = 0u;
                for (const meld& m : d.melds())
                    if (m.contains(tile_set::terminal_honour_tiles) && m.type() > meld_type::sequence) ++count;
                return count;
            });
        }

        constexpr res_t nine_gates(const hand& h) {
            auto c = h.counter(false);
            c -= h.winning_tile();
            return (c == std::make_pair(patterns::nine_gates_m_s, 0ull) || c == std::make_pair(0ull, patterns::nine_gates_m_s) || c == std::make_pair(patterns::nine_gates_p, 0ull));
        }

        constexpr res_t full_flush(const hand& h) {
            for (tile_t ti : tile_set::honour_tiles)
            if (h.counter().count(ti)) return false;
            auto check_suit = [](const hand& h, suit_type st) {
                for (tile_t ti : tile_set::tiles_of_suit(st))
                    if (h.counter().count(ti)) return true;
                return false;
            };
            return (check_suit(h, suit_type::m) + check_suit(h, suit_type::p) + check_suit(h, suit_type::s) == 1);
        }

        constexpr res_t half_flush(const hand& h) {
            auto check_suit = [](const hand& h, suit_type st) {
                for (tile_t ti : tile_set::tiles_of_suit(st))
                    if (h.counter().count(ti)) return true;
                return false;
            };
            return (check_suit(h, suit_type::m) + check_suit(h, suit_type::p) + check_suit(h, suit_type::s) == 1);
        }

        constexpr res_t two_suits(const hand& h) {
            auto check_suit = [](const hand& h, suit_type st) {
                for (tile_t ti : tile_set::tiles_of_suit(st))
                    if (h.counter().count(ti)) return true;
                return false;
            };
            return (check_suit(h, suit_type::m) + check_suit(h, suit_type::p) + check_suit(h, suit_type::s) == 2);
        }

        constexpr res_t lower_tiles(const hand& h) {
            uint16_t num_table = 0u;
            for (tile_t ti : tile_set::all_tiles)
                if (h.counter().count(ti))
                    num_table |= 1 << tile(ti).num();
            return (num_table | 0b1110u) == 0b1110u;
        }

        constexpr res_t middle_tiles(const hand& h) {
            uint16_t num_table = 0u;
            for (tile_t ti : tile_set::all_tiles)
                if (h.counter().count(ti))
                    num_table |= 1 << tile(ti).num();
            return (num_table | 0b1110000u) == 0b1110000u;
        }

        constexpr res_t upper_tiles(const hand& h) {
            uint16_t num_table = 0u;
            for (tile_t ti : tile_set::all_tiles)
                if (h.counter().count(ti))
                    num_table |= 1 << tile(ti).num();
            return (num_table | 0b1110000000u) == 0b1110000000u;
        }

        constexpr res_t lower_four(const hand& h) {
            uint16_t num_table = 0u;
            for (tile_t ti : tile_set::all_tiles)
                if (h.counter().count(ti))
                    num_table |= 1 << tile(ti).num();
            return (num_table | 0b11110u) == 0b11110u;
        }

        constexpr res_t upper_four(const hand& h) {
            uint16_t num_table = 0u;
            for (tile_t ti : tile_set::all_tiles)
                if (h.counter().count(ti))
                    num_table |= 1 << tile(ti).num();
            return (num_table | 0b1111000000u) == 0b1111000000u;
        }

        res_v all_fives(const hand& h) {
            for (tile_t ti : tile_set::honour_tiles)
                if (h.counter().count(ti)) return std::vector<uint8_t>(h.decompose().size(), 0u);
            return utils::for_all_decompositions<res_t>(h, [](const hand::decomposition& d) {
                if (d.is_knitted_straight()) return false;
                if (d.pair().num() != 5) return false;
                for (const meld& m : d.melds())
                    if (!m.contains(tile_set::tiles_of_number(5))) return false;
                return true;
            });
        }

        res_v quadruple_sequence(const hand& h) {
            return utils::for_all_decompositions<res_t>(h, [](const hand::decomposition& d) {
                if (d.is_knitted_straight()) return false;
                for (const meld& m : d.melds())
                    if (!utils::is_equivalent(m, d.melds()[0])) return false;
                return true;
            });
        }

        res_v triple_sequence(const hand& h) {
            return utils::for_all_decompositions<res_t>(h, [](const hand::decomposition& d) {
                uint8_t count = 0u;
                for (uint8_t i = 0; i < d.melds().size(); ++i)
                    for (uint8_t j = i + 1; j < d.melds().size(); ++j)
                        if (utils::is_equivalent(d.melds()[i], d.melds()[j])) ++count;
                return (count == 3u);
            });
        }

        res_v double_sequence(const hand& h) {
            return utils::for_all_decompositions<res_t>(h, [](const hand::decomposition& d) {
                uint8_t count = 0u;
                for (uint8_t i = 0; i < d.melds().size(); ++i)
                    for (uint8_t j = i + 1; j < d.melds().size(); ++j)
                        if (utils::is_equivalent(d.melds()[i], d.melds()[j])) ++count;
                return (count == 1u) | ((count == 2u) << 1);
            });
        }
        
        res_v mixed_triple_triplet(const hand& h) {
            return utils::for_all_decompositions<res_t>(h, [](const hand::decomposition& d) {
                uint8_t count = 0u;
                for (uint8_t i = 0; i < d.melds().size(); ++i)
                    for (uint8_t j = i + 1; j < d.melds().size(); ++j)
                        if (utils::is_mixed_double_triplet(d.melds()[i], d.melds()[j])) ++count;
                return count == 3u;
            });
        }

        res_v mixed_double_triplet(const hand& h) {
            return utils::for_all_decompositions<res_t>(h, [](const hand::decomposition& d) {
                uint8_t count = 0u;
                for (uint8_t i = 0; i < d.melds().size(); ++i)
                    for (uint8_t j = i + 1; j < d.melds().size(); ++j)
                        if (utils::is_mixed_double_triplet(d.melds()[i], d.melds()[j])) ++count;
                return (count == 1u) | ((count == 2u) << 1);
            });
        }

        res_v mixed_triple_sequence(const hand& h) {
            return utils::for_all_decompositions<res_t>(h, [](const hand::decomposition& d) {
                for (tile_t ti : {2_m, 3_m, 4_m, 5_m, 6_m, 7_m, 8_m})
                    if (utils::contains(d, {meld(ti, meld_type::sequence), meld(ti + 0b00100000u, meld_type::sequence), meld(ti + 0b10000000u, meld_type::sequence)})) 
                        return true;
                return false;
            });
        }

        res_v mixed_double_sequence(const hand& h) {
            return utils::for_all_decompositions<res_t>(h, [](const hand::decomposition& d) {
                uint8_t count = 0u;
                uint8_t visited = 0u;
                for (uint8_t i = 0; i < d.melds().size(); ++i)
                    for (uint8_t j = i + 1; j < d.melds().size(); ++j)
                        if (utils::is_mixed_double_sequence(d.melds()[i], d.melds()[j])) {
                            count += !(visited & ((1 << i) + (1 << j)));
                            if (!(visited & ((1 << i) + (1 << j)))) visited |= (1 << i) | (1 << j);
                        }
                return (count == 1u) | ((count == 2u) << 1);
            });
        }

        res_v four_shifted_triplets(const hand& h) {
            return utils::for_all_decompositions<res_t>(h, [](const hand::decomposition& d) {
                for (tile_t ti : {1_m, 2_m, 3_m, 4_m, 5_m, 6_m, 1_p, 2_p, 3_p, 4_p, 5_p, 6_p, 1_s, 2_s, 3_s, 4_s, 5_s, 6_s})
                    if (utils::contains(d, {meld(ti, meld_type::triplet), meld(ti + 1, meld_type::triplet), meld(ti + 2, meld_type::triplet), meld(ti + 3, meld_type::triplet)})) 
                        return true;
                return false;
            });
        }

        res_v three_shifted_triplets(const hand& h) {
            return utils::for_all_decompositions<res_t>(h, [](const hand::decomposition& d) {
                for (tile_t ti : {1_m, 2_m, 3_m, 4_m, 5_m, 6_m, 7_m, 1_p, 2_p, 3_p, 4_p, 5_p, 6_p, 7_p, 1_s, 2_s, 3_s, 4_s, 5_s, 6_s, 7_s})
                    if (utils::contains(d, {meld(ti, meld_type::triplet), meld(ti + 1, meld_type::triplet), meld(ti + 2, meld_type::triplet)})) 
                        return true;
                return false;
            });
        }

        res_v four_shifted_sequences(const hand& h) {
            return utils::for_all_decompositions<res_t>(h, [](const hand::decomposition& d) {
                for (tile_t ti : {2_m, 3_m, 4_m, 5_m, 2_p, 3_p, 4_p, 5_p, 2_s, 3_s, 4_s, 5_s})
                    if (utils::contains(d, {meld(ti, meld_type::sequence), meld(ti + 1, meld_type::sequence), meld(ti + 2, meld_type::sequence), meld(ti + 3, meld_type::sequence)})) 
                        return true;
                for (tile_t ti : {2_m, 2_p, 2_s})
                    if (utils::contains(d, {meld(ti, meld_type::sequence), meld(ti + 2, meld_type::sequence), meld(ti + 4, meld_type::sequence), meld(ti + 6, meld_type::sequence)})) 
                        return true;
                return false;
            });
        }

        res_v three_shifted_sequences(const hand& h) {
            return utils::for_all_decompositions<res_t>(h, [](const hand::decomposition& d) {
                for (tile_t ti : {2_m, 3_m, 4_m, 5_m, 6_m, 2_p, 3_p, 4_p, 5_p, 6_p, 2_s, 3_s, 4_s, 5_s, 6_s, 7_s})
                    if (utils::contains(d, {meld(ti, meld_type::sequence), meld(ti + 1, meld_type::sequence), meld(ti + 2, meld_type::sequence)})) 
                        return true;
                for (tile_t ti : {2_m, 2_p, 2_s, 3_m, 3_p, 3_s, 4_m, 4_p, 4_s})
                    if (utils::contains(d, {meld(ti, meld_type::sequence), meld(ti + 2, meld_type::sequence), meld(ti + 4, meld_type::sequence)})) 
                        return true;
                return false;
            });
        }

        res_v pure_straight(const hand& h) {
            return utils::for_all_decompositions<res_t>(h, [](const hand::decomposition& d) {
                for (tile_t ti : {2_m, 2_p, 2_s})
                    if (utils::contains(d, {meld(ti, meld_type::sequence), meld(ti + 3, meld_type::sequence), meld(ti + 6, meld_type::sequence)})) 
                        return true;
                return false;
            });
        }

        res_v short_straight(const hand& h) {
            return utils::for_all_decompositions<res_t>(h, [](const hand::decomposition& d) {
                uint8_t count = 0u;
                uint8_t visited = 0u;
                for (uint8_t i = 0; i < d.melds().size(); ++i)
                    for (uint8_t j = i + 1; j < d.melds().size(); ++j)
                        if (utils::is_shifted_sequences(d.melds()[i], d.melds()[j], 3)) {
                            count += !(visited & ((1 << i) + (1 << j)));
                            visited |= (1 << i) | (1 << j);
                        }
                return count;
            });
        }

        res_v two_terminal_sequences(const hand& h) {
            return utils::for_all_decompositions<res_t>(h, [](const hand::decomposition& d) {
                for (uint8_t i = 0; i < d.melds().size(); ++i)
                    for (uint8_t j = i + 1; j < d.melds().size(); ++j)
                        if (utils::is_shifted_sequences(d.melds()[i], d.melds()[j], 6))
                            return true;
                return false;
            });
        }

        res_v mixed_shifted_triplets(const hand& h) {
            return utils::for_all_decompositions<res_t>(h, [](const hand::decomposition& d) {
                for (auto& seq : patterns::mixed_shifted_triplets)
                    if (utils::contains(d, seq)) return true;
                return false;
            });
        }

        res_v mixed_shifted_sequences(const hand& h) {
            return utils::for_all_decompositions<res_t>(h, [](const hand::decomposition& d) {
                for (auto& seq : patterns::mixed_shifted_sequences)
                    if (utils::contains(d, seq)) return true;
                return false;
            });
        }

        res_v mixed_straight(const hand& h) {
            return utils::for_all_decompositions<res_t>(h, [](const hand::decomposition& d) {
                for (auto& seq : patterns::mixed_straight)
                    if (utils::contains(d, seq)) return true;
                return false;
            });
        }

        res_v mirrored_short_straights(const hand& h) {
            return utils::for_all_decompositions<res_t>(h, [](const hand::decomposition& d) {
                for (auto& seq : patterns::mirrored_short_straights)
                    if (utils::contains(d, seq)) return true;
                return false;
            });
        }

        constexpr res_t seven_pairs(const hand& h) {
            return is_seven_pairs(h);
        }

        constexpr res_t seven_shifted_pairs(const hand& h) {
            if (!is_seven_pairs(h)) return false;
            for (tile_t ti : {1_m, 2_m, 3_m, 1_p, 2_p, 3_p, 1_s, 2_s, 3_s})
                if (utils::contains_pair_of(h, {
                    static_cast<tile_t>(ti), static_cast<tile_t>(ti + 1), static_cast<tile_t>(ti + 2), static_cast<tile_t>(ti + 3), 
                    static_cast<tile_t>(ti + 4), static_cast<tile_t>(ti + 5), static_cast<tile_t>(ti + 6)
                })) return true;
            return false;
        }

        constexpr res_t thirteen_orphans(const hand& h) {
            return is_thirteen_orphans(h);
        }

        constexpr res_t lesser_honours_and_knitted_tiles(const hand& h) {
            return is_honours_and_knitted_tiles(h) && h.counter().count(tile_set::honour_tiles) <= 6;
        }

        constexpr res_t knitted_straight(const hand& h) {
            if (h.decompose().size() != 1)
                return is_honours_and_knitted_tiles(h) && h.counter().count(tile_set::honour_tiles) == 5;
            return h.decompose()[0].is_knitted_straight();
        }

        constexpr res_t greater_honours_and_knitted_tiles(const hand& h) {
            return is_honours_and_knitted_tiles(h) && h.counter().count(tile_set::honour_tiles) == 7;
        }

        constexpr res_t pure_terminal_sequences(const hand& h) {
            for (auto& p : patterns::pure_terminal_sequences)
                if (h.counter() == p) return true;
            return false;
        }

        constexpr res_t mixed_terminal_sequences(const hand& h) {
            for (auto& p : patterns::mixed_terminal_sequences)
                if (h.counter() == p) return true;
            return false;
        }

        constexpr res_t all_even_triplets(const hand& h) {
            if (!h.decompose().size()) return false;
            return h.counter().count(patterns::even_tiles) == h.counter().count();
        }

        constexpr res_t all_green(const hand& h) {
            return h.counter().count(patterns::green_tiles) == h.counter().count();
        }

        constexpr res_t reversible_tiles(const hand& h) {
            return h.counter().count(patterns::reversible_tiles) == h.counter().count();
        }

        constexpr res_t all_types(const hand& h) {
            return h.counter().count(tile_set::bamboo_tiles) && h.counter().count(tile_set::character_tiles) && h.counter().count(tile_set::dot_tiles)
                && h.counter().count(tile_set::dragon_tiles) && h.counter().count(tile_set::wind_tiles);
        }

        constexpr res_t melded_hand(const hand& h) {
            if (h.counter(false) != 2) return false;
            if (!self_drawn(h)) return false;
            for (const auto& m : h.melds())
                if (m.type() == meld_type::kong && m.concealed()) return false;
            return true;
        }

        constexpr res_t fully_concealed_hand(const hand& h) {
            if (!self_drawn(h)) return false;
            for (const auto& m : h.melds())
                if (!m.concealed()) return false;
            return true;
        }

        constexpr res_t all_simples(const hand& h) {
            return !h.counter().count(tile_set::terminal_honour_tiles);
        }

        constexpr res_t no_honours(const hand& h) {
            return !h.counter().count(tile_set::honour_tiles);
        }

        constexpr res_t last_tile(const hand& h) {
            if (h.counter().count(h.winning_tile()) - h.counter(false).count(h.winning_tile()) == 3)
                return true;
            return h.winning_type()(win_type::heavenly_or_earthly_hand); // used for last tile instead, since heavenly/earthly hand does not exist in MCR
        }

        res_v edge_wait(const hand& h) {
            if (h.winning_tile().num() != 3 && h.winning_tile().num() != 7)
                return std::vector<uint8_t>(h.decompose().size(), 0u);
            return utils::for_all_decompositions<res_t>(h, [](const hand::decomposition& d, const hand& hh) {
                for (const auto& m : d.melds())
                    if (m.type() == meld_type::sequence && m.contains({hh.winning_tile()}) && m.contains(tile_set::terminal_tiles))
                        return utils::all_waits(hh, is_5tile_winning_hand).size() == 1;
                return false;
            });
        }

        res_v closed_wait(const hand& h) {
            if (h.winning_tile().num() == 0) return std::vector<uint8_t>(h.decompose().size(), 0u);
            return utils::for_all_decompositions<res_t>(h, [](const hand::decomposition& d, const hand& hh) {
                for (const auto& m : d.melds())
                    if (m.type() == meld_type::sequence && m.tile() == hh.winning_tile())
                        return utils::all_waits(hh, is_5tile_winning_hand).size() == 1;
                return false;
            });
        }

        res_v single_wait(const hand& h) {
            return utils::for_all_decompositions<res_t>(h, [](const hand::decomposition& d, const hand& hh) {
                if (d.pair() == hh.winning_tile()) 
                    return utils::all_waits(hh, is_5tile_winning_hand).size() == 1;
                return false;
            });
        }

        res_v all_sequences(const hand& h) {
            if (h.counter().count(tile_set::honour_tiles)) return std::vector<uint8_t>(h.decompose().size(), 0u);
            return utils::for_all_decompositions<res_t>(h, [](const hand::decomposition& d) {
                for (const meld& m : d.melds())
                    if (m.type() != meld_type::sequence) return false;
                return true;
            });
        }

        constexpr res_t chicken_hand(const hand& h) {
            return h.winning_type().seat_wind() == h.winning_type().prevalent_wind();
        }

    }

    const std::vector<fan> fans = {
        fan("大四喜", {88}, criteria::big_four_winds),
        fan("大三元", {88}, criteria::big_three_dragons),
        fan("绿一色", {88, 1}, criteria::all_green),
        fan("九莲宝灯", {88}, criteria::nine_gates),
        fan("四杠", {88}, criteria::four_kongs),
        fan("连七对", {88, 1, 1}, criteria::seven_shifted_pairs),
        fan("十三幺", {88, 1, 1}, criteria::thirteen_orphans),
        fan("清幺九", {64, 1}, criteria::all_terminals),
        fan("小四喜", {64}, criteria::little_four_winds),
        fan("小三元", {64}, criteria::little_three_dragons),
        fan("字一色", {64, 1}, criteria::all_honours),
        fan("四暗刻", {64}, criteria::four_concealed_triplets),
        fan("一色双龙会", {64}, criteria::pure_terminal_sequences),
        fan("一色四同顺", {48}, criteria::quadruple_sequence),
        fan("一色四节高", {48}, criteria::four_shifted_triplets),
        fan("一色四步高", {32}, criteria::four_shifted_sequences),
        fan("三杠", {32}, criteria::three_kongs),
        fan("混幺九", {32, 1}, criteria::all_terminals_and_honours),
        fan("七对", {24, 1, 1}, criteria::seven_pairs),
        fan("七星不靠", {24, 1, 1}, criteria::greater_honours_and_knitted_tiles),
        fan("全双刻", {24}, criteria::all_even_triplets),
        fan("清一色", {24, 1}, criteria::full_flush),
        fan("一色三同顺", {24}, criteria::triple_sequence),
        fan("一色三节高", {24}, criteria::three_shifted_triplets),
        fan("全大", {24, 1}, criteria::upper_tiles),
        fan("全中", {24, 1}, criteria::middle_tiles),
        fan("全小", {24, 1}, criteria::lower_tiles),
        fan("清龙", {16}, criteria::pure_straight),
        fan("三色双龙会", {16}, criteria::mixed_terminal_sequences),
        fan("一色三步高", {16}, criteria::three_shifted_sequences),
        fan("全带五", {16}, criteria::all_fives),
        fan("三同刻", {16}, criteria::mixed_triple_triplet),
        fan("三暗刻", {16}, criteria::three_concealed_triplets),
        fan("全不靠", {12, 1, 1}, criteria::lesser_honours_and_knitted_tiles),
        fan("组合龙", {12, 1}, criteria::knitted_straight),
        fan("大于五", {12, 1}, criteria::upper_four),
        fan("小于五", {12, 1}, criteria::lower_four),
        fan("三风刻", {12}, criteria::three_wind_triplets),
        fan("花龙", {8}, criteria::mixed_straight),
        fan("推不倒", {8, 1}, criteria::reversible_tiles),
        fan("三色三同顺", {8}, criteria::mixed_triple_sequence),
        fan("三色三节高", {8}, criteria::mixed_shifted_triplets),
        fan("无番和", {8, 1}, criteria::chicken_hand),
        fan("妙手回春", {8, 1}, criteria::last_tile_draw),
        fan("海底捞月", {8, 1}, criteria::last_tile_claim),
        fan("杠上开花", {8, 1}, criteria::out_with_replacement_tile),
        fan("抢杠和", {8, 1}, criteria::robbing_the_kong),
        fan("碰碰和", {6}, criteria::all_triplets),
        fan("混一色", {6, 1}, criteria::half_flush),
        fan("三色三步高", {6}, criteria::mixed_shifted_sequences),
        fan("五门齐", {6, 1}, criteria::all_types),
        fan("全求人", {6}, criteria::melded_hand),
        fan("双暗杠", {6}, criteria::two_concealed_kongs),
        fan("双箭刻", {6}, criteria::two_dragon_triplets),
        fan("明暗杠", {5}, criteria::melded_and_concealed_kongs),
        fan("全带幺", {4}, criteria::outside_hand),
        fan("不求人", {4}, criteria::fully_concealed_hand),
        fan("双明杠", {4}, criteria::two_melded_kongs),
        fan("和绝张", {4, 1}, criteria::last_tile),
        fan("箭刻", {2}, criteria::dragon_triplet),
        fan("圈风刻", {2}, criteria::prevalent_wind),
        fan("门风刻", {2}, criteria::seat_wind),
        fan("门前清", {2}, criteria::concealed_hand),
        fan("平和", {2}, criteria::all_sequences),
        fan("四归一", {2, 1}, criteria::tile_hog),
        fan("双同刻", {2}, criteria::mixed_double_triplet),
        fan("双暗刻", {2}, criteria::two_concealed_triplets),
        fan("暗杠", {2}, criteria::concealed_kong),
        fan("断幺", {2, 1}, criteria::all_simples),
        fan("一般高", {1}, criteria::double_sequence),
        fan("喜相逢", {1}, criteria::mixed_double_sequence),
        fan("连六", {1}, criteria::short_straight),
        fan("老少副", {1}, criteria::two_terminal_sequences),
        fan("幺九刻", {1}, criteria::terminal_triplet),
        fan("明杠", {1}, criteria::melded_kong),
        fan("缺一门", {1, 1}, criteria::two_suits),
        fan("无字", {1, 1}, criteria::no_honours),
        fan("边张", {1}, criteria::edge_wait),
        fan("嵌张", {1}, criteria::closed_wait),
        fan("单吊", {1}, criteria::single_wait),
        fan("自摸", {1, 1}, criteria::self_drawn)
    };

    enum indices {
        big_four_winds,
        big_three_dragons,
        all_green,
        nine_gates,
        four_kongs,
        seven_shifted_pairs,
        thirteen_orphans,
        all_terminals,
        little_four_winds,
        little_three_dragons,
        all_honours,
        four_concealed_triplets,
        pure_terminal_sequences,
        quadruple_sequence,
        four_shifted_triplets,
        four_shifted_sequences,
        three_kongs,
        all_terminals_and_honours,
        seven_pairs,
        greater_honours_and_knitted_tiles,
        all_even_triplets,
        full_flush,
        triple_sequence,
        three_shifted_triplets,
        upper_tiles,
        middle_tiles,
        lower_tiles,
        pure_straight,
        mixed_terminal_sequences,
        three_shifted_sequences,
        all_fives,
        mixed_triple_triplet,
        three_concealed_triplets,
        lesser_honours_and_knitted_tiles,
        knitted_straight,
        upper_four,
        lower_four,
        three_wind_triplets,
        mixed_straight,
        reversible_tiles,
        mixed_triple_sequence,
        mixed_shifted_triplets,
        chicken_hand,
        last_tile_draw,
        last_tile_claim,
        out_with_replacement_tile,
        robbing_the_kong,
        all_triplets,
        half_flush,
        mixed_shifted_sequences,
        all_types,
        melded_hand,
        two_concealed_kongs,
        two_dragon_triplets,
        melded_and_concealed_kongs,
        outside_hand,
        fully_concealed_hand,
        two_melded_kongs,
        last_tile,
        dragon_triplet,
        prevalent_wind,
        seat_wind,
        concealed_hand,
        all_sequences,
        tile_hog,
        mixed_double_triplet,
        two_concealed_triplets,
        concealed_kong,
        all_simples,
        double_sequence,
        mixed_double_sequence,
        short_straight,
        two_terminal_sequences,
        terminal_triplet,
        melded_kong,
        two_suits,
        no_honours,
        edge_wait,
        closed_wait,
        single_wait,
        self_drawn,
        fan_count
    };

    std::vector<uint8_t> derepellenise(const std::vector<uint8_t>& f) {
        using enum indices;
        std::vector<uint8_t> fr = f;
        fr[concealed_hand] &= !(fr[nine_gates] || fr[four_concealed_triplets]);
        fr[fully_concealed_hand] &= !(fr[nine_gates] || fr[four_concealed_triplets]);
        fr[self_drawn] &= !(fr[out_with_replacement_tile] || fr[last_tile_draw] || fr[fully_concealed_hand]);
        fr[no_honours] &= !(fr[upper_tiles] || fr[middle_tiles] || fr[lower_tiles] || fr[upper_four] || fr[lower_four] || fr[all_simples] || fr[all_sequences] || fr[full_flush] || fr[all_terminals]);
        fr[two_suits] &= !fr[reversible_tiles];
        fr[terminal_triplet] *= !(fr[all_terminals_and_honours] || fr[all_terminals] || fr[all_honours] || fr[big_four_winds] || fr[little_four_winds]);
        if (fr[terminal_triplet])
            fr[terminal_triplet] -= fr[dragon_triplet] + (fr[three_wind_triplets] ? 3 : (fr[prevalent_wind] + fr[seat_wind] - (fr[chicken_hand] && fr[seat_wind])) + 2 * fr[two_dragon_triplets] + 3 * fr[big_three_dragons]);
        if (fr[nine_gates] && fr[terminal_triplet]) --fr[terminal_triplet];
        if (fr[double_sequence] == 2 && fr[mixed_double_sequence] == 2) fr[mixed_double_sequence] = 1;
        if (fr[short_straight] == 2 && (fr[double_sequence] == 2 || fr[mixed_double_sequence] == 2)) fr[short_straight] = 1;
        fr[mixed_double_sequence] *= !fr[mixed_triple_sequence];
        fr[double_sequence] *= !fr[triple_sequence];
        fr[double_sequence] *= !fr[quadruple_sequence];
        fr[double_sequence] *= !fr[pure_terminal_sequences];
        fr[short_straight] *= !(fr[mixed_straight] || fr[pure_straight] || fr[four_shifted_sequences]);
        fr[two_terminal_sequences] *= !(fr[mixed_straight] || fr[pure_straight] || fr[pure_terminal_sequences] || fr[mixed_terminal_sequences] || fr[four_shifted_sequences]);
        fr[all_simples] &= !(fr[all_fives] || fr[middle_tiles] || fr[all_even_triplets]);
        fr[two_concealed_triplets] &= !fr[two_concealed_kongs];
        fr[mixed_double_triplet] *= !(fr[mixed_triple_triplet] || fr[all_terminals]);
        fr[tile_hog] *= !fr[quadruple_sequence];
        fr[all_sequences] &= !(fr[mixed_terminal_sequences] || fr[pure_terminal_sequences]);
        fr[seat_wind] &= !fr[big_four_winds];
        fr[prevalent_wind] &= !fr[big_four_winds];
        fr[outside_hand] &= !fr[all_terminals_and_honours];
        fr[all_types] &= !(fr[lesser_honours_and_knitted_tiles] || fr[greater_honours_and_knitted_tiles] || fr[thirteen_orphans]);
        fr[half_flush] &= !(fr[all_green] || fr[full_flush]);
        fr[two_dragon_triplets] &= !fr[little_three_dragons];
        fr[all_triplets] &= !(fr[big_four_winds] || fr[all_honours] || fr[all_terminals] || fr[all_terminals_and_honours] || fr[all_even_triplets] || fr[four_concealed_triplets] || fr[four_shifted_triplets] || fr[four_kongs]);
        fr[three_wind_triplets] &= !fr[little_four_winds];
        fr[lower_four] &= !fr[lower_tiles];
        fr[upper_four] &= !fr[upper_tiles];
        fr[lesser_honours_and_knitted_tiles] &= !fr[greater_honours_and_knitted_tiles];
        fr[three_shifted_sequences] &= !fr[four_shifted_sequences];
        fr[three_shifted_triplets] &= !fr[four_shifted_triplets];
        fr[seven_pairs] &= !fr[seven_shifted_pairs];
        fr[full_flush] &= !(fr[pure_terminal_sequences] || fr[nine_gates] || fr[seven_shifted_pairs]);
        fr[single_wait] &= !(fr[edge_wait] || fr[closed_wait] || fr[four_kongs] || fr[melded_hand]);
        fr[closed_wait] &= !fr[edge_wait];
        fr[all_terminals_and_honours] &= !fr[all_terminals];
        fr[all_terminals_and_honours] &= !fr[all_honours];
        fr[all_terminals_and_honours] &= !fr[thirteen_orphans];
        fr[chicken_hand] = 0;
        return fr;
    }

    std::pair<uint16_t, std::vector<uint8_t>> basic_score_from_fans(const std::vector<uint8_t>& f) {
        using enum indices;
        uint16_t res = 0;
        std::vector<uint8_t> fr = derepellenise(f);
        for (uint8_t i = 0; i < fan_count; ++i)
            res += fr[i] * fans[i].tag.value;
        if (res == 0) {
            fr[chicken_hand] = 1;
            res = 8;
        } else {
            fr[chicken_hand] = 0;
        }
        return {res, fr};
    }

    const auto score_from_fans = [](const std::vector<std::vector<uint8_t>>& fan_results) -> scorer::result {
        using enum indices;
        std::vector<uint8_t> fr(fan_count, 0u);
        std::vector<uint8_t> fr_res(fan_count, 0u);
        const std::size_t c = fan_results[mixed_straight].size();
        uint16_t res = 0;
        for (std::size_t j = 0; j < c; ++j) {
            for (uint8_t i = 0; i < fan_count; ++i) {
                if (fans[i].tag.is_special) continue;
                fr[i] = (fan_results[i].size() == 1) ? fan_results[i][0] : fan_results[i][j];
            }
            const auto r = basic_score_from_fans(fr);
            if (r.first > res) {
                res = r.first;
                fr_res = r.second;
            }
        }
        for (uint8_t i = 0; i < fan_count; ++i)
            fr[i] = (fans[i].tag.special_compatible) ? fan_results[i][0] : 0u;
        const auto r = basic_score_from_fans(fr);
        if (r.first > res) {
            res = r.first;
            fr_res = r.second;
        }
        auto size_in_console = [](const std::string& s) {
            std::size_t size = 0;
            for (unsigned char c : s) {
                if ((c & 0b11000000) != 0b10000000)
                    size += (1 + (c >= 0b10000000));
            }
            return size;
        };
        auto extend = [&size_in_console](const std::string& s, int32_t length) {
            if (length > 0)
                return s + std::string(length - size_in_console(s), ' ');
            return std::string(- length - size_in_console(s), ' ') + s;
        };
        std::stringstream ss;
        ss << std::string(23, '-') << '\n';
        for (uint8_t i = 0; i < fan_count; ++i)
            if (fr_res[i]) {
                ss << extend(fans[i].name, 13) << ((fr_res[i] == 1) ? "  " : "×" + std::to_string((int)fr_res[i])) << extend(std::to_string(fr_res[i] * fans[i].tag.value), -8);
                ss << '\n';
            }
        ss << std::string(23, '=') << '\n';
        ss << extend("总计", 5) << extend(std::to_string(res), -18) << '\n';
        return {true, res, ss.str()};
    };

    const scorer calculator(fans, score_from_fans, is_winning_hand);

}

#endif