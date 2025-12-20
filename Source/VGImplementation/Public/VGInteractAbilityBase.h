// Copyright (c) Jared Taylor

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "VGInteractAbilityBase.generated.h"

class UVGGraspData;
/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class VGIMPLEMENTATION_API UVGInteractAbilityBase : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, 
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	virtual bool ShouldAbilityRespondToEvent(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayEventData* Payload) const override;
	
	UFUNCTION(BlueprintNativeEvent, Category=Interaction)
	void OnActivateInteraction(const FGameplayEventData& EventData, const APawn* Avatar, const UPrimitiveComponent* GraspableComponent, const UVGGraspData* GraspData);
	
	UFUNCTION(BlueprintNativeEvent, Category=Interaction)
	bool CanActivateInteraction(const FGameplayEventData& EventData, const APawn* Avatar, const UPrimitiveComponent* GraspableComponent, const UVGGraspData* GraspData) const;
	
#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;
#endif
};
