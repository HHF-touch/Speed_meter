#include "speed_meter_common.h"

void speed_meter_translation_init(void)
{
    static const char * languages[] = {"en", "ch", NULL};
    static const char * tags[] = {"language", "dark mode", "gpx", "general", "settings", NULL};
    static const char * translations[] = {
        "Language", "语言",
        "Dark Mode", "深色模式",
        "GPX", "路书",
        "General", "通用",
        "Settings", "设置",
        NULL
    };


    lv_translation_add_static(languages, tags, translations);

    // 设置默认语种
    lv_translation_set_language("ch");
}