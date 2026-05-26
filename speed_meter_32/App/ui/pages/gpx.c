#include "gpx.h"

extern Speed_Meter_Sub_t *speed_meter_sub;

static Map_Attract_t *map_attr;

void speed_meter_map_updata(lv_obj_t *map_grid, bool have_to);

// 瓦片地图的路径
static char img_path[128] = {0};

// 标识是否是代码执行的滚动
static bool is_code_scroll = false;


// 回归原点按钮的回调
static void back_to_origin_cb(lv_event_t *e)
{
    lv_obj_t *map_grid = lv_event_get_user_data(e);

    map_attr->old_zoom_level = 14;
    lv_subject_set_int(&map_attr->zoom_level, 14);

    // 重新用经纬度计算像素坐标
    latlng_to_pixel_float(lv_subject_get_float(&speed_meter_sub->lon), lv_subject_get_float(&speed_meter_sub->lat), lv_subject_get_int(&map_attr->zoom_level), &map_attr->pixel_x, &map_attr->pixel_y);

    speed_meter_map_updata(map_grid, true);
}

// 地图放大缩小滑块的回调
static void map_zoom_changed_cb(lv_event_t *e)
{
    lv_obj_t *map_grid = lv_event_get_user_data(e);

    int32_t new_zoom_level = lv_subject_get_int(&map_attr->zoom_level);

    pixel_zoom_convert_float(map_attr->pixel_x, map_attr->pixel_y, map_attr->old_zoom_level, new_zoom_level, &map_attr->pixel_x, &map_attr->pixel_y);
    map_attr->old_zoom_level = new_zoom_level;

    speed_meter_map_updata(map_grid, false);
}

