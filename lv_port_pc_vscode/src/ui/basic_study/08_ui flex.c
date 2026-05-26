#include "ui.h"

void ui_init(void)
{

  // 获取活动屏幕对象
  lv_obj_t *screen = lv_screen_active();
  // 创建元素对象
  lv_obj_t *obj = lv_obj_create(screen);

  // 设置内边距
  lv_obj_set_style_pad_all(obj, 0, LV_PART_MAIN);
  // 清除的行和列的内边距
  lv_obj_set_style_pad_row(obj, 0, LV_PART_MAIN);
  lv_obj_set_style_pad_column(obj, 0, LV_PART_MAIN);
  // 设置圆角
  lv_obj_set_style_radius(obj, 0, LV_PART_MAIN);
  // 设置边框
  lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN);

  // 大小
  lv_obj_set_size(obj, 300, 300);

  // 设置flex布局
  lv_obj_set_layout(obj, LV_LAYOUT_FLEX);
  // 设置flex的布局方向
  lv_obj_set_flex_flow(obj, LV_FLEX_FLOW_ROW);
  // 设置flex的对齐方式
  lv_obj_set_flex_align(obj, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);

  // for (size_t i = 0; i < 10; i++)
  // {
  //   lv_obj_t *child = lv_obj_create(obj);
  //   lv_obj_set_size(child, i * 5 + 10, i * 5 + 10);
  //   lv_obj_set_style_bg_color(child, lv_color_hex(0xff0000), LV_PART_MAIN);
  // }
  for (size_t i = 0; i < 2; i++)
  {
    lv_obj_t *child = lv_obj_create(obj);
    lv_obj_set_size(child, 100, 100);
    lv_obj_set_style_border_width(child, 0, LV_PART_MAIN);
    lv_obj_set_style_bg_color(child, lv_color_hex(0xff0000), LV_PART_MAIN);
  }
}
