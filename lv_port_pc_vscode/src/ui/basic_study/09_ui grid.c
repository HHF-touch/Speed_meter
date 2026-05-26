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
  // lv_obj_set_style_pad_row(obj, 0, LV_PART_MAIN);
  // lv_obj_set_style_pad_column(obj, 0, LV_PART_MAIN);
  // 设置圆角
  lv_obj_set_style_radius(obj, 0, LV_PART_MAIN);
  // 设置边框
  lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN);

  // 大小
  lv_obj_set_size(obj, 400, 400);

  // 设置grid布局
  lv_obj_set_layout(obj, LV_LAYOUT_GRID);

  static int32_t column_dsc[] = {100, 100, 100, LV_GRID_TEMPLATE_LAST};
  static int32_t row_dsc[] = {100, 100, 100, LV_GRID_TEMPLATE_LAST};

  // 添加网格的行列的描述
  lv_obj_set_grid_dsc_array(obj, column_dsc, row_dsc);

  // 给每个网格添加元素
  lv_obj_t *label;

  uint8_t i;
  for (i = 0; i < 9; i++)
  {
    uint8_t col = i % 3;
    uint8_t row = i / 3;

    lv_obj_t *btn = lv_button_create(obj);

    lv_obj_set_grid_cell(btn, LV_GRID_ALIGN_STRETCH, col, 1,
                         LV_GRID_ALIGN_STRETCH, row, 1);

    if (i == 6)
    {
      lv_obj_set_grid_cell(btn, LV_GRID_ALIGN_STRETCH, col, 1,
                           LV_GRID_ALIGN_STRETCH, row - 1, 2);
    }

    if (i == 8)
    {
      lv_obj_set_grid_cell(btn, LV_GRID_ALIGN_STRETCH, col -1, 2,
                           LV_GRID_ALIGN_STRETCH, row, 1);
    }

    label = lv_label_create(btn);
    lv_label_set_text_fmt(label, "c%d, r%d", col, row);
    // lv_label_set_text(label, "xxxxx");
    lv_obj_center(label);
  }
}
