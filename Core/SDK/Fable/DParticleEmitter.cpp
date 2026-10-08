#include "DParticleEmitter.h"

CThing* (__fastcall* CTCDParticleEmitter::OCreate)(long, C3DVector const&, bool) = nullptr;
CThing* __fastcall CTCDParticleEmitter::HCreate(long particle_type_id, C3DVector const& pos, bool force)
{
	return OCreate(particle_type_id, pos, force);
}

CThing* CTCDParticleEmitter::Create(long particle_type_id, C3DVector const& pos, bool force)
{
	return OCreate(particle_type_id, pos, force);
}

void(__thiscall* CTCDParticleEmitter::OAttachToThing)(CTCDParticleEmitter*, CThing&, long, CCharString const&, long, float) = nullptr;
void __fastcall CTCDParticleEmitter::HAttachToThing(CTCDParticleEmitter* _this, void* _EDX, CThing& thing, long attach_flags, CCharString const& pos_name, long pos_index, float height_offset)
{
	OAttachToThing(_this, thing, attach_flags, pos_name, pos_index, height_offset);
}

void CTCDParticleEmitter::AttachToThing(CThing& thing, long attach_flags, CCharString const& pos_name, long pos_index, float height_offset)
{
	OAttachToThing(this, thing, attach_flags, pos_name, pos_index, height_offset);
}

void CTCDParticleEmitter::Hook()
{
	ADD_HOOK(0x006E0880, HCreate, OCreate);
	ADD_HOOK(0x006E0BE0, HAttachToThing, OAttachToThing);
}
