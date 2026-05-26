#include "ui.h"
#include "stdio.h"
#include "my_component.h"

void obj_event_cb(lv_event_t *e)
{
}
void ui_init(void)
{

  // 获取活动屏幕对象
  lv_obj_t *screen = lv_screen_active();
  // 创建元素对象
  lv_obj_t *obj = lv_obj_create(screen);

  lv_obj_set_style_bg_color(obj, lv_color_hex(0xff0000), LV_PART_MAIN);
  // 给元素设置样式
  // 设置内边距
  lv_obj_set_style_pad_all(obj, 0, LV_PART_MAIN);
  // 设置圆角
  lv_obj_set_style_radius(obj, 0, LV_PART_MAIN);
  // 设置边框
  lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN);

  // 大小
  lv_obj_set_size(obj, 300, 300);


  // 给obj绑定事件
  lv_obj_add_event_cb(obj, obj_event_cb, LV_EVENT_CLICKED, (void *)123);

  // my_component.width = 200;

  My_Component_t *cmp = My_Component_Create(obj);
  My_Component_set_size(cmp, 100, 200);
}
