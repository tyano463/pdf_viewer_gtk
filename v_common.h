#ifndef __V_COMMON_H__
#define __V_COMMON_H__

#include <string.h>
#include <gtk/gtk.h>

#define min(a, b) (((b) < (a)) ? (b) : (a))
#define max(a, b) (((b) > (a)) ? (b) : (a))

/**
 * There is no button definition in gtk.
 *
 * The following is the gtk explanation.
 *
 * /usr/include/gtk-3.0/gdk/gdkevents.h:706L
 *
 * @button: the button which was pressed or released, numbered from 1 to 5.
 *   Normally button 1 is the left mouse button, 2 is the middle button,
 *   and 3 is the right button. On 2-button mice, the middle button can
 *   often be simulated by pressing both mouse buttons together.
 *
 */
#define MOUSE_BUTTON_LEFT 1
#define MOUSE_BUTTON_MIDDLE 2
#define MOUSE_BUTTON_RIGHT 3


#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define d(x, ...)                                                                      \
    do                                                                                 \
    {                                                                                  \
        g_print("%s(%d) %s " x "\n", __FILENAME__, __LINE__, __func__, ##__VA_ARGS__); \
    } while (0)

#define ERR_RETn(c)            \
    do                         \
    {                          \
        if (c)                 \
            goto error_return; \
    } while (0)

typedef enum
{
    ST_SUCCESS,
    ST_PDF_OPEN_FAILED,
    ST_PDF_CONTEXT_CREAT_FAILED,
    ST_PDF_DOCUMENT_OPEN_FAILED,
    ST_MENU_OPEN_FAIL,
} v_status_t;


#endif