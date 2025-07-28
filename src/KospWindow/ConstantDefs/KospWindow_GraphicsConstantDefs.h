/**
 * @file KospWindow_GraphicsConstantDefs.h
 *
 * @brief
 *
 * @date 2025-07-27
 *
 * @copyright KOSP Project 2025
 */

#ifndef H_KOSPWINDOW_GRAPHICSCONSTANTDEFS_H_
#define H_KOSPWINDOW_GRAPHICSCONSTANTDEFS_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Generic colurs / colours of the x plane window bezel */
#define CAIRO_COLOUR_XPLANE_BLACK (0.0), (0.0), (0.0)
#define CAIRO_COLOUR_XPLANE_WHITE (1.0), (1.0), (1.0)
#define CAIRO_COLOUR_XPLANE_MENU_FRAME (0.282), (0.314), (0.342)

/* Colours of the menu and backgrounds. */
#define CAIRO_COLOUR_MENU_MARGIN (0.126), (0.150), (0.165)
#define CAIRO_COLOUR_MENU_BACKGROUND_SHADOW (0.029), (0.033), (0.037)
#define CAIRO_COLOUR_MENU_BACKGROUND (0.058), (0.067), (0.075)
#define CAIRO_COLOUR_MENU_BACKGROUND_GLOW (0.08), (0.102), (0.110)
#define CAIRO_COLOUR_MENU_BUTTON_BACKGROUND (0.134), (0.157), (0.173)
#define CAIRO_COLOUR_MENU_BUTTON_BACKGROUND_GLOW (0.181), (0.204), (0.224)

/* Custom colour for slider bars. */
#define CAIRO_COLOUR_SLIDER_BAR_GREY (0.787), (0.796), (0.804)

/* Properties of the vertical placement of the title bar */
#define KOSPWINDOW_TITLE_BIG_TEXT_Y (80)
#define KOSPWINDOW_TITLE_SMALL_TEXT_Y (105)

/* Properties of the vertical placement of the menu bar */
#define KOSPWINDOW_MENU_BAR_TOP_EDGE_Y (135)
#define KOSPWINDOW_MENU_BAR_TOP_EDGE_Y_GAPPED (138)
#define KOSPWINDOW_MENU_BAR_BOTTOM_EDGE_Y (190)

/* Properties of the background rounded rectangles */
#define KOSPWINDOW_MENU_ROUNDED_CORNER_OUTER_RADIUS (10)
#define KOSPWINDOW_MENU_ROUNDED_CORNER_INNER_RADIUS (3)
#define KOSPWINDOW_MENU_MARGIN_WIDTH (3)

/* Properties of a slider block */
#define KOSPWINDOW_SLIDER_START_X (50)
#define KOSPWINDOW_SLIDER_END_X (350)
#define KOSPWINDOW_SLIDER_START_Y (250)
#define KOSPWINDOW_SLIDER_END_Y (650)
#define KOSPWINDOW_SLIDER_TEXT_Y_OFFSET (0)
#define KOSPWINDOW_SLIDER_BAR_Y_OFFSET (25)
#define KOSPWINDOW_SLIDER_BAR_THICKNESS (4)

/* Vertical distance between each slider block */
#define KOSPWINDOW_SLIDER_Y_SPACING (85)

/* Anything more than this will be assumed to be invisible and therefore
 * clipped. */
#define KOSPWINDOW_SLIDER_MAX_NUM_DISPLAYABLE_SLIDERS (5)

/* How many empty sliders to show at the bottom of the page*/
#define KOSPWINDOW_SLIDER_BOTTOM_BUFFER_SPACE (1)

/* Speed of the smooth animation when you scroll down */
#define KOSPWINDOW_SLIDER_SCROLL_ANIM_SPEED (10)

#ifdef __cplusplus
}
#endif
#endif /* H_KOSPWINDOW_GRAPHICSCONSTANTDEFS_H_ */
