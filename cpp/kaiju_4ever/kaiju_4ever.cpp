#include "amoeboid.hpp"
#include "types/msvc.hpp"
// #include "utilities/debug_console.hpp"
#include "utilities/function_hook.hpp"
#include "utilities/portal.hpp"

// Makes it so that the kaiju you've picked remains in the
// background of the house, even after unlocking the Rift!
//
// polymeric 2026

struct PrivateState {
    bool override_properties_mapflag_DimensionXUnlocked = false;
};

static PrivateState P;

MAKE_SDPORTAL(DATAOFF_glaiel__MewDirector__p_singleton,
    uint8_t *, get_p_mewdirector_singleton
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

    if(P.override_properties_mapflag_DimensionXUnlocked) {
        if(key_clone == "mapflag_DimensionXUnlocked") {
            // D::debug("query for mapflag_DimensionXUnlocked");
            if(G.kaiju_setting == KaijuSetting::Never) {
                result = 1;
            } else {
                result = 0;
            }
        }
    }

    return result;
}

MAKE_SHOOK(0, ADDRESS_glaiel__BackgroundKaiju__unlocked_update,
    void, __cdecl, glaiel__BackgroundKaiju__unlocked_update,
    void *thiss
) {
    // D::debug("kaiju unlocked_update");
    if(G.kaiju_setting == KaijuSetting::Never) {
        // Override mapflag_DimensionXUnlocked to 1 to force the game to hide the kaiju
        P.override_properties_mapflag_DimensionXUnlocked = true;
        glaiel__BackgroundKaiju__unlocked_update_hook.orig(thiss);
        P.override_properties_mapflag_DimensionXUnlocked = false;
    } else {
        uint8_t *p_mewdirector = get_p_mewdirector_singleton();
        // Safety note: these hardcoded offsets are verified as part of signature scanning for ADDRESS_glaiel__BackgroundKaiju__unlocked_update
        // so we can be confident here that we are modifying the memory we expect.
        uint8_t *p_globalprogressiondata = *reinterpret_cast<uint8_t **>(p_mewdirector + MEWDIRECTOR_GLOBALPROGRESSIONDATA_OFFSET);
        MsvcReleaseModeXString *kaiju_name = reinterpret_cast<MsvcReleaseModeXString *>(p_globalprogressiondata + GLOBALPROGRESSIONDATA_KAIJU_NAME_OFFSET);
        // D::debug("kaiju {}", kaiju_name->as_native_string_view());
        std::string kaiju_name_clone = kaiju_name->copy_to_native_string();

        // Now we override the field in memory that stores which kaiju was chosen by the player
        // The game checks this string every frame to know if it should draw Pyrophina or Zaratana or nothing as the background kaiju
        switch(G.kaiju_setting) {
            case KaijuSetting::Pyrophina:
                // Always show Pyrophina
                kaiju_name->destroy();
                kaiju_name->construct("pyrophina");
                break;
            case KaijuSetting::Zaratana:
                // Always show Zaratana
                kaiju_name->destroy();
                kaiju_name->construct("zaratana");
                break;
            default: // case KaijuSetting::Auto:
                // In Auto mode, we start displaying the kaiju chosen after Pyrophina vs. Zaratana
                // and ensure they continue to be displayed after the Rift is unlocked.
                // When a save unlocks the Rift, the game clears the kaiju field in GlobalProgressionData
                // but writes a SQL flag into the properties table. We read those flags and
                // override the GlobalProgressionData value to match.
                uint8_t *p_properties = *reinterpret_cast<uint8_t **>(p_mewdirector + MEWDIRECTOR_PROPERTIES_OFFSET);
                MsvcReleaseModeXString sql_key = {};
                sql_key.construct("TheRift_UsedPyrophina");
                if(maybe_get_sql_properties_int64_hook.target(p_properties, &sql_key, 0)) { // destroys sql_key
                    kaiju_name->destroy();
                    kaiju_name->construct("pyrophina");
                    break;
                }
                sql_key.construct("TheRift_UsedZaratana");
                if(maybe_get_sql_properties_int64_hook.target(p_properties, &sql_key, 0)) { // destroys sql_key
                    kaiju_name->destroy();
                    kaiju_name->construct("zaratana");
                    break;
                }
                break;
        }

        // We then must override mapflag_DimensionXUnlocked to 0 so that the game does not hide the kaiju
        P.override_properties_mapflag_DimensionXUnlocked = true;
        glaiel__BackgroundKaiju__unlocked_update_hook.orig(thiss);
        // undo the mapflag override
        P.override_properties_mapflag_DimensionXUnlocked = false;

        // undo the string override
        kaiju_name->destroy();
        kaiju_name->construct(kaiju_name_clone.data(), kaiju_name_clone.size());
    }
}
