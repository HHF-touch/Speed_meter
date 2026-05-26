#include "ui.h"
#include "stdio.h"

void ui_init(void)
{
  // 获取活动屏幕对象
  lv_obj_t *screen = lv_screen_active();
  // 创建元素对象
  lv_obj_t *obj = lv_obj_create(screen);
  // 给元素设置样式
  // 大小
  lv_obj_set_size(obj, 300, 300);

  // 背景颜色
  lv_obj_set_style_bg_color(obj, lv_color_hex(0xff0000), LV_PART_MAIN);
  // 设置圆角
  lv_obj_set_style_radius(obj, 0, LV_PART_MAIN);
  // 设置边框
  lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN);
  // 设置位置
  lv_obj_set_pos(obj, 100, 100);

  // 创建slider
  lv_obj_t *slider = lv_slider_create(screen);
  // 设置slider大小
  // lv_obj_set_size(slider, 20, 200);
  lv_obj_set_size(slider, 200, 20);
  lv_obj_set_pos(slider, 30, 30);
  /* Set slider-specific attributes */
  lv_slider_set_range(slider, 40, 100);         /* Set the min and max values */
  lv_slider_set_value(slider, 10, LV_ANIM_OFF); /* Set the current value (position) */


  // 删除控件
  // lv_delay_ms(3000);
  // lv_obj_delete(slider);
  lv_obj_delete_delayed(slider, 3000);










}
