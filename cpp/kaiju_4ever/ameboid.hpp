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
inline constexpr char MOD_VERSION[] = "1.0.1";

// These signatures were extracted from Mewgenics.exe

// Function offsets are encoded as relative VAs
inline constexpr const auto ADDRESS_maybe_get_sql_properties_int64 = DirectSig::make<"48 89 54 24 10 55 53 56 57 41 56 48 8D 6C 24 C9 48 81 EC E0 00 00 00 49 8B F0 48 8B FA 48 8B D9">(0);
inline constexpr const auto ADDRESS_glaiel__BackgroundKaiju__unlocked_update = DirectSig::make<"48 89 5C 24 18 55 56 57 48 83 EC 70 0F 29 74 24 60 48 8B F9 48 8B 41 28 F2 0F 10 48 28 F2 0F 59 49 78">(0);

// Data offsets are encoded as relative VAs

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
};
