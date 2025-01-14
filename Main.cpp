#include "GameManager.h"
#include "Character.h"
#include "Shop.h"
#include <iostream>
#include <limits>

int main() {
    // �ִ� ���� ���� ����
    const size_t maxNameLength = 20;
    std::string playerName;

    std::cout << "ĳ���� �̸��� �Է����ּ��� (�ִ� " << maxNameLength << "��): ";

    std::getline(std::cin, playerName);

    // �̸� ���� ���� ó�� / ���� �Է� ó��
    while (playerName.empty() || playerName.length() > maxNameLength) {
        if (playerName.empty()) {
            std::cout << "�̸��� ��� ���� �� �����ϴ�. �ٽ� �Է����ּ���: ";
        }
        else {
            std::cout << "�̸��� �ʹ� ��ϴ�. �ִ� " << maxNameLength << "�� �̳��� �Է����ּ���: ";
        }
        std::getline(std::cin, playerName);
    }


    // ĳ���Ϳ� ���� ����
    Character* player = new Character(playerName);
    Shop* shop = new Shop();

    // ���� �Ŵ��� ���� �� ����
    GameManager gameManager;
    gameManager.StartGame(player, shop);

    // �޸� ����
    delete player;
    delete shop;

    return 0;
}
