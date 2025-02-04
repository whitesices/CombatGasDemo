// WSL All Rights Reserved


#include "DataAssets/StartupData/DataAsset_HeroStartUpData.h"
#include "AbilitySystem/Abilities/WarriorGameplayAbility.h"
#include "AbilitySystem/WarriorAbilitySystemComponent.h"


bool FWarriorHeroAbilitySet::IsValid() const
{
    return InputTag.IsValid() && AbilityToGrant;
}

void UDataAsset_HeroStartUpData::GiveToAbilitySystemComponent(UWarriorAbilitySystemComponent* InWarriorASCToGive, int32 ApplyLevel)
{
    Super::GiveToAbilitySystemComponent(InWarriorASCToGive, ApplyLevel);

    //激活绑定的GA与InputTag
    for (const FWarriorHeroAbilitySet& AbilitySet : HeroStartUpAbilitySets)
    {
        if (!AbilitySet.IsValid()) continue;

        FGameplayAbilitySpec AbilitySpec( AbilitySet.AbilityToGrant);
        AbilitySpec.SourceObject = InWarriorASCToGive->GetAvatarActor();
        AbilitySpec.Level = ApplyLevel;
        AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);

        InWarriorASCToGive->GiveAbility(AbilitySpec);
    }

}
