#include "Shop.h"
#include "Character.h"
#include "HealthPotion.h"
#include "AttackBoost.h"
#include "RevivePotion.h"
#include "Equipment.h"
#include <iostream>
#include <memory>

Shop::Shop()
{
    AvailableItems.emplace_back(std::make_unique<HealthPotion>("체력 포션", 20, 1)); // 1 추가
    AvailableItems.emplace_back(std::make_unique<AttackBoost>("공격력 포션", 50, 1)); // 1 추가
    AvailableItems.emplace_back(std::make_unique<RevivePotion>("부활 포션", 100, 1)); // 1 추가

    AvailableItems.emplace_back(std::make_unique<Equipment>("목검", 100, 7, Equipment::EquipmentType::Weapon));
    AvailableItems.emplace_back(std::make_unique<Equipment>("나무갑옷", 100, 7, Equipment::EquipmentType::Armor));
    AvailableItems.emplace_back(std::make_unique<Equipment>("구리검", 200, 10, Equipment::EquipmentType::Weapon));
    AvailableItems.emplace_back(std::make_unique<Equipment>("구리갑옷", 200, 10, Equipment::EquipmentType::Armor));
    AvailableItems.emplace_back(std::make_unique<Equipment>("철검",300,20,Equipment::EquipmentType::Weapon));
    AvailableItems.emplace_back(std::make_unique<Equipment>("철갑옷",300,20,Equipment::EquipmentType::Armor));
    AvailableItems.emplace_back(std::make_unique<Equipment>("미스릴 검",500,35,Equipment::EquipmentType::Weapon));
    AvailableItems.emplace_back(std::make_unique<Equipment>("미스릴 갑옷",500,35,Equipment::EquipmentType::Armor));
    AvailableItems.emplace_back(std::make_unique<Equipment>("드래곤 슬레이어",1000,50,Equipment::EquipmentType::Weapon));
    AvailableItems.emplace_back(std::make_unique<Equipment>("드래곤 비늘갑옷",1000,50,Equipment::EquipmentType::Armor));
   
    ItemDescriptions["체력 포션"] = "체력을 50 회복합니다.";
    ItemDescriptions["공격력 포션"] = "공격력을 일시적으로 한번의 전투동안 10 증가시킵니다.";
    ItemDescriptions["부활 포션"] = "사망 시 사용되어 체력을 절반 회복합니다.";
    ItemDescriptions["목검"] = "공격력을 3 증가시키는 무기.";
    ItemDescriptions["나무갑옷"] = "방어력을 5 증가시키는 방어구.";
    ItemDescriptions["구리검"] = "공격력을 5 증가시키는 무기.";
    ItemDescriptions["구리갑옷"] = "방어력을 7 증가시키는 방어구.";
    ItemDescriptions["철검"] = "공격력을 20 증가시키는 무기.";
    ItemDescriptions["철갑옷"] = "방어력을 20 증가시키는 방어구.";
    ItemDescriptions["미스릴 검"] = "공격력을 20 증가시키는 무기.";
    ItemDescriptions["미스릴 갑옷"] = "방어력을 20 증가시키는 방어구.";
    ItemDescriptions["드래곤 슬레이어"] = "공격력을 50 증가시키는 무기.";
    ItemDescriptions["드래곤 비늘갑옷"] = "방어력을 50 증가시키는 방어구.";
    ItemDescriptions["고블린의 창"] = "고블린이 사용 하던 창 수집가들이 간혹 찾아서 상점에서 싼 가격에 매입된다.";
    ItemDescriptions["슬라임 체액"] = "슬라임을 잡으면서 채취한 슬라임의 체액 약재로 간혹 쓰여 상점에서 매우 싼 가격에 매입된다.";
    ItemDescriptions["트롤의 발톱"] = "트롤을 잡고 채취한 트롤의 발톱 약재로 쓰여 꽤 비싼 가격에 매입된다.";
    ItemDescriptions["오크의 도끼"] = "오크가 사용하던 도끼 수집가들이 매우 원하는 아이템이라 매우 비싼 가격에 매입된다.";
}

void Shop::DisplayItems() const
{
    std::cout << "상점 판매 아이템 목록:\n";
    for (size_t i = 0; i < AvailableItems.size(); ++i)
    {
        std::cout << i + 1 << ". " << AvailableItems[i]->GetName() << " - "
            << AvailableItems[i]->GetPrice() << " 골드\n";
    }
}

void Shop::BuyItem(int index,Character* player) {
    if(index < 0 || index >= AvailableItems.size()) {
        std::cout << "잘못된 선택입니다.\n";
        return;
    }

    // 가격 확인
    int price = AvailableItems[index]->GetPrice();

    if(player->Gold >= price) {
        player->Gold -= price;

        // 아이템을 인벤토리에 추가
        std::unique_ptr<Item> purchasedItem = std::move(AvailableItems[index]);
        std::cout << "구매 완료!\n";
        // 장비 아이템인지 확인
        Equipment* equipment = dynamic_cast<Equipment*>(purchasedItem.get());

        if(equipment) {
            // 장비 아이템 구매한 경우
            std::cout << "구매한 장비: " << equipment->GetName() << ", 타입: " << equipment->GetTypeText() << "\n";

            // 장비 구매
            player->AddItem(std::move(purchasedItem));

            // 장비 유형에 따른 추가 처리 (예: 무기, 방어구 등)
            if(equipment->GetEquimentType() == Equipment::EquipmentType::Weapon) {
                player->EquipWeapon(equipment);  // 무기 장착
            } else if(equipment->GetEquimentType() == Equipment::EquipmentType::Armor) {
                player->EquipArmor(equipment);   // 방어구 장착
            }

            // 구매 후 AvailableItems에서 해당 아이템 삭제
            AvailableItems.erase(AvailableItems.begin() + index);
        } else {
            // 사용 아이템인 경우
            std::cout << "구매한 아이템: " << purchasedItem->GetName() << " 사용 아이템입니다.\n";

            // 사용 아이템도 인벤토리에 추가
            player->AddItem(std::move(purchasedItem));
        }

        // 골드 차감
        player->Gold -= equipment ? equipment->GetPrice() : purchasedItem->GetPrice();




       
    } else {
        std::cout << "골드가 부족합니다.\n";
    }
}




// 아이템 판매
void Shop::SellItem(const std::string& itemName, Character* player)
{
    auto it = player->Inventory.find(itemName);
    if (it != player->Inventory.end() && it->second->GetAmount() > 0) {
        int sellPrice = it->second->GetPrice() / 2;
        player->Gold += sellPrice;
        it->second->DecreaseAmount(1);
        std::cout << itemName << "을(를) " << sellPrice << " 골드에 판매했습니다.\n";
    }
    else {
        std::cout << "이 아이템을 가지고 있지 않습니다.\n";
    }
}

// 아이템 상세 설명용 메서드(index 기준)
void Shop::DisplayItemDetails(int index) const
{
    if (index < 0 || index >= AvailableItems.size())
    {
        std::cout << "잘못된 아이템 선택입니다.\n";
        return;
    }

    const std::string& itemName = AvailableItems[index]->GetName();
    auto it = ItemDescriptions.find(itemName);
    if (it != ItemDescriptions.end())
    {
        std::cout << itemName << ": " << it->second << "\n";
    }
    else
    {
        std::cout << itemName << ": 설명이 없습니다.\n";
    }
}