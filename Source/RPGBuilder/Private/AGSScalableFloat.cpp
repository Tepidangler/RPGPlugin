#include "AGSScalableFloat.h"
#include "Stats/StatsMisc.h"
#include "EngineDefines.h"
#include "Engine/Blueprint.h"
#include "AssetData.h"
#include "Engine/ObjectLibrary.h"
#include "UObject/UObjectIterator.h"
#include "DataRegistrySubsystem.h"

#if WITH_EDITOR
#include "EditorReimportHandler.h"
#endif

bool FAGSScalableFloat::EvaluateCurveAtLevel(float& OutValue, const FRealCurve*& OutCurve, float Level, const FString& ContextString) const
{
	if (!Curve.RowName.IsNone())
	{
		// This is a simple mechanism for invalidating our cached curve. If someone calls FScalableFloat::InvalidateAllCachedCurves (static method)
		// all cached curve tables are invalidated and will be updated the next time they are accessed
		const int32 GlobalCachedCurveID = UCurveTable::GetGlobalCachedCurveID();
		if (LocalCachedCurveID != GlobalCachedCurveID)
		{
			CachedCurve = nullptr;
		}

		OutCurve = CachedCurve;
		if (OutCurve == nullptr)
		{
			// Cache not valid, look at sources
			if (Curve.CurveTable)
			{
				CachedCurve = OutCurve = Curve.GetCurve(ContextString);
				LocalCachedCurveID = GlobalCachedCurveID;
			}
			else if (RegistryType.IsValid())
			{
				UDataRegistrySubsystem* SubSystem = UDataRegistrySubsystem::Get();
				if (ensure(SubSystem))
				{
					// Always evaluate
					float OutTempValue = 0.0f;
					FDataRegistryCacheGetResult GetResult = SubSystem->EvaluateCachedCurve(OutTempValue, OutCurve, FDataRegistryId(RegistryType, Curve.RowName), Level);

					if (GetResult)
					{
						if (GetResult.IsPersistent() && GetResult.GetVersionSource() == EDataRegistryCacheVersionSource::CurveTable)
						{
							// Only cache if safe
							CachedCurve = OutCurve;
							LocalCachedCurveID = GetResult.GetCacheVersion();
						}

						OutValue = Value * OutTempValue;
						return true;
					}
				}
			}
		}

		// Use cached curve to evaluate
		if (OutCurve != nullptr)
		{
			OutValue = Value * OutCurve->Eval(Level);
			return true;
		}
		else
		{
			// Has row name but no curve, this is an error but fallback to raw value
			OutValue = Value;
			return false;
		}
	}

	// No curve, use raw value
	OutCurve = nullptr;
	OutValue = Value;
	return true;
}

float FAGSScalableFloat::GetValueAtLevel(float Level, const FString* ContextString) const
{
	float OutFloat;
	const FRealCurve* FoundCurve;
	static const FString DefaultContextString = TEXT("FAGSScalableFloat::GetValueAtLevel");

	EvaluateCurveAtLevel(OutFloat, FoundCurve, Level, ContextString ? *ContextString : DefaultContextString);

	return OutFloat;
}

float FAGSScalableFloat::GetValue(const FString* ContextString /*= nullptr*/) const
{
	return GetValueAtLevel(0, ContextString);
}

float FAGSScalableFloat::GetCurrentValue(const FString* ContextSTring) const
{
	return Value;
}

bool FAGSScalableFloat::AsBool(float Level, const FString* ContextString) const
{
	return GetValueAtLevel(Level, ContextString) > 0.0f;
}

void FAGSScalableFloat::SetValue(float NewValue)
{
	Value = NewValue;
	Curve.CurveTable = nullptr;
	Curve.RowName = NAME_None;
	CachedCurve = nullptr;
	LocalCachedCurveID = INDEX_NONE;
}

