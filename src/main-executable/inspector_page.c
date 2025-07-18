#include <gtk/gtk.h>

#include "../api-impl-jni/widgets/WrapperWidget.h"

#include "inspector_page.h"

G_DEFINE_FINAL_TYPE(ATLInspectorPage, atl_inspector_page, GTK_TYPE_BOX)

typedef enum { PROP_TITLE = 1, N_PROPERTIES } ATLInspectorPageProperty;

static GParamSpec *props[N_PROPERTIES];

static void atl_inspector_get_property(GObject *object, guint property_id, GValue *value, GParamSpec *pspec)
{
	switch ((ATLInspectorPageProperty)property_id)
	{
		case PROP_TITLE:
		{
			g_value_set_string(value, "ATL");
			break;
		}

		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
			break;
	}
}

/* HACK: private - no guarantee that the inspector window will always have the object tree pointer at this offset (or that the object tree widget will continue to be a thing) */
typedef struct {
	GtkWindow parent;

	GtkWidget *top_stack;
	GtkWidget *object_stack;
	GtkWidget *button_stack;
	GtkWidget *object_tree;
	/* ... */
} GtkInspectorWindow;

typedef bool (*widget_callback)(GtkWidget *widget, ATLInspectorPage *atl_inspector_page, const char *id_text);

static bool _traverse_widget_hierarchy(GtkWidget *widget, widget_callback func, ATLInspectorPage *atl_inspector_page, const char *id_text)
{
	func(widget, atl_inspector_page, id_text);

	GtkWidget *child = gtk_widget_get_first_child(widget);
	while (child)
	{
		if(_traverse_widget_hierarchy(child, func, atl_inspector_page, id_text))
			return true;
		child = gtk_widget_get_next_sibling(child);
	}

	return false;
}

void for_each_rooted_widget(GtkApplication *application, widget_callback func, ATLInspectorPage *atl_inspector_page, const char *id_text)
{
	GList *windows_head = gtk_application_get_windows(application);

	for (GList *l = windows_head; l; l = l->next)
	{
		GtkWindow *window = GTK_WINDOW(l->data);

		if(_traverse_widget_hierarchy(GTK_WIDGET(window), func, atl_inspector_page, id_text))
			break;
	}
}

void show_details(ATLInspectorPage *atl_inspector_page, GObject *gobject)
{
	GtkInspectorWindow *inspector_window = (GtkInspectorWindow *)gtk_widget_get_root(GTK_WIDGET(atl_inspector_page));

	GObject *object_tree = G_OBJECT(inspector_window->object_tree);
	/* HACK: private - no guarantee that the object tree will always have these signals (or that the object tree widget will continue to be a thing) */
	g_signal_emit_by_name(object_tree, "object-selected", gobject);
	g_signal_emit_by_name(object_tree, "object-activated", gobject);
}

gboolean show_gobject_details(ATLInspectorPage *atl_inspector_page, GtkEntry *entry)
{
	const char *gobject_ptr_text = gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(entry)));
	uintptr_t gobject_ptr = (uintptr_t)strtoul(gobject_ptr_text, NULL, 16);

	show_details(atl_inspector_page, G_OBJECT(gobject_ptr));

	return false;
}

bool show_details_if_id(GtkWidget *widget, ATLInspectorPage *atl_inspector_page, const char *id_text) {
	if(g_type_is_a(G_OBJECT_TYPE(widget), wrapper_widget_get_type())) {
		char *id = NULL;
		g_object_get(widget, "ATL-id-name", &id, NULL);
		if(id && !strcmp(id, id_text)) {
			show_details(atl_inspector_page, G_OBJECT(widget));
			return true;
		}
	}

	return false;
}

extern GtkWindow *window;
gboolean show_id_details(ATLInspectorPage *atl_inspector_page, GtkEntry *entry)
{
	const char *id_text = gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(entry)));

	GtkApplication *application = gtk_window_get_application(window);
	for_each_rooted_widget(application, show_details_if_id, atl_inspector_page, id_text);

	return false;
}

static void atl_inspector_page_init (ATLInspectorPage *atl_inspector_page)
{
	gtk_orientable_set_orientation(GTK_ORIENTABLE(atl_inspector_page), GTK_ORIENTATION_VERTICAL);

	GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	GtkWidget *entry = gtk_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "GObject *");
	GtkWidget *button = gtk_button_new_with_label("show details");
	g_signal_connect(button, "clicked", G_CALLBACK(show_gobject_details), entry);

	gtk_box_append(GTK_BOX(box), entry);
	gtk_box_append(GTK_BOX(box), button);

	gtk_box_append(GTK_BOX(atl_inspector_page), box);

	GtkWidget *id_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	GtkWidget *id_entry = gtk_entry_new();
	gtk_entry_set_placeholder_text(GTK_ENTRY(id_entry), "android:id");
	GtkWidget *id_button = gtk_button_new_with_label("show details");
	g_signal_connect(id_button, "clicked", G_CALLBACK(show_id_details), id_entry);

	gtk_box_append(GTK_BOX(id_box), id_entry);
	gtk_box_append(GTK_BOX(id_box), id_button);

	gtk_box_append(GTK_BOX(atl_inspector_page), box);
	gtk_box_append(GTK_BOX(atl_inspector_page), id_box);
}

static void atl_inspector_page_class_init(ATLInspectorPageClass *class)
{
	GObjectClass *object_class = G_OBJECT_CLASS(class);

	object_class->get_property = atl_inspector_get_property;

	props[PROP_TITLE] = g_param_spec_string("title", NULL, NULL, "", G_PARAM_READABLE | G_PARAM_STATIC_STRINGS);

	g_object_class_install_properties(object_class, N_PROPERTIES, props);
}
