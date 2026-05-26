#include "ui.h"

void some_observer_cb(lv_observer_t *observer, lv_subject_t *subject)
{
  lv_log("observer cb called... \n");
  int32_t new_sub_value = lv_subject_get_int(subject);
  lv_log("new sub value: %d \n", new_sub_value);
}
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
void ui_init(void)
{

  // 获取活动屏幕对象
  lv_obj_t *screen = lv_screen_active();

  // 初始化主题, 主题的定义必须是全局
  static lv_subject_t my_sub;
  lv_subject_init_int(&my_sub, 30);
  // 获取主题的值
  int32_t sub_value = lv_subject_get_int(&my_sub);
  lv_log("sub_value: %d \n", sub_value);

  // 给主题绑定观察者, 会触发一次观察的回调
  lv_observer_t *observer = lv_subject_add_observer(&my_sub, some_observer_cb, NULL);
  // lv_subject_set_int(&my_sub, 20);

  // 创建slider
  lv_obj_t *slider = lv_slider_create(screen);
  lv_obj_set_size(slider, 200, 20);
  lv_slider_set_range(slider, 0, 100);
  // lv_slider_set_value(slider, 50, LV_ANIM_OFF);

  lv_obj_set_pos(slider, 100, 100);

  lv_slider_bind_value(slider, &my_sub);


  // 创建label
  lv_obj_t *label = lv_label_create(screen);
  // lv_label_set_text(label, "123");
  // 给label绑定主题
  lv_label_bind_text(label, &my_sub, "look at me: %d");
}
