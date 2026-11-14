#include "HeroAttachableAppearanceModifiers.h"

std::map<std::string, std::function<void()>> CTCHeroAttachableAppearanceModifiers::frameUpdateCallbacks;
std::map<std::string, std::function<void(NGraphicAppearance::CGraphicAppearanceDrawInfo const&)>> CTCHeroAttachableAppearanceModifiers::onAppearanceDrawCallbacks;

std::vector<std::vector<long>> CTCHeroAttachableAppearanceModifiers::GetAllAppearanceModifierLists()
{
    std::vector<std::vector<long>> modifiers(NO_OF_APPEARANCE_MODIFIER_TYPES);

    const uintptr_t base = reinterpret_cast<uintptr_t>(this);
    const uintptr_t outerStart =
        *reinterpret_cast<const uintptr_t*>(base + 0x30);

    for (int type = 0; type < NO_OF_APPEARANCE_MODIFIER_TYPES; ++type)
    {
        const uintptr_t inner = outerStart + type * 0x0C;
        const uintptr_t start = *reinterpret_cast<const uintptr_t*>(inner);
        const uintptr_t finish = *reinterpret_cast<const uintptr_t*>(inner + 0x04);

        for (uintptr_t entry = start; entry < finish; entry += 0x08)
        {
            const long defNum = *reinterpret_cast<const long*>(entry);

            if (defNum > 0)
                modifiers[type].push_back(defNum);
        }
    }

    return modifiers;
}

void CTCHeroAttachableAppearanceModifiers::SetAllAppearanceModifierLists(
    const std::vector<std::vector<long>>& modifiers)
{
    const uintptr_t outerStart = *reinterpret_cast<const uintptr_t*>(
        reinterpret_cast<uintptr_t>(this) + 0x30
        );

    for (int type = 0; type < NO_OF_APPEARANCE_MODIFIER_TYPES; ++type)
    {
        const uintptr_t inner = outerStart + type * 0x0C;
        const uintptr_t startPtr = *reinterpret_cast<uintptr_t*>(inner);
        *reinterpret_cast<uintptr_t*>(inner + 0x04) = startPtr;
    }

    for (const auto& modifierList : modifiers)
    {
        for (long defNum : modifierList)
        {
            AddAppearanceModifierWithReplace(defNum);
        }
    }
}

void(__thiscall* CTCHeroAttachableAppearanceModifiers::OAddAppearanceModifierWithReplace)(CTCHeroAttachableAppearanceModifiers*, long) = nullptr;
void __fastcall CTCHeroAttachableAppearanceModifiers::HAddAppearanceModifierWithReplace(CTCHeroAttachableAppearanceModifiers* _this, void* _EDX, long def_num)
{
	OAddAppearanceModifierWithReplace(_this, def_num);
}

void CTCHeroAttachableAppearanceModifiers::AddAppearanceModifierWithReplace(long def_num)
{
	OAddAppearanceModifierWithReplace(this, def_num);
}

void(__thiscall* CTCHeroAttachableAppearanceModifiers::OGetAppearanceModifierList)(CTCHeroAttachableAppearanceModifiers*, std::list<long>&, EHeroAttachableAppearanceModifierType) = nullptr;
void __fastcall CTCHeroAttachableAppearanceModifiers::HGetAppearanceModifierList(CTCHeroAttachableAppearanceModifiers* _this, void* _EDX, std::list<long>& fill_in_list, EHeroAttachableAppearanceModifierType type)
{
	OGetAppearanceModifierList(_this, fill_in_list, type);
}

void CTCHeroAttachableAppearanceModifiers::GetAppearanceModifierList(std::list<long>& fill_in_list, EHeroAttachableAppearanceModifierType type)
{
	OGetAppearanceModifierList(this, fill_in_list, type);
}

void(__thiscall* CTCHeroAttachableAppearanceModifiers::OFrameUpdate)(CTCHeroAttachableAppearanceModifiers*) = nullptr;
void __fastcall CTCHeroAttachableAppearanceModifiers::HFrameUpdate(CTCHeroAttachableAppearanceModifiers* _this, void* _EDX)
{
    OFrameUpdate(_this);

    for (const auto& pair : frameUpdateCallbacks)
    {
        if (pair.second)
            pair.second();
    }
}

void(__thiscall* CTCHeroAttachableAppearanceModifiers::OUpdateGraphics)(CTCHeroAttachableAppearanceModifiers*) = nullptr;
void __fastcall CTCHeroAttachableAppearanceModifiers::HUpdateGraphics(CTCHeroAttachableAppearanceModifiers* _this, void* _EDX)
{
    OUpdateGraphics(_this);
}

bool(__thiscall* CTCHeroAttachableAppearanceModifiers::OOnAppearanceDraw)(CTCHeroAttachableAppearanceModifiers*, NGraphicAppearance::CTCGraphicAppearance&, NGraphicAppearance::CGraphicAppearanceDrawInfo const&) = nullptr;
bool __fastcall CTCHeroAttachableAppearanceModifiers::HOnAppearanceDraw(CTCHeroAttachableAppearanceModifiers* _this, void* _EDX, NGraphicAppearance::CTCGraphicAppearance& tc_appearance, NGraphicAppearance::CGraphicAppearanceDrawInfo const& draw_info)
{
    for (const auto& pair : onAppearanceDrawCallbacks)
    {
        if (pair.second)
            pair.second(draw_info);
    }

    return OOnAppearanceDraw(_this, tc_appearance, draw_info);
}

void CTCHeroAttachableAppearanceModifiers::Hook()
{
	ADD_HOOK(0x00706950, HAddAppearanceModifierWithReplace, OAddAppearanceModifierWithReplace);
    ADD_HOOK(0x00706800, HGetAppearanceModifierList, OGetAppearanceModifierList);
    ADD_HOOK(0x00707AD0, HFrameUpdate, OFrameUpdate);
    ADD_HOOK(0x007070D0, HUpdateGraphics, OUpdateGraphics);
    ADD_HOOK(0x00707440, HOnAppearanceDraw, OOnAppearanceDraw);
}
