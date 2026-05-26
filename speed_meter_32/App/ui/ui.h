#pragma once

#include "lvgl.h"
#include "gpx.h"
#include "general.h"
#include "setting.h"
#include "speed_meter_translation.h"

void ui_init(void);

void ui_update_battery(bool is_charging, uint8_t vol_level);
