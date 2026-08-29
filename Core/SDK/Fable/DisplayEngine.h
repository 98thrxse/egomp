#pragma once

#include <iostream>

#include "../Utils/Hook.h"

#include "IEngine.h"

class CMainGameComponent;
class CPlayerManager;
class CWorld;

class CDisplayEngine
{
public:
    char pad0[0x4];

    unsigned int EnginePreloadFlags;
    const CMainGameComponent* Component;
    const CPlayerManager* PlayerManager;

    char pad1[0x4]; // const CGameDefinitionManager* DefinitionManager;
    char pad2[0x4]; // const CGraphicDataBank* EngineGraphicBank;
    char pad3[0x4]; // CMeshDataBank* MeshBank;
    char pad4[0x10]; // C2DBoxF MainWindow;
    
    CIEngine* Engine3D;

    char pad5[0x4]; // HINSTANCE__* EngineHandle
    char pad6[0x38]; // CCamera Camera

    int Frame;
    bool DrawGame;

    char pad7[0x3];
    char pad8[0x20]; // CLetterBoxModeInfo LetterBox;

    bool CameraInputsOn;

    char pad9[0x3];

    long double LastRefreshTime;
    long double LastRenderTimeLength;
    long double LastWorldUpdateRenderTime;
    bool PreparePrimitives;

    char pad10[0x3];

    float GammaRamp;
    float OldGammaRamp;

    char pad11[0x1C]; // CFadeInFadeOutBase ScreenFadeOutInfo;

    bool ScreenFadeOutLocked;
    bool DrawMemoryUse;

    char pad12[0x2];

    int DrawDebugPage;

    char pad13[0x8]; // CCountedPointer<CDisplayViewManager> PViewManager;

    int InitialFadeReadynessCount;
    bool InitialFadeActive;

    char pad14[0x3];

    float ScreenFadeDuration;
    float TimeSinceFadeStarted;
    const CWorld* World;

    char pad15[0x4];

    CIEngine* Get3DEngine();

    static void Hook();
};