void FAGSScalableFloat::SetScalingValue(float InCoeffecient, FName InRowName, UCurveTable* InTable)
{
	Value = InCoeffecient;
	Curve.RowName = InRowName;
	Curve.CurveTable = InTable;
	CachedCurve = nullptr;
	LocalCachedCurveID = INDEX_NONE;
}

FString FAGSScalableFloat::ToSimpleString() const
{
	if (Curve.RowName != NAME_None)
	{
		if (Curve.CurveTable)
		{
			return FString::Printf(TEXT("%.2f - %s@%s"), Value, *Curve.RowName.ToString(), *Curve.CurveTable->GetName());
		}
		return FString::Printf(TEXT("%.2f - %s:%s"), Value, *RegistryType.ToString(), *Curve.RowName.ToString());
	}
	return FString::Printf(TEXT("%.2f"), Value);
}

bool FAGSScalableFloat::IsValid() const
{
	float OutFloat;
	const FRealCurve* FoundCurve;
	static const FString DefaultContextString = TEXT("FScalableFloat::GetValueAtLevel");

	return EvaluateCurveAtLevel(OutFloat, FoundCurve, 1.f, DefaultContextString);
}

bool FAGSScalableFloat::SerializeFromMismatchedTag(const FPropertyTag& Tag, FStructuredArchive::FSlot Slot)
{
	if (Tag.Type == NAME_FloatProperty)
	{
		float OldValue;
		Slot << OldValue;
		*this = FAGSScalableFloat(OldValue);

		return true;
	}
	else if (Tag.Type == NAME_IntProperty)
	{
		int32 OldValue;
		Slot << OldValue;
		*this = FAGSScalableFloat((float)OldValue);

		return true;
	}
	else if (Tag.Type == NAME_Int8Property)
	{
		int8 OldValue;
		Slot << OldValue;
		*this = FAGSScalableFloat((float)OldValue);

		return true;
	}
	else if (Tag.Type == NAME_Int16Property)
	{
		int16 OldValue;
		Slot << OldValue;
		*this = FAGSScalableFloat((float)OldValue);

		return true;
	}
	else if (Tag.Type == NAME_BoolProperty)
	{
		*this = FAGSScalableFloat(Tag.BoolVal ? 1.f : 0.f);
		return true;
	}
	return false;
}

bool FAGSScalableFloat::operator==(const FAGSScalableFloat& Other) const
{
	return ((Other.Curve == Curve) && (Other.RegistryType == RegistryType) && (Other.Value == Value));
}

bool FAGSScalableFloat::operator!=(const FAGSScalableFloat& Other) const
{
	return ((Other.Curve != Curve) || (Other.RegistryType != RegistryType) || (Other.Value != Value));
}

void FAGSScalableFloat::operator=(const FAGSScalableFloat& Src)
{
	Value = Src.Value;
	Curve = Src.Curve;
	RegistryType = Src.RegistryType;
	LocalCachedCurveID = Src.LocalCachedCurveID;
	CachedCurve = Src.CachedCurve;
}

float FAGSScalableFloat::operator+=(const float& Buff)
{
	return Value += Buff;
}

float FAGSScalableFloat::operator-=(const float& Debuff)
{
	return Value -= Debuff;
}


// --------------------------------------------------------------------------------

#if WITH_EDITOR

struct FBadScalableFloat
{
	UObject* Asset;
	FProperty* Property;

	FString String;
};

static FBadScalableFloat GCurrentBadScalableFloat;
static TArray<FBadScalableFloat> GCurrentBadScalableFloatList;
static TArray<FBadScalableFloat> GCurrentNaughtyScalableFloatList;


static bool CheckForBadScalableFloats_r(void* Data, UStruct* Struct, UClass* Class);

