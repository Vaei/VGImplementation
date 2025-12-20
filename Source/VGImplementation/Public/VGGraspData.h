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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Grasp)
	FText InteractionPromptText = FText::FromString("Interact");
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Grasp)
	FText InteractionPromptDescription = FText::GetEmpty();
};
