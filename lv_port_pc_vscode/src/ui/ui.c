#include "ui.h"
#include "speed_meter_common.h"

//! 定义主题的对象
Speed_Meter_Sub_t *speed_meter_sub;

// 所有的运动状态
static char *running_states[] = {"running", "stopped"};

lv_obj_t *screen = NULL;
void speed_meter_screen_init(void)
{
  screen = lv_screen_active();
  clear_default_style(screen);
  // 设置flex布局
  lv_obj_set_layout(screen, LV_LAYOUT_FLEX);
  // 设置纵向布局
  lv_obj_set_flex_flow(screen, LV_FLEX_FLOW_COLUMN);
}

/* 顶部导航栏初始化 */
void speed_meter_nav_bar_init(void)
{
  // 1. 创建导航栏的包裹器
  lv_obj_t *nav_bar_wrapper = lv_obj_create(screen);
  // 2. 清除默认样式
  clear_default_style(nav_bar_wrapper);
  // 2.1 设置样式
  lv_obj_set_layout(nav_bar_wrapper, LV_LAYOUT_FLEX);
  lv_obj_set_flex_flow(nav_bar_wrapper, LV_FLEX_FLOW_ROW);
  lv_obj_set_flex_align(nav_bar_wrapper, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
  lv_obj_set_style_pad_left(nav_bar_wrapper, 5, LV_PART_MAIN);
  lv_obj_set_style_pad_right(nav_bar_wrapper, 5, LV_PART_MAIN);
  // 3. 设置大小
  lv_obj_set_size(nav_bar_wrapper, lv_pct(100), lv_pct(10));
  // 4. 设置背景颜色
  lv_obj_set_style_bg_color(nav_bar_wrapper, SPEED_METER_THEME_COLOR, LV_PART_MAIN);

  // 5. 创建显示的3个内容 label
  lv_obj_t *gps_label = lv_label_create(nav_bar_wrapper);
  lv_obj_t *running_state_label = lv_label_create(nav_bar_wrapper);
  lv_obj_t *battery_level_label = lv_label_create(nav_bar_wrapper);

  // 6. 和对应的主题绑定
  lv_label_bind_text(gps_label, &speed_meter_sub->gps, LV_SYMBOL_GPS " %d");
  lv_label_bind_text(running_state_label, &speed_meter_sub->running_state, "%s");
  lv_label_bind_text(battery_level_label, &speed_meter_sub->battery_level, " %s");
}

void speed_meter_tabview_init(void)
{
  // 创建tabview
  lv_obj_t *tabview = lv_tabview_create(lv_screen_active());
  // 设置tabbar的位置
  lv_tabview_set_tab_bar_position(tabview, LV_DIR_BOTTOM);
  // 设置tabview大小
  lv_obj_set_size(tabview, lv_pct(100), lv_pct(90));
  // 设置tabbar的大小
  lv_tabview_set_tab_bar_size(tabview, lv_pct(10));

  // 给tabview添加多个tabbar
  lv_obj_t *GPX = lv_tabview_add_tab(tabview, "GPX"); // 路书
  lv_obj_t *General = lv_tabview_add_tab(tabview, "General");
  lv_obj_t *Settings = lv_tabview_add_tab(tabview, "Settings");

  // 初始化三个tabview的页面
  speed_meter_gpx_init(GPX);
  speed_meter_general_init(General);
  speed_meter_setting_init(Settings);

  // 设置三个tabber中label对应的tag
  // 获取tabber
  lv_obj_t *tabbers = lv_tabview_get_tab_bar(tabview);
  lv_label_set_translation_tag(lv_obj_get_child(lv_obj_get_child(tabbers, 0), 0), "gpx");
  lv_label_set_translation_tag(lv_obj_get_child(lv_obj_get_child(tabbers, 1), 0), "general");
  lv_label_set_translation_tag(lv_obj_get_child(lv_obj_get_child(tabbers, 2), 0), "settings");

  // lv_tabview_set_active(tabview, 1, LV_ANIM_OFF);
}

/* 用于初始化所有的主题 */
void speed_meter_sub_init(void)
{
  // 为主题的结构体指针分配内存大小
  speed_meter_sub = lv_malloc_zeroed(sizeof(Speed_Meter_Sub_t));
  /* gps主题 */
  lv_subject_init_int(&speed_meter_sub->gps, 1);
  /* 运动状态主题 */
  lv_subject_init_pointer(&speed_meter_sub->running_state, running_states[0]);
  /* 电池电量主题 */
  lv_subject_init_pointer(&speed_meter_sub->battery_level, LV_SYMBOL_BATTERY_2);
  /* 速度主题 */
  lv_subject_init_float(&speed_meter_sub->speed, 20.0);
  /* 距离主题 */
  lv_subject_init_float(&speed_meter_sub->distance, 0.00);
  /* 坡度主题 */
  lv_subject_init_float(&speed_meter_sub->slope, 0.0);
  /* 经度 */
  lv_subject_init_float(&speed_meter_sub->lon, 116.365682);
  /* 纬度 */
  lv_subject_init_float(&speed_meter_sub->lat, 40.102833);
  /* 时间-小时 */
  lv_subject_init_int(&speed_meter_sub->hour, 0);
  /* 时间-分钟 */
  lv_subject_init_int(&speed_meter_sub->min, 0);

}
void ui_init(void)
{
  // 整个屏幕的初始化
  speed_meter_screen_init();

  // 设置项目的主题
  speed_meter_set_theme(SPEED_METER_THEME_COLOR, false);

  // 初始化所有的主题
  speed_meter_sub_init();

  // 翻译初始化
  speed_meter_translation_init();

  // 顶部导航栏初始化
  speed_meter_nav_bar_init();

  // 底部tabview初始化
  speed_meter_tabview_init();
}
