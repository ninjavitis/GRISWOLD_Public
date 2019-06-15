#pragma once

#include "CoreMinimal.h"
#include "engine.h"
#include "Containers/Map.h"
#include "Engine/DataTable.h"
#include "Types.generated.h"

UENUM(BLueprintType)
enum class EEconomicAction : uint8
{
	EconomicActionE_Default UMETA(DisplayName = "Default"),
	EconomicActionE_None UMETA(DisplayName = "N/A"),
	EconomicActionE_Manufacturing UMETA(DisplayName = "Manufacturing"),
	EconomicActionE_Trade UMETA(DisplayName = "Trade"),
	EconomicActionE_Stockpile UMETA(DisplayName = "Stockpile"),
	EconomicActionE_Liquidate UMETA(DisplayName = "Liquidate")
};


// Enum - Good Type
UENUM(BlueprintType)
enum class ESectorType : uint8
{
	SectorTypeE_Default UMETA(DisplayName = "Default"),
	SectorTypeE_None UMETA(DisplayName = "N/A"),
	SectorTypeE_Commodity  UMETA(DisplayName = "Commodity"),
	SectorTypeE_Commercial  UMETA(DisplayName = "Commercial"),
	SectorTypeE_Vehicle  UMETA(DisplayName = "Vehicle"),
	SectorTypeE_HumanResource  UMETA(DisplayName = "Human Resource")
};

// Enum - Commodity Groups
UENUM(BlueprintType)
enum class ECommodityGroups : uint8
{
	CGE_Default UMETA(DisplayName = "Default"),
	CGE_None UMETA(DisplayName = "N/A"),
	CGE_Raw  UMETA(DisplayName = "Raw Resource"),
	CGE_Processed  UMETA(DisplayName = "Processed"),
	CGE_Composite  UMETA(DisplayName = "Composite"),
	CGE_Component  UMETA(DisplayName = "Component"),
	CGE_Item  UMETA(DisplayName = "Item"),
	CGE_Vehicle  UMETA(DisplayName = "Vehicle")
};

// Enum - Commodity SubGroups
UENUM(BlueprintType)
enum class ECommoditySubGroups : uint8
{
	CSGE_Default UMETA(DisplayName = "Default"),
	CSGE_None UMETA(DisplayName = "None"),
	CSGE_Ore UMETA(DisplayName = "Ore"),
	CSGE_Food UMETA(DisplayName = "Food"),
	CSGE_Consumer UMETA(DisplayName = "Consumer Goods"),
	CSGE_Vice UMETA(DisplayName = "Vice"),
	CSGE_Metal UMETA(DisplayName = "Metal"),
	CSGE_NonMetal UMETA(DisplayName = "NonMetal")
};

UENUM(BlueprintType)
enum class EShipComponentType : uint8
{
	SCTE_Default UMETA(DisplayName = "Default"),
	SCTE_None UMETA(DisplayName = "None"),
	SCTE_PowerPlant UMETA(DisplayName = "PowerPlant"),
	SCTE_Engine UMETA(DisplayName = "Engine"),
	SCTE_ShieldArray UMETA(DisplayName = "Shield Array"),
	SCTE_WeaponBattery UMETA(DisplayName = "Weapon Battery"),
	SCTE_CoolantSystem UMETA(DisplayName = "Coolant System"),
	SCTE_SensorArray UMETA(DisplayName = "Sensor Array"),
	SCTE_Turret UMETA(DisplayName = "Turret")
};

// Enum - Ship Classes
UENUM(BlueprintType)
enum class EObjectClasses : uint8
{
	OCE_DefaultClass UMETA(DisplayName = "ChangeMe"),
	OCE_LightFreighter UMETA(DisplayName = "Light Freighter"),
	OCE_MediumFreighter UMETA(DisplayName = "Medium Freighter"),
	OCE_HeavyFreighter UMETA(DisplayName = "HeavyFreighter"),
	OCE_Tanker UMETA(DisplayName = "Tanker"),
	OCE_SuperTanker UMETA(DisplayName = "SuperTanker"),
	OCE_LightCorvette UMETA(DisplayName = "Light Corvette"),
	OCE_MediumCorvette UMETA(DisplayName = "Medium Corvette"),
	OCE_HeavyCorvette UMETA(DisplayName = "Heavy Corvette"),
	OCE_LightCruiser UMETA(DisplayName = "Light Cruiser"),
	OCE_Cruiser UMETA(DisplayName = "Cruiser"),
	OCE_HeavyCruiser UMETA(DisplayName = "HeavyCruiser"),
	OCE_BattleCruiser UMETA(DisplayName = "BattleCruiser"),
	OCE_Destroyer UMETA(DisplayName = "Destroyer"),
	OCE_Battleship UMETA(DisplayName = "Battleship"),
	OCE_Carrier UMETA(DisplayName = "Carrier"),
	OCE_Station UMETA(DisplayName = "Station")
};

