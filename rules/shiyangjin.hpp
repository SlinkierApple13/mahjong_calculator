#ifndef SHIYANGJIN_HPP
#define SHIYANGJIN_HPP

#include <math.h>

#include "../basic/mahjong.hpp"
#include "../basic/mahjong_utils.hpp"

namespace shiyangjin {

    using namespace mahjong;

    struct tag {
        uint8_t value;
        bool special_compatible = false;
        bool is_special = false;
    };

    using fan = scoring_element<uint8_t, tag>;
    using scorer = scoring_system<uint16_t, uint8_t, tag, std::string>;

    const verifier is_seven_pairs([](const hand& h) {
        if (h.melds().size()) return false;
        for (tile_t ti : tile_set::all_tiles)
            if (h.counter().count(ti) & 1u) return false;
        return true;
    });

    const verifier input_verifier([](const hand& h) {
        for (tile_t ti : tile_set::honour_tiles)
            if (h.counter().count(ti)) return false;
        if (!h.is_valid()) return false;
        uint8_t kong_count = 0;
        for (const auto& m : h.melds())
            if (m.type() == meld_type::kong) ++kong_count;
        if (kong_count == 0 && h.winning_type()(win_type::kong_related | win_type::self_drawn)) return false;
        if (h.counter().count(h.winning_tile()) > 1 && h.winning_type()(win_type::kong_related, win_type::self_drawn)) return false;
        return true;
    });

    const verifier is_winning_hand([](const hand& h) {
        if (!input_verifier(h)) return false;
        if (h.decompose().size()) return true;
        if (is_seven_pairs(h)) return true;
        return false;
    });

    using namespace tile_literals;

    namespace criteria {

        using res_t = uint8_t;
        using res_v = std::vector<uint8_t>;

        constexpr res_t out_with_replacement_tile(const hand& h) {
            return h.winning_type()(win_type::kong_related | win_type::self_drawn);
        }

        constexpr res_t final_tile(const hand& h) {
            return h.winning_type()(win_type::final_tile);
        }

        constexpr res_t robbing_the_kong(const hand& h) {
            return h.winning_type()(win_type::kong_related, win_type::self_drawn);
        }

        constexpr res_t fully_concealed_hand(const hand& h) {
            for (const auto& m : h.melds())
                if (!m.concealed()) return false;
            return h.winning_type()(win_type::self_drawn);
        }

        res_v all_triplets(const hand& h) {
            return utils::for_all_decompositions<res_t>(h, [](const hand::decomposition& d) {
                for (const meld& m : d.melds())
                    if (m.type() == meld_type::sequence) return false;
                return true;
            });
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

        constexpr res_t full_flush(const hand& h) {
            auto check_suit = [](const hand& h, suit_type st) {
                for (tile_t ti : tile_set::tiles_of_suit(st))
                    if (h.counter().count(ti)) return true;
                return false;
            };
            return (check_suit(h, suit_type::m) + check_suit(h, suit_type::p) + check_suit(h, suit_type::s) == 1);
        }

        res_v pure_straight(const hand& h) {
            return utils::for_all_decompositions<res_t>(h, [](const hand::decomposition& d) {
                for (tile_t ti : {2_m, 2_p, 2_s})
                    if (utils::contains(d, {meld(ti, meld_type::sequence), meld(ti + 3, meld_type::sequence), meld(ti + 6, meld_type::sequence)})) 
                        return true;
                return false;
            });
        }

        constexpr res_t seven_pairs(const hand& h) {
            return is_seven_pairs(h);
        }

        constexpr res_t big_seven_pairs(const hand& h) {
            if (!is_seven_pairs(h)) return false;
            for (tile_t ti : tile_set::all_tiles)
                if (h.counter().count(ti) == 4) return true;
            return false;
        }

        constexpr res_t all_258(const hand& h) {
            return h.counter().count() == h.counter().count({2_m, 5_m, 8_m, 2_p, 5_p, 8_p, 2_s, 5_s, 8_s});
        }

        res_v pair_258(const hand& h) {
            return utils::for_all_decompositions<res_t>(h, [](const hand::decomposition& d) {
                return d.original_hand().winning_type()(win_type::self_drawn) && d.pair().is_in({2_m, 5_m, 8_m, 2_p, 5_p, 8_p, 2_s, 5_s, 8_s});
            });
        }

        constexpr res_t all_terminal_pairs(const hand& h) {
            return h.counter().count() == h.counter().count({1_m, 9_m, 1_p, 9_p, 1_s, 9_s}) && is_seven_pairs(h);
        }

    }

    const std::vector<fan> fans = {
        fan("平和", {1}, criteria::pair_258),
        fan("门清自摸", {1, 1}, criteria::fully_concealed_hand),
        fan("杠上开花", {1, 1}, criteria::out_with_replacement_tile),
        fan("抢杠和", {2, 1}, criteria::robbing_the_kong),
        fan("海底和", {2, 1}, criteria::final_tile),
        fan("一条龙", {2}, criteria::pure_straight),
        fan("碰碰和", {3}, criteria::all_triplets),
        fan("小七对", {3, 1, 1}, criteria::seven_pairs),
        fan("全带幺", {3}, criteria::pure_outside_hand),
        fan("全带幺", {3, 1, 1}, criteria::all_terminal_pairs),
        fan("清一色", {4, 1}, criteria::full_flush),
        fan("豪华七对", {5, 1, 1}, criteria::big_seven_pairs),
        fan("将一色", {5, 1}, criteria::all_258)
    };

    enum indices {
        pair_258,
        fully_concealed_hand,
        out_with_replacement_tile,
        robbing_the_kong,
        final_tile,
        pure_straight,
        all_triplets,
        seven_pairs,
        pure_outside_hand,
        all_terminal_pairs,
        full_flush,
        big_seven_pairs,
        all_258,
        fan_count
    };

    std::vector<uint8_t> derepellenise(const std::vector<uint8_t>& f) {
        using enum indices;
        std::vector<uint8_t> fr = f;
        fr[seven_pairs] &= !fr[big_seven_pairs];
        fr[pair_258] &= !(fr[all_258] || fr[full_flush] || fr[all_triplets]);
        return fr;
    }

    std::pair<uint16_t, std::vector<uint8_t>> basic_score_from_fans(const std::vector<uint8_t>& f) {
        using enum indices;
        uint16_t res = 0;
        std::vector<uint8_t> fr = derepellenise(f);
        for (uint8_t i = 0; i < fan_count; ++i)
            res += fr[i] * fans[i].tag.value;
        return {res, fr};
    }

    const auto score_from_fans = [](const std::vector<std::vector<uint8_t>>& fan_results) -> scorer::result {
        using enum indices;
        std::vector<uint8_t> fr(fan_count, 0u);
        std::vector<uint8_t> fr_res(fan_count, 0u);
        const std::size_t c = fan_results[pair_258].size();
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
                ss << extend(fans[i].name, 15) << extend(std::to_string(fr_res[i] * fans[i].tag.value), -8);
                ss << '\n';
            }
        ss << std::string(23, '=') << '\n';
        ss << extend("总计", 5) << extend(std::to_string(res), -18) << '\n';
        return {true, res, ss.str()};
    };

    const scorer calculator(fans, score_from_fans, is_winning_hand);

}

#endif