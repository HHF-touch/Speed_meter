#include "setting.h"

void switch_event_cb(lv_event_t *e)
{
    lv_obj_t *target = lv_event_get_target(e);
    bool is_on = lv_obj_has_state(target, LV_STATE_CHECKED);
    lv_log("is_on : %d \n", is_on);
    
    speed_meter_set_theme(SPEED_METER_THEME_COLOR, is_on);

}

// 下拉列表value_changed发送改变的事件
void dropdown_event_cb(lv_event_t *e)
{
    lv_obj_t *target = lv_event_get_target(e);
    
    uint32_t dropdown_value = lv_dropdown_get_selected(target);
    lv_translation_set_language(dropdown_value?"ch" : "en");
}

void speed_meter_setting_init(lv_obj_t *parent)
{
    clear_default_style(parent);
    lv_obj_set_layout(parent, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(parent, LV_FLEX_FLOW_COLUMN);

    // 创建语言包裹器
    lv_obj_t *language_container = lv_obj_create(parent);

    // 清除默认样式
    clear_default_style(language_container);

    // 设置padding
    lv_obj_set_style_pad_all(language_container, 10, LV_PART_MAIN);

    // 设置flex
    lv_obj_set_layout(language_container, LV_LAYOUT_FLEX);
    lv_obj_set_flex_align(language_container, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER); 
    lv_obj_set_size(language_container, lv_pct(100), LV_SIZE_CONTENT);

    // 创建label
    lv_obj_t *language_label = lv_label_create(language_container);
    // lv_label_set_text(language_label, "Language");

    // 设置翻译的tag
    lv_label_set_translation_tag(language_label, "language");

    // 创建下拉列表
    lv_obj_t *language_dropdown = lv_dropdown_create(language_container);
    lv_dropdown_set_options(language_dropdown, "English\n"
                                               "Chinese");

    // 给下拉列表绑定value_changed事件
    lv_obj_add_event_cb(language_dropdown, dropdown_event_cb, LV_EVENT_VALUE_CHANGED, NULL);

    // Dark Mode
    lv_obj_t *dark_mode_container = lv_obj_create(parent);
    clear_default_style(dark_mode_container);
    lv_obj_set_style_pad_all(dark_mode_container, 10, LV_PART_MAIN);
    lv_obj_set_layout(dark_mode_container, LV_LAYOUT_FLEX);
    lv_obj_set_flex_align(dark_mode_container, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER); 
    lv_obj_set_size(dark_mode_container, lv_pct(100), LV_SIZE_CONTENT);

    lv_obj_t *dark_mode_label = lv_label_create(dark_mode_container);
    // lv_label_set_text(dark_mode_label, "Dark Mode");
    lv_label_set_translation_tag(dark_mode_label, "dark mode");

    // 创建switch开关
    lv_obj_t *dark_mode_switch = lv_switch_create(dark_mode_container);

    // 绑定事件
    lv_obj_add_event_cb(dark_mode_switch, switch_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
}

