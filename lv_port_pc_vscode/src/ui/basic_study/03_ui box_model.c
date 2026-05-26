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

  // 背景颜色
  // lv_obj_set_style_bg_color(obj, lv_color_hex(0xff0000), LV_PART_MAIN);
  // 设置圆角
  lv_obj_set_style_radius(obj, 0, LV_PART_MAIN);
  // 设置边框
  lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN);

  // 大小
  // lv_obj_set_size(obj, 300, 300);
  lv_obj_set_width(obj, 300);
  lv_obj_set_height(obj, 300);

  //! 通过style样式表设置样式的优先级低于通过对象直接设置元素的样式
  static lv_style_t style_main;
  lv_style_init(&style_main);
  lv_style_set_width(&style_main, 300);
  lv_style_set_bg_color(&style_main, lv_color_hex(0x00ff00));

  lv_obj_add_style(obj, &style_main, LV_PART_MAIN);

  // 基于obj创建一个子元素
  lv_obj_t *child = lv_obj_create(obj);
  lv_obj_set_style_bg_color(child, lv_color_hex(0xff0000), LV_PART_MAIN);
  // 动态设置元素大小  lv_pct： 百分比(基于父元素)
  lv_obj_set_size(child, lv_pct(50), lv_pct(50));

  // LV_SIZE_CONTENT由内容撑开
  // lv_obj_set_size(child, LV_SIZE_CONTENT, LV_SIZE_CONTENT);

  // ! 设置位置
  lv_obj_set_pos(obj, 100, 100);
  
  // lv_obj_set_x(obj, 200);
  // lv_obj_set_y(obj, 200);
  // ! 动态定位  lv_obj_align可以相对于父元素的任意位置定位
  lv_obj_align(child, LV_ALIGN_CENTER, 0, 0);
  // 相对于指定的元素进行对齐
  lv_obj_t *child2 = lv_obj_create(obj);
  lv_obj_set_style_bg_color(child2, lv_color_hex(0x0000ff), LV_PART_MAIN);
  lv_obj_set_size(child2, lv_pct(50), lv_pct(50));



  lv_obj_align_to(child2, child, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);




}
