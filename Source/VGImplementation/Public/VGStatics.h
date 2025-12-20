// Copyright (c) Jared Taylor

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "VGStatics.generated.h"

class UGraspData;
struct FGameplayTag;
class UVigilComponent;
class UVGGraspData;
/**
 * 
 */
UCLASS()
class VGIMPLEMENTATION_API UVGStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category=Grasp, meta=(DisplayName="Get VG Grasp Data"))
	static const UVGGraspData* GetVGGraspData(const UPrimitiveComponent* GraspableComponent);
	
	/** 
	 * Attempt to perform an interact action on the focused Vigil target
	 * Intended to be called from PlayerController when interact input is pressed
	 * @return True if the interact ability was successfully activated
	 */
	UFUNCTION(BlueprintCallable, Category=Grasp)
	static bool InteractPressed(FGameplayTag VigilInteractionTag, const UVigilComponent* VigilComponent, const APawn* Pawn);
	
	UFUNCTION(BlueprintPure, Category=Grasp)
	static float GetNormalizedDistanceBetweenInteractAndHighlight(const UGraspData* GraspData, float NormalizedHighlightDistance);
};
