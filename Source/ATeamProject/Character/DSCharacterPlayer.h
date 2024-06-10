// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/DSCharacterBase.h"
#include "InputActionValue.h"
#include "Interface/DSCharacterItemInterface.h"
#include "Interface/DSAnimationShotInterface.h"
#include "Interface/DSAnimationStasisInterface.h"
#include "Interface/DSAnimationStompInterface.h"
#include "DSCharacterPlayer.generated.h"

DECLARE_DELEGATE_OneParam(FOnTakeItemDelegate, class UDSItemData* /*InItemData*/)
USTRUCT(BlueprintType)
struct FTakeItemDelegateWrapper
{
	GENERATED_BODY()

	FTakeItemDelegateWrapper() {}
	FTakeItemDelegateWrapper(const FOnTakeItemDelegate& InItemDelegate) : ItemDelegate(InItemDelegate) {}

	FOnTakeItemDelegate ItemDelegate;
};

/**
 * 
 */
UCLASS()
class ATEAMPROJECT_API ADSCharacterPlayer : public ADSCharacterBase, public IDSCharacterItemInterface, public IDSAnimationStasisInterface, public IDSAnimationShotInterface, public IDSAnimationStompInterface
{
	GENERATED_BODY()
	
public:
	ADSCharacterPlayer();

protected:
	virtual void BeginPlay() override;

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Control Data Section
	virtual void SetCharacterControlData(const class UDSCharacterControlData* CharacterControlData) override;
	void SetCharacterControl(ECharacterControlType NewCharacterControlType);
	void SetCharacterControlType(ECharacterControlType CharacterControlType);
	ECharacterControlType CharacterControlType;
	ECharacterControlType CurrentCharacterControlType;

	// Camera Section
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> Camera;

	// Input Section
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ZoomAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> WheelAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ShotAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> ReloadAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> StasisAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> StompAction;

	/*UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> EndingAction;*/

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	// Item Section
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Equipment, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USkeletalMeshComponent> Weapon;

	UPROPERTY()
	TArray<FTakeItemDelegateWrapper> TakeItemActions;
	bool bEquippedWeapon = false;

	virtual void TakeItem(class UDSItemData* InItemData) override;
	virtual void DrinkPotion(class UDSItemData* InItemData);
	virtual void EquipWeapon(class UDSItemData* InItemData);

	// Attack Section
	UPROPERTY(EditDefaultsOnly, Category = BulletFactory)
	TSubclassOf<class ADSBullet> BulletFactory;

	UPROPERTY(EditAnywhere, Category = BulletEffect)
	TObjectPtr<class UParticleSystem> BulletEffectFactory;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Attack, Meta = (AllowPrivateAccess = "true"))
	bool bPressedZoom = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Attack, Meta = (AllowPrivateAccess = "true"))
	bool bPressedShot = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Attack, Meta = (AllowPrivateAccess = "true"))
	bool bPressedReload = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Attack, Meta = (AllowPrivateAccess = "true"))
	bool bPressedWheel = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Attack, Meta = (AllowPrivateAccess = "true"))
	bool bPressedStasis = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Attack, Meta = (AllowPrivateAccess = "true"))
	bool bPressedStomp = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Attack, Meta = (AllowPrivateAccess = "true"))
	bool bAttack = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Attack, Meta = (AllowPrivateAccess = "true"))
	float CurrentHP = 100.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> ShotActionMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> ReloadActionMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> StompActionMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> StasisActionMontage;

	void Zoom();
	void Wheel();
	void Shot();
	void ShotActionEnd(class UAnimMontage* TargetMontage, bool IsProperlyEnded);

	UFUNCTION(BlueprintCallable, Category="CYJ")
	void OverReload();
	
	void Reload();
	void ReloadActionEnd(class UAnimMontage* TargetMontage, bool IsProperlyEnded);
	void Stasis();
	void StasisActionEnd(class UAnimMontage* TargetMontage, bool IsProperlyEnded);
	void Stomp();
	void StompActionEnd(class UAnimMontage* TargetMontage, bool IsProperlyEnded);
	float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	// Hit Section
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> HitReactionMontage;
	
	// Dead Section
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> DeadActionMontage;

	UFUNCTION(BlueprintCallable, Category="CYJ")
	void Dead();

	// Ending Section
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	bool bEnding = false;

	void Finish();
};
