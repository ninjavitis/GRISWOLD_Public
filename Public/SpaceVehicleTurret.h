// PROJECT GRISWOLD - Peter Mackay 2018/2019

#pragma once

#include "CoreMinimal.h"
#include "SpaceVehicleComponent.h"
#include "types.h"
#include "Components/StaticMeshComponent.h"
#include "SpaceVehicleTurret.generated.h"

class AProjectile;
class ASpaceVehicleWeaponBattery;
class ASpaceVehicleCoolantSystem;
class AProjectileWeapon;

/**
 * 
 */


USTRUCT(BlueprintType)
struct FTurretParams : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(VisibleDefaultsOnly, Category = ItemParams)
	FString ItemType;

	UPROPERTY(VisibleDefaultsOnly, Category = ItemParams)
	FString Manufacturer;

	UPROPERTY(VisibleDefaultsOnly, Category = ItemParams)
	FString ProductLineName;

	UPROPERTY(VisibleDefaultsOnly, Category = ItemParams)
	FString DisplayName;

	UPROPERTY(VisibleDefaultsOnly, Category = ItemParams)
	FString Class;

	UPROPERTY(VisibleDefaultsOnly, Category = ItemParams)
	int Size;

	UPROPERTY(VisibleDefaultsOnly, Category = ItemParams)
	int32 Barrels;

	UPROPERTY(VisibleDefaultsOnly, Category = ItemParams)
	float Mass; //in kg

	UPROPERTY(VisibleDefaultsOnly, Category = ItemParams)
	float HP;

	UPROPERTY(VisibleDefaultsOnly, Category = ItemParams)
	float Damage; // power generated per second

	UPROPERTY(VisibleDefaultsOnly, Category = ItemParams)
	float ProjectileVelocity;

	UPROPERTY(VisibleDefaultsOnly, Category = ItemParams)
	float Range;

	UPROPERTY(VisibleDefaultsOnly, Category = ItemParams)
	float FireRate;

	UPROPERTY(VisibleDefaultsOnly, Category = ItemParams)
	float PowerFactor;

	UPROPERTY(VisibleDefaultsOnly, Category = ItemParams)
	float PowerDraw;

	UPROPERTY(VisibleDefaultsOnly, Category = ItemParams)
	TAssetPtr<UStaticMesh> Mesh;


	FTurretParams()
	{
		ItemType = "Projectile Weapon",
		Manufacturer = "Default Industries",
		ProductLineName = "Replace Me",
		DisplayName = "Default Projectile Weapon",
		Class = "Replace Me",
		Size = 0,
		Barrels = 0,
		Mass = 100.0f,
		HP = 100.0f,
		Damage = 10.0f,
		ProjectileVelocity = 950.0f,
		Range = 5000.0f,
		FireRate = 1.0f,
		PowerFactor = 1.2f,
		PowerDraw = 12.0;
	}

};


UCLASS()
class GRISWOLD_API ASpaceVehicleTurret : public ASpaceVehicleComponent
{
	GENERATED_BODY()
	
	
public:
	ASpaceVehicleTurret();

	UFUNCTION(BlueprintCallable)
	void SetRotationLimits(float MyMinRoll, float MyMaxRoll, float MyMinPitch, float MyMaxPitch, float MyMinYaw, float MyMaxYaw, float MyMaxTrainRate);

	UFUNCTION(BlueprintCallable)
	void RotateTurret(FRotator TargetRotation);



	
protected:
	FTurretParams ItemParams;
	AActor* OwnerReference;

	UPROPERTY(BlueprintReadWrite)
	EProjectileWeaponReadyState ReadyState;
	
	UPROPERTY(BlueprintReadOnly)
	float PowerFactor = ItemParams.PowerFactor;

	UPROPERTY(BlueprintReadOnly)
	float PowerDraw = ItemParams.PowerDraw;

	UFUNCTION(BlueprintCallable)
	void FireWeapon(UStaticMeshComponent* Barrel);

	UFUNCTION(BlueprintCallable)
	void SetWeaponBattery(ASpaceVehicleWeaponBattery* MyWeaponBattery);

	void GenerateHeat() override;


	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(BlueprintReadOnly)
	TArray<UStaticMeshComponent*> Barrels;
	



private:

	ASpaceVehicleWeaponBattery * WeaponBattery;

	


	/**/
	float MinRoll = 0.0f;
	float MaxRoll = 0.0f;
	float MinPitch = 0.0f;
	float MaxPitch = 0.0f;
	float MinYaw = 0.0f;
	float MaxYaw = 0.0f;
	float MaxTrainRate = 0.0f;
};
