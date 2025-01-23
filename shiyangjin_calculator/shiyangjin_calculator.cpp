#include <iostream>

#include "../rules/shiyangjin.hpp"

using namespace mahjong::tile_literals;

bool calculate(const std::string& s0 = "") {
    std::string str;
    if (s0 == "") {
        std::cout << "> ";
        std::getline(std::cin, str);
    } else str = s0;
    if (str.empty()) return false;
    auto h = mahjong::utils::parse_hand(str, 0u, 0u, true, [](char c, mahjong::win_t& w) {
        switch (c) {
            case '%': w |= mahjong::win_type::self_drawn; return true;
            case '^': w |= mahjong::win_type::kong_related; return true;
            case '&': w |= mahjong::win_type::final_tile; return true;
            default: return false;
        }
    });
    if (!shiyangjin::input_verifier(h)) {
        std::cout << "- 无效输入.\n" << std::endl;
        return true;
    }
    auto res = shiyangjin::calculator(h);
    if (!res)
        std::cout << "- 此牌不能和牌.\n";
    else std::cout << res.tag();
    std::cout << std::endl;
    return true;
}

int main() {
#ifdef _WIN32
    setlocale(LC_ALL, "zh_CN.UTF-8");
#endif
    std::cout << "[十样锦麻将计算器]\n\n";
    std::cout << "牌张：123456789m/p/s\n";
    std::cout << "和牌:  % - 自摸,  ^ - 杠上开花/抢杠和,  & - 海底和\n";
    std::cout << "副露: [] - 暗杠, () - 其余\n\n输入的最后一张牌视为和张.\n\n";
    std::cout << "例: [3333s](789p)12356p22s4p%^\n";
    calculate("[3333s](789p)12356p22s4p%^");
    while (calculate());
    return 0;
}