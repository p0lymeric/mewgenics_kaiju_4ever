#include "ameboid.hpp"
#include "types/msvc.hpp"
// #include "utilities/debug_console.hpp"
#include "utilities/function_hook.hpp"

// Makes it so that the kaiju you've picked in your save remains in the
// background of the house, even after unlocking the Rift!
//
// polymeric 2026

struct PrivateState {
    bool override_properties_mapflag_DimensionXUnlocked_to_0 = false;
};

static PrivateState P;

MAKE_SHOOK(0, ADDRESS_maybe_get_sql_properties_int64,
    int64_t, __cdecl, maybe_get_sql_properties_int64,
    void *thiss, MsvcReleaseModeXString *key, int64_t default_value
) {
    // Clone key because it may be callee-destroyed
    std::string key_clone = key->copy_to_native_string();

    // Always call the original function in case key needs to be callee-destroyed
    int64_t result = maybe_get_sql_properties_int64_hook.orig(thiss, key, default_value);

    // D::debug("sqlite properties query key {} default_value {} result {}", key_clone, default_value, result);

    if(P.override_properties_mapflag_DimensionXUnlocked_to_0) {
        if(key_clone == "mapflag_DimensionXUnlocked") {
            // D::debug("query for mapflag_DimensionXUnlocked");
            return G.config_true_to_hide_kaiju_false_to_show_kaiju ? 1 : 0;
        }
    }

    return result;
}

MAKE_SHOOK(0, ADDRESS_glaiel__BackgroundKaiju__unlocked_update,
    void, __cdecl, glaiel__BackgroundKaiju__unlocked_update,
    void *thiss
) {
    // D::debug("kaiju unlocked_update");
    P.override_properties_mapflag_DimensionXUnlocked_to_0 = true;
    glaiel__BackgroundKaiju__unlocked_update_hook.orig(thiss);
    P.override_properties_mapflag_DimensionXUnlocked_to_0 = false;
}
