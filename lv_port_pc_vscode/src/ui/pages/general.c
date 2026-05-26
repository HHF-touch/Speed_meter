#include "general.h"

extern Speed_Meter_Sub_t *speed_meter_sub;

void speed_meter_set_boder_style(lv_obj_t *target)
{
  // 设置边框及边框的颜色
  lv_obj_set_style_border_width(target, 5, LV_PART_MAIN);
  lv_obj_set_style_border_color(target, SPEED_METER_THEME_COLOR, LV_PART_MAIN);
}

void speed_meter_general_init(lv_obj_t *parent)
{
  clear_default_style(parent);
  // 创建general的包裹器
  lv_obj_t *general_wrapper = lv_obj_create(parent);

  // 设置大小
  lv_obj_set_size(general_wrapper, lv_pct(100), lv_pct(100));

  // 设置general_wrapper为网格布局
  lv_obj_set_layout(general_wrapper, LV_LAYOUT_GRID);
  // 设置并添加网格的描述
  static int32_t col_dsc[] = {LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
  static int32_t row_dsc[] = {LV_GRID_FR(2), LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
  lv_obj_set_grid_dsc_array(general_wrapper, col_dsc, row_dsc);

  // 速度区域
  lv_obj_t *speed_container = lv_obj_create(general_wrapper);

  speed_meter_set_boder_style(speed_container);

  lv_obj_t *speed_label = lv_label_create(speed_container);
  // 绑定主题
  lv_label_bind_text(speed_label, &speed_meter_sub->speed, "%.1f km/h");
  // 添加至网格
  lv_obj_set_grid_cell(speed_container, LV_GRID_ALIGN_STRETCH, 0, 2, LV_GRID_ALIGN_STRETCH, 0, 1);
  lv_obj_align(speed_label, LV_ALIGN_CENTER, 0, 0);
  // 设置字体大小
  lv_obj_set_style_text_font(speed_label, &lv_font_montserrat_28, LV_PART_MAIN);


  // 距离
  lv_obj_t *distance_container = lv_obj_create(general_wrapper);
  speed_meter_set_boder_style(distance_container);
  lv_obj_t *distance_label = lv_label_create(distance_container);
  // 绑定主题
  lv_label_bind_text(distance_label, &speed_meter_sub->distance, "%.2f km");
  // 添加至网格
  lv_obj_set_grid_cell(distance_container, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 1, 1);
  lv_obj_align(distance_label, LV_ALIGN_CENTER, 0, 0);


  // 坡度
  lv_obj_t *slope_container = lv_obj_create(general_wrapper);
  speed_meter_set_boder_style(slope_container);
  lv_obj_t *slope_label = lv_label_create(slope_container);
  // 绑定主题
  lv_label_bind_text(slope_label, &speed_meter_sub->slope, "%.1f %%");
  // 添加至网格
  lv_obj_set_grid_cell(slope_container, LV_GRID_ALIGN_STRETCH, 1, 1, LV_GRID_ALIGN_STRETCH, 1, 1);
  lv_obj_align(slope_label, LV_ALIGN_CENTER, 0, 0);


  // 经纬度
  lv_obj_t *lon_lat_container = lv_obj_create(general_wrapper);
  speed_meter_set_boder_style(lon_lat_container);
  lv_obj_set_style_pad_all(lon_lat_container, 0, LV_PART_MAIN);

  // 设置flex布局
  lv_obj_set_layout(lon_lat_container, LV_LAYOUT_FLEX);
  lv_obj_set_flex_flow(lon_lat_container, LV_FLEX_FLOW_COLUMN);
  lv_obj_set_flex_align(lon_lat_container, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

  lv_obj_t *lon_label = lv_label_create(lon_lat_container);
  lv_obj_t *lat_label = lv_label_create(lon_lat_container);
  // 绑定主题
  lv_label_bind_text(lon_label, &speed_meter_sub->lon, "%.5f");
  lv_label_bind_text(lat_label, &speed_meter_sub->lat, "%.5f");
  // 添加至网格
  lv_obj_set_grid_cell(lon_lat_container, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 2, 1);


  // 时间
  lv_obj_t *timer_container = lv_obj_create(general_wrapper);
  speed_meter_set_boder_style(timer_container);

  // 设置flex布局
  lv_obj_set_layout(timer_container, LV_LAYOUT_FLEX);
  lv_obj_set_flex_align(timer_container, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

  lv_obj_t *hour_label = lv_label_create(timer_container);
  lv_obj_t *min_label = lv_label_create(timer_container);
  // 绑定主题
  lv_label_bind_text(hour_label, &speed_meter_sub->lon, "%d  :");
  lv_label_bind_text(min_label, &speed_meter_sub->lat, "%d");
  // 添加至网格
  lv_obj_set_grid_cell(timer_container, LV_GRID_ALIGN_STRETCH, 1, 1, LV_GRID_ALIGN_STRETCH, 2, 1);
}
