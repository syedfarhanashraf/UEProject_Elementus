// Author: Lucas Vilas-Boas
// Year: 2022
// Repo: https://github.com/lucoiso/UEProject_Elementus

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Management/Data/GASAbilityData.h"
#include "GAS/System/GASTrace.h"
#include "GASGameplayAbility.generated.h"

class AGameplayAbilityTargetActor;
class AProjectileActor;
/**
 *
 */
UCLASS(Abstract, NotPlaceable, Blueprintable, HideDropdown, Category = "Custom GAS | Components")
class PROJECTELEMENTUS_API UGASGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UGASGameplayAbility(const FObjectInitializer& ObjectInitializer);

	FORCEINLINE virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("Ability", GetFName());
	}

	/* Mix with bEndAbilityAfterActiveTime to end ability with a pre-determined time */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Custom GAS | Defaults")
		float AbilityActiveTime;

	/* This will determine the line trace distance to perform */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Custom GAS | Defaults")
		float AbilityMaxRange;

protected:
	/* Will finish ability when the AbilityActiveTime is complete */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Custom GAS | Defaults")
		bool bEndAbilityAfterActiveTime;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Custom GAS | Defaults")
		bool bAutoActivateOnGrant;

	/* Gameplay Effects that will be applied to self via ApplyAbilityEffectsToSelf function */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Custom GAS | Defaults")
		TArray<FGameplayEffectGroupedData> SelfAbilityEffects;

	/* Gameplay Effects that will be applied to target via ApplyAbilityEffectsToTarget function */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Custom GAS | Defaults")
		TArray<FGameplayEffectGroupedData> TargetAbilityEffects;

	/* Single Montage to play with ActivateWaitMontageTask function - You can mix this with ActivateWaitGameplayEventTask function */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Custom GAS | Defaults")
		UAnimMontage* AbilityAnimation;

