#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/DamageType.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Projectiles/FPSProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "Gamemode/FPSGamemode.h"
#include "HealthComponent/HealthComponent.h"
#include "Interfaces/IDetectable.h"
#include "FPSCharacter.generated.h"


UCLASS()
class VGP221_LEE_IVAN_CPP_API AFPSCharacter : public ACharacter, public IIDetectable
{
	GENERATED_BODY()

public:
	AFPSCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FPSCameraComponent;

	// First-person mesh (arms), visible only to the owning player.
	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	USkeletalMeshComponent* FPSMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	UHealthComponent* HealthComponent;

	// Projectile class to spawn.
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<class AFPSProjectile> ProjectileClass;

	// Gun muzzle offset from the camera location.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	FVector MuzzleOffset;

private:
	UFUNCTION()
	void MoveForward(float value);

	UFUNCTION()
	void MoveRight(float value);

	UFUNCTION()
	void StartJump();

	UFUNCTION()
	void EndJump();

	UFUNCTION()
	void Fire();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	// IDetectable interface implementation
	bool IsPlayerDetected_Implementation() override;

	UFUNCTION()
	void UpdateHealthUI(float NewHealthPercentage);

	UFUNCTION()
	void OnCharacterDeath();
};
