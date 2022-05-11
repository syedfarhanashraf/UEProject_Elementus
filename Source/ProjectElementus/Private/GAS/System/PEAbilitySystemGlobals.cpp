// Author: Lucas Vilas-Boas
// Year: 2022
// Repo: https://github.com/lucoiso/UEProject_Elementus

#include "GAS/System/PEAbilitySystemGlobals.h"
#include "GameplayEffect.h"
#include "Engine/DataTable.h"

UPEAbilitySystemGlobals::UPEAbilitySystemGlobals(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static const ConstructorHelpers::FClassFinder<UGameplayEffect> DeathGameplayEffect_ClassRef(
		TEXT("/Game/Main/GAS/Effects/States/GE_Death"));
	if constexpr (&DeathGameplayEffect_ClassRef.Class != nullptr)
	{
		GlobalDeathEffect = DeathGameplayEffect_ClassRef.Class;
	}

	static const ConstructorHelpers::FClassFinder<UGameplayEffect> StunGameplayEffect_ClassRef(
		TEXT("/Game/Main/GAS/Effects/States/GE_Stun"));
	if constexpr (&StunGameplayEffect_ClassRef.Class != nullptr)
	{
		GlobalStunEffect = StunGameplayEffect_ClassRef.Class;
	}

	static const ConstructorHelpers::FObjectFinder<UDataTable> MainAttributesMetaData_ObjRef(
		TEXT("/Game/Main/GAS/Data/DT_BasicStatusAS"));
	if constexpr (&MainAttributesMetaData_ObjRef.Object != nullptr)
	{
		MainStatusAttributeData = MainAttributesMetaData_ObjRef.Object;
	}

	static const ConstructorHelpers::FObjectFinder<UDataTable> CustomAttributesMetaData_ObjRef(
		TEXT("/Game/Main/GAS/Data/DT_CustomStatusAS"));
	if constexpr (&CustomAttributesMetaData_ObjRef.Object != nullptr)
	{
		CustomStatusAttributeData = CustomAttributesMetaData_ObjRef.Object;
	}

	static const ConstructorHelpers::FObjectFinder<UDataTable> LevelingAttributesMetaData_ObjRef(
		TEXT("/Game/Main/GAS/Data/DT_LevelingAS"));
	if constexpr (&LevelingAttributesMetaData_ObjRef.Object != nullptr)
	{
		LevelingAttributeData = LevelingAttributesMetaData_ObjRef.Object;
	}

	static const ConstructorHelpers::FObjectFinder<UDataTable> LevelingBonus_ObjRef(
		TEXT("/Game/Main/GAS/Data/DT_LevelingBonus"));
	if constexpr (&LevelingBonus_ObjRef.Object != nullptr)
	{
		LevelingBonusData = LevelingBonus_ObjRef.Object;
	}

	static const ConstructorHelpers::FObjectFinder<UEnum> InputIDEnum_ObjRef(
		TEXT("/Game/Main/GAS/Data/EN_AbilityInputID"));
	if constexpr (&InputIDEnum_ObjRef.Object != nullptr)
	{
		MainInputIDEnum = InputIDEnum_ObjRef.Object;
	}
}

UGameplayEffect* UPEAbilitySystemGlobals::GetGlobalDeathEffect() const
{
	return GlobalDeathEffect.LoadSynchronous()->GetDefaultObject<UGameplayEffect>();
}

UGameplayEffect* UPEAbilitySystemGlobals::GetGlobalStunEffect() const
{
	return GlobalStunEffect.LoadSynchronous()->GetDefaultObject<UGameplayEffect>();
}

UDataTable* UPEAbilitySystemGlobals::GetMainStatusAttributeMetaData() const
{
	return MainStatusAttributeData.LoadSynchronous();
}

UDataTable* UPEAbilitySystemGlobals::GetCustomStatusAttributeMetaData() const
{
	return CustomStatusAttributeData.LoadSynchronous();
}

UDataTable* UPEAbilitySystemGlobals::GetLevelingAttributeMetaData() const
{
	return LevelingAttributeData.LoadSynchronous();
}

UDataTable* UPEAbilitySystemGlobals::GetLevelingBonusData() const
{
	return LevelingBonusData.LoadSynchronous();
}

UEnum* UPEAbilitySystemGlobals::GetMainInputIDEnum() const
{
	return MainInputIDEnum.LoadSynchronous();
}
