#pragma once

#include "CoreMinimal.h"
#include "Components/SpotLightComponent.h"
#include "Sound/SoundBase.h"
#include "FlashlightComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class YOURPROJECTNAME_API UFlashlightComponent : public USpotLightComponent
{
	GENERATED_BODY()

public:
	// Constructor
	UFlashlightComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every tick
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;

public:
	// Toggle the flashlight on/off
	UFUNCTION(BlueprintCallable, Category="Flashlight")
	void ToggleFlashlight();

	// Check if flashlight is currently on
	UFUNCTION(BlueprintCallable, Category="Flashlight")
	bool IsOn() const { return bIsOn; }

	// Turn flashlight off immediately
	UFUNCTION(BlueprintCallable, Category="Flashlight")
	void TurnOffInstant();

	// Turn flashlight on immediately
	UFUNCTION(BlueprintCallable, Category="Flashlight")
	void TurnOnInstant();

	// Set fade speed dynamically
	UFUNCTION(BlueprintCallable, Category="Flashlight")
	void SetFadeSpeed(float NewFadeSpeed) { FadeSpeed = NewFadeSpeed; }

	// Set intensity dynamically
	UFUNCTION(BlueprintCallable, Category="Flashlight")
	void SetOnIntensity(float NewIntensity) { OnIntensity = NewIntensity; }

private:
	// Current state
	UPROPERTY()
	bool bIsOn;

	// Current intensity (for smooth fade)
	UPROPERTY()
	float CurrentIntensity;

	// Target intensity for fade
	UPROPERTY()
	float TargetIntensity;

	// Fade speed for smooth transition
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Flashlight", meta=(AllowPrivateAccess="true"))
	float FadeSpeed;

	// Intensity when fully on
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Flashlight", meta=(AllowPrivateAccess="true"))
	float OnIntensity;

	// Sound to play when toggled
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Flashlight", meta=(AllowPrivateAccess="true"))
	USoundBase* ToggleSound;

private:
	// Internal helper: Update light visibility
	void UpdateVisibility();

	// Internal helper: Play toggle sound
	void PlayToggleSound();

	// Internal helper: Interpolate intensity for smooth fade
	void UpdateIntensity(float DeltaTime);

	// Optional: Reset flashlight to default settings
	void ResetFlashlight();
};
