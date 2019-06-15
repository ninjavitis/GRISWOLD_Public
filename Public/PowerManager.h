// PROJECT GRISWOLD - Peter Mackay 2018/2019

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PowerManager.generated.h"

class ASpaceVehicle;
class ASpaceVehicleComponent;
class ASpaceVehiclePowerPlant;

// DEPRECATED - will be removed
//class ASpaceVehicleWeaponBattery;
//class ASensorSystem;
//class ASpaceVehicleCoolantSystem;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GRISWOLD_API UPowerManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPowerManager();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// The main power manager loop.  Queries registered devices then calls their work loop.
	UFUNCTION(BluePrintCallable)
	void RunManager();

	UFUNCTION(BlueprintCallable)
	void SetPowerPlantReference(ASpaceVehiclePowerPlant* PowerPlant);

	// Returns the ratio of the power generated to maximum power output - Usually 100% unless the powerplant is suffering an abnormal effect
	UFUNCTION(BlueprintCallable)
	float GetPowerGeneratedRatio();

	// Returns the ratio of the total requested power to the maximum power output - Mainly used to drive UI
	UFUNCTION(BlueprintCallable)
	float GetPowerRequestRatio();

	UPROPERTY(BlueprintReadWrite, Category = "Griswold")
	TArray<ASpaceVehicleComponent*> ConnectedDevices;

	// DEPRECATED
	//UFUNCTION(BlueprintCallable)
	//void Initialize(ASpaceVehiclePowerPlant * PowerPlant, ASpaceVehicleWeaponBattery* WeaponBattery, ASpaceVehicleCoolantSystem* CoolantSystem, ASensorSystem* SensorSystem);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:	
	ASpaceVehiclePowerPlant* MyPowerPlant = nullptr;

	float TotalPowerRequests = 0.0f;
	float PowerGenerated = 0.0f;
	float PowerRequestSatisfaction = 0.0f;
	float PowerGeneratedRatio = 0.0f;

	// Deprecated - Will be removed
	//float WeaponBatteryPowerRequest = 0.0f;
	//float SensorSystemPowerRequest = 0.0f;
	//float CoolantSystemPowerRequest = 0.0f;
	//ASpaceVehicleWeaponBattery* MyWeaponBattery = nullptr;
	//ASensorSystem* MySensorSystem = nullptr;
	//ASpaceVehicleCoolantSystem* MyCoolantSystem = nullptr;
};
