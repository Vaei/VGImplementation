// Copyright (c) Jared Taylor

#pragma once

#include "CoreMinimal.h"
#include "GraspData.h"
#include "VGGraspData.generated.h"

/**
 * Sub-class or fork this to add your own project-specific properties
 */
UCLASS()
class VGIMPLEMENTATION_API UVGGraspData : public UGraspData
{
	GENERATED_BODY()
	
public:
	/** Text to show in the interaction prompt when looking at this graspable object */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Grasp)
	FText InteractionPromptText = FText::FromString("Interact");
	
	/** Description text to show in the interaction prompt when looking at this graspable object and within interactable range */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Grasp)
	FText InteractionPromptDescription = FText::GetEmpty();
	
	/** Whether to show an interaction option hint when looking at a different graspable object, but within highlight range of this one */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Grasp, meta=(UIMin="0.1", ClampMin="0.001", UIMax="2", Delta="0.05", ForceUnits="x"))
	bool bAllowOptionHint = true;
	
	/** Size scalar for the interaction option hint, utilized when looking at a different graspable object, but within highlight range of this one */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Grasp, meta=(UIMin="0.1", UIMax="2", Delta="0.05", ForceUnits="x", EditCondition="bAllowOptionHint", EditConditionHides))
	float OptionHintSizeScalar = 1.f;
};
