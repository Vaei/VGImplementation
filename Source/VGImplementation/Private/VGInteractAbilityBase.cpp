// Copyright (c) Jared Taylor


#include "VGInteractAbilityBase.h"

#include "AbilitySystemLog.h"
#include "VGGraspData.h"
#include "GraspStatics.h"

#if WITH_EDITOR
#include "Misc/DataValidation.h"
#endif

#include UE_INLINE_GENERATED_CPP_BY_NAME(VGInteractAbilityBase)


void UVGInteractAbilityBase::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	if (bHasBlueprintActivateFromEvent || bHasBlueprintActivate)
	{
		const FString IllegalEvent = bHasBlueprintActivateFromEvent && bHasBlueprintActivate ? TEXT("ActivateAbilityFromEvent and ActivateAbility") : bHasBlueprintActivateFromEvent ? TEXT("ActivateAbilityFromEvent") : TEXT("ActivateAbility");
		UE_LOG(LogAbilitySystem, Warning, TEXT("Ability %s has illegal blueprint event(s) that must be replaced with OnActivateInteraction: %s"), *GetName(), *IllegalEvent);
		constexpr bool bReplicateEndAbility = false;
		constexpr bool bWasCancelled = true;
		EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
		return;
	}
	
	const FGameplayEventData& EventData = *TriggerEventData;
	const UObject* GraspObject = UGraspStatics::GetGraspObjectFromPayload(EventData);
	const UPrimitiveComponent* GraspableComponent = CastChecked<UPrimitiveComponent>(GraspObject);
	const UGraspData* BaseGraspData = UGraspStatics::GetGraspData(GraspableComponent);
	const UVGGraspData* VGGraspData = CastChecked<UVGGraspData>(BaseGraspData);
	
	const AActor* Avatar = ActorInfo->AvatarActor.IsValid() ? ActorInfo->AvatarActor.Get() : nullptr;
	const APawn* PawnAvatar = Cast<APawn>(Avatar);
	OnActivateInteraction(EventData, PawnAvatar, GraspableComponent, VGGraspData);
}

bool UVGInteractAbilityBase::ShouldAbilityRespondToEvent(const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayEventData* Payload) const
{
	const FGameplayEventData& EventData = *Payload;
	const UObject* GraspObject = UGraspStatics::GetGraspObjectFromPayload(EventData);
	const UPrimitiveComponent* GraspableComponent = CastChecked<UPrimitiveComponent>(GraspObject);
	const UGraspData* BaseGraspData = UGraspStatics::GetGraspData(GraspableComponent);
	const UVGGraspData* VGGraspData = CastChecked<UVGGraspData>(BaseGraspData);
	
	const AActor* Avatar = ActorInfo->AvatarActor.IsValid() ? ActorInfo->AvatarActor.Get() : nullptr;
	const APawn* PawnAvatar = Cast<APawn>(Avatar);
	return CanActivateInteraction(EventData, PawnAvatar, GraspableComponent, VGGraspData);
}

void UVGInteractAbilityBase::OnActivateInteraction_Implementation(const FGameplayEventData& EventData,
	const APawn* Avatar, const UPrimitiveComponent* GraspableComponent, const UVGGraspData* GraspData)
{
}

bool UVGInteractAbilityBase::CanActivateInteraction_Implementation(const FGameplayEventData& EventData,
	const APawn* Avatar, const UPrimitiveComponent* GraspableComponent, const UVGGraspData* GraspData) const
{
	return true;
}

#if WITH_EDITOR
EDataValidationResult UVGInteractAbilityBase::IsDataValid(class FDataValidationContext& Context) const
{
	if (bHasBlueprintActivateFromEvent || bHasBlueprintActivate)
	{
		const FString IllegalEvent = bHasBlueprintActivateFromEvent && bHasBlueprintActivate ? TEXT("ActivateAbilityFromEvent and ActivateAbility") : bHasBlueprintActivateFromEvent ? TEXT("ActivateAbilityFromEvent") : TEXT("ActivateAbility");
		Context.AddError(FText::Format(NSLOCTEXT("DataValidation", "VGInteractAbilityBase_InvalidBlueprintEvent",
			"Ability {0} has illegal blueprint event(s) that must be replaced with OnActivateInteraction: {1}"),
			FText::FromString(GetName()), FText::FromString(IllegalEvent)));
	}
	return Super::IsDataValid(Context);
}
#endif