// 速度和距离的初始化
void speed_dis_init(lv_obj_t *speed_dis_warp)
{
    clear_default_style(speed_dis_warp);

    // 设置flex布局
    lv_obj_set_layout(speed_dis_warp, LV_LAYOUT_FLEX);
    lv_obj_set_flex_align(speed_dis_warp, LV_FLEX_ALIGN_SPACE_AROUND, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_size(speed_dis_warp, lv_pct(100), lv_pct(15));
    lv_obj_set_style_bg_color(speed_dis_warp, SPEED_METER_THEME_COLOR, LV_PART_MAIN);

    // 创建两个label
    lv_obj_t *speed_label = lv_label_create(speed_dis_warp);
    lv_obj_t *dis_label = lv_label_create(speed_dis_warp);

    // 绑定主题
    lv_label_bind_text(speed_label, &speed_meter_sub->speed, "%0.1f km/h");
    lv_label_bind_text(dis_label, &speed_meter_sub->distance, "%0.2f km");
}

// 地图的铺设
void speed_meter_map_updata(lv_obj_t *map_grid, bool have_to)
{
    // // 测试瓦片坐标计算
    // float pixel_x, pixel_y;
    // latlng_to_pixel_float(lv_subject_get_float(&speed_meter_sub->lon), lv_subject_get_float(&speed_meter_sub->lat), lv_subject_get_int(&map_attr->zoom_level), &pixel_x, &pixel_y);

    // int tile_x, tile_y;
    // pixel_to_tile_float(pixel_x, pixel_y, &tile_x, &tile_y);
    // lv_log("title_x:%d,title_y:%d", tile_x, tile_y);

    // 根据像素点坐标计算瓦片坐标
    int new_tile_x, new_tile_y;
    pixel_to_tile_float(map_attr->pixel_x, map_attr->pixel_y, &new_tile_x, &new_tile_y);


    // 判断瓦片坐标是否发生变化
    if(new_tile_x != map_attr->tile_x || new_tile_y != map_attr->tile_y || have_to)
    {
        // 将计算的瓦片坐标保存起来
        map_attr->tile_x = new_tile_x;
        map_attr->tile_y = new_tile_y;

        // 给每一个网格的cell添加瓦片地图
        for (size_t i = 0; i < 9; i++)
        {
            lv_obj_t *tile_map = lv_img_create(map_grid);
            sprintf(img_path, "C:/map/%d/%d/%d/tile.bmp", lv_subject_get_int(&map_attr->zoom_level), map_attr->tile_x + i % 3 - 1, map_attr->tile_y + i / 3 - 1);

            lv_img_set_src(tile_map, img_path);
            lv_obj_set_grid_cell(tile_map, LV_GRID_ALIGN_STRETCH, i % 3, 1, LV_GRID_ALIGN_STRETCH, i / 3, 1);
        }
        
        lv_obj_update_layout(map_grid);
        // 获取地图的可视区域的宽高
        map_attr->map_wrapper_width = lv_obj_get_width(map_grid);
        map_attr->map_wrapper_height = lv_obj_get_height(map_grid);
        // lv_log("map_wrapper_width: %d, map_wrapper_height: %d \n", map_attr->map_wrapper_width, map_attr->map_wrapper_height);

        map_attr->scroll_x = 256 + (uint32_t)map_attr->pixel_x % 256 - map_attr->map_wrapper_width / 2;
        map_attr->scroll_y = 256 + (uint32_t)map_attr->pixel_y % 256 - map_attr->map_wrapper_height / 2;

        // 移动经纬度定位的瓦片地图到中心
        is_code_scroll = true;
        lv_obj_scroll_to_y(map_grid, map_attr->scroll_y, LV_ANIM_OFF);
        lv_obj_scroll_to_x(map_grid, map_attr->scroll_x, LV_ANIM_OFF);
    }

}

// 地图的滚动回调
static void speed_meter_map_scroll_event_cb(lv_event_t *e)
{
    if(is_code_scroll)
    {
        is_code_scroll = false;
        return;
    }

    lv_obj_t *map_grid = lv_event_get_target(e);
    // 获取旧的scroll偏移量
    int32_t old_scroll_x = map_attr->scroll_x;
    int32_t old_scroll_y = map_attr->scroll_y;

    // 获取新的scroll偏移量
    int32_t new_scroll_x = lv_obj_get_scroll_x(map_grid);
    int32_t new_scroll_y = lv_obj_get_scroll_y(map_grid);

    // 计算偏移量
    map_attr->pixel_x += new_scroll_x - old_scroll_x;
    map_attr->pixel_y += new_scroll_y - old_scroll_y;

    // 更新地图
    speed_meter_map_updata(map_grid, true);

}

// 地图区域初始化
void speed_meter_map_init(lv_obj_t *map_warp)
{
    // 分配内存大小
    map_attr = lv_malloc_zeroed(sizeof(Map_Attract_t));
    // 初始化主题
    lv_subject_init_int(&map_attr->zoom_level, 14);
    // 保存到旧的里边
    map_attr->old_zoom_level = lv_subject_get_int(&map_attr->zoom_level);

    // 创建地图网格
    lv_obj_t *map_grid = lv_obj_create(map_warp);
    clear_default_style(map_grid);
    lv_obj_set_scrollbar_mode(map_grid, LV_SCROLLBAR_MODE_OFF);
    lv_obj_remove_flag(map_grid, LV_OBJ_FLAG_SCROLL_MOMENTUM);
    lv_obj_remove_flag(map_grid, LV_OBJ_FLAG_SCROLL_ELASTIC);

    lv_obj_set_size(map_grid, lv_pct(100), lv_pct(100));


    // 设置网格布局
    lv_obj_set_layout(map_grid, LV_LAYOUT_GRID);

    // 描述网格
    static uint32_t col_dsc[] = {256, 256, 256, LV_GRID_TEMPLATE_LAST};
    static uint32_t row_dsc[] = {256, 256, 256, LV_GRID_TEMPLATE_LAST};
    lv_obj_set_grid_dsc_array(map_grid, (int32_t *)col_dsc, (int32_t *)row_dsc);

    latlng_to_pixel_float(lv_subject_get_float(&speed_meter_sub->lon), lv_subject_get_float(&speed_meter_sub->lat), lv_subject_get_int(&map_attr->zoom_level), &map_attr->pixel_x, &map_attr->pixel_y);
    // 铺设地图
    speed_meter_map_updata(map_grid, false);

    // 给地图网格绑定滚动事件
    lv_obj_add_event_cb(map_grid, speed_meter_map_scroll_event_cb, LV_EVENT_SCROLL_END, NULL);

    // 回到原点区域
    lv_obj_t *back_up_pointer = lv_obj_create(map_warp);
    clear_default_style(back_up_pointer);
    lv_obj_set_size(back_up_pointer, 26, 26);
    lv_obj_set_style_bg_color(back_up_pointer, SPEED_METER_THEME_COLOR, LV_PART_MAIN);
    lv_obj_set_style_radius(back_up_pointer, lv_pct(50), LV_PART_MAIN);
    lv_obj_align(back_up_pointer, LV_ALIGN_BOTTOM_LEFT, 20, -20);

    // 创建小水滴的label
    lv_obj_t *back_up_label = lv_label_create(back_up_pointer);
    lv_label_set_text(back_up_label, LV_SYMBOL_TINT);
    lv_obj_center(back_up_label);
    lv_obj_set_style_text_color(back_up_label, lv_color_hex(0xffffff), LV_PART_MAIN);

    // 绑定点击事件
    lv_obj_add_event_cb(back_up_pointer, back_to_origin_cb, LV_EVENT_CLICKED, map_grid);

    // 滑块区域
    lv_obj_t *slider = lv_slider_create(map_warp);
    lv_obj_set_size(slider, 10, lv_pct(80));
    lv_slider_set_range(slider, 4, 14);
    lv_obj_align(slider, LV_ALIGN_RIGHT_MID, -15, 0);

    // 绑定主题
    lv_slider_bind_value(slider, &map_attr->zoom_level);

    // 绑定缩放事件主题
    lv_obj_add_event_cb(slider, map_zoom_changed_cb, LV_EVENT_VALUE_CHANGED, map_grid);

    // 标记一个中心原点
    lv_obj_t *center_point = lv_obj_create(map_warp);
    lv_obj_set_size(center_point, 10, 10);
    clear_default_style(center_point);
    lv_obj_set_style_bg_color(center_point, lv_color_hex(0xff0000), LV_PART_MAIN);
    lv_obj_set_style_radius(center_point, lv_pct(50), LV_PART_MAIN);
    lv_obj_align(center_point, LV_ALIGN_CENTER, 0, 0);

}

void speed_meter_gpx_init(lv_obj_t *parent)
{
    clear_default_style(parent);
    lv_obj_set_layout(parent, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(parent, LV_FLEX_FLOW_COLUMN);

    // 创建地图网格
    lv_obj_t *map_warp = lv_obj_create(parent);
    clear_default_style(map_warp);
    lv_obj_set_size(map_warp, lv_pct(100), lv_pct(85));

    // 地图区域初始化
    speed_meter_map_init(map_warp);


    // 速度和距离的区域
    lv_obj_t *speed_dis_warp = lv_obj_create(parent);
    speed_dis_init(speed_dis_warp);
}
