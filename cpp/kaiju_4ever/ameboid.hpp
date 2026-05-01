#pragma once

#include "utilities/signature.hpp"

#include <cstdint>

// Main program declarations.
//
// polymeric 2026

// CONSTANTS

// Mod information

inline constexpr char MOD_AUTHOR[] = "polymeric";
inline constexpr char MOD_NAME[] = "Kaiju 4Ever";
inline constexpr char MOD_URL[] = "https://github.com/p0lymeric/mewgenics_kaiju_4ever";
inline constexpr char MOD_VERSION[] = "1.0.3-beta";

// These signatures were extracted from Mewgenics.exe

// Function offsets are encoded as relative VAs
inline constexpr const auto ADDRESS_maybe_get_sql_properties_int64 = DirectSig::make<"48 89 54 24 10 55 53 56 57 41 56 48 8D 6C 24 C9 48 81 EC E0 00 00 00 49 8B F0 48 8B FA 48 8B D9">(0);
// NB: We use the signature as a safety check to verify that the hooked version of the game has not changed where it stores the kaiju's name
// Specifically these two instructions 48 8B 93 A8 05 00 00  48 81 C2 B8 04 00 00 (*(p_MewDirector + 0x5a8) + 0x4b8)
inline constexpr const auto ADDRESS_glaiel__BackgroundKaiju__unlocked_update = DirectSig::make<"48 89 5C 24 18 55 56 57 48 83 EC 70 0F 29 74 24 60 48 8B F9 48 8B 41 28 F2 0F 10 48 28 F2 0F 59 49 78 48 8B 41 18 F2 0F 10 40 10 F2 0F 59 41 30 F2 0F 59 C8 F2 0F 58 89 88 00 00 00 F2 0F 11 89 88 00 00 00 48 8B 1D ?? ?? ?? ?? 48 8B 93 A8 05 00 00 48 81 C2 B8 04 00 00">(0);

// Data offsets are encoded as relative VAs
inline constexpr const auto DATAOFF_glaiel__MewDirector__p_singleton = IndirectSig::make<"48 89 5C 24 10 48 89 4C 24 08 57 48 83 EC 40 48 8B CA 48 8B 05 ?? ?? ?? ?? 48 8B B8 A8 05 00 00">(21, 4, true, true);

// TLS variable offsets are encoded relative to the base VA of their TLS slot

// CROSS-TU DECLARATIONS

// The "everything" struct
// Exporter: ameboid.cpp
struct GlobalContext;
extern GlobalContext G;

// TYPE DECLARATIONS

struct GlobalContext {
    // ameboid.dll offset.
    uintptr_t dll_base_va;
    uintptr_t dll_image_size;

    // Mewgenics.exe offset.
    uintptr_t host_exec_base_va;
    uintptr_t host_exec_image_size;

    // Whether it is permissible for the dll to self-eject
    // (false if the dll cannot self-uninstall its hooks)
    bool dll_can_self_eject;

    // Configuration
    bool config_true_to_hide_kaiju_false_to_show_kaiju;
    bool config_true_for_zaratana_false_for_pyrophina;
};
