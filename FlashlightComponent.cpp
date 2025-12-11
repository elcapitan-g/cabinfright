#include "FlashlightComponent.h"
#include "Kismet/GameplayStatics.h"

UFlashlightComponent::UFlashlightComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// Default state
	bIsOn = false;
	OnIntensity = 5000.f;
	FadeSpeed = 8.f;

	CurrentIntensity = 0.f;
	TargetIntensity = 0.f;

	// Initial visibility off
	SetVisibility(false);
	SetIntensity(CurrentIntensity);

	// Light shape settings
	SetAttenuationRadius(1000.f);
	SetInnerConeAngle(20.f);
	SetOuterConeAngle(40.f);
}

void UFlashlightComponent::BeginPlay()
{
	Super::BeginPlay();
	UpdateVisibility();
}

void UFlashlightComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateIntensity(DeltaTime);
	UpdateVisibility();
}

void UFlashlightComponent::ToggleFlashlight()
{
	bIsOn = !bIsOn;
	TargetIntensity = bIsOn ? OnIntensity : 0.f;
	PlayToggleSound();

	// Instant toggle if fade speed is zero
	if (FadeSpeed <= 0.f)
	{
		CurrentIntensity = TargetIntensity;
		SetIntensity(CurrentIntensity);
	}
}

void UFlashlightComponent::TurnOffInstant()
{
	bIsOn = false;
	TargetIntensity = 0.f;
	CurrentIntensity = 0.f;
	SetIntensity(0.f);
	UpdateVisibility();
}

void UFlashlightComponent::TurnOnInstant()
{
	bIsOn = true;
	TargetIntensity = OnIntensity;
	CurrentIntensity = OnIntensity;
	SetIntensity(OnIntensity);
	UpdateVisibility();
	PlayToggleSound();
}

void UFlashlightComponent::UpdateIntensity(float DeltaTime)
{
	if (!FMath::IsNearlyEqual(CurrentIntensity, TargetIntensity, 1.f))
	{
		CurrentIntensity = FMath::FInterpTo(CurrentIntensity, TargetIntensity, DeltaTime, FadeSpeed);
		SetIntensity(CurrentIntensity);
	}
}

void UFlashlightComponent::UpdateVisibility()
{
	if (bIsOn || CurrentIntensity > 1.f)
		SetVisibility(true);
	else
		SetVisibility(false);
}

void UFlashlightComponent::PlayToggleSound()
{
