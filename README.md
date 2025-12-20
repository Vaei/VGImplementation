# Vigil + Grasp Implementation <img align="right" width=128, height=128 src="https://github.com/Vaei/Vigil/blob/main/Resources/Icon128.png">

> [!IMPORTANT]
> You can use this as a learning resource or you can modify it for your own project after completing the setup guide
> <br>This is intended to provide a common implementation of Vigil and Grasp to to accelerate the setup process

> [!TIP]
> You don't need to retain this plugin if you copy the classes and content out
> <br>The guide will tell you to do this, but its optional

This implementation features a UI with interaction prompt, as well as highlights for nearby interactables, and demo interactables, as well as custom Grasp Data extended with custom interaction text and description text.

https://github.com/user-attachments/assets/5a9b08ac-69e1-4e7b-a024-079808f982ca

# Setup Guide

> [!NOTE]
> This guide starts from the perspective of a new UE5.5 Third Person template project

## Pre-Setup

> [!WARNING]
> Perform these steps in order. It is recommended that you don't even add this plugin until you have completed the Pre-Setup steps.

### Collision

Add the following channels to your project:

* Interaction - TraceChannel - Default: Ignore
* Grasp - ObjectChannel - Default: Ignore
* Grasp - Preset - Query only - ObjectType Grasp - Ignore everything, except overlap Interaction channel

Under GraspDeveloperSettings assign the Grasp profile then click "Set as Default"

### Gameplay Tags

Add the following gameplay tags:

* Vigil.Interaction

### Plugins

Add the following plugins to your project:

* [Vigil](https://github.com/Vaei/Vigil)
* [Grasp](https://github.com/Vaei/Grasp)
* [PlayWidgetAnimation](https://github.com/Vaei/PlayWidgetAnimation)
* This Plugin

> [!NOTE]
> PlayWidgetAnimation provides the `PlayAnimationWithFinishedEventDuo` node that is used for widget animations, it is optional but you should add it, then replace it in the project before removing the plugin.

## Implementation

### Ability System Component

Your Character or PlayerState must have a `UAbilitySystemComponent` (that you can retrieve from your PlayerController during `OnPossess()`)

### HUD

Assign the included BP_HUD, or extract its functionality into your own

### PlayerController

Add both a `BP_VG_VigilComponent` and `BP_VG_GraspComponent`

OnPossess if PossessedPawn is valid, retrieve the `UAbilitySystemComponent` then call `InitializeGrasp()` on the Grasp Component. Then call `GiveAbility()` for the `VigilScan` ability.

<img width="1151" height="395" alt="image" src="https://github.com/user-attachments/assets/4e708a87-d040-44a5-b66e-798fee0f0704" />

When input E is pressed activate Grasp

<img width="1903" height="440" alt="image" src="https://github.com/user-attachments/assets/755f9746-a49b-4dd0-8b87-fc35d2c6ce23" />

### Interactable Ability

Open up the GA_Interactable_Demo and assign a montage to the `PlayMontageAndWait` node - none are included here, so add anything you want for testing.

### Interaction Options

You might notice that up to 3 interaction options can be displayed along with the current interaction target. If you want to increase or decrease the number, then modify `W_InteractionHandler` by duplicating or removing them from `OptionPanel`

# Changelog

## 1.0.0
* Initial Release