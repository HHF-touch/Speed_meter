#pragma once

#include "lvgl.h"

typedef struct
{
  /* GPS数量 */
  lv_subject_t gps;
  /* 运动状态 */
  lv_subject_t running_state;
  /* 电池电量 */
  lv_subject_t battery_level;
  /* 速度 */
  lv_subject_t speed;
  /* 距离 */
  lv_subject_t distance;
  /*坡度*/
  lv_subject_t slope;
  /*经度*/
  lv_subject_t lon;
  /*纬度*/
  lv_subject_t lat;
  /*时间-小时*/
  lv_subject_t hour;
  /*时间-分钟*/
  lv_subject_t min;

} Speed_Meter_Sub_t;

// 地图相关的参数
typedef struct 
{
  // 地图的缩放等级
  lv_subject_t zoom_level;
  // 旧的缩放等级
  int32_t old_zoom_level;

  // 像素点坐标
  float pixel_x;
  float pixel_y;

  // 瓦片坐标
  int tile_x;
  int tile_y;

  // 地图可视化宽高
  int32_t map_wrapper_width;
  int32_t map_wrapper_height;

  // 网格地图偏移量
  int32_t scroll_x;
  int32_t scroll_y;

}Map_Attract_t;


void clear_default_style(lv_obj_t *target);

// 项目主题颜色
#define SPEED_METER_THEME_COLOR lv_color_hex(0x00cc99)

void speed_meter_set_theme(lv_color_t theme_color, bool is_dark);