static bool CheckForBadScalableFloats_Prop_r(void* Data, FProperty* Prop, UClass* Class)
{
	void* InnerData = Prop->ContainerPtrToValuePtr<void>(Data);

	FStructProperty* StructProperty = CastField<FStructProperty>(Prop);
	if (StructProperty)
	{
		if (StructProperty->Struct == FAGSScalableFloat::StaticStruct())
		{
			FAGSScalableFloat* ThisScalableFloat = static_cast<FAGSScalableFloat*>(InnerData);
			if (ThisScalableFloat)
			{
				if (ThisScalableFloat->IsValid() == false)
				{
					if (ThisScalableFloat->Curve.RowName == NAME_None)
					{
						// Just fix this case up here
						ThisScalableFloat->Curve.CurveTable = nullptr;
						ThisScalableFloat->RegistryType = NAME_None;
						GCurrentBadScalableFloat.Asset->MarkPackageDirty();
					}
					else if (ThisScalableFloat->Curve.CurveTable == nullptr && !ThisScalableFloat->RegistryType.IsValid())
					{
						// Just fix this case up here
						ThisScalableFloat->Curve.RowName = NAME_None;
						GCurrentBadScalableFloat.Asset->MarkPackageDirty();
					}
					else
					{
						GCurrentBadScalableFloat.Property = Prop;
						GCurrentBadScalableFloat.String = ThisScalableFloat->ToSimpleString();

						GCurrentBadScalableFloatList.Add(GCurrentBadScalableFloat);
					}
				}
				else
				{
					if (ThisScalableFloat->Curve.RowName != NAME_None && ThisScalableFloat->Value != 1.f)
					{
						GCurrentBadScalableFloat.Property = Prop;
						GCurrentBadScalableFloat.String = ThisScalableFloat->ToSimpleString();

						GCurrentNaughtyScalableFloatList.Add(GCurrentBadScalableFloat);
					}
				}
			}
		}
		else
		{
			CheckForBadScalableFloats_r(InnerData, StructProperty->Struct, Class);
		}
	}

	FArrayProperty* ArrayProperty = CastField<FArrayProperty>(Prop);
	if (ArrayProperty)
	{
		FScriptArrayHelper ArrayHelper(ArrayProperty, InnerData);
		int32 n = ArrayHelper.Num();
		for (int32 i = 0; i < n; ++i)
		{
			void* ArrayData = ArrayHelper.GetRawPtr(i);
			CheckForBadScalableFloats_Prop_r(ArrayData, ArrayProperty->Inner, Class);
		}
	}

	return false;
}

static bool	CheckForBadScalableFloats_r(void* Data, UStruct* Struct, UClass* Class)
{
	for (TFieldIterator<FProperty> FieldIt(Struct, EFieldIteratorFlags::IncludeSuper); FieldIt; ++FieldIt)
	{
		FProperty* Prop = *FieldIt;
		CheckForBadScalableFloats_Prop_r(Data, Prop, Class);

	}

	return false;
}

// -------------

static bool FindClassesWithScalableFloat_r(const TArray<FString>& Args, UStruct* Struct, UClass* Class);

static bool FindClassesWithScalableFloat_Prop_r(const TArray<FString>& Args, FProperty* Prop, UClass* Class)
{
	FStructProperty* StructProperty = CastField<FStructProperty>(Prop);
	if (StructProperty)
	{
		if (StructProperty->Struct == FAGSScalableFloat::StaticStruct())
		{
			return true;

		}
		else
		{
			return FindClassesWithScalableFloat_r(Args, StructProperty->Struct, Class);
		}
	}

	FArrayProperty* ArrayProperty = CastField<FArrayProperty>(Prop);
	if (ArrayProperty)
	{
		return FindClassesWithScalableFloat_Prop_r(Args, ArrayProperty->Inner, Class);
	}

	return false;
}

static bool	FindClassesWithScalableFloat_r(const TArray<FString>& Args, UStruct* Struct, UClass* Class)
{
	for (TFieldIterator<FProperty> FieldIt(Struct, EFieldIteratorFlags::ExcludeSuper); FieldIt; ++FieldIt)
	{
		FProperty* Prop = *FieldIt;
		if (FindClassesWithScalableFloat_Prop_r(Args, Prop, Class))
		{
			return true;
		}
	}

	return false;
}

