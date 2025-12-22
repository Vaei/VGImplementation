# Vigil + Grasp Implementation <img align="right" width=128, height=128 src="https://github.com/Vaei/Vigil/blob/main/Resources/Icon128.png">

> [!IMPORTANT]
> You can use this as a learning resource or you can modify it for your own project after completing the setup guide
> <br>This is intended to provide a common implementation of Vigil and Grasp to to accelerate the setup process

> [!TIP]
> You don't need to retain this plugin if you copy the classes and content out
> <br>The guide will tell you to do this, but its optional

> [!NOTE]
> Content engine version is UE5.6

This implementation features a UI with interaction prompt, as well as highlights for nearby interactables, and demo interactables, as well as custom Grasp Data extended with custom interaction text and description text.

https://github.com/user-attachments/assets/5a9b08ac-69e1-4e7b-a024-079808f982ca

# Plugin Guides

Vigil and Grasp both have their own setup guides, you will want to familiarize yourself with these

[Vigil](https://github.com/Vaei/Vigil/wiki)

[Grasp](https://github.com/Vaei/Grasp/wiki)

# Setup Guide

> [!NOTE]
> This guide starts from the perspective of a new UE5.5 Third Person template project

## Pre-Setup

> [!WARNING]
> Perform these steps in order. It is recommended that you don't even add this plugin until you have completed the Pre-Setup steps.

### Collision

Add the following channels to your project:

* `Interaction` - TraceChannel - Default: Ignore
* `Grasp` - ObjectChannel - Default: Ignore
* `Grasp` - Preset - Query Only - ObjectType Grasp - Ignore everything, except overlap Interaction channel

### Gameplay Tags

Add the following gameplay tags:

* `Vigil.Interaction`

### Plugins

Add the following plugins to your project and enable them:

* [Vigil](https://github.com/Vaei/Vigil)
* [Grasp](https://github.com/Vaei/Grasp)
* [PlayWidgetAnimation](https://github.com/Vaei/PlayWidgetAnimation)

> [!NOTE]
> PlayWidgetAnimation provides the `PlayAnimationWithFinishedEventDuo` node that is used for widget animations, it is optional but you should add it, then replace it in the project before removing the plugin if you do not wish to use it.

### Grasp Preset

In Project Settings, under Grasp Developer Settings, assign the Grasp profile then click "Set as Default"

## This Plugin

Now add this plugin to your project.

### Fix Collision Channel Assignments

> [!WARNING]
> This is vitally important because the engine references channels as `ECC_GameTraceChannel1` etc. instead of the channel name
> <br>The included data assets often have incorrect channels assigned as a result

Open `VG_VigilTargeting`, expand `VigilTargetSelection` and ensure `CollisionChannel` is `Interaction`

Open `VG_GraspTargeting`, expand `GraspTargetSelection` and ensure `CollisionChannel` is `Grasp`

### Migration

> [!NOTE]
> These steps are optional
> <br>This plugin isn't intended to remain in your project but it is up to you whether you keep it or not
> <br>Removing it will require some C++ familiarity and you might end up breaking things if you make a mistake or misunderstand a step

> [!IMPORTANT]
> If you are not comfortable compiling from an IDE add this to your `Config/DefaultEditorPerProjectUserSettings.ini`

```ini
[/Script/UnrealEd.EditorLoadingSavingSettings]
bForceCompilationAtStartup=True
```

Make sure your project is closed. Move the following classes out of the plugin and into your project:

* `VGGraspData`
* `VGInteractAbilityBase`
* `VGStatics`

> [!WARNING]
> Ensure these were moved and not copied, the originals must not exist

Change the API macros from `VGIMPLEMENTATION_API` to your project's API macro.

Add `"GameplayAbilities"`, `"GameplayTags"`, and `"Grasp"` to your `Build.cs` `PublicDependencyModuleNames`

In your project's `DefaultEngine.ini` add these redirectors:

```ini
[CoreRedirects]
+ClassRedirects=(OldName="/Script/VGImplementation.VGStatics",NewName="/Script/MYPROJECTNAME.VGStatics")
+ClassRedirects=(OldName="/Script/VGImplementation.VGInteractAbilityBase",NewName="/Script/MYPROJECTNAME.VGInteractAbilityBase")
+ClassRedirects=(OldName="/Script/VGImplementation.VGGraspData",NewName="/Script/MYPROJECTNAME.VGGraspData")
```

> [!CAUTION]
> You must change `MYPROJECTNAME` to match your project's module name

Compile and open your project.

Navigate to this plugin's content folder. Open the content one by one to ensure no errors occurred due to the migration process. There should be no errors pertaining to missing parent classes and the widgets should compile.

Move the content out of the plugin and into your project.

Close your project and delete this plugin entirely - we have now fully absorbed it into our project.

## Implementation

### Ability System Component

Your Character or PlayerState must have a `UAbilitySystemComponent` (that you can retrieve from your PlayerController during `OnPossess()`). If in doubt, or if you will not use GAS for any other reason, add it to your Character.

### HUD

Assign the included `BP_HUD` to your game mode, or extract its functionality into your own HUD class.

### PlayerController

Create a PlayerController and assign it to your game mode.

Add both a `BP_VG_VigilComponent` and `BP_VG_GraspComponent`

`OnPossess` if `PossessedPawn` is valid, retrieve the `UAbilitySystemComponent` then call `InitializeGrasp()` on the Grasp Component passing in the `GraspScan` ability. Then call `GiveAbility()` for the `VigilScan` ability.

> [!WARNING]
> Make sure you pass `GraspScan` and `VigilScan`, not the `GraspScanAbility` or `VigilScanAbility`

<img width="1151" height="395" alt="image" src="https://github.com/user-attachments/assets/4e708a87-d040-44a5-b66e-798fee0f0704" />

When input E is pressed activate Grasp

<img width="1903" height="440" alt="image" src="https://github.com/user-attachments/assets/755f9746-a49b-4dd0-8b87-fc35d2c6ce23" />

### Interactable Ability

Open up the GA_Interactable_Demo and assign a montage to the `PlayMontageAndWait` node - none are included here, so add anything you want for testing.

## Testing

Place a few `BP_Interactable_Demo` into your level, roughly at the height of the character's waist. PIE and you should see interaction prompts occurring. Pressing E when close enough should result in interaction.

## Troubleshooting

If no interaction prompt occurs:
* `p.Vigil.Selection.Debug 1` - when near an interactable, does the cone turn red? If its only ever green, then its not detecting your graspable components
  * Check the collision profile assigned is `Grasp` and that it is setup correctly as specified in this guide
  * Check that the `CollisionChannel` assigned to `VG_VigilTargeting` is `Interaction`

If interaction prompt is always busy:
* Check that the ability has been granted
  * `ShowDebug AbilitySystem` then run 2x `AbilitySystem.Debug.NextCategory`
  * Check that the `CollisionObjectTypes` assigned to `VG_GraspTargeting` includes `Grasp`

## Extra

### Interaction Options

You might notice that up to 3 interaction options can be displayed along with the current interaction target. If you want to increase or decrease the number, then modify `W_InteractionHandler` by duplicating or removing them from `OptionPanel`

# Changelog

## 1.0.0
* Initial Release