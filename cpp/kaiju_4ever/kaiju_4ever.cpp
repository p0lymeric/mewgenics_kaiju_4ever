#include "ameboid.hpp"
#include "types/glaiel_toplevel.hpp"
#include "types/msvc.hpp"
#include "types/glaiel.hpp"
// #include "utilities/debug_console.hpp"
#include "utilities/function_hook.hpp"
#include "utilities/portal.hpp"

// Makes it so that the kaiju you've picked in your save remains in the
// background of the house, even after unlocking the Rift!
//
// polymeric 2026

struct PrivateState {
    bool override_properties_mapflag_DimensionXUnlocked_to_0 = false;
};

static PrivateState P;

MAKE_SDPORTAL(DATAOFF_glaiel__MewDirector__p_singleton,
    MewDirector *, get_p_mewdirector_singleton
)


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
    MewDirector *p_md = get_p_mewdirector_singleton();
    uint8_t *p_md_plus_0x5a8 = *reinterpret_cast<uint8_t **>(reinterpret_cast<uint8_t *>(p_md) + 0x5a8);
    MsvcReleaseModeXString *kaiju_name = reinterpret_cast<MsvcReleaseModeXString *>(p_md_plus_0x5a8 + 0x4b8);
    // D::debug("kaiju {}", kaiju_name->as_native_string_view());
    std::string kaiju_name_clone = kaiju_name->copy_to_native_string();
    kaiju_name->destroy();
    kaiju_name->construct("pyrophina");
    P.override_properties_mapflag_DimensionXUnlocked_to_0 = true;
    glaiel__BackgroundKaiju__unlocked_update_hook.orig(thiss);
    P.override_properties_mapflag_DimensionXUnlocked_to_0 = false;
    kaiju_name->destroy();
    kaiju_name->construct(kaiju_name_clone.data(), kaiju_name_clone.size());
}