static void	FindInvalidScalableFloats(const TArray<FString>& Args, bool ShowCoeffecients)
{
	GCurrentBadScalableFloatList.Empty();

	TArray<UClass*>	ClassesWithScalableFloats;
	for (TObjectIterator<UClass> ClassIt; ClassIt; ++ClassIt)
	{
		UClass* ThisClass = *ClassIt;
		if (FindClassesWithScalableFloat_r(Args, ThisClass, ThisClass))
		{
			ClassesWithScalableFloats.Add(ThisClass);
			//ABILITY_LOG(Warning, TEXT("Class has scalable float: %s"), *ThisClass->GetName());
		}
	}

	for (UClass* ThisClass : ClassesWithScalableFloats)
	{
		UObjectLibrary* ObjLibrary = nullptr;
		TArray<FAssetData> AssetDataList;
		TArray<FString> Paths;
		Paths.Add(TEXT("/Game/"));

		{
			FString PerfMessage = FString::Printf(TEXT("Loading %s via ObjectLibrary"), *ThisClass->GetName());
			SCOPE_LOG_TIME_IN_SECONDS(*PerfMessage, nullptr)
				ObjLibrary = UObjectLibrary::CreateLibrary(ThisClass, true, true);

			ObjLibrary->LoadBlueprintAssetDataFromPaths(Paths, true);
			ObjLibrary->LoadAssetsFromAssetData();
			ObjLibrary->GetAssetDataList(AssetDataList);

			//ABILITY_LOG(Warning, TEXT("Found: %d %s assets."), AssetDataList.Num(), *ThisClass->GetName());
		}


		for (FAssetData Data : AssetDataList)
		{
			UPackage* ThisPackage = Data.GetPackage();
			UBlueprint* ThisBlueprint = CastChecked<UBlueprint>(Data.GetAsset());
			UClass* AssetClass = ThisBlueprint->GeneratedClass;
			UObject* ThisCDO = AssetClass->GetDefaultObject();

			FString PathName = ThisCDO->GetName();
			PathName.RemoveFromStart(TEXT("Default__"));

			GCurrentBadScalableFloat.Asset = ThisCDO;


			//ABILITY_LOG( Warning, TEXT("Asset: %s "), *PathName	);
			CheckForBadScalableFloats_r(ThisCDO, AssetClass, AssetClass);
		}
	}


	//ABILITY_LOG(Error, TEXT(""));
	//ABILITY_LOG(Error, TEXT(""));

	if (ShowCoeffecients == false)
	{

		for (FBadScalableFloat& BadFoo : GCurrentBadScalableFloatList)
		{
			//ABILITY_LOG(Error, TEXT(", %s, %s, %s,"), *BadFoo.Asset->GetFullName(), *BadFoo.Property->GetFullName(), *BadFoo.String);

		}

		//ABILITY_LOG(Error, TEXT(""));
		//ABILITY_LOG(Error, TEXT("%d Errors total"), GCurrentBadScalableFloatList.Num());
	}
	else
	{
		//ABILITY_LOG(Error, TEXT("Non 1 coefficients: "));

		for (FBadScalableFloat& BadFoo : GCurrentNaughtyScalableFloatList)
		{
			//ABILITY_LOG(Error, TEXT(", %s, %s, %s"), *BadFoo.Asset->GetFullName(), *BadFoo.Property->GetFullName(), *BadFoo.String);

		}
	}
}

FAutoConsoleCommand FindInvalidScalableFloatsCommand(
	TEXT("FindInvalidScalableFloats"),
	TEXT("Searches for invalid scalable floats in all assets. Warning this is slow!"),
	FConsoleCommandWithArgsDelegate::CreateStatic(FindInvalidScalableFloats, false)
);

FAutoConsoleCommand FindCoefficientScalableFloatsCommand(
	TEXT("FindCoefficientScalableFloats"),
	TEXT("Searches for scalable floats with a non 1 coeffecient. Warning this is slow!"),
	FConsoleCommandWithArgsDelegate::CreateStatic(FindInvalidScalableFloats, true)
);

#endif
