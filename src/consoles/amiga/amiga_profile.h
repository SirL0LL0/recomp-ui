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

// ---- input vocabulary (rebind page) ---------------------------------------------
// What a modern keyboard or gamepad can drive on the emulated Amiga: the port 2
// joystick (four directions + fire), the two mouse buttons and the keys games
// commonly read outside of text entry. Bindings are host-consumed
// (GameInfo.settings_bindings): the runner reads player_key_bind/player_pad_bind
// by these indices. Unbound keyboard keys still reach the Amiga keyboard, and
// the left analog stick always moves the mouse pointer.
static const ButtonDef kAmigaPadButtons[] = {
    { "Joystick up", 0 }, { "Joystick down", 1 }, { "Joystick left", 2 }, { "Joystick right", 3 },
    { "Joystick fire", 4 }, { "Mouse left button", 5 }, { "Mouse right button", 6 },
    { "Space", 7 }, { "Return", 8 }, { "Backspace", 9 }, { "Escape", 10 },
};
#define LNG_AMIGA_PAD_BUTTON_COUNT \
    ((int)(sizeof(kAmigaPadButtons) / sizeof(kAmigaPadButtons[0])))

// ---- panel composition ----------------------------------------------------------
// Dashboard: the GAME card plus MOUSE & KEYBOARD (pointer sensitivity,
// grab-on-start, legend, and the way into the rebind view) where consoles show
// the controller card. The rebind view maps keys and gamepad buttons onto the
// inputs above. No save card (no SRAM; games that save write to disk).
// Settings: video + audio.
static const char* const kPanelsDashboardAmiga[]  = { "game", "mouse_keyboard", NULL };
static const char* const kPanelsControllerAmiga[] = { "controller_config", NULL };
static const char* const kPanelsSettingsAmiga[] = { "video", "audio", NULL };

// ---- screen model -------------------------------------------------------------
// The runner presents sharp pixels or one of its CRT shaders: a Commodore
// 1084S monitor (Lanczos, gaussian beam, slot mask, halation, light
// curvature), an Easymode-style flat CRT, or plain scanlines. The pixel
// shape (PAL 4:3, NTSC 4:3 or square) is the separate aspect setting (aspect_labels).
static const char* const kAmigaScreenKinds[] = {
    "Sharp", "Commodore 1084S", "CRT Easymode", "Scanlines" };
#define LNG_AMIGA_SCREEN_KIND_COUNT \
    ((int)(sizeof(kAmigaScreenKinds) / sizeof(kAmigaScreenKinds[0])))

// ---- game file-picker filter ----------------------------------------------------
static const char* const kAmigaRomPatterns[] = { "*.ipf", "*.adf", "*.bin" };
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
        /* max_players */ 1, /* has_pad_mode */ 0,
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
    /* screen_kind_count */ LNG_AMIGA_SCREEN_KIND_COUNT,
    /* rom_filter        */ { kAmigaRomPatterns, LNG_AMIGA_ROM_PATTERN_COUNT,
                              "Amiga disk image (.ipf/.adf) or memory image (.bin)" },
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
    gi->has_screen_kind = 1;            // Sharp / 1084S / Easymode / Scanlines
    gi->has_integer_scale = 1;          // pixel perfect: whole multiples of the game's lines
    gi->settings_bindings = 1;          // the runner consumes the key/pad chips
}

#ifdef __cplusplus
}
#endif

#endif // RUI_CONSOLE_AMIGA_PROFILE_H