// Enum - Damage Types
UENUM(BlueprintType)
enum class EDamageTypes : uint8
{
	DTE_Kinetic UMETA(DisplayName = "Kinetic"),
	DTE_Energy UMETA(DisplayName = "Energy"),
	DTE_Plasma UMETA(DisplayName = "Plasma")
};

// Enum - Projectile Weapon Ready States
UENUM(BlueprintType)
enum class EProjectileWeaponReadyState : uint8
{
	PWRSE_Ready UMETA(DisplayName = "Ready"),
	PWRSE_Cycling UMETA(DisplayName = "Cycling"),
	PWRSE_NoPower UMETA(DisplayName = "Insufficient Power")
};

// Enum - On/Off states
UENUM(BlueprintType)
enum class EEnabledState : uint8
{
	ESE_Enabled UMETA(DisplayName = "Device Enabled"),
	ESE_Disabled UMETA(DisplayName = "Device Disabled")
};


// Enum - DamageStates
UENUM(BlueprintType)
enum class EDamageState : uint8
{
	DSE_None UMETA(DisplayName = "No Damage"), // No Damage: 0-25%
	DSE_Light UMETA(DisplayName = "Light Damage"), // Light Damage 26-50%
	DSE_Heavy UMETA(DisplayName = "Heavy Damage"), // Heavy Damage 51-75%
	DSE_Critical UMETA(DisplayName = "Critical Damage") // Critical Damage 76-100%
};


// Enum - HeatStates
UENUM(BlueprintType)
enum class EHeatState : uint8
{
	HSE_Normal UMETA(DisplayName = "Normal"), // Within Operating Temperature
	HSE_Warning UMETA(DisplayName = "Warning"), // Operating Temperature Warning
	HSE_Over UMETA(DisplayName = "Overheating") // Overheating
};

// Power States
UENUM(BlueprintType)
enum class EPowerState : uint8
{
	PSE_Powered UMETA(DisplayName = "Powered On"),
	PSE_Partial UMETA(DisplayName = "Low Power"),
	PSE_Unpowered UMETA(DisplayName = "Powered Off")
};


USTRUCT(BlueprintType)
struct FCommodityParams : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
		UPROPERTY(BlueprintReadWrite, Category = "CommodityParams")
		FName Name;

	UPROPERTY(BlueprintReadWrite, Category = "CommodityParams")
		float mass;

	UPROPERTY(BlueprintReadWrite, Category = "CommodityParams")
		float BaseValue;

	UPROPERTY(BlueprintReadWrite, Category = "CommodityParams")
		float CurrentBuyPrice;

	UPROPERTY(BlueprintReadWrite, Category = "CommodityParams")
		float CurrentSellPrice;

	UPROPERTY(BlueprintReadWrite, Category = "CommodityParams")
		float Demand;

	UPROPERTY(BlueprintReadWrite, Category = "CommodityParams")
		float Supply;
	
	UPROPERTY(BlueprintReadWrite, Category = "CommodityParams")
		float CurrentStock;

	UPROPERTY(BlueprintReadWrite, Category = "CommodityParams")
		float TargetStock;

	UPROPERTY(BlueprintReadWrite, Category = "CommodityParams")
		float UnitsExport;

	UPROPERTY(BlueprintReadWrite, Category = "CommodityParams")
		float UnitsImport;

	//TODO Initialize my struct!
};



// TODO I think this is deprecated but I need to make sure before I nuke
USTRUCT(BlueprintType)
struct FCommodityElement
{
	GENERATED_USTRUCT_BODY();
	UPROPERTY(BlueprintReadWrite)
		FName Name;

