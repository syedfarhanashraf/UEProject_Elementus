// Author: Lucas Vilas-Boas
// Year: 2022
// Repo: https://github.com/lucoiso/UEProject_Elementus

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GAS/System/PETrace.h"
#include "PEAbilityFunctions.generated.h"

/**
 *
 */
UCLASS(Category = "Project Elementus | Classes")
class PROJECTELEMENTUS_API UPEAbilityFunctions final : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Project Elementus | Functions")
	static FGameplayAbilityTargetDataHandle MakeTargetDataHandleFromSingleHitResult(const FHitResult HitResult);

	UFUNCTION(BlueprintPure, Category = "Project Elementus | Functions")
	static FGameplayAbilityTargetDataHandle MakeTargetDataHandleFromHitResultArray(
		const TArray<FHitResult> HitResults);

	UFUNCTION(BlueprintPure, Category = "Project Elementus | Functions")
	static FGameplayAbilityTargetDataHandle
	MakeTargetDataHandleFromActorArray(const TArray<AActor*> TargetActors);

	/* Give a new Ability to the Player -
	 * bAutoAdjustInput will ignore InputId and select Skill_1, Skill_2 or Skill_3 based on current owned abilities */
	UFUNCTION(BlueprintCallable, Category = "Project Elementus | Functions")
	static void GiveAbility(UAbilitySystemComponent* TargetABSC, TSubclassOf<UGameplayAbility> Ability,
	                        const FName InputId,
	                        const bool bTryRemoveExistingAbilityWithInput,
	                        const bool bTryRemoveExistingAbilityWithClass);

	/* Will remove the ability associated to the InputAction */
	UFUNCTION(BlueprintCallable, Category = "Project Elementus | Functions")
	static void RemoveAbility(UAbilitySystemComponent* TargetABSC, TSubclassOf<UGameplayAbility> Ability);
};
