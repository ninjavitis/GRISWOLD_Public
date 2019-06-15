// PROJECT GRISWOLD - Peter Mackay 2018/2019

#pragma once

#include "CoreMinimal.h"
#include "SpaceVehicleComponent.h"
#include "Engine/DataTable.h"
#include "SpaceVehiclePowerPlant.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EPowerPlantClass : uint8
{
	Balanced UMETA(DisplayName="Balanced"), 
	Durable UMETA(DisplayName = "Durable"),
	HighOutput UMETA(DisplayName = "High Output"),
	LowSignature UMETA(DisplayName = "Low Signature")

};


USTRUCT(BlueprintType)
struct FPowerPlantParams : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	
	UPROPERTY(VisibleDefaultsOnly, Category = PowerPlantParams)
	FString ItemType;

	UPROPERTY(VisibleDefaultsOnly, Category = PowerPlantParams)
	FString Manufacturer;

	UPROPERTY(VisibleDefaultsOnly, Category = PowerPlantParams)
	FString ProductLineName;

	UPROPERTY(VisibleDefaultsOnly, Category = PowerPlantParams)
	FString DisplayName;
	
	UPROPERTY(VisibleDefaultsOnly, Category = PowerPlantParams)
	int Size;
	
	UPROPERTY(VisibleDefaultsOnly, Category = PowerPlantParams)
	float Mass; //in kg
	
	UPROPERTY(VisibleDefaultsOnly, Category = PowerPlantParams)
	float HP;
	
	UPROPERTY(VisibleDefaultsOnly, Category = PowerPlantParams)
	float MaxPowerOutput; // power generated per second
	
	UPROPERTY(VisibleDefaultsOnly, Category = PowerPlantParams)
	float PowerFactor;

	UPROPERTY(VisibleDefaultsOnly, Category = PowerPlantParams)
		int32 BaseValue;
	
	UPROPERTY(VisibleDefaultsOnly, Category = PowerPlantParams)
	float SignatureRatio;

	UPROPERTY(VisibleDefaultsOnly, Category = PowerPlantParams)
	TAssetPtr<UStaticMesh> Mesh;

	FPowerPlantParams()
	{
		DisplayName = "",
			ItemType = "",
			Manufacturer = "",
			Size = 0,
			BaseValue = 100;		
	}
};


UCLASS()
class GRISWOLD_API ASpaceVehiclePowerPlant : public ASpaceVehicleComponent
{
	GENERATED_BODY()

public:	
	ASpaceVehiclePowerPlant();
		
	//UDataTable* PowerPlantTable;
	FPowerPlantParams* ItemParams;



	float GeneratePower(); //TODO add additional inputs for modifying the power generated each tick
	void GenerateHeat() override;

		
	// This UPROPERTY Block is only used to show the parameter values to the designer in the editor
	//UPROPERTY(VisibleAnywhere, Category = PowerPlantParams)
	//FString DisplayName;

	UPROPERTY(VisibleAnywhere, Category = PowerPlantParams)
	FString ItemType;
	
	UPROPERTY(VisibleAnywhere, Category = PowerPlantParams)
	int Size;

	UPROPERTY(VisibleAnywhere, Category = PowerPlantParams)
	int Mass;

	UPROPERTY(VisibleAnywhere, Category = PowerPlantParams)
	int HP;
	
	UPROPERTY(VisibleAnywhere, Category = PowerPlantParams)
	float MaxPowerOutput;

	UPROPERTY(VisibleAnywhere, Category = PowerPlantParams)
	float PowerFactor;

	UPROPERTY(VisibleAnywhere, Category = PowerPlantParams)
	float SignatureRatio;
		
protected:
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	

private:	
	
	float PowerGenerated = 0.0f;
	float HeatGenerated = 0.0f;

};
