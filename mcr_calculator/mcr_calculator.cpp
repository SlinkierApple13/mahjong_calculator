#include <iostream>

#include "../rules/mcr_mahjong.hpp"

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
            case '*': w |= mahjong::win_type::heavenly_or_earthly_hand; return true; // this is used for "last_tile" instead
            case '!': 
                if (w & 0b0000000100000000u) {
                    w = (w & 0b1111111111111100u) | 0b00u;
                } else { 
                    w = (w & 0b1111111111110011u) | 0b0000u;
                    w |= 0b0000000100000000u;
                }
                return true;
            case '@':
                if (w & 0b0000000100000000u) {
                    w = (w & 0b1111111111111100u) | 0b01u;
                } else { 
                    w = (w & 0b1111111111110011u) | 0b0100u;
                    w |= 0b0000000100000000u;
                }
                return true;
            case '#':
                if (w & 0b0000000100000000u) {
                    w = (w & 0b1111111111111100u) | 0b10u;
                } else { 
                    w = (w & 0b1111111111110011u) | 0b1000u;
                    w |= 0b0000000100000000u;
                }
                return true;
            case '$':
                if (w & 0b0000000100000000u) {
                    w = (w & 0b1111111111111100u) | 0b11u;
                } else { 
                    w = (w & 0b1111111111110011u) | 0b1100u;
                    w |= 0b0000000100000000u;
                }
                return true;
            default: return false;
        }
    });
    if (!h.is_valid()) {
        std::cout << "- ��Ч����.\n" << std::endl;
        return true;
    }
    auto res = mcr_mahjong::calculator(h);
    if (!res)
        std::cout << "- ���Ʋ��ܺ���.\n";
    else std::cout << res.tag();
    std::cout << std::endl;
    return true;
}

int main() {
    std::cout << "[������ȸ 1998 �� ������]\n\n";
    std::cout << "Ȧ�ŷ�:  ! - �|,    @ - ��,    # - ��,    $ - ��\n";
    std::cout << "  ����:  % - ����,  ^ - ���Ͽ���/����,  & - ����/�ӵ�,  * - ����\n";
    std::cout << "  ��¶: [] - ����, () - ����\n\n";
    std::cout << "��: [WWWW](123m)456p789sFF#@%\n";
    calculate("[WWWW](123m)456p789sFF#@%");
    while (calculate());
    return 0;
}