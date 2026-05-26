#include "ui.h"
#include "stdio.h"

void ui_init(void)
{

  // 获取活动屏幕对象
  lv_obj_t *screen = lv_screen_active();
  // 创建元素对象
  lv_obj_t *obj = lv_obj_create(screen);
  lv_obj_t *obj2 = lv_obj_create(screen);
  lv_obj_t *obj3 = lv_obj_create(screen);
  lv_obj_set_style_bg_color(obj, lv_color_hex(0xff0000), LV_PART_MAIN);
  lv_obj_set_style_bg_color(obj2, lv_color_hex(0x00ff00), LV_PART_MAIN);
  lv_obj_set_style_bg_color(obj3, lv_color_hex(0x0000ff), LV_PART_MAIN);
  // 给元素设置样式
  // 设置内边距
  lv_obj_set_style_pad_all(obj, 0, LV_PART_MAIN);
  // 设置圆角
  lv_obj_set_style_radius(obj, 0, LV_PART_MAIN);
  // 设置边框
  lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN);
  lv_obj_set_style_bg_color(obj, lv_color_hex(0x00ff00), LV_PART_SCROLLBAR);

  // 大小
  lv_obj_set_size(obj, 100, 100);
  lv_obj_set_size(obj2, 100, 100);
  lv_obj_set_size(obj3, 100, 100);

  lv_obj_set_pos(obj, 50, 50);
  lv_obj_set_pos(obj2, 100, 100);
  lv_obj_set_pos(obj3, 150, 150);

  // lv_log("obj index: %d \n", lv_obj_get_index(obj));
  // lv_log("obj2 index: %d \n", lv_obj_get_index(obj2));

  // lv_obj_move_to_index(obj, 1);
  // lv_log("obj index: %d \n", lv_obj_get_index(obj));
  // lv_log("obj2 index: %d \n", lv_obj_get_index(obj2));

  lv_obj_swap(obj, obj3);
}
