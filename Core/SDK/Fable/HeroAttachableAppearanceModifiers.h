#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <functional>

#include "../Utils/Hook.h"

#include "HeroAttachableAppearanceModifierType.h"

class CTCHeroAttachableAppearanceModifiers
{
public:
    std::vector<std::vector<long>> GetAllAppearanceModifierLists();
    void SetAllAppearanceModifierLists(const std::vector<std::vector<long>>& modifiers);

    void AddAppearanceModifierWithReplace(long);
    void GetAppearanceModifierList(std::list<long>&, EHeroAttachableAppearanceModifierType);

    void AddFrameUpdateCallback(const std::string& id, std::function<void()> callback) { frameUpdateCallbacks[id] = callback; }
    void RemoveFrameUpdateCallback(const std::string& id) { frameUpdateCallbacks.erase(id); }

    static void Hook();

private:
    static std::map<std::string, std::function<void()>> frameUpdateCallbacks;

    static void(__thiscall* OAddAppearanceModifierWithReplace)(CTCHeroAttachableAppearanceModifiers*, long);
    static void __fastcall HAddAppearanceModifierWithReplace(CTCHeroAttachableAppearanceModifiers* _this, void* _EDX, long def_num);

    static void(__thiscall* OGetAppearanceModifierList)(CTCHeroAttachableAppearanceModifiers*, std::list<long>&, EHeroAttachableAppearanceModifierType);
    static void __fastcall HGetAppearanceModifierList(CTCHeroAttachableAppearanceModifiers* _this, void* _EDX, std::list<long>& fill_in_list, EHeroAttachableAppearanceModifierType type);

    static void(__thiscall* OFrameUpdate)(CTCHeroAttachableAppearanceModifiers*);
    static void __fastcall HFrameUpdate(CTCHeroAttachableAppearanceModifiers* _this, void* _EDX);
};
