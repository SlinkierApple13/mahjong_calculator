#include <iostream>

#include "../rules/momochai_lingque.hpp"

using namespace mahjong::tile_literals;
using namespace mahjong::honours;

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
            case '*': w |= mahjong::win_type::heavenly_or_earthly_hand; return true;
            case '!': w = (w & 0b1111111111111100u) | 0b00u; return true;
            case '@': w = (w & 0b1111111111111100u) | 0b01u; return true;
            case '#': w = (w & 0b1111111111111100u) | 0b10u; return true;
            case '$': w = (w & 0b1111111111111100u) | 0b11u; return true;
            default: return false;
        }
    });
    if (!momochai_lingque::input_verifier(h)) {
        std::cout << "- 无效输入.\n" << std::endl;
        return true;
    }
    auto res = momochai_lingque::calculator(h);
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
    std::cout << "[灵雀 第 28 版 计算器]\n\n";
    std::cout << "牌张：123456789m/p/s, ESWNCFP\n";
    std::cout << "门风:  ! - 東,    @ - 南,    # - 西,    $ - 北\n";
    std::cout << "和牌:  % - 自摸,  ^ - 岭上开花/抢杠,  & - 海底捞月/河底捞鱼,  * - 天和/地和\n";
    std::cout << "副露: [] - 暗杠, () - 其余\n\n输入的最后一张牌视为和张.\n\n";
    std::cout << "例: [WWWW](123m)456p789sFF#%^&\n";
    calculate("[WWWW](123m)456p789sFF#@%^&");
    while (calculate());
    return 0;
}