#include "my_component.h"

struct my_component
{
  int width;
  int height;
  int border_width;
  lv_color_t bg_color;
  lv_obj_t *handle;
};

My_Component_t *My_Component_Create(lv_obj_t *parent)
{
  My_Component_t *cmp = lv_malloc_zeroed(sizeof(My_Component_t));
  cmp->width = 200;
  cmp->height = 200;
  cmp->border_width = 5;
  cmp->bg_color = lv_color_hex(0x00ff00);

  lv_obj_t *child = lv_obj_create(parent);
  lv_obj_set_size(child, cmp->width, cmp->height);
  lv_obj_set_style_border_width(child, cmp->border_width, LV_PART_MAIN);
  lv_obj_set_style_bg_color(child, cmp->bg_color, LV_PART_MAIN);

  cmp->handle = child;

  return cmp;
}



void My_Component_set_size(My_Component_t *cmp, int w, int h)
{
  cmp->width = w;
  cmp->height = h;
  lv_obj_set_size(cmp->handle, cmp->width, cmp->height);

}


int32_t My_Component_get_width(My_Component_t *cmp)
{
  return cmp->width;
}
