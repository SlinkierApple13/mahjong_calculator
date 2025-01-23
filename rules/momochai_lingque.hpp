#ifndef MOMOCHAI_LINGQUE_HPP
#define MOMOCHAI_LINGQUE_HPP

#include <math.h>

#include "../basic/mahjong.hpp"
#include "../basic/mahjong_utils.hpp"

namespace momochai_lingque {

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

    }

    enum category {
        occasional,
        special,
        concealed,
        triplets,
        honours,
        terminals,
        suits,
        numbers,
        overall_correlation,
        identical_melds,
        partial_correlation
    };

    struct tag {
        category category;
        uint16_t base_point;
        uint8_t multiplier;
        bool special_compatible = false;
        bool is_special = false;
    };

    using fan = scoring_element<uint8_t, tag>;
    using scorer = scoring_system<uint16_t, uint8_t, tag, std::string>;

    const verifier is_seven_pairs([](const hand& h) {
        if (h.melds().size()) return false;
        for (tile_t ti : tile_set::all_tiles)
            if (h.counter().count(ti) != 0 && h.counter().count(ti) != 2) return false;
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
        if (h.melds().size() && h.winning_type()(win_type::heavenly_or_earthly_hand)) return false;
        if (h.counter().count(h.winning_tile()) > 1 && h.winning_type()(win_type::kong_related, win_type::self_drawn)) return false;
        if (h.winning_type()(win_type::final_tile | win_type::heavenly_or_earthly_hand)) return false;
        return true;
    });

    const verifier is_winning_hand([](const hand& h) {
        if (!input_verifier(h)) return false;
        if (h.decompose().size()) return true;
        if (is_seven_pairs(h) || is_thirteen_orphans(h) || is_honours_and_knitted_tiles(h)) return true;
        return false;
    });

    using namespace tile_literals;

    namespace criteria {

        using res_t = uint8_t;
        using res_v = std::vector<uint8_t>;
        constexpr res_t heavenly_hand(const hand& h) {
            return h.winning_type()(win_type::heavenly_or_earthly_hand | win_type::self_drawn);
        }

        constexpr res_t earthly_hand(const hand& h) {
            return h.winning_type()(win_type::heavenly_or_earthly_hand, win_type::self_drawn);
        }

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

        constexpr res_t two_kongs(const hand& h) {
            return h.counter().count() == 16;
        }

        constexpr res_t kong(const hand& h) {
            return h.counter().count() == 15;
        }

        res_v four_concealed_triplets(const hand& h) {
            return utils::for_all_decompositions<res_t>(h, [](const hand::decomposition& d) {
                for (const meld& m : d.melds())
                    if (!m.concealed() || m.type() == meld_type::sequence) return false;
                return true;
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

        res_v concealed_triplet(const hand& h) {
            return utils::for_all_decompositions<res_t>(h, [](const hand::decomposition& d) {
                uint8_t counter = 0;
                for (const meld& m : d.melds())
                    if (m.concealed() && m.type() > meld_type::sequence) ++counter;
                return counter == 1;
            });
        }

        res_v all_triplets(const hand& h) {
            return utils::for_all_decompositions<res_t>(h, [](const hand::decomposition& d) {
                for (const meld& m : d.melds())
                    if (m.type() == meld_type::sequence) return false;
                return true;
            });
        }

        constexpr res_t tile_hog(const hand& h) {
            uint8_t count = 0u;
            for (tile_t ti : tile_set::all_tiles)
            if (h.counter().count(ti) >= 4) ++count;
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
            return (h.counter().count(h.winning_type().seat_wind()) >= 3) + (h.counter().count(h.winning_type().seat_wind()) >= 2);
        }

        constexpr res_t red_dragon(const hand& h) {
            return (h.counter().count(honours::C) >= 3) + (h.counter().count(honours::C) >= 2);
        }

        constexpr res_t green_dragon(const hand& h) {
            return (h.counter().count(honours::F) >= 3) + (h.counter().count(honours::F) >= 2);
        }

        constexpr res_t white_dragon(const hand& h) {
            return (h.counter().count(honours::P) >= 3) + (h.counter().count(honours::P) >= 2);
        }

        constexpr res_t wind_triplet(const hand& h) {
            uint8_t count = 0u;
            for (tile_t ti : tile_set::wind_tiles)
                count += h.counter().count(ti) >= 3 && h.winning_type().seat_wind() != ti;
            return count;
        }

        constexpr res_t all_terminals(const hand& h) {
            for (tile_t ti : tile_set::all_tiles)
            if (h.counter().count(ti) && tile(ti).num() != 1 && tile(ti).num() != 9) return false;
            return true;
        }

        constexpr res_t all_terminals_and_honours(const hand& h) {
            for (tile_t ti : tile_set::simple_tiles)
            if (h.counter().count(ti)) return false;
            return true;
        }

        res_v pure_outside_hand(const hand& h) {
            auto poh_check = [](const hand::decomposition& d) {
                if (!d.pair().is_in(tile_set::terminal_tiles)) return false;
                for (const meld& m : d.melds())
                    if (!m.contains(tile_set::terminal_tiles)) return false;
                return true;
            };
            return utils::for_all_decompositions<res_t>(h, poh_check);
        }

        res_v mixed_outside_hand(const hand& h) {
            return utils::for_all_decompositions<res_t>(h, [](const hand::decomposition& d) {
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
                    if (m.contains(tile_set::terminal_tiles) && m.type() > meld_type::sequence) ++count;
                return count;
            });
        }

        constexpr res_t nine_gates(const hand& h) {
            auto c = h.counter(false);
            c.add(h.winning_tile(), -1);
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
            for (tile_t ti : tile_set::honour_tiles)
            if (h.counter().count(ti)) return false;
            auto check_suit = [](const hand& h, suit_type st) {
                for (tile_t ti : tile_set::tiles_of_suit(st))
                    if (h.counter().count(ti)) return true;
                return false;
            };
            return (check_suit(h, suit_type::m) + check_suit(h, suit_type::p) + check_suit(h, suit_type::s) == 2);
        }

        constexpr res_t all_types(const hand& h) {
            if (!h.counter().count(tile_set::character_tiles)) return false;
            if (!h.counter().count(tile_set::bamboo_tiles)) return false;
            if (!h.counter().count(tile_set::dot_tiles)) return false;
            if (!h.counter().count(tile_set::wind_tiles)) return false;
            if (!h.counter().count(tile_set::dragon_tiles)) return false;
            return true;
        }

        constexpr res_t two_numbers(const hand& h) {
            uint16_t num_table = 0u;
            for (tile_t ti : tile_set::all_tiles)
                if (h.counter().count(ti)) {
                    if (tile(ti).num() == 0) return false;
                    num_table |= 1 << tile(ti).num();
                }
            return utils::popcount(num_table) == 2u;
        }

        constexpr res_t three_consecutive_numbers(const hand& h) {
            uint16_t num_table = 0u;
            for (tile_t ti : tile_set::all_tiles)
                if (h.counter().count(ti))
                    num_table |= 1 << tile(ti).num();
            return num_table == 0b1110u || num_table == 0b11100u || num_table == 0b111000u || num_table == 0b1110000u || num_table == 0b11100000u || num_table == 0b111000000u || num_table == 0b1110000000u;
        }

        constexpr res_t four_consecutive_numbers(const hand& h) {
            uint16_t num_table = 0u;
            for (tile_t ti : tile_set::all_tiles)
                if (h.counter().count(ti))
                    num_table |= 1 << tile(ti).num();
            return num_table == 0b11110u || num_table == 0b111100u || num_table == 0b1111000u || num_table == 0b11110000u || num_table == 0b111100000u || num_table == 0b1111000000u;
        }

        res_v nine_numbers(const hand& h) {
            return utils::for_all_decompositions<res_t>(h, [](const hand::decomposition& d) {
                uint32_t num_table = 0u;
                for (const meld& m : d.melds())
                    if (m.type() == meld_type::sequence)
                        num_table += 0b001001001u << ((m.tile().num() - 1) * 3);
                    else num_table += 0b001u << (m.tile().num() * 3);
                num_table += (0b001u << (d.pair().num() * 3));
                return num_table == 153391688u;
            });
        }

        res_v reflected_hand(const hand& h) {
            for (tile_t ti : tile_set::honour_tiles)
            if (h.counter().count(ti)) return std::vector<uint8_t>(h.decompose().size(), 0u);
            uint8_t min_num = 10u, max_num = 0u;
            for (tile_t ti : tile_set::numbered_tiles)
            if (h.counter().count(ti)) {
                min_num = std::min(min_num, tile(ti).num());
                max_num = std::max(max_num, tile(ti).num());
            }
            const uint8_t ref = min_num + max_num;
            return utils::for_all_decompositions<res_t>(h, [ref](const hand::decomposition& d, const hand& hand) {
                for (const hand::decomposition& d2 : hand.decompose())
                    if (utils::is_reflection(d, d2, ref)) return true;
                return false;
            });
        }

        res_v common_number(const hand& h) {
            for (tile_t ti : tile_set::honour_tiles)
            if (h.counter().count(ti)) return std::vector<uint8_t>(h.decompose().size(), 0u);
            return utils::for_all_decompositions<res_t>(h, [](const hand::decomposition& d) {
                num_t num = d.pair().num();
                for (const meld& m : d.melds())
                    if (!m.contains(tile_set::tiles_of_number(num))) return false;
                return true;
            });
        }

        res_v quadruple_sequence(const hand& h) {
            return utils::for_all_decompositions<res_t>(h, [](const hand::decomposition& d) {
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

        res_v two_double_sequences(const hand& h) {
            return utils::for_all_decompositions<res_t>(h, [](const hand::decomposition& d) {
                uint8_t count = 0u;
                for (uint8_t i = 0; i < d.melds().size(); ++i)
                    for (uint8_t j = i + 1; j < d.melds().size(); ++j)
                        if (utils::is_equivalent(d.melds()[i], d.melds()[j])) ++count;
                return (count == 2u);
            });
        }

        res_v double_sequence(const hand& h) {
            return utils::for_all_decompositions<res_t>(h, [](const hand::decomposition& d) {
                uint8_t count = 0u;
                for (uint8_t i = 0; i < d.melds().size(); ++i)
                    for (uint8_t j = i + 1; j < d.melds().size(); ++j)
                        if (utils::is_equivalent(d.melds()[i], d.melds()[j])) ++count;
                return (count == 1u);
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

        res_v mirrored_hand(const hand& h) {
            return utils::for_all_decompositions<res_t>(h, [](const hand::decomposition& d, const hand& hand) {
                uint8_t suit_distribution = 0u;
                for (const meld& m : d.melds())
                    suit_distribution |= (1 << (m.tile().suit() >> 5));
                if (utils::popcount(suit_distribution) != 2u) return false;
                uint8_t count = 0u;
                uint8_t visited = 0u;
                for (uint8_t i = 0; i < d.melds().size(); ++i)
                    for (uint8_t j = i + 1; j < d.melds().size(); ++j)
                        if (utils::is_mixed_double_sequence(d.melds()[i], d.melds()[j]) || utils::is_mixed_double_triplet(d.melds()[i], d.melds()[j])) {
                            count += !(visited & ((1 << i) + (1 << j)));
                            if (!(visited & ((1 << i) + (1 << j)))) visited |= (1 << i) | (1 << j);
                        }
                return count == 2u;
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
                return false;
            });
        }

        res_v three_shifted_sequences(const hand& h) {
            return utils::for_all_decompositions<res_t>(h, [](const hand::decomposition& d) {
                for (tile_t ti : {2_m, 3_m, 4_m, 5_m, 6_m, 2_p, 3_p, 4_p, 5_p, 6_p, 2_s, 3_s, 4_s, 5_s, 6_s, 7_s})
                    if (utils::contains(d, {meld(ti, meld_type::sequence), meld(ti + 1, meld_type::sequence), meld(ti + 2, meld_type::sequence)})) 
                        return true;
                return false;
            });
        }

        res_v four_chained_sequences(const hand& h) {
            return utils::for_all_decompositions<res_t>(h, [](const hand::decomposition& d) {
                for (tile_t ti : {2_m, 2_p, 2_s})
                    if (utils::contains(d, {meld(ti, meld_type::sequence), meld(ti + 2, meld_type::sequence), meld(ti + 4, meld_type::sequence), meld(ti + 6, meld_type::sequence)})) 
                        return true;
                return false;
            });
        }

        res_v three_chained_sequences(const hand& h) {
            return utils::for_all_decompositions<res_t>(h, [](const hand::decomposition& d) {
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

        res_v two_short_straights(const hand& h) {
            return utils::for_all_decompositions<res_t>(h, [](const hand::decomposition& d) {
                uint8_t count = 0u;
                uint8_t visited = 0u;
                for (uint8_t i = 0; i < d.melds().size(); ++i)
                    for (uint8_t j = i + 1; j < d.melds().size(); ++j)
                        if (utils::is_shifted_sequences(d.melds()[i], d.melds()[j], 3)) {
                            count += !(visited & ((1 << i) + (1 << j)));
                            if (!(visited & ((1 << i) + (1 << j)))) visited |= (1 << i) | (1 << j);
                        }
                if (count == 2u) return true;
                count = 0u;
                visited = 0u;
                for (uint8_t i = 0; i < d.melds().size(); ++i)
                    for (uint8_t j = i + 1; j < d.melds().size(); ++j)
                        if (utils::is_shifted_sequences(d.melds()[i], d.melds()[j], 6)) {
                            count += !(visited & ((1 << i) + (1 << j)));
                            if (!(visited & ((1 << i) + (1 << j)))) visited |= (1 << i) | (1 << j);
                        }
                return count == 2u;
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
                return count == 1u;
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

        res_v mixed_chained_sequences(const hand& h) {
            return utils::for_all_decompositions<res_t>(h, [](const hand::decomposition& d) {
                for (auto& seq : patterns::mixed_chained_sequences)
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

        constexpr res_t big_seven_honours(const hand& h) {
            if (!is_seven_pairs(h)) return false;
            return utils::contains_pair_of(h, tile_set::honour_tiles);
        }

        constexpr res_t four_wind_pairs(const hand& h) {
            if (!is_seven_pairs(h)) return false;
            return utils::contains_pair_of(h, tile_set::wind_tiles);
        }

        constexpr res_t three_dragon_pairs(const hand& h) {
            if (!is_seven_pairs(h)) return false;
            return utils::contains_pair_of(h, tile_set::dragon_tiles);
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

        constexpr res_t reflected_pairs(const hand& h) {
            if (!is_seven_pairs(h)) return false;
            const auto& c = h.counter();
            for (tile_t ti : tile_set::honour_tiles)
                if (c.count(ti)) return false;
            uint8_t min_num = 10u, max_num = 0u;
            for (tile_t ti : tile_set::numbered_tiles)
                if (c.count(ti)) {
                    min_num = std::min(min_num, tile(ti).num());
                    max_num = std::max(max_num, tile(ti).num());
                }
            const uint8_t ref = min_num + max_num;
            for (tile_t t : tile_set::numbered_tiles)
                if (c.count(t) && c.count(t) != c.count((t & 0b11110000) | (ref - (t & 0b00001111)))) return false;
            return true;
        }

        constexpr res_t two_triple_pairs(const hand& h) {
            if (!is_seven_pairs(h)) return false;
            auto m = tile_literals::operator""_m;
            auto p = tile_literals::operator""_p;
            auto s = tile_literals::operator""_s;
            for (uint8_t i = 1; i <= 8; ++i)
                for (uint8_t j = i + 1; j <= 9; ++j)
                    if (utils::contains_pair_of(h, {m(i), p(i), s(i), m(j), p(j), s(j)})) return true;
            return false;
        }

        constexpr res_t three_mirrored_pairs(const hand& h) {
            if (!is_seven_pairs(h)) return false;
            auto m = tile_literals::operator""_m;
            auto p = tile_literals::operator""_p;
            auto s = tile_literals::operator""_s;
            for (uint8_t i = 1; i <= 7; ++i)
                for (uint8_t j = i + 1; j <= 8; ++j)
                    for (uint8_t k = j + 1; k <= 9; ++k) {
                        if (utils::contains_pair_of(h, {m(i), m(j), m(k), p(i), p(j), p(k)})) return true;
                        if (utils::contains_pair_of(h, {s(i), s(j), s(k), p(i), p(j), p(k)})) return true;
                        if (utils::contains_pair_of(h, {m(i), m(j), m(k), s(i), s(j), s(k)})) return true;
                    }
            return false;
        }

        constexpr res_t thirteen_orphans(const hand& h) {
            return is_thirteen_orphans(h);
        }

        constexpr res_t honours_and_knitted_tiles(const hand& h) {
            return is_honours_and_knitted_tiles(h);
        }

    }

    const std::vector<fan> list_of_fans = {
        fan("天和", {category::occasional, 64, 3, 1}, criteria::heavenly_hand),
        fan("地和", {category::occasional, 64, 3, 1}, criteria::earthly_hand),
        fan("岭上开花", {category::occasional, 8, 2, 1}, criteria::out_with_replacement_tile),
        fan("海底捞月", {category::occasional, 8, 2, 1}, criteria::last_tile_draw),
        fan("河底捞鱼", {category::occasional, 8, 2, 1}, criteria::last_tile_claim),
        fan("抢杠", {category::occasional, 8, 2, 1}, criteria::robbing_the_kong),
        fan("自摸", {category::occasional, 2, 1, 1}, criteria::self_drawn),
        fan("七对", {category::special, 8, 3, 1, 1}, criteria::seven_pairs),
        fan("全不靠", {category::special, 8, 3, 1, 1}, criteria::honours_and_knitted_tiles),
        fan("十三幺", {category::special, 48, 3, 1, 1}, criteria::thirteen_orphans),
        fan("门前清", {category::concealed, 2, 1, 1}, criteria::concealed_hand),
        fan("四杠", {category::triplets, 88, 5}, criteria::four_kongs),
        fan("三杠", {category::triplets, 32, 4}, criteria::three_kongs),
        fan("双杠", {category::triplets, 8, 2}, criteria::two_kongs),
        fan("杠", {category::triplets, 4, 1}, criteria::kong),
        fan("四暗刻", {category::triplets, 48, 3}, criteria::four_concealed_triplets),
        fan("三暗刻", {category::triplets, 16, 3}, criteria::three_concealed_triplets),
        fan("双暗刻", {category::triplets, 4, 2}, criteria::two_concealed_triplets),
        fan("暗刻", {category::triplets, 2, 1}, criteria::concealed_triplet),
        fan("对对和", {category::triplets, 8, 3}, criteria::all_triplets),
        fan("四归", {category::triplets, 4, 1}, criteria::tile_hog),
        fan("大七星", {category::honours, 112, 5, 1, 1}, criteria::big_seven_honours),
        fan("字一色", {category::honours, 32, 5, 1}, criteria::all_honours),
        fan("大四喜", {category::honours, 88, 5}, criteria::big_four_winds),
        fan("小四喜", {category::honours, 48, 5}, criteria::little_four_winds),
        fan("四喜对", {category::honours, 24, 3, 1}, criteria::four_wind_pairs),
        fan("大三元", {category::honours, 48, 4}, criteria::big_three_dragons),
        fan("小三元", {category::honours, 24, 4}, criteria::little_three_dragons),
        fan("三元对", {category::honours, 12, 3, 1}, criteria::three_dragon_pairs),
        fan("番牌 门风牌", {category::honours, 2, 1, 1}, criteria::seat_wind),
        fan("番牌 中", {category::honours, 2, 1, 1}, criteria::red_dragon),
        fan("番牌 發", {category::honours, 2, 1, 1}, criteria::green_dragon),
        fan("番牌 白", {category::honours, 2, 1, 1}, criteria::white_dragon),
        fan("客风刻", {category::honours, 2, 1, 1}, criteria::wind_triplet),
        fan("清幺九", {category::terminals, 88, 5}, criteria::all_terminals),
        fan("混幺九", {category::terminals, 16, 3, 1}, criteria::all_terminals_and_honours),
        fan("清带幺", {category::terminals, 12, 3}, criteria::pure_outside_hand),
        fan("混带幺", {category::terminals, 4, 3}, criteria::mixed_outside_hand),
        fan("幺九刻", {category::terminals, 2, 1}, criteria::terminal_triplet),
        fan("九莲宝灯", {category::suits, 112, 5}, criteria::nine_gates),
        fan("连七对", {category::suits, 88, 5, 1, 1}, criteria::seven_shifted_pairs),
        fan("清一色", {category::suits, 24, 4, 1}, criteria::full_flush),
        fan("混一色", {category::suits, 8, 3, 1}, criteria::half_flush),
        fan("缺一门", {category::suits, 2, 1, 1}, criteria::two_suits),
        fan("五门齐", {category::suits, 4, 2}, criteria::all_types),
        fan("二数", {category::numbers, 48, 5}, criteria::two_numbers),
        fan("三聚", {category::numbers, 24, 3, 1}, criteria::three_consecutive_numbers),
        fan("四聚", {category::numbers, 8, 3, 1}, criteria::four_consecutive_numbers),
        fan("九数贯通", {category::numbers, 12, 3}, criteria::nine_numbers),
        fan("镜数", {category::overall_correlation, 12, 3}, criteria::reflected_hand),
        fan("镜数对", {category::overall_correlation, 24, 3, 1, 1}, criteria::reflected_pairs),
        fan("四同顺", {category::identical_melds, 112, 6}, criteria::quadruple_sequence),
        fan("三同顺", {category::identical_melds, 32, 4}, criteria::triple_sequence),
        fan("二般高", {category::identical_melds, 24, 3}, criteria::two_double_sequences),
        fan("一般高", {category::identical_melds, 4, 2}, criteria::double_sequence),
        fan("三同刻", {category::partial_correlation, 24, 3}, criteria::mixed_triple_triplet),
        fan("双同刻", {category::partial_correlation, 4, 2}, criteria::mixed_double_triplet),
        fan("三色同顺", {category::partial_correlation, 8, 3}, criteria::mixed_triple_sequence),
        fan("喜相逢", {category::partial_correlation, 2, 1}, criteria::mixed_double_sequence),
        fan("三同二对", {category::partial_correlation, 24, 3, 1, 1}, criteria::two_triple_pairs),
        fan("镜同", {category::partial_correlation, 4, 3}, criteria::mirrored_hand),
        fan("镜同对", {category::partial_correlation, 12, 3, 1, 1}, criteria::three_mirrored_pairs),
        fan("四连刻", {category::partial_correlation, 48, 4}, criteria::four_shifted_triplets),
        fan("三连刻", {category::partial_correlation, 24, 3}, criteria::three_shifted_triplets),
        fan("四步高", {category::partial_correlation, 48, 4}, criteria::four_shifted_sequences),
        fan("三步高", {category::partial_correlation, 16, 3}, criteria::three_shifted_sequences),
        fan("四连环", {category::partial_correlation, 32, 4}, criteria::four_chained_sequences),
        fan("三连环", {category::partial_correlation, 8, 3}, criteria::three_chained_sequences),
        fan("一气贯通", {category::partial_correlation, 8, 3}, criteria::pure_straight),
        fan("双龙会", {category::partial_correlation, 8, 3}, criteria::two_short_straights),
        fan("连六", {category::partial_correlation, 2, 1}, criteria::short_straight),
        fan("老少副", {category::partial_correlation, 2, 1}, criteria::two_terminal_sequences),
        fan("三色连刻", {category::partial_correlation, 8, 2}, criteria::mixed_shifted_triplets),
        fan("三色步高", {category::partial_correlation, 4, 2}, criteria::mixed_shifted_sequences),
        fan("三色连环", {category::partial_correlation, 4, 2}, criteria::mixed_chained_sequences),
        fan("三色贯通", {category::partial_correlation, 8, 2}, criteria::mixed_straight),
        fan("镜龙会", {category::partial_correlation, 12, 3}, criteria::mirrored_short_straights)
    };

    enum indices {
        blessing_of_heaven,
        blessing_of_earth,
        out_with_replacement_tile,
        last_tile_draw,
        last_tile_claim,
        robbing_the_kong,
        self_drawn,
        seven_pairs,
        honours_and_knitted_tiles,
        thirteen_orphans,
        concealed_hand,
        four_kongs,
        three_kongs,
        two_kongs,
        kong,
        four_concealed_triplets,
        three_concealed_triplets,
        two_concealed_triplets,
        concealed_triplet,
        all_triplets,
        tile_hog,
        big_seven_honours,
        all_honours,
        big_four_winds,
        little_four_winds,
        four_wind_pairs,
        big_three_dragons,
        little_three_dragons,
        three_dragon_pairs,
        seat_wind,
        red_dragon,
        green_dragon,
        white_dragon,
        wind_triplet,
        all_terminals,
        all_terminals_and_honours,
        pure_outside_hand,
        mixed_outside_hand,
        terminal_triplet,
        nine_gates,
        seven_shifted_pairs,
        full_flush,
        half_flush,
        two_suits,
        all_types,
        two_numbers,
        three_consecutive_numbers,
        four_consecutive_numbers,
        nine_numbers,
        reflected_hand,
        reflected_pairs,
        quadruple_sequence,
        triple_sequence,
        two_double_sequences,
        double_sequence,
        mixed_triple_triplet,
        mixed_double_triplet,
        mixed_triple_sequence,
        mixed_double_sequence,
        two_triple_pairs,
        mirrored_hand,
        three_mirrored_pairs,
        four_shifted_triplets,
        three_shifted_triplets,
        four_shifted_sequences,
        three_shifted_sequences,
        four_chained_sequences,
        three_chained_sequences,
        pure_straight,
        two_short_straights,
        short_straight,
        two_terminal_sequences,
        mixed_shifted_triplets,
        mixed_shifted_sequences,
        mixed_chained_sequences,
        mixed_straight,
        mirrored_short_straights,
        fan_count
    };

    std::vector<uint8_t> derepellenise(const std::vector<uint8_t>& f) {
        using enum indices;
        std::vector<uint8_t> fr = f;
        fr[self_drawn] &= (!f[blessing_of_heaven] && !f[last_tile_draw] && !f[out_with_replacement_tile]);
        fr[concealed_hand] &= (!f[blessing_of_heaven] && !f[blessing_of_earth] && !f[four_concealed_triplets]
            && !f[nine_gates] && !f[seven_pairs] && !f[big_seven_honours] && !f[four_wind_pairs]
            && !f[three_dragon_pairs] && !f[seven_shifted_pairs] && !f[reflected_pairs] && !f[two_triple_pairs]
            && !f[three_mirrored_pairs] && !f[thirteen_orphans] && !f[honours_and_knitted_tiles]);
        fr[two_concealed_triplets] &= !f[nine_gates];
        fr[concealed_triplet] &= !f[nine_gates];
        fr[all_triplets] &= (!f[four_kongs] && !f[four_concealed_triplets] && !f[big_four_winds] && !f[all_terminals] && !f[two_numbers] && !f[four_shifted_triplets]);
        fr[tile_hog] -= fr[kong];
        fr[tile_hog] -= 2 * fr[two_kongs];
        fr[tile_hog] -= 3 * fr[three_kongs];
        fr[tile_hog] -= 4 * fr[four_kongs];
        fr[tile_hog] *= (!f[quadruple_sequence] && !f[nine_gates]);
        fr[all_honours] &= !f[big_seven_honours];
        fr[seat_wind] *= (!f[big_four_winds] && !f[little_four_winds] && !f[four_wind_pairs]);
        fr[red_dragon] *= (!f[big_three_dragons] && !f[little_three_dragons] && !f[three_dragon_pairs]);
        fr[green_dragon] *= (!f[big_three_dragons] && !f[little_three_dragons] && !f[three_dragon_pairs]);
        fr[white_dragon] *= (!f[big_three_dragons] && !f[little_three_dragons] && !f[three_dragon_pairs]);
        fr[wind_triplet] *= (!f[big_four_winds] && !f[little_four_winds]);
        fr[all_terminals_and_honours] &= (!f[all_terminals] && !f[all_honours] && !f[thirteen_orphans]);
        fr[pure_outside_hand] &= !f[all_terminals];
        fr[mixed_outside_hand] &= (!f[all_terminals_and_honours] && !f[pure_outside_hand]);
        fr[terminal_triplet] *= (!f[all_terminals] && !f[nine_gates]);
        fr[full_flush] &= (!f[nine_gates] && !f[seven_shifted_pairs]);
        fr[half_flush] &= (!f[full_flush] && !f[big_four_winds] && !f[little_four_winds]);
        fr[two_numbers] &= !f[all_terminals];
        fr[nine_numbers] &= !f[nine_gates];
        fr[reflected_hand] &= !f[nine_gates];
        fr[mixed_double_triplet] *= (!f[mixed_triple_triplet] && !f[two_numbers]);
        fr[mixed_double_sequence] *= (!f[mixed_triple_sequence] && !f[mirrored_short_straights]);
        fr[three_shifted_triplets] &= !f[four_shifted_triplets];
        fr[three_shifted_sequences] &= !f[four_shifted_sequences];
        fr[three_chained_sequences] &= (!f[four_chained_sequences] && !f[three_shifted_sequences]);
        fr[short_straight] &= (!f[nine_gates] && !f[pure_straight] && !f[two_short_straights] && !f[four_shifted_sequences] && !f[mixed_straight]);
        fr[two_terminal_sequences] &= (!f[nine_gates] && !f[pure_straight] && !f[four_chained_sequences] && !f[mixed_straight] && !f[two_short_straights]);
        fr[two_short_straights] &= (!f[pure_straight] && !f[mirrored_short_straights]);
        fr[mirrored_hand] &= !f[mirrored_short_straights];
        fr[pure_straight] &= !f[nine_gates];
        fr[mixed_chained_sequences] &= !f[mixed_shifted_sequences];
        fr[seven_pairs] &= (!f[big_seven_honours] && !f[seven_shifted_pairs]);
        fr[four_wind_pairs] &= !f[big_seven_honours];
        fr[three_dragon_pairs] &= !f[big_seven_honours];
        fr[reflected_pairs] &= !f[seven_shifted_pairs];
        return fr;
    }

    std::pair<std::pair<uint16_t, uint8_t>, std::pair<std::vector<uint8_t>, std::bitset<3 << 5>>> basic_score_from_fans(const std::vector<uint8_t>& fan_results) {
        using enum category;
        using enum indices;
        const std::vector<uint8_t> fr = derepellenise(fan_results);
        std::bitset<3 << 5> chosen_for_mult;
        uint16_t base_point = 0u;
        for (uint8_t i = 0; i < fr.size(); ++i)
            base_point += list_of_fans[i].tag.base_point * fr[i];
        uint8_t multiplier = 0u;
        std::array<uint8_t, 11> mult_by_category = {0u};
        for (uint8_t i = 0; i < fr.size(); ++i)
            if (fr[i] && mult_by_category[list_of_fans[i].tag.category] < list_of_fans[i].tag.multiplier)
                mult_by_category[list_of_fans[i].tag.category] = list_of_fans[i].tag.multiplier;
        mult_by_category[honours] = std::max((int)mult_by_category[honours],
            (fr[seat_wind] == 2) + (fr[red_dragon] == 2) + (fr[green_dragon] == 2) + (fr[white_dragon] == 2));
        uint8_t first_mult = 0u, second_mult = 0u, first_cat = 11u, second_cat = 11u;
        for (uint8_t i = 0; i < 11; ++i)
            if (mult_by_category[i] > first_mult) {
                second_mult = first_mult;
                first_mult = mult_by_category[i];
                second_cat = first_cat;
                first_cat = i;
            } else if (mult_by_category[i] > second_mult) {
                second_mult = mult_by_category[i];
                second_cat = i;
            }
        multiplier = first_mult + (second_mult * second_mult > (first_mult << 1));
        for (uint8_t j = 0; j < fan_count; ++j)
            if (list_of_fans[j].tag.category == first_cat && fr[j] && list_of_fans[j].tag.multiplier == first_mult) {
                chosen_for_mult[j] = true;
                goto j0;
            }
        if (first_cat == honours)
            chosen_for_mult[seat_wind] = chosen_for_mult[red_dragon] = chosen_for_mult[green_dragon] = chosen_for_mult[white_dragon] = true;
j0:     if (first_mult == multiplier) goto j1;
        for (uint8_t j = 0; j < fan_count; ++j)
            if (list_of_fans[j].tag.category == second_cat && fr[j] && list_of_fans[j].tag.multiplier == second_mult) {
                chosen_for_mult[j] = true;
                goto j1;
            }
        if (second_cat == honours)
            chosen_for_mult[seat_wind] = chosen_for_mult[red_dragon] = chosen_for_mult[green_dragon] = chosen_for_mult[white_dragon] = true;
j1:     if (fan_results[concealed_hand]) ++multiplier;
        return {{base_point, multiplier}, {fr, chosen_for_mult}};
    }

    const auto score_from_fans = [](const std::vector<std::vector<uint8_t>>& fan_results) -> scorer::result {
        using enum category;
        using enum indices;
        std::vector<uint8_t> fr(fan_count, 0u);
        const std::size_t c = fan_results[reflected_hand].size();
        uint16_t res_bp = 0, res_mult = 0;
        std::vector<uint8_t> fans;
        std::bitset<3 << 5> chosen_for_mult;
        for (std::size_t j = 0; j < c; ++j) {
            for (uint8_t i = 0; i < fan_count; ++i) {
                if (list_of_fans[i].tag.is_special) continue;
                fr[i] = (fan_results[i].size() == 1) ? fan_results[i][0] : fan_results[i][j];
            }
            const auto r = basic_score_from_fans(fr);
            if (r.first.first * r.first.second >= res_bp * res_mult) {
                res_bp = r.first.first;
                res_mult = r.first.second;
                fans = r.second.first;
                chosen_for_mult = r.second.second;
            }
        }
        for (uint8_t i = 0; i < fan_count; ++i)
            fr[i] = (list_of_fans[i].tag.special_compatible) ? fan_results[i][0] : 0u;
        const auto r = basic_score_from_fans(fr);
        if (r.first.first * r.first.second > res_bp * res_mult) {
            res_bp = r.first.first;
            res_mult = r.first.second;
            fans = r.second.first;
            chosen_for_mult = r.second.second;
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
            return std::string(-length - size_in_console(s), ' ') + s;
        };
        if (res_mult == 0u) return {true, 0u, std::string(34, '=') + '\n' + extend("平和", 20) + "  0 × 0 =    0\n"};
        std::stringstream ss;
        ss << std::string(34, '-') << '\n';
        for (uint8_t i = 0; i < fan_count; ++i)
            if (fans[i]) {
                ss << extend(list_of_fans[i].name, 13) << ((fans[i] == 1 || i == red_dragon || i == green_dragon || i == white_dragon || i == seat_wind) ? "  " : "×" + std::to_string((int)fans[i])) << extend(std::to_string(fans[i] * list_of_fans[i].tag.base_point), -8);
                if (chosen_for_mult[i])
                    ss << " × " << (int)list_of_fans[i].tag.multiplier;
                ss << '\n';
            }
        if (fan_results[concealed_hand][0]) ss << std::string(34, '-') << '\n' << extend("门清跳翻", 23) << " + 1" << '\n';
        ss << std::string(34, '=') << '\n';
        ss << extend("总计", 20) << extend(std::to_string(res_bp), -3) << " × " << (int)res_mult << " = " << extend(std::to_string(res_bp * res_mult), -4) << '\n';
        return {true, static_cast<uint16_t>(res_bp * res_mult), ss.str()};
    };

    const scorer calculator(list_of_fans, score_from_fans, is_winning_hand);

}

#endif