// consoles/amiga/amiga_profile.h - the Commodore Amiga (OCS/ECS) console unit,
// in one file: joystick vocabulary, panel composition, SystemProfile row, name
// aliases, and the ABI capability defaults launcher_profile_apply() writes for
// "amiga".
//
// Include via src/launcher_system.h (profiles + lookups) or
// src/launcher_profile.h (ABI apply) - consumers never include this directly.
//
// The Amiga is a computer, not a cartridge console: the game arrives as a
// floppy image (ADF) or a prepared memory image, there is no battery SRAM, and
// the stock controller is a one-button 9-pin joystick (Competition Pro style)
// plus the keyboard and mouse. The rebind page therefore lists the joystick
// directions and fire; keyboard keys go straight to the emulated Amiga
// keyboard and need no binding.

#ifndef RUI_CONSOLE_AMIGA_PROFILE_H
#define RUI_CONSOLE_AMIGA_PROFILE_H

#include "launcher_system_types.h"

#ifdef __cplusplus
extern "C" {
#endif

// ---- joystick vocabulary (rebind page) ------------------------------------------
// Port 2 joystick: four directions and one fire button. Fire 2 is the second
// button some joysticks wire to pin 9 (POTY); few games read it.
static const ButtonDef kAmigaPadButtons[] = {
    { "Up", 0 }, { "Down", 1 }, { "Left", 2 }, { "Right", 3 },
    { "Fire", 4 }, { "Fire 2", 5 },
};
#define LNG_AMIGA_PAD_BUTTON_COUNT \
    ((int)(sizeof(kAmigaPadButtons) / sizeof(kAmigaPadButtons[0])))

// ---- panel composition ----------------------------------------------------------
// Dashboard: the GAME card plus MOUSE & KEYBOARD (pointer sensitivity,
// grab-on-start, legend) where consoles show the controller card. Amiga games
// are played with mouse, keyboard and a one-button joystick that the runner
// maps directly; there is no pad to rebind, so no controller-config view.
// No save card (no SRAM; games that save write to disk). Settings: video + audio.
static const char* const kPanelsDashboardAmiga[]  = { "game", "mouse_keyboard", NULL };
static const char* const kPanelsControllerAmiga[] = { NULL };
static const char* const kPanelsSettingsAmiga[] = { "video", "audio", NULL };

// ---- screen model -------------------------------------------------------------
// The runner presents either sharp square pixels or a Commodore 1084S monitor
// shader (curvature, beam-width scanlines, RGB phosphor mask, glow, 4:3).
static const char* const kAmigaScreenKinds[] = { "Sharp", "Commodore 1084S" };

// ---- game file-picker filter ----------------------------------------------------
static const char* const kAmigaRomPatterns[] = { "*.adf", "*.bin" };
#define LNG_AMIGA_ROM_PATTERN_COUNT \
    ((int)(sizeof(kAmigaRomPatterns) / sizeof(kAmigaRomPatterns[0])))

// ---- SystemProfile row ----------------------------------------------------------
static const SystemProfile kSystemProfileAmiga = {
    /* id       */ "amiga",
    /* platform */ "COMMODORE AMIGA",
    /* theme    */ "amiga",      // Workbench 1.3 blue/orange, CRT scanlines (launcher_theme.h)
    /* rom_noun */ "DISK",
    /* controller */ {
        kAmigaPadButtons, LNG_AMIGA_PAD_BUTTON_COUNT,
        "pad_amiga.tga", NULL, NULL,
        /* max_players */ 2, /* has_pad_mode */ 0,
        /* binds_per_input */ 1,
        NULL, 0,
        /* has_pad_binds */ 1,
    },
    /* save */    { SAVE_NONE, 0, NULL },
    /* video */   {
        /*window_scale*/1, /*fullscreen*/1, /*linear_filter*/1, /*widescreen*/0,
        /*renderer*/0, /*supersampling*/0, /*screen_kind*/1, /*frame_interp*/0, /*aspect*/0,
        /*texture_filter*/0, /*antialiasing*/0, /*spu_hq*/0, /*skip_fmv*/0, /*turbo_loads*/0,
        /*bios*/0, /*deadzone*/0,
        /*widescreen_cells*/0,
    },
    /* verify */  { 0, NULL },   // hash of the supplied disk / image vs the game's expected CRC
    /* hotkeys_mask */ 0u,
    /* panels_dashboard  */ kPanelsDashboardAmiga,
    /* panels_settings   */ kPanelsSettingsAmiga,
    /* panels_controller */ kPanelsControllerAmiga,
    /* screen_kind_names */ kAmigaScreenKinds,
    /* screen_kind_count */ 2,
    /* rom_filter        */ { kAmigaRomPatterns, LNG_AMIGA_ROM_PATTERN_COUNT,
                              "Amiga disk image (.adf) or memory image (.bin)" },
    /* renderer_labels   */ NULL,
    /* hide_audio_freq   */ 0,
    /* brand             */ "brand_amiga.tga",
};

// ---- name aliases + ABI capability defaults -------------------------------------
static inline int launcher_console_is_amiga(const char* name) {
    return lps_streq_ci(name, "amiga") || lps_streq_ci(name, "a500") ||
           lps_streq_ci(name, "commodoreamiga");
}

static inline void launcher_profile_apply_amiga(RecompLauncherCGameInfo* gi) {
    gi->theme    = "amiga";
    gi->platform = "COMMODORE AMIGA";
    gi->rom_noun = "DISK";
    gi->widescreen_supported = 0;
    gi->has_screen_kind = 1;            // Sharp / Commodore 1084S
}

#ifdef __cplusplus
}
#endif

#endif // RUI_CONSOLE_AMIGA_PROFILE_H
