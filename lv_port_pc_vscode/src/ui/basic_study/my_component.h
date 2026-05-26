#pragma once

#include "lvgl.h"

// 透明指针
// typedef struct
// {
//   int width;
//   int height;
// } My_Component_t;

// My_Component_t my_component;

// 不透明指针
typedef struct my_component My_Component_t;

My_Component_t *My_Component_Create(lv_obj_t *parent);

void My_Component_set_size(My_Component_t *cmp, int w, int h);
int32_t My_Component_get_width(My_Component_t *cmp);
