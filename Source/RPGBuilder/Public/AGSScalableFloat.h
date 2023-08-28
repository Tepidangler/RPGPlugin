#pragma once
#include "CoreMinimal.h"
#include "Engine/CurveTable.h"
#include "DataRegistryId.h"
#include "AGSScalableFloat.generated.h"

/** Generic numerical value in the form Value * Curve[Level] */

USTRUCT(BlueprintType)
struct RPGBUILDER_API FAGSScalableFloat
{
	GENERATED_USTRUCT_BODY()

	FAGSScalableFloat()
	: Value(1.f)
	, LocalCachedCurveID(INDEX_NONE)
	, CachedCurve(nullptr)
	{
	}

	FAGSScalableFloat(float InInitialValue)
	: Value(InInitialValue)
	, LocalCachedCurveID(INDEX_NONE)
	, CachedCurve(nullptr)
	{
	}

	~FAGSScalableFloat()
	{
	}

public:

	/** Raw value, is multiplied by curve */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ScalableFloat)
	float Value;

private:
	mutable int32 LocalCachedCurveID;

public:
	/** Curve that is evaluated at a specific level. If found, it is multipled by Value */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ScalableFloat)
	FCurveTableRowHandle Curve;

	/** Name of Data Registry containing curve to use. If set the RowName inside Curve is used as the item name */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ScalableFloat)
	FDataRegistryType RegistryType;

	/** Returns the scaled value at a given level */
	float GetValueAtLevel(float Level, const FString* ContextString = nullptr) const;

	/** Returns the scaled value at level 0 */
	float GetValue(const FString* ContextString = nullptr) const;

	/** Used when using a scalable float as a bool */
	bool AsBool(float Level = 0, const FString* ContextString = nullptr) const;

	/** Returns the value as an int32 */
	int32 AsInteger(float Level = 0, const FString* ContextString = nullptr) const;

	/** Gets the value and possible curve at a given level, returning false if any errors occurred */
	bool EvaluateCurveAtLevel(float& OutValue, const FRealCurve*& OutCurve, float Level, const FString& ContextString) const;

	/** True if there is no curve lookup */
	bool IsStatic() const
	{
		return Curve.RowName.IsNone();
	}

	/** Sets raw value */
	void SetValue(float NewValue);

	/** Overrides raw value and curve reference */
	void SetScalingValue(float InCoeffecient, FName InRowName, UCurveTable* InTable);

	/** Returns static value, only safe if this has no curve reference */
	float GetValueChecked() const
	{
		check(IsStatic());
		return Value;
	}

	/** Outputs human readable string */
	FString ToSimpleString() const;

	/** Error checking: checks if we have a curve source specified but no valid curve entry */
	bool IsValid() const;

	/** Equality/Inequality operators */
	bool operator==(const FAGSScalableFloat& Other) const;
	bool operator!=(const FAGSScalableFloat& Other) const;

	/** copy operator to prevent duplicate handles */
	void operator=(const FAGSScalableFloat& Src);

	float operator+=(const float& Buff);
	float operator-=(const float& Debuff);

	/** Used to upgrade a float or int8/int16/int32 property into an FScalableFloat */
	bool SerializeFromMismatchedTag(const FPropertyTag& Tag, FStructuredArchive::FSlot Slot);

private:

	// Cached direct pointer to the RealCurve we should evaluate
	mutable const FRealCurve* CachedCurve;
};

template<>
struct TStructOpsTypeTraits<FAGSScalableFloat>
	: public TStructOpsTypeTraitsBase2<FAGSScalableFloat>
{
	enum
	{
		WithStructuredSerializeFromMismatchedTag = true,
	};
};

