// WSL All Rights Reserved


#include "Components/Combat/PawnCombatComponent.h"
#include "Items/Weapons/WarriorWeaponBase.h"

#include "Components/BoxComponent.h"

#include "WarriorDebugHelper.h"


void UPawnCombatComponent::RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, AWarriorWeaponBase* InWeaponToRegister, bool bResgisterAsEquippedWeapon)
{
	//检查有效性
	checkf( !CharacterCarriedWeaponMap.Contains( InWeaponTagToRegister ) , TEXT("A named %s has already been added as carried weapon") , *InWeaponTagToRegister.ToString() );
	//检查有效性
	check(InWeaponToRegister);

	CharacterCarriedWeaponMap.Emplace( InWeaponTagToRegister , InWeaponToRegister );

	//当完成武器注册后进行武器类中碰撞单播委托的触发绑定(观察者模式)
	InWeaponToRegister->OnWeaponHitTarget.BindUObject(this, &ThisClass::OnHitTargetActor);
	InWeaponToRegister->OnWeaponPulledFromTarget.BindUObject(this , &ThisClass::OnWeaponPulledFromTargetActor);

	//如果装备了
	if (bResgisterAsEquippedWeapon)
	{
		CurrentEquippedWeaponTag = InWeaponTagToRegister;
	}

	//打印相应信息
	/*const FString WeaponString = FString::Printf(TEXT("A weapon named: %s has been registered using the tag %s "), *InWeaponToRegister->GetName() , *InWeaponTagToRegister.ToString() );
	Debug::print( WeaponString );*/
}

AWarriorWeaponBase* UPawnCombatComponent::GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const
{
	//判断Gameplaytag的有效性
	if (CharacterCarriedWeaponMap.Contains(InWeaponTagToGet))
	{
		if (AWarriorWeaponBase* const* FoundWeapon = CharacterCarriedWeaponMap.Find(InWeaponTagToGet))
		{
			return *FoundWeapon;
		}
	}


	return nullptr;
}

AWarriorWeaponBase* UPawnCombatComponent::GetCharacterCurrentEquippedWeapon() const
{
	//判断当前装备武器的Tag是否有效
	if (!CurrentEquippedWeaponTag.IsValid())
	{
		return nullptr;
	}

	return GetCharacterCarriedWeaponByTag(CurrentEquippedWeaponTag);
}

void UPawnCombatComponent::ToggleWeaponCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType)
{
	//检查触发的武器碰撞类型
	if (ToggleDamageType == EToggleDamageType::CurrentEquippedWeapon )
	{
		//创建一个武器类局部变量来存储获得武器类
		AWarriorWeaponBase* WeaponToToggle = GetCharacterCurrentEquippedWeapon();
		//检查WeaponToToggle是否有效
		check( WeaponToToggle );

		//是否启用碰撞
		if (bShouldEnable)
		{
			WeaponToToggle->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
			/*Debug::print( WeaponToToggle->GetName() + TEXT(" collision Enabled ") , FColor::Green );*/
		}
		else
		{
			WeaponToToggle->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			/*Debug::print(WeaponToToggle->GetName() + TEXT(" collision Disabled "), FColor::Red);*/

			//指控OverlappedActors
			OverlappedActors.Empty();
		}
		
	}

	//TODO: Handle body collision boxes
}

void UPawnCombatComponent::OnHitTargetActor(AActor* HitActor)
{
}

void UPawnCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{
}
