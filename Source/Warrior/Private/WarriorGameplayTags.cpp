// WSL All Rights Reserved


#include "WarriorGameplayTags.h"

namespace WarriorGameplayTags
{
	//InputTags
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move,"InputTag.Move")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Look,"InputTag.Look")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_EquipAxe, "InputTag.EquipAxe")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_UnEquipAxe, "InputTag.UnEquipAxe")

	UE_DEFINE_GAMEPLAY_TAG(InputTag_LightAttack_Axe, "InputTag.LightAttack.Axe")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_HeavyAttack_Axe, "InputTag.HeavyAttack.Axe")
	//PlayerTags
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Equip_Axe, "Player.Ability.Equip.Axe")
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_UnEquip_Axe, "Player.Ability.UnEquip.Axe")
		//Attack
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Light_Axe, "Player.Ability.Attack.Light.Axe")
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Heavy_Axe, "Player.Ability.Attack.Heavy.Axe")


	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Axe,"Player.Weapon.Axe")

	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Equip_Axe,"Player.Event.Equip.Axe")
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_UnEquip_Axe, "Player.Event.UnEquip.Axe")
		////Attack
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Attack_Light_Axe, "Player.Event.Attack.Light.Axe")
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Attack_Heavy_Axe, "Player.Event.Attack.Heavy.Axe")

	UE_DEFINE_GAMEPLAY_TAG(Player_Status_JumpToFinisher, "Player.Status.JumpToFinisher")

	//EnemyTags
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Weapon,"Enemy.Weapon")

}
