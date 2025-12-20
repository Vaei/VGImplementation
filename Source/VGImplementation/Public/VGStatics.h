// Copyright (c) Jared Taylor

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "VGStatics.generated.h"

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
};
