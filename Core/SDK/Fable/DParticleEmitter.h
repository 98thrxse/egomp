#pragma once

#include <iostream>

#include "../Utils/Hook.h"

#include "Thing.h"
#include "CharString.h"

class CTCDParticleEmitter
{
public:
    static CThing* Create(long, C3DVector const&, bool);
    void AttachToThing(CThing&, long, CCharString const&, long, float);

    static void Hook();

private:
    static CThing* (__fastcall* OCreate)(long, C3DVector const&, bool);
    static CThing* __fastcall HCreate(long particle_type_id, C3DVector const& pos, bool force);

    static void(__thiscall* OAttachToThing)(CTCDParticleEmitter*, CThing&, long, CCharString const&, long, float);
    static void __fastcall HAttachToThing(CTCDParticleEmitter* _this, void* _EDX, CThing& thing, long attach_flags, CCharString const& pos_name, long pos_index, float height_offset);
};
