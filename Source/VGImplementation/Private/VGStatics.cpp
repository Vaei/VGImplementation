// Copyright (c) Jared Taylor


#include "VGStatics.h"

#include "GraspableComponent.h"
#include "GraspStatics.h"
#include "VGGraspData.h"
#include "VigilComponent.h"
#include "VigilTypes.h"
#include "Kismet/KismetMathLibrary.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(VGStatics)


const UVGGraspData* UVGStatics::GetVGGraspData(const UPrimitiveComponent* GraspableComponent)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(UAhoySharedLib::GetAhoyGraspData);
	
	if (!GraspableComponent)
	{
		return nullptr;
	}

	const IGraspableComponent* Graspable = Cast<IGraspableComponent>(GraspableComponent);
	if (!Graspable)
	{
		return nullptr;
	}

	const UGraspData* GraspData = Graspable->GetGraspData();
	return GraspData ? CastChecked<UVGGraspData>(GraspData) : nullptr;
}

bool UVGStatics::InteractPressed(FGameplayTag VigilInteractionTag, const UVigilComponent* VigilComponent, const APawn* Pawn)
{
	if (!IsValid(Pawn) || !VigilComponent)
	{
		return false;
	}
	
	ensureAlways(VigilInteractionTag.IsValid());
	bool bValidFocus = false;
	const FVigilFocusResult& Focus = VigilComponent->GetFocusResult(VigilInteractionTag, bValidFocus);
	if (!bValidFocus)
	{
		return false;
	}

	const TWeakObjectPtr<UPrimitiveComponent>& Component = Focus.HitResult.Component;
	if (!Component.IsValid())
	{
		return false;
	}
	
	if (UGraspStatics::CanGraspActivateAbility(Pawn, Component.Get()))
	{
		return UGraspStatics::TryActivateGraspAbility(Pawn, Component.Get());
	}
	
	return false;
}

float UVGStatics::GetNormalizedDistanceBetweenInteractAndHighlight(const UGraspData* GraspData, float NormalizedHighlightDistance)
{
	if (GraspData->MaxHighlightDistance <= 0.f)
	{
		return 0.f;
	}
	const float Divisor = GraspData->MaxGraspDistance / GraspData->MaxHighlightDistance;
	return UKismetMathLibrary::MapRangeClamped(NormalizedHighlightDistance, Divisor, 1.f, 0.f, 1.f);
}
