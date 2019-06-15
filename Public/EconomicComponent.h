// PROJECT GRISWOLD - Peter Mackay 2018/2019

#pragma once

#include "CoreMinimal.h"
#include "Types.h"
#include "Engine/DataTable.h"
#include "Components/ActorComponent.h"
#include "EconomicComponent.generated.h"


USTRUCT()
struct FRecipeElement2DArray {
	GENERATED_USTRUCT_BODY()
	
public:
	// This array holds all of the commodity elements (individual key:value pair structs)
	// Allows for iteration over the key:value pairs, where simply putting all of them into a single struct would not
	TArray<FCommodityElement> RecipeElementArray;

	FCommodityElement operator[] (int32 i)
	{
		return RecipeElementArray[i];
	}

	// Adds a given element to the given recipe array
	void Add(FCommodityElement recipe)
	{
		RecipeElementArray.Add(recipe);
	}
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GRISWOLD_API UEconomicComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UEconomicComponent();


public:
	
	TArray<FCommodityElement> ProductionTotalRequirements;
	TArray<FRecipe> RecipeList;
	UDataTable* RecipeTable;
	
	// The commodity table holds a list of all commodities currently in the game
	UDataTable* CommodityTable;

	UPROPERTY(BlueprintReadOnly)
	TArray<FInventoryRecord> InventoryRecordArray;
	   
	// Performs several tasks to get the component ready.  Executed from BP.
	// The primary function is to read in the local recipe list and populate the market display with the goods this node supplies and demands
	UFUNCTION(BlueprintCallable)
	void Initialize();

	// Updates the local economic simulation
	UFUNCTION(BlueprintCallable)
	void TickProduction();

	// Add units to the local stock level via deliveries or production.
	UFUNCTION(BlueprintCallable)
	void AdjustStockLevel(FName CommodityID, bool ImportFlag ,int32 DeltaStock);



protected:
	// Called when the game starts
	//virtual void BeginPlay() override;

	// Called every frame - Probably wont ever need it but commenting out so I dont have to look up the signature if I change my mind.
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintReadWrite, Category = "Setup")
		TArray<FName> Commodities;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Setup")
		UDataTable* BaseInventory;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Setup")
		UDataTable* ShopInventory;

	//////////////////////////
	// Designer tuning
	/////////////

	// The price curve is an Unreal Blueprint curve object that defines how the price scales with stock level
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "Economic Settings")
		UCurveFloat* PriceCurve;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "Economic Settings")
		int32 Population = 0;

	// Workforce is an abstract representation of the local population 'happiness'.  Happy people do better work!
	UPROPERTY(BlueprintReadOnly, Category = "Economic Settings")
		int32 Workforce = 0;

	// Tax rate is added to the cost of all purchases.  This will be used later to allow for grey market smuggling
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "Economic Settings")
		float TaxRate = 1;

	// The maximum production multiplier when all local demands are 100% satisfied
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "Economic Settings")
		int32 MaxProductionCapacity = 10;

	// The number of economy ticks worth of goods the node attempts to stockpile.  Used in the pricing formula.
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "Economic Settings")
		int32 TickBuffer = 1000;

	// What percentage of a tick buffers worth of goods does the node begin with at simulation start
	UPROPERTY(BlueprintReadWrite, Category = "Economic Settings")
		float StartingInventoryAdjustment = 0.8f;



private:
	int32* PopulationPTR = &Population;
	int32* WorkforcePTR = &Workforce;
	FRecipe* Recipe;
	TArray<FEconComponentInventory> BaseInventoryItems;
	TArray<FCommodityElement> TempRecipeArray;
	TArray<TArray<FCommodityElement>> InputMaps;
	TArray<TArray<FCommodityElement>> OutputMaps;

	// Called when agents deliver stock to this node
	// Aggregates all imports made to this node between ticks.  Moved into inventory on the next tick
	void AddStock(FInventoryRecord* InventoryRecord, int32 StockToAdd);

	// Remove units from the local stock level.  Usually consumed in production.
	void RemoveStock(FInventoryRecord* InventoryRecord, int32 StockToRemove);

	// Searches an an array for a struct with a 'ID' value that matches the ID of the desired commodity and returns the index
	FInventoryRecord* InventoryLookup(FName CommodityID);

	// When a new recipe is installed this function checks to see if any of the required commodities have already been added to this node.
	// If they have this function increments the total demand for that commodity
	// Otherwise the new commodity is added to the market
	FInventoryRecord* AddInventoryRecord(FCommodityElement& CommodityElement);

	// Returns a row from a datatable that matches the RecipeName 
	FRecipe* LookUpRecipe(FName RecipeName);

	// Takes a recipe datatable row and splits it into a set of variables that can be used other market functions.
	// Handles recipes with up to 5 inputs and outputs each.
	TArray<FCommodityElement> BreakRecipe(FName RecipeName);

	// Commodity elements are key:value pairs that are used to build recipe arrays of varying lengths (not all recipes have the same number of ingredients for example)
	// the MAP datatype was introduced after this was made and might be a good candidate for simplifying this process
	FCommodityElement MakeCommodityElement(FName CommodityName, float Quantity);

	// Determines how much the local population feels like working today
	float CalculateLabor();

	// Gets a time value to pass into the price curve
	float GetPriceT(FInventoryRecord& InventoryRecord);

	int32 GetCurrentPrice(FInventoryRecord& InventoryRecord);

};



