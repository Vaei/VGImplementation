// Copyright (c) Jared Taylor


#include "VGStatics.h"

#include "GraspableComponent.h"
#include "VGGraspData.h"
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