private:
	virtual void
		OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override final;

	virtual void PreActivate(const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		FOnGameplayAbilityEnded::FDelegate* OnGameplayAbilityEndedDelegate,
		const FGameplayEventData* TriggerEventData = nullptr) override final;

	void ActivateWaitCancelInputTask();

	UFUNCTION(Category = "Custom GAS | Callbacks")
		void WaitCancelInput_Callback();

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		bool bReplicateEndAbility,
		bool bWasCancelled) override final;

	/* Wait Confirm input and call WaitConfirmInput_Callback function */
	UFUNCTION(BlueprintCallable, Category = "Custom GAS | Delegates")
		void ActivateWaitConfirmInputTask();

	/* Wait a Gameplay Tag to be added to owner and call WaitAddedTag_Callback function */
	UFUNCTION(BlueprintCallable, Category = "Custom GAS | Delegates")
		void ActivateWaitAddedTagTask(const FGameplayTag Tag);

	/* Wait a Gameplay Tag to be removed from owner and call WaitRemovedTag_Callback function */
	UFUNCTION(BlueprintCallable, Category = "Custom GAS | Delegates")
		void ActivateWaitRemovedTagTask(const FGameplayTag Tag);

	/* Perform a animation montage and call WaitMontage_Callback function */
	UFUNCTION(BlueprintCallable, Category = "Custom GAS | Delegates")
		void ActivateWaitMontageTask();

	/* Performs targeting and call WaitTargetData_Callback function */
	UFUNCTION(BlueprintCallable, Category = "Custom GAS | Delegates")
		void ActivateWaitTargetDataTask(const TEnumAsByte<EGameplayTargetingConfirmation::Type> TargetingConfirmation,
			const TSubclassOf<AGameplayAbilityTargetActor_Trace> TargetActorClass,
			struct FTargetActorSpawnParams TargetParameters);

	/* Start a task to wait for a Gameplay Event and call WaitGameplayEvent_Callback function */
	UFUNCTION(BlueprintCallable, Category = "Custom GAS | Delegates")
		void ActivateWaitGameplayEventTask(const FGameplayTag EventTag);

	/* Spawn a actor and call SpawnActor_Callback function */
	UFUNCTION(BlueprintCallable, Category = "Custom GAS | Delegates")
		void ActivateSpawnActorTask(const FGameplayAbilityTargetDataHandle TargetDataHandle,
			TSubclassOf<AActor> ActorClass);

	/* Default callback for ActivateWaitMontageTask function */
	UFUNCTION(BlueprintNativeEvent, Category = "Custom GAS | Callbacks")
		void WaitMontage_Callback();

	virtual void WaitMontage_Callback_Implementation()
	{
	}; // Override this function on children classes.

	/* Default callback for ActivateWaitConfirmInputTask function */
	UFUNCTION(BlueprintNativeEvent, Category = "Custom GAS | Callbacks")
		void WaitConfirmInput_Callback();

	virtual void WaitConfirmInput_Callback_Implementation()
	{
	}; // Override this function on children classes.

	/* Default callback for ActivateWaitAddedTagTask function */
	UFUNCTION(BlueprintNativeEvent, Category = "Custom GAS | Callbacks")
		void WaitAddedTag_Callback();

	virtual void WaitAddedTag_Callback_Implementation()
	{
	}; // Override this function on children classes.

	/* Default callback for ActivateWaitRemovedTagTask function */
	UFUNCTION(BlueprintNativeEvent, Category = "Custom GAS | Callbacks")
		void WaitRemovedTag_Callback();

	virtual void WaitRemovedTag_Callback_Implementation()
	{
	}; // Override this function on children classes.

	/* Default callback for ActivateWaitAttributeChangeTask function */
	UFUNCTION(BlueprintNativeEvent, Category = "Custom GAS | Callbacks")
		void WaitAttributeChange_Callback();

	virtual void WaitAttributeChange_Callback_Implementation()
	{
	}; // Override this function on children classes.

	/* Default callback for ActivateWaitGameplayEventTask function */
	UFUNCTION(BlueprintNativeEvent, Category = "Custom GAS | Callbacks")
		void WaitGameplayEvent_Callback(FGameplayEventData Payload);

	virtual void WaitGameplayEvent_Callback_Implementation(FGameplayEventData Payload)
	{
	}; // Override this function on children classes.

	/* Default callback for ActivateWaitTargetDataTask function */
	UFUNCTION(BlueprintNativeEvent, Category = "Custom GAS | Callbacks")
		void WaitTargetData_Callback(const FGameplayAbilityTargetDataHandle& TargetDataHandle);

	virtual void WaitTargetData_Callback_Implementation(const FGameplayAbilityTargetDataHandle& TargetDataHandle)
	{
	}; // Override this function on children classes.

	/* Default callback for ActivateSpawnActorTask function */
	UFUNCTION(BlueprintNativeEvent, Category = "Custom GAS | Callbacks")
		void SpawnActor_Callback(AActor* SpawnedActor);

	virtual void SpawnActor_Callback_Implementation(AActor* SpawnedActor)
	{
	}; // Override this function on children classes.

	/* Activate a Gameplay Cue */
	UFUNCTION(BlueprintCallable, Category = "Custom GAS | Management")
		void ActivateGameplayCues(const FGameplayTag GameplayCueTag, FGameplayCueParameters Parameters,
			UAbilitySystemComponent* SourceAbilitySystem);

	static FGameplayAbilityTargetDataHandle MakeTargetDataHandleFromSingleHitResult(const FHitResult HitResult);

	static FGameplayAbilityTargetDataHandle MakeTargetDataHandleFromMultipleHitResults(
		const TArray<FHitResult> HitResults);

	static FGameplayAbilityTargetDataHandle MakeTargetDataHandleFromActorArray(const TArray<AActor*> TargetActors);

	/* Apply SelfAbilityEffects to self */
	UFUNCTION(BlueprintCallable, DisplayName = "ApplyAbilityEffectsToSelf", Category = "Custom GAS | Management")
		void BP_ApplyAbilityEffectsToSelf();

	void ApplyAbilityEffectsToSelf(const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo);

	/* Remove SelfAbilityEffects from self */
	UFUNCTION(BlueprintCallable, DisplayName = "RemoveAbilityEffectsFromSelf", Category = "Custom GAS | Management")
		void BP_RemoveAbilityEffectsFromSelf();

	void RemoveAbilityEffectsFromSelf(const FGameplayAbilityActorInfo* ActorInfo);

	/* Apply TargetAbilityEffects to target */
	UFUNCTION(BlueprintCallable, DisplayName = "ApplyAbilityEffectsToTarget", Category = "Custom GAS | Management")
		void BP_ApplyAbilityEffectsToTarget(const FGameplayAbilityTargetDataHandle TargetDataHandle);

	void ApplyAbilityEffectsToTarget(const FGameplayAbilityTargetDataHandle TargetDataHandle,
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo);

	/* Spawn and fire a projectile with TargetAbilityEffects effects */
	UFUNCTION(BlueprintCallable, DisplayName = "SpawnProjectileWithTargetEffects", Category = "Custom GAS | Management")
		void BP_SpawnProjectileWithTargetEffects(
			const TSubclassOf<AProjectileActor> ProjectileClass,
			const FTransform ProjectileTransform,
			const FVector ProjectileFireDirection);

	void SpawnProjectileWithTargetEffects(
		TSubclassOf<AProjectileActor> ProjectileClass,
		const FTransform ProjectileTransform,
		const FVector ProjectileFireDirection,
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo);

	/* Remove the cooldown effect */
	UFUNCTION(BlueprintCallable, Category = "Custom GAS | Management")
		void RemoveCooldownEffect(UAbilitySystemComponent* SourceAbilitySystem) const;
};
