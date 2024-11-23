#include <gtk/gtk.h>

#include "../defines.h"
#include "../util.h"

#include "WrapperWidget.h"
#include "AdapterView.h"

#include "../generated_headers/android_widget_Spinner.h"

static void bind_listitem_cb(GtkListItemFactory *factory, GtkListItem *list_item)
{
	JNIEnv *env = get_jni_env();

	guint index = gtk_list_item_get_position(list_item);
	WrapperWidget *wrapper = WRAPPER_WIDGET(gtk_list_item_get_child(list_item));
	RangeListModel *model = RANGE_LIST_ITEM(gtk_list_item_get_item(list_item))->model;
	int n_items = g_list_model_get_n_items(G_LIST_MODEL(model));
	if (index >= n_items) {
		printf("invalid index: %d >= %d\n", index, n_items);
		exit(0);
	}
	jmethodID getView = _METHOD(_CLASS(model->adapter), "getDropDownView", "(ILandroid/view/View;Landroid/view/ViewGroup;)Landroid/view/View;");
	jobject view = (*env)->CallObjectMethod(env, model->adapter, getView, index, wrapper ? wrapper->jobj : NULL, model->jobject);
	view = _REF(view);
	GtkWidget *child = gtk_widget_get_parent(GTK_WIDGET(_PTR(_GET_LONG_FIELD(view, "widget"))));
	gtk_list_item_set_child(list_item, child);
}

JNIEXPORT jlong JNICALL Java_android_widget_Spinner_native_1constructor(JNIEnv *env, jobject this, jobject context, jobject attrs)
{
	GtkWidget *wrapper = g_object_ref(wrapper_widget_new());
	GtkListItemFactory *factory = gtk_signal_list_item_factory_new();
	g_signal_connect(factory, "bind", G_CALLBACK(bind_listitem_cb), NULL);
	RangeListModel *model = g_object_new(range_list_model_get_type(), NULL);
	GtkWidget *dropdown = gtk_drop_down_new(G_LIST_MODEL(model), NULL);
	gtk_drop_down_set_factory(GTK_DROP_DOWN(dropdown), factory);
	model->list_view = dropdown;
	model->jobject = _WEAK_REF(this);
	wrapper_widget_set_child(WRAPPER_WIDGET(wrapper), dropdown);
	gtk_widget_set_name(dropdown, "Spinner");
	return _INTPTR(dropdown);
}

JNIEXPORT void JNICALL Java_android_widget_Spinner_native_1setAdapter(JNIEnv *env, jobject this, jlong widget_ptr, jobject adapter)
{
	GtkDropDown *dropdown = GTK_DROP_DOWN(_PTR(widget_ptr));
	RangeListModel *model = RANGE_LIST_MODEL(gtk_drop_down_get_model(dropdown));

	if (model->adapter)
		_UNREF(model->adapter);
	model->adapter = adapter ? _REF(adapter) : NULL;
	guint old_n_items = model->n_items;
	model->n_items = adapter ? (*env)->CallIntMethod(env, adapter, _METHOD(_CLASS(adapter), "getCount", "()I")) : 0;
	g_list_model_items_changed(G_LIST_MODEL(model), 0, old_n_items, model->n_items);
}

static void on_selected_changed(GtkDropDown *dropdown, GParamSpec *pspec, jobject listener)
{
	JNIEnv *env = get_jni_env();
	int index = gtk_drop_down_get_selected(dropdown);
	RangeListModel *model = RANGE_LIST_ITEM(gtk_drop_down_get_selected_item(dropdown))->model;
	jmethodID onItemSelected = _METHOD(_CLASS(listener), "onItemSelected", "(Landroid/widget/AdapterView;Landroid/view/View;IJ)V");
	(*env)->CallVoidMethod(env, listener, onItemSelected, model->jobject, NULL, index, (long)0);
}

JNIEXPORT void JNICALL Java_android_widget_Spinner_setOnItemSelectedListener(JNIEnv *env, jobject this, jobject listener)
{
	GtkDropDown *dropdown = GTK_DROP_DOWN(_PTR(_GET_LONG_FIELD(this, "widget")));
	g_signal_connect(dropdown, "notify::selected", G_CALLBACK(on_selected_changed), _REF(listener));
}
