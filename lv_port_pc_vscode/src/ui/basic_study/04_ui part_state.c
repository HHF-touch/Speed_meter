#include "ui.h"
#include "stdio.h"

void ui_init(void)
{

  // 获取活动屏幕对象
  lv_obj_t *screen = lv_screen_active();
  // 创建元素对象
  lv_obj_t *obj = lv_obj_create(screen);
  // 给元素设置样式
  // 设置内边距
  lv_obj_set_style_pad_all(obj, 0, LV_PART_MAIN);
  // 设置圆角
  lv_obj_set_style_radius(obj, 0, LV_PART_MAIN);
  // 设置边框
  lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN);
  lv_obj_set_style_bg_color(obj, lv_color_hex(0x00ff00), LV_PART_SCROLLBAR);

  // 大小
  // lv_obj_set_size(obj, 300, 300);
  lv_obj_set_width(obj, 300);
  lv_obj_set_height(obj, 300);

  lv_obj_t *child = lv_obj_create(obj);
  lv_obj_set_style_bg_color(child, lv_color_hex(0xff0000), LV_PART_MAIN);
  lv_obj_set_size(child, 200, 200);
  lv_obj_set_pos(child, 200, 200);
}
