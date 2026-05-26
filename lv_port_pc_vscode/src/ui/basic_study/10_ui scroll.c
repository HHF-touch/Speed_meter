#include "ui.h"

void obj_event_cb(lv_event_t *e)
{
  lv_obj_t *target = lv_event_get_target(e);
  int32_t scroll_x =  lv_obj_get_scroll_x(target);
  lv_log("scroll_x: %d \n", scroll_x);

}

void ui_init(void)
{

  // 获取活动屏幕对象
  lv_obj_t *screen = lv_screen_active();
  // 创建元素对象
  lv_obj_t *obj = lv_obj_create(screen);

  // 设置内边距
  lv_obj_set_style_pad_all(obj, 0, LV_PART_MAIN);
  // 清除的行和列的内边距
  // lv_obj_set_style_pad_row(obj, 0, LV_PART_MAIN);
  // lv_obj_set_style_pad_column(obj, 0, LV_PART_MAIN);
  // 设置圆角
  lv_obj_set_style_radius(obj, 0, LV_PART_MAIN);
  // 设置边框
  lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN);

  // 大小
  lv_obj_set_size(obj, 300, 300);
  lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLL_MOMENTUM);
  // 禁用弹性滚动
  lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLL_ELASTIC );


  lv_obj_t *child = lv_obj_create(obj);
  lv_obj_set_size(child, 200, 200);
  lv_obj_set_pos(child, 200, 0);
  lv_obj_set_style_bg_color(child, lv_color_hex(0xff0000), LV_PART_MAIN);
  // 禁用链式滚动
  lv_obj_remove_flag(child, LV_OBJ_FLAG_SCROLL_CHAIN_HOR);
  // 禁用/启用滚动惯性
  lv_obj_remove_flag(child, LV_OBJ_FLAG_SCROLL_MOMENTUM);


  lv_obj_t *box = lv_obj_create(child);
  lv_obj_set_size(box, 100, 100);
  lv_obj_set_pos(box, 200, 0);
  lv_obj_set_style_bg_color(box, lv_color_hex(0x00ff00), LV_PART_MAIN);

  // 绑定滚动的事件
  lv_obj_add_event_cb(obj, obj_event_cb, LV_EVENT_SCROLL_END, NULL);
}
