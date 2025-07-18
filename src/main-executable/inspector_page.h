#ifndef INSPECTOR_PAGE_H
#define INSPECTOR_PAGE_H

#include <gtk/gtk.h>

struct _ATLInspectorPage
{
	GtkBox parent_instance;
};

struct _ATLInspectorPageClass
{
	GtkWidgetClass parent_class;
};

#define ATL_INSPECTOR_PAGE_TYPE (atl_inspector_page_get_type())

G_DECLARE_FINAL_TYPE (ATLInspectorPage, atl_inspector_page, ATL, INSPECTOR_PAGE, GtkBox)

#endif
