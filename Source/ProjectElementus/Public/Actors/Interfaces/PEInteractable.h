// Author: Lucas Vilas-Boas
// Year: 2022
// Repo: https://github.com/lucoiso/UEProject_Elementus

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayTagContainer.h"
#include "PEInteractable.generated.h"

/**
 *
 */
UINTERFACE(MinimalAPI, Category = "Custom GAS | Interfaces")
class UPEInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTELEMENTUS_API IPEInteractable
{
	GENERATED_BODY()

public:
	UFUNCTION(Category = "Custom Functions | Behaviors")
		virtual void DoInteractionBehavior()
	{
	};

	UFUNCTION(Category = "Custom Functions | Management")
		virtual bool IsInteractEnabled()
	{
	};
	
	UFUNCTION(Category = "Custom Functions | Management")
		virtual bool IsInteractAllowedForActor(const AActor* Actor)
	{
	};

protected:
	/* Tags that target require to interact with this */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Custom Functions | Management")
		TArray<FGameplayTag> RequiredTags;
};
