#include "PartySystem.h"
#include "CharacterBase.h"

UPartySystem::UPartySystem()
{
	PartyLimit = 0;
}

ACharacterBase* UPartySystem::GetPrimaryPartyMember()
{
	return Party[ControlledCharacterKey];
}
void UPartySystem::SetPartyLimit(int Limit)
{
	PartyLimit = Limit;
}

int UPartySystem::GetPartyLimit()
{
	return PartyLimit;
}

void UPartySystem::SetPlayerControlledMember(int Key)
{
	for (int x = 0; x < Party.Num(); ++x)
	{
		if (x == Key)
		{
			Party[x]->SetControllerType(EControlledType::ECT_PlayerControlled);
		}
		else
		{
			Party[x]->SetControllerType(EControlledType::ECT_AIControlled);
		}
	}
}

void UPartySystem::AttachPartyMember(ACharacterBase* Value)
{
	int PartySize = 0; // ASPlayerParty::SizeOfParty();
	if (PartySize < PartyLimit)
	{
	//	Party.Push(Cast<ASPlayerCharacter>(member));
		Party.Add(PartySize, Value);
		if (PartySize == 0)
		{
			SetPrimaryPartyMember(1);
		}
	}
	else if (PartySize == PartyLimit)
	{
		Party.Add(PartyLimit, Value);
	}
}

void UPartySystem::SetPrimaryPartyMember(int Key)
{
	int PartySize = Party.Num();

	if (Key < PartySize)
	{
		ControlledCharacterKey = Key;
	}
}


int UPartySystem::FindMember(ACharacterBase* Value)
{
	for (int32 x = 0; x < Party.Num(); ++x)
	{
		ACharacterBase* ValueRef = *Party.Find(x);

		if (Value == ValueRef)
		{
			return x;
		}
	}

	return INDEX_NONE;
	
}

void UPartySystem::DetachPartyMember(ACharacterBase* Value)
{
	int MemberPos = FindMember(Value);
	if (MemberPos > -1 && Party.Num() > 1)
	{
		Party.Remove(MemberPos);
	}
}

void UPartySystem::ReplacePartyMember(int Key, ACharacterBase* Value)
{
	if (Key >= 0 && Key < PartyLimit)
	{
		DetachPartyMember(Party[Key]);
		Party.Emplace(Key, Value);
	}
}

TMap<int, ACharacterBase*> UPartySystem::GetMembers()
{
	return Party;
}