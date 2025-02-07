// WSL All Rights Reserved


#include "WarriorTypes/WarriorStructTypes.h"
#include "AbilitySystem/Abilities/WarriorGameplayAbility.h"
#include "AbilitySystem/WarriorAbilitySystemComponent.h"
#include "InputMappingContext.h"
#include "AbilitySystem/Abilities/WarriorHeroGameplayAbility.h"

//#include "AbilitySystem/Abilities/WarriorEnemyGameplayAbility.h"

//#include "AnimaInstances/Hero/WarriorHeroLinkedAnimLayer.h"

bool FWarriorHeroAbilitySet::IsValid() const
{
    return InputTag.IsValid() && AbilityToGrant;
}

//bool FWarriorEnemyAbilitySet::IsValid() const
//{
//    return InputTag.IsValid() && AbilityToGrant;
//}
