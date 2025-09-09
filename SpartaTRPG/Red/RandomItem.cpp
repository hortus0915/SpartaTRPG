#include "RandomItem.h"
#include "../Black/Singletons/CommonManagers.h"
#include "../Black/CommonFuncs.h"

void RandomItem::Init()
{
    auto& boxItems = randomItemTable[RandomItemType::Box];
    auto& stage1BoxItems = boxItems[1];
    stage1BoxItems.push_back(Item(Item::GetItemUID(ItemType::Cost, ItemValueType::Cost, 1)));
    stage1BoxItems.push_back(Item(Item::GetItemUID(ItemType::Cost, ItemValueType::Cost, 1)));
    stage1BoxItems.push_back(Item(Item::GetItemUID(ItemType::Cost, ItemValueType::Cost, 1)));
    stage1BoxItems.push_back(Item(Item::GetItemUID(ItemType::Cost, ItemValueType::Cost, 1)));
    stage1BoxItems.push_back(Item(Item::GetItemUID(ItemType::Eequipment, ItemValueType::StatAdd_HP, 1)));
    stage1BoxItems.push_back(Item(Item::GetItemUID(ItemType::Eequipment, ItemValueType::StatAdd_HP, 2)));
    stage1BoxItems.push_back(Item(Item::GetItemUID(ItemType::Eequipment, ItemValueType::StatAdd_HP, 3)));
    stage1BoxItems.push_back(Item(Item::GetItemUID(ItemType::Eequipment, ItemValueType::StatAdd_HP, 4)));
    stage1BoxItems.push_back(Item(Item::GetItemUID(ItemType::Potion, ItemValueType::HPHeal, 1)));
    stage1BoxItems.push_back(Item(Item::GetItemUID(ItemType::Potion, ItemValueType::HPHeal, 1)));
    stage1BoxItems.push_back(Item(Item::GetItemUID(ItemType::Potion, ItemValueType::HPHeal, 2)));
    auto& stage2BoxItems = boxItems[2];
    stage2BoxItems.push_back(Item(Item::GetItemUID(ItemType::Cost, ItemValueType::Cost, 1)));
    stage2BoxItems.push_back(Item(Item::GetItemUID(ItemType::Cost, ItemValueType::Cost, 1)));
    stage2BoxItems.push_back(Item(Item::GetItemUID(ItemType::Cost, ItemValueType::Cost, 1)));
    stage2BoxItems.push_back(Item(Item::GetItemUID(ItemType::Cost, ItemValueType::Cost, 1)));
    stage2BoxItems.push_back(Item(Item::GetItemUID(ItemType::Eequipment, ItemValueType::StatAdd_HP, 2)));
    stage2BoxItems.push_back(Item(Item::GetItemUID(ItemType::Eequipment, ItemValueType::StatAdd_HP, 3)));
    stage2BoxItems.push_back(Item(Item::GetItemUID(ItemType::Eequipment, ItemValueType::StatAdd_HP, 4)));
    stage2BoxItems.push_back(Item(Item::GetItemUID(ItemType::Eequipment, ItemValueType::StatAdd_HP, 5)));
    stage2BoxItems.push_back(Item(Item::GetItemUID(ItemType::Potion, ItemValueType::HPHeal, 1)));
    stage2BoxItems.push_back(Item(Item::GetItemUID(ItemType::Potion, ItemValueType::HPHeal, 2)));
    stage2BoxItems.push_back(Item(Item::GetItemUID(ItemType::Potion, ItemValueType::HPHeal, 3)));
    auto& stage3BoxItems = boxItems[3];
    stage3BoxItems.push_back(Item(Item::GetItemUID(ItemType::Cost, ItemValueType::Cost, 1)));
    stage3BoxItems.push_back(Item(Item::GetItemUID(ItemType::Cost, ItemValueType::Cost, 1)));
    stage3BoxItems.push_back(Item(Item::GetItemUID(ItemType::Cost, ItemValueType::Cost, 1)));
    stage3BoxItems.push_back(Item(Item::GetItemUID(ItemType::Cost, ItemValueType::Cost, 1)));
    stage3BoxItems.push_back(Item(Item::GetItemUID(ItemType::Eequipment, ItemValueType::StatAdd_HP, 3)));
    stage3BoxItems.push_back(Item(Item::GetItemUID(ItemType::Eequipment, ItemValueType::StatAdd_HP, 4)));
    stage3BoxItems.push_back(Item(Item::GetItemUID(ItemType::Eequipment, ItemValueType::StatAdd_HP, 5)));
    stage3BoxItems.push_back(Item(Item::GetItemUID(ItemType::Eequipment, ItemValueType::StatAdd_HP, 6)));
    stage3BoxItems.push_back(Item(Item::GetItemUID(ItemType::Potion, ItemValueType::HPHeal, 2)));
    stage3BoxItems.push_back(Item(Item::GetItemUID(ItemType::Potion, ItemValueType::HPHeal, 2)));
    stage3BoxItems.push_back(Item(Item::GetItemUID(ItemType::Potion, ItemValueType::HPHeal, 3)));

    auto& monsterItems = randomItemTable[RandomItemType::Monster];
    auto& stage1MonsterItems = monsterItems[1];
    stage1MonsterItems.push_back(Item(Item::GetItemUID(ItemType::Cost, ItemValueType::Cost, 1)));
    stage1MonsterItems.push_back(Item(Item::GetItemUID(ItemType::Cost, ItemValueType::Cost, 1)));
    stage1MonsterItems.push_back(Item(Item::GetItemUID(ItemType::Cost, ItemValueType::Cost, 1)));
    stage1MonsterItems.push_back(Item(Item::GetItemUID(ItemType::Cost, ItemValueType::Cost, 1)));
    stage1MonsterItems.push_back(Item(Item::GetItemUID(ItemType::Eequipment, ItemValueType::StatAdd_HP, 1)));
    stage1MonsterItems.push_back(Item(Item::GetItemUID(ItemType::Eequipment, ItemValueType::StatAdd_HP, 2)));
    stage1MonsterItems.push_back(Item(Item::GetItemUID(ItemType::Eequipment, ItemValueType::StatAdd_HP, 3)));
    stage1MonsterItems.push_back(Item(Item::GetItemUID(ItemType::Eequipment, ItemValueType::StatAdd_HP, 4)));
    stage1MonsterItems.push_back(Item(Item::GetItemUID(ItemType::Potion, ItemValueType::HPHeal, 1)));
    stage1MonsterItems.push_back(Item(Item::GetItemUID(ItemType::Potion, ItemValueType::HPHeal, 1)));
    stage1MonsterItems.push_back(Item(Item::GetItemUID(ItemType::Potion, ItemValueType::HPHeal, 2)));
    auto& stage2MonsterItems = monsterItems[2];
    stage2MonsterItems.push_back(Item(Item::GetItemUID(ItemType::Cost, ItemValueType::Cost, 1)));
    stage2MonsterItems.push_back(Item(Item::GetItemUID(ItemType::Cost, ItemValueType::Cost, 1)));
    stage2MonsterItems.push_back(Item(Item::GetItemUID(ItemType::Cost, ItemValueType::Cost, 1)));
    stage2MonsterItems.push_back(Item(Item::GetItemUID(ItemType::Cost, ItemValueType::Cost, 1)));
    stage2MonsterItems.push_back(Item(Item::GetItemUID(ItemType::Eequipment, ItemValueType::StatAdd_HP, 2)));
    stage2MonsterItems.push_back(Item(Item::GetItemUID(ItemType::Eequipment, ItemValueType::StatAdd_HP, 3)));
    stage2MonsterItems.push_back(Item(Item::GetItemUID(ItemType::Eequipment, ItemValueType::StatAdd_HP, 4)));
    stage2MonsterItems.push_back(Item(Item::GetItemUID(ItemType::Eequipment, ItemValueType::StatAdd_HP, 5)));
    stage2MonsterItems.push_back(Item(Item::GetItemUID(ItemType::Potion, ItemValueType::HPHeal, 1)));
    stage2MonsterItems.push_back(Item(Item::GetItemUID(ItemType::Potion, ItemValueType::HPHeal, 2)));
    stage2MonsterItems.push_back(Item(Item::GetItemUID(ItemType::Potion, ItemValueType::HPHeal, 3)));
    auto& stage3MonsterItems = monsterItems[3];
    stage3MonsterItems.push_back(Item(Item::GetItemUID(ItemType::Cost, ItemValueType::Cost, 1)));
    stage3MonsterItems.push_back(Item(Item::GetItemUID(ItemType::Cost, ItemValueType::Cost, 1)));
    stage3MonsterItems.push_back(Item(Item::GetItemUID(ItemType::Cost, ItemValueType::Cost, 1)));
    stage3MonsterItems.push_back(Item(Item::GetItemUID(ItemType::Cost, ItemValueType::Cost, 1)));
    stage3MonsterItems.push_back(Item(Item::GetItemUID(ItemType::Eequipment, ItemValueType::StatAdd_HP, 3)));
    stage3MonsterItems.push_back(Item(Item::GetItemUID(ItemType::Eequipment, ItemValueType::StatAdd_HP, 4)));
    stage3MonsterItems.push_back(Item(Item::GetItemUID(ItemType::Eequipment, ItemValueType::StatAdd_HP, 5)));
    stage3MonsterItems.push_back(Item(Item::GetItemUID(ItemType::Eequipment, ItemValueType::StatAdd_HP, 6)));
    stage3MonsterItems.push_back(Item(Item::GetItemUID(ItemType::Potion, ItemValueType::HPHeal, 2)));
    stage3MonsterItems.push_back(Item(Item::GetItemUID(ItemType::Potion, ItemValueType::HPHeal, 2)));
    stage3MonsterItems.push_back(Item(Item::GetItemUID(ItemType::Potion, ItemValueType::HPHeal, 3)));

    auto& miniGameItems = randomItemTable[RandomItemType::MiniGame];
    auto& stage1MiniGameItems = miniGameItems[1];
    stage1MiniGameItems.push_back(Item(Item::GetItemUID(ItemType::Cost, ItemValueType::Cost, 1)));
    stage1MiniGameItems.push_back(Item(Item::GetItemUID(ItemType::Cost, ItemValueType::Cost, 1)));
    stage1MiniGameItems.push_back(Item(Item::GetItemUID(ItemType::Cost, ItemValueType::Cost, 1)));
    stage1MiniGameItems.push_back(Item(Item::GetItemUID(ItemType::Cost, ItemValueType::Cost, 1)));
    stage1MiniGameItems.push_back(Item(Item::GetItemUID(ItemType::Potion, ItemValueType::HPHeal, 1)));
    stage1MiniGameItems.push_back(Item(Item::GetItemUID(ItemType::Potion, ItemValueType::HPHeal, 1)));
    stage1MiniGameItems.push_back(Item(Item::GetItemUID(ItemType::Potion, ItemValueType::HPHeal, 2)));
    auto& stage2MiniGameItems = miniGameItems[2];
    stage2MiniGameItems.push_back(Item(Item::GetItemUID(ItemType::Cost, ItemValueType::Cost, 1)));
    stage2MiniGameItems.push_back(Item(Item::GetItemUID(ItemType::Cost, ItemValueType::Cost, 1)));
    stage2MiniGameItems.push_back(Item(Item::GetItemUID(ItemType::Cost, ItemValueType::Cost, 1)));
    stage2MiniGameItems.push_back(Item(Item::GetItemUID(ItemType::Cost, ItemValueType::Cost, 1)));
    stage2MiniGameItems.push_back(Item(Item::GetItemUID(ItemType::Potion, ItemValueType::HPHeal, 1)));
    stage2MiniGameItems.push_back(Item(Item::GetItemUID(ItemType::Potion, ItemValueType::HPHeal, 2)));
    stage2MiniGameItems.push_back(Item(Item::GetItemUID(ItemType::Potion, ItemValueType::HPHeal, 3)));
    auto& stage3MiniGameItems = miniGameItems[3];
    stage3MiniGameItems.push_back(Item(Item::GetItemUID(ItemType::Cost, ItemValueType::Cost, 1)));
    stage3MiniGameItems.push_back(Item(Item::GetItemUID(ItemType::Cost, ItemValueType::Cost, 1)));
    stage3MiniGameItems.push_back(Item(Item::GetItemUID(ItemType::Cost, ItemValueType::Cost, 1)));
    stage3MiniGameItems.push_back(Item(Item::GetItemUID(ItemType::Cost, ItemValueType::Cost, 1)));
    stage3MiniGameItems.push_back(Item(Item::GetItemUID(ItemType::Potion, ItemValueType::HPHeal, 2)));
    stage3MiniGameItems.push_back(Item(Item::GetItemUID(ItemType::Potion, ItemValueType::HPHeal, 2)));
    stage3MiniGameItems.push_back(Item(Item::GetItemUID(ItemType::Potion, ItemValueType::HPHeal, 3)));
}

Item* RandomItem::GetRandomItem(RandomItemType randomType)
{
    if (randomType == RandomItemType::None)
        return nullptr;

    auto& allIitems = randomItemTable[randomType];
    auto& stageItems = allIitems[USERMANAGER->GetStage()];

    if (stageItems.size() == 0)
        return nullptr;

    int index = GetIntRange(0, stageItems.size() - 1);
    return &(stageItems[index]);
}
