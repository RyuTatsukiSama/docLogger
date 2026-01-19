// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InteractiveToolBuilder.h"
#include "BaseTools/SingleClickTool.h"
#include "EM_TestSimpleTool.generated.h"

/**
 * Builder for UEM_TestSimpleTool
 */
UCLASS()
class EM_TEST_API UEM_TestSimpleToolBuilder : public UInteractiveToolBuilder
{
	GENERATED_BODY()

public:
	virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override { return true; }
	virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;
};



/**
 * Settings UObject for UEM_TestSimpleTool. This UClass inherits from UInteractiveToolPropertySet,
 * which provides an OnModified delegate that the Tool will listen to for changes in property values.
 */
UCLASS(Transient)
class EM_TEST_API UEM_TestSimpleToolProperties : public UInteractiveToolPropertySet
{
	GENERATED_BODY()
public:
	UEM_TestSimpleToolProperties();

	/** If enabled, dialog should display extended information about the actor clicked on. Otherwise, only basic info will be shown. */
	UPROPERTY(EditAnywhere, Category = Options, meta = (DisplayName = "Show Extended Info"))
	bool ShowExtendedInfo;
};




/**
 * UEM_TestSimpleTool is an example Tool that opens a message box displaying info about an actor that the user
 * clicks left mouse button. All the action is in the ::OnClicked handler.
 */
UCLASS()
class EM_TEST_API UEM_TestSimpleTool : public USingleClickTool
{
	GENERATED_BODY()

public:
	UEM_TestSimpleTool();

	virtual void SetWorld(UWorld* World);

	virtual void Setup() override;

	virtual void OnClicked(const FInputDeviceRay& ClickPos);


protected:
	UPROPERTY()
	TObjectPtr<UEM_TestSimpleToolProperties> Properties;


protected:
	/** target World we will raycast into to find actors */
	UWorld* TargetWorld;
};