// PROJECT GRISWOLD - Peter Mackay 2018/2019

#pragma once

#include "CoreMinimal.h"
#include "SpaceVehicleComponent.h"
#include "Engine/DataTable.h"
#include "SpaceVehicleWeaponBattery.generated.h"

/**
 * 
 */

class ASpaceVehicle;
class ASpaceVehicleCoolantSystem;

USTRUCT(BlueprintType)
struct FWeaponBatteryParams : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "ItemParams")
	FName ItemID;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "ItemParams")
	FString DisplayName;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "ItemParams")
	FString ItemType;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "ItemParams")
	FString Manufacturer;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "ItemParams")
	FString ProductLine;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "ItemParams")
	int32 Size;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "ItemParams")
	FString Class;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "ItemParams")
	int32 BaseMass; //in kg

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "ItemParams")
	float BaseMaxHP;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "ItemParams")
	float BaseMaxChargeRate; // power generated per second

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "ItemParams")
	float BasePowerFactor;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "ItemParams")
	float BaseStandbyPower;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "ItemParams")
	float BaseMaxDraw;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "ItemParams")
	float BaseMaxCharge;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "ItemParams")
	int32 BaseValue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemParams")
	UTexture2D* Thumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemParams")
	FText Description;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "ItemParams")
	TAssetPtr<UStaticMesh> Mesh;

	FWeaponBatteryParams()
	{
		ItemID = "";
		DisplayName = "",
		ItemType = "",
		Manufacturer = "",
		ProductLine = "",
		Size = 0,
		Class = "",
		BaseMass = 0,
		BaseMaxHP = 0.0f,
		BaseMaxChargeRate = 0.0f,
		BasePowerFactor = 1.0f,
		BaseStandbyPower = 10.0f,
		BaseMaxDraw = 0.0f,
		BaseMaxCharge = 0.0f;
	}
};

UCLASS()
class GRISWOLD_API ASpaceVehicleWeaponBattery : public ASpaceVehicleComponent
{
	GENERATED_BODY()
	

public:
	ASpaceVehicleWeaponBattery();
	
	// The pointer to the weapon battery datatable
	UDataTable* WeaponBatteryTable;
	
	// The pointer to the struct used by the datatable to parse the spreadsheet
	FWeaponBatteryParams* ItemParams;
		
	float HeatGenerated = 0.0f;
	float CurrentCharge = 0.0f;
	float PowerConsumed = 0.0f;
	float ChargePercent = 0.0f;

	//Called by the Power Manager to get the power requested by this device
	float GetPowerRequest() override;
	void GenerateHeat() override;
	
	// DoWork Charges the battery.
	//TODO add additional inputs for modifying the power generated each tick.
	void DoWork() override;

	// The weapons ask the weapon battery for power via this function
	bool RequestWeaponPower(float RequestedPower);
				
	// called by the UI to display the current charge level
	UFUNCTION(BlueprintCallable)
	float GetChargeLevel();

	void Initialize();

protected:
	//TODO remove 'current' because its overly wordy and redundant
	int32 CurrentMass = 0;
	float CurrentMaxHP = 0.0f;
	float CurrentMaxChargeRate = 0.0f;
	float CurrentPowerFactor = 0.0f;
	float StandbyPower = 0.0f;
	float CurrentMaxDraw = 0.0f;
	float CurrentMaxCharge = 0.0f;
	float WorkDone = 0.0f;
	
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
};