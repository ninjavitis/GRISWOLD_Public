// PROJECT GRISWOLD - Peter Mackay 2018/2019

#pragma once

#include "CoreMinimal.h"
#include "SpaceVehicleComponent.h"
#include "SensorSystem.generated.h"

class ASpaceVehicle;


/**
 * 
 */

UENUM(BlueprintType)
enum class EScanType : uint8
{
	EScanType_Passive UMETA(DisplayName = "Passive Scan"),
	EScanType_Active UMETA(DisplayName = "Active Scan"),
	EScanType_IR UMETA(DisplayName = "Infrared")
};

USTRUCT(BlueprintType)
struct FSensorSystemParams : public FTableRowBase
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

	UPROPERTY(BlueprintReadonly, VisibleDefaultsOnly, Category = "ItemParams")
	float BaseTransmitPower;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "ItemParams")
	float BaseMaxRange;  // this should generally always be 50000 unreal units

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "ItemParams")
	float BasePowerFactor;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "ItemParams")
	float BaseStandbyPower;

	FSensorSystemParams()
	{
		DisplayName = "",
		ItemType = "",
		Manufacturer = "",
		ProductLine = "",
		Size = 0,
		Class = "",
		BaseMass = 0,
		BaseMaxHP = 0.0f,
		BaseTransmitPower = 1.0f,
		BaseMaxRange = 50000.0f,
		BasePowerFactor = 1.0f,
		BaseStandbyPower = 10.0f;
	}
};


UCLASS()
class GRISWOLD_API ASensorSystem : public ASpaceVehicleComponent
{
	GENERATED_BODY()

public:
	void Initialize() override;

	///////////////////////////////////
	// PUBLIC Setters
	/////////////////////////////////

	///////////////////////////////////
	// PUBLIC Getters
	/////////////////////////////////
	float GetPowerRequest() override;



protected:
	///////////////////////////////////
	// PROTECTED Setters
	/////////////////////////////////
	void SetScanType(EScanType ScanType);

	///////////////////////////////////
	// PROTECTED Getters
	/////////////////////////////////
	TArray<ASpaceVehicle*> GetContactList();
	float GetSNR(AActor* TargetVehicle, EScanType ScanType);
	

private:
	FSensorSystemParams ItemParams;
	
	TArray<ASpaceVehicle*> ContactList;
	
	EScanType ScanType = EScanType::EScanType_Passive;
	
	float SNR = 0.0f;
	float TransmitPower = ItemParams.BaseTransmitPower;
	float PowerFactor = ItemParams.BasePowerFactor;
	float EnvironmentalNoise = 0.0f;
	
	// Used to tune the effects of range.  Might make this a parameter later.
	float RangeNoiseScale = 0.0f;



};