	UPROPERTY(BlueprintReadWrite)
		float Value;

};


USTRUCT(BlueprintType)
struct FEconComponentInventory : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FName CommodityID;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		EEconomicAction EconomicAction;
};


// Stores inventory data for each commodity
USTRUCT(BlueprintType)
struct FInventoryRecord : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName CommodityID;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EEconomicAction EconomicAction;
	   
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool ProductionFlag;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool ConsumptionFlag;

	// Units added to the inventory this turn.
	// Either from exteral suppliers or local production.
	UPROPERTY(BlueprintReadOnly)
	int32 UnitsImported;

	UPROPERTY(BlueprintReadOnly)
	int32 UnitsExported;

	UPROPERTY(BlueprintReadOnly)
	int32 UnitsProduced;

	// Units removed from the inventory this turn in the course of production.
	UPROPERTY(BlueprintReadOnly)
	int32 UnitsConsumed;

	// Units required to produce the base recipe output (output values listed in the data table).
	// Usually 1 / output.  Recipes with multiple outputs might be less than 1/.
	UPROPERTY(BlueprintReadOnly)
	float BaseDemand;

	UPROPERTY(BlueprintReadOnly)
	float BaseSupply;

	UPROPERTY(BlueprintReadOnly)
	int32 CurrentInventory;

	//Base Demand * Tick Buffer
	UPROPERTY(BlueprintReadOnly)
	int32 TargetInventory;

	// CurrentInventory / TargetInventory
	UPROPERTY(BlueprintReadOnly)
	float InventoryRatio;

	UPROPERTY(BlueprintReadOnly)
	float BasePrice;

	UPROPERTY(BlueprintReadOnly)
	float CurrentPrice;

	FInventoryRecord()
	{
		CommodityID = "";
		EconomicAction = EEconomicAction::EconomicActionE_Default;
		ProductionFlag = false;
		ConsumptionFlag = false;
		UnitsImported = 0;
		UnitsExported = 0;
		UnitsProduced = 0;
		UnitsConsumed = 0;
		BaseDemand = 0;
		BaseSupply = 0;
		CurrentInventory = 0;
		TargetInventory = 0;
		InventoryRatio = 0.0f;
		BasePrice = 1.0f;
		CurrentPrice = 0.0f;
	};
	
};


USTRUCT(BlueprintType)
struct FCommodityRecord : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	FName CommodityID;

	UPROPERTY(EditDefaultsOnly)
	FString DisplayName;

	UPROPERTY(EditDefaultsOnly)
	ESectorType CommercialSector;

	UPROPERTY(EditDefaultsOnly)
	ECommodityGroups CommodityGroup;

	UPROPERTY(EditDefaultsOnly)
	ECommoditySubGroups CommoditySubGroup;

	UPROPERTY(EditDefaultsOnly)
	int32 BaseValue;
};


USTRUCT(BlueprintType)
struct FRecipe : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly)
	FName CommodityID;

	UPROPERTY(EditDefaultsOnly)
	FName Input1;  // The commodity ID of the first ingredient...
	
	UPROPERTY(EditDefaultsOnly)
	FName Input2;

	UPROPERTY(EditDefaultsOnly)
	FName Input3;
	
	UPROPERTY(EditDefaultsOnly)
	FName Input4;
	
	UPROPERTY(EditDefaultsOnly)
	FName Input5;
	
	UPROPERTY(EditDefaultsOnly)
	float Input1Units;
	
	UPROPERTY(EditDefaultsOnly)
	float Input2Units;
	
	UPROPERTY(EditDefaultsOnly)
	float Input3Units;

	UPROPERTY(EditDefaultsOnly)
	float Input4Units;
	
	UPROPERTY(EditDefaultsOnly)
	float Input5Units;

	FRecipe()
	{
		CommodityID = "";
		Input1 = "";
		Input2 = "";
		Input3 = "";
		Input4 = "";
		Input5 = "";
		Input1Units = 0;
		Input2Units = 0;
		Input3Units = 0;
		Input4Units = 0;
		Input5Units = 0;
	}
		
};

/*
USTRUCT(BlueprintType)
struct FCommodityPrice : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite)
	int32 BasePrice;

	FCommodityPrice()
	{
		BasePrice = 1;
	};

};
*/

