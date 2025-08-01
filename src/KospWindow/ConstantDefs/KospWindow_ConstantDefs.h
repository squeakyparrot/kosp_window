/**
 * @file KospWindow_ConstantDefs.h
 *
 * @brief
 *
 * @date 2025-07-25
 *
 * @copyright KOSP Project 2025
 */

#ifndef H_KOSPWINDOW_CONSTANTDEFS_H_
#define H_KOSPWINDOW_CONSTANTDEFS_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Acfutils includes */
#include "acfutils/math.h"

/* Custom includes */
#include "KospWindow/ConstantDefs/KospWindow_GraphicsConstantDefs.h"

#define KOSPWINDOW_ASSETS_DIR "assets"
#define KOSPWINDOW_FONTS_DIR "fonts"
#define KOSPWINDOW_FONTS_MONTSERATT_LIGHT_NAME "Montserrat-Light.ttf"
#define KOSPWINDOW_FONTS_MONTSERATT_MEDIUM_NAME "Montserrat-Medium.ttf"
#define KOSPWINDOW_FONTS_MONTSERATT_REGULAR_NAME "Montserrat-Regular.ttf"
#define KOSPWINDOW_FONTS_ROBOTO_REGULAR_NAME "Roboto_Condensed-Regular.ttf"
#define KOSPWINDOW_FONTS_ROBOTO_SEMIBOLD_NAME "Roboto_Condensed-SemiBold.ttf"

#define KOSPWINDOW_CONFIG_DIR "config"
#define KOSPWINDOW_USER_CONFIG_FILE_NAME "userconfig.json"
#define KOSPWINDOW_CHANGELOG_FILE_NAME "changelog.json"

#define KOSPWINDOW_RENDER_FPS (30)
#define KOSPWINDOW_CLICKSPOT_MARGIN (30)
#define KOSPWINDOW_WINDOW_WIDTH (400)
#define KOSPWINDOW_WINDOW_HEIGHT (800)

#define KOSPWINDOW_MAX_NUM_VOLUME_DRFS (30)

#define KOSPWINDOW_NUM_PAGES (4)
#define KOSPWINDOW_PAGE_1 (0)
#define KOSPWINDOW_PAGE_2 (1)
#define KOSPWINDOW_PAGE_3 (2)
#define KOSPWINDOW_PAGE_4 (3)

#ifdef __cplusplus
}
#endif
#endif /* H_KOSPWINDOW_CONSTANTDEFS_H_ */
