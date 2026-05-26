#include "ui.h"

void ui_init(void)
{

  // 获取活动屏幕对象
  lv_obj_t *screen = lv_screen_active();
  // 创建元素对象
  lv_obj_t *obj = lv_obj_create(screen);
  lv_obj_t *obj2 = lv_obj_create(screen);

  // 设置内边距
  lv_obj_set_style_pad_all(obj, 0, LV_PART_MAIN);
  // 清除的行和列的内边距
  // lv_obj_set_style_pad_row(obj, 0, LV_PART_MAIN);
  // lv_obj_set_style_pad_column(obj, 0, LV_PART_MAIN);
  // 设置圆角
  lv_obj_set_style_radius(obj, 0, LV_PART_MAIN);
  // 设置边框
  lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN);
  // lv_obj_set_style_translate_x(obj, 50, LV_PART_MAIN);
  lv_obj_set_style_transform_width(obj, 300, LV_PART_MAIN);


  // 大小
  lv_obj_set_size(obj, 100, 100);
  lv_obj_set_size(obj2, 100, 100);
  lv_obj_set_style_bg_color(obj, lv_color_hex(0xff0000), LV_PART_MAIN);
  lv_obj_set_style_bg_color(obj2, lv_color_hex(0x00ff00), LV_PART_MAIN);
  lv_obj_set_x(obj2, 100);
}
