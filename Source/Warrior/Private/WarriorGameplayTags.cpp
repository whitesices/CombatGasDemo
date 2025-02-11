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
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_HitPause, "Player.Ability.HitPause")


	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Axe,"Player.Weapon.Axe")

	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Equip_Axe,"Player.Event.Equip.Axe")
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_UnEquip_Axe, "Player.Event.UnEquip.Axe")
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_HitPause, "Player.Event.HitPause")
		////Attack
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Attack_Light_Axe, "Player.Event.Attack.Light.Axe")
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Attack_Heavy_Axe, "Player.Event.Attack.Heavy.Axe")

	UE_DEFINE_GAMEPLAY_TAG(Player_Status_JumpToFinisher, "Player.Status.JumpToFinisher")

	UE_DEFINE_GAMEPLAY_TAG(Player_SetByCaller_AttackType_Light, "Player.SetByCaller.AttackType.Light")
	UE_DEFINE_GAMEPLAY_TAG(Player_SetByCaller_AttackType_Heavy, "Player.SetByCaller.AttackType.Heavy")

	//EnemyTags
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Weapon,"Enemy.Weapon")
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Melee, "Enemy.Ability.Melee")
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Ranged, "Enemy.Ability.Ranged")

	//ShareTags
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_MeleeHit,"Shared.Event.MeleeHit")
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_HitReact,"Shared.Event.HitReact")

	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_HitReact, "Shared.Ability.HitReact")
	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_BaseDamage,"Shared.SetByCaller.BaseDamage")

}
