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
    if (!h.is_valid()) {
        std::cout << "- ��Ч����.\n" << std::endl;
        return true;
    }
    auto res = momochai_lingque::calculator(h);
    if (!res)
        std::cout << "- ���Ʋ��ܺ���.\n";
    else std::cout << res.tag();
    std::cout << std::endl;
    return true;
}

int main() {
    std::cout << "[��ȸ �� 27 �� ������]\n\n";
    std::cout << "�ŷ�:  ! - �|,    @ - ��,    # - ��,    $ - ��\n";
    std::cout << "����:  % - ����,  ^ - ���Ͽ���/����,  & - ����/�ӵ�,  * - ���/�غ�\n";
    std::cout << "��¶: [] - ����, () - ����\n\n";
    std::cout << "��: [FFFF](123m)456p789sWW#%\n";
    calculate("[FFFF](123m)456p789sWW#%");
    while (calculate());
    return 0;
}