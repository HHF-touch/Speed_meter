#include "ui.h"

typedef enum
{
  UI_COLOR_RED = 0xFF0000,
  UI_COLOR_GREEN = 0x00FF00,
  UI_COLOR_BLUE = 0x0000FF,
} UI_Color_t;

static UI_Color_t ui_colors[] = {UI_COLOR_BLUE, UI_COLOR_RED, UI_COLOR_GREEN, UI_COLOR_BLUE, UI_COLOR_RED};

static uint8_t center_index = 2;
bool is_code_scroll = false;

lv_obj_t *obj;

void scroll_event_cb(lv_event_t *e)
{
  if (is_code_scroll)
  {
    is_code_scroll = false;
    return;
  }

  lv_obj_t *target = lv_event_get_target(e);
  int32_t scroll_x = lv_obj_get_scroll_x(target);
  lv_log("scroll_x: %d \n", scroll_x);

  // 判断向左滚动
  if (scroll_x > 300)
  {
    if (center_index == 4)
    {
      center_index = 1;
    }
    center_index++;
  }

  // 判断向右滚动
  if (scroll_x < 300)
  {
    if (center_index == 0)
    {
      center_index = 3;
    }

    center_index--;
  }

  // 重铺背景颜色
  for (size_t i = 0; i < 3; i++)
  {
    lv_obj_t *child = lv_obj_get_child(obj, i);
    lv_obj_set_style_bg_color(child, lv_color_hex(ui_colors[center_index + i - 1]), LV_PART_MAIN);
  }

  // 移动元素至原有的显示效果
  if (scroll_x > 300)
  {
    is_code_scroll = true;
    lv_obj_scroll_to_x(obj, scroll_x - 300, LV_ANIM_OFF);
  }
  if (scroll_x < 300)
  {
    is_code_scroll = true;
    lv_obj_scroll_to_x(obj, scroll_x + 300, LV_ANIM_OFF);
  }
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
  // 创建元素对象
  obj = lv_obj_create(screen);
  // 清除默认样式
  clear_default_style(obj);
  // 大小
  lv_obj_set_size(obj, 300, 300);
  // 设置网格布局
  lv_obj_set_layout(obj, LV_LAYOUT_GRID);
  static int32_t col[] = {300, 300, 300, LV_GRID_TEMPLATE_LAST};
  static int32_t row[] = {300, LV_GRID_TEMPLATE_LAST};
  lv_obj_set_grid_dsc_array(obj, col, row);

  lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
  lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLL_MOMENTUM);

  // 为每一个网格cell添加成员
  for (size_t i = 0; i < 3; i++)
  {
    lv_obj_t *child = lv_obj_create(obj);
    // 清除默认样式
    clear_default_style(child);
    // 将child添加至cell中
    lv_obj_set_grid_cell(child, LV_GRID_ALIGN_STRETCH, i, 1, LV_GRID_ALIGN_STRETCH, 0, 1);

    // 分别设置背景颜色
    lv_obj_set_style_bg_color(child, lv_color_hex(ui_colors[center_index + i - 1]), LV_PART_MAIN);
  }

  // 移动元素至中心位置
  lv_obj_scroll_to_x(obj, 300, LV_ANIM_OFF);
  // 绑定滚动事件
  lv_obj_add_event_cb(obj, scroll_event_cb, LV_EVENT_SCROLL_END, NULL);
}
