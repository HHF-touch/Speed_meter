#include "speed_meter_common.h"

extern const lv_font_t noto_sans_sc_14;

void clear_default_style(lv_obj_t *target)
{
  // 设置内边距
  lv_obj_set_style_pad_all(target, 0, LV_PART_MAIN);
  // 清除的行和列的内边距
  lv_obj_set_style_pad_row(target, 0, LV_PART_MAIN);
  lv_obj_set_style_pad_column(target, 0, LV_PART_MAIN);
  // 设置圆角
  lv_obj_set_style_radius(target, 0, LV_PART_MAIN);
  // 设置边框
  lv_obj_set_style_border_width(target, 0, LV_PART_MAIN);
}

// 设置主题
void speed_meter_set_theme(lv_color_t theme_color, bool is_dark)
{
  // 获取显示对象
  lv_display_t * display = lv_disp_get_default();
  lv_theme_t * th = lv_theme_default_init(display,
                                        theme_color,
                                        lv_color_hex(0x00ff00),
                                        is_dark,
                                        &noto_sans_sc_14);

lv_display_set_theme(display, th);
}
