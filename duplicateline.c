#include <gedit/gedit-app-activatable.h>
#include <gedit/gedit-window-activatable.h>
#include <gedit/gedit-window.h>
#include <gedit/gedit-document.h>
#include <libpeas/peas.h>

/* App Activatable - registers menu item and accelerator */

#define DUPLICATE_LINE_TYPE_APP_ACTIVATABLE (duplicate_line_app_activatable_get_type ())
G_DECLARE_FINAL_TYPE (DuplicateLineAppActivatable, duplicate_line_app_activatable,
                      DUPLICATE_LINE, APP_ACTIVATABLE, GObject)

struct _DuplicateLineAppActivatable
{
	GObject parent;
	GeditMenuExtension *menu_ext;
};

static void duplicate_line_app_activatable_iface_init (GeditAppActivatableInterface *iface);
G_DEFINE_TYPE_WITH_CODE (DuplicateLineAppActivatable, duplicate_line_app_activatable, G_TYPE_OBJECT,
                         G_IMPLEMENT_INTERFACE (GEDIT_TYPE_APP_ACTIVATABLE, duplicate_line_app_activatable_iface_init))

enum { APP_PROP_0, APP_PROP_APP };

static void
duplicate_line_app_activatable_set_property (GObject *object, guint prop_id,
                                            const GValue *value, GParamSpec *pspec)
{
	if (prop_id == APP_PROP_APP)
		/* just store it via g_object_set_data for simplicity */
		g_object_set_data (object, "app", g_value_get_object (value));
	else
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
}

static void
duplicate_line_app_activatable_get_property (GObject *object, guint prop_id,
                                            GValue *value, GParamSpec *pspec)
{
	if (prop_id == APP_PROP_APP)
		g_value_set_object (value, g_object_get_data (object, "app"));
	else
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
}

static void
duplicate_line_app_activate (GeditAppActivatable *activatable)
{
	DuplicateLineAppActivatable *self = DUPLICATE_LINE_APP_ACTIVATABLE (activatable);
	GtkApplication *app = g_object_get_data (G_OBJECT (self), "app");
	GMenuItem *item;
	const gchar *accels[] = { "<Primary><Shift>d", NULL };

	self->menu_ext = gedit_app_activatable_extend_menu (activatable, "edit-section-1");
	item = g_menu_item_new ("Duplicate Line/Selection", "win.duplicate-line");
	gedit_menu_extension_append_menu_item (self->menu_ext, item);
	g_object_unref (item);

	gtk_application_set_accels_for_action (app, "win.duplicate-line", accels);
}

static void
duplicate_line_app_deactivate (GeditAppActivatable *activatable)
{
	DuplicateLineAppActivatable *self = DUPLICATE_LINE_APP_ACTIVATABLE (activatable);
	GtkApplication *app = g_object_get_data (G_OBJECT (self), "app");
	const gchar *accels[] = { NULL };

	gtk_application_set_accels_for_action (app, "win.duplicate-line", accels);
	gedit_menu_extension_remove_items (self->menu_ext);
	g_clear_object (&self->menu_ext);
}

static void
duplicate_line_app_activatable_iface_init (GeditAppActivatableInterface *iface)
{
	iface->activate = duplicate_line_app_activate;
	iface->deactivate = duplicate_line_app_deactivate;
}

static void
duplicate_line_app_activatable_class_init (DuplicateLineAppActivatableClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS (klass);
	object_class->set_property = duplicate_line_app_activatable_set_property;
	object_class->get_property = duplicate_line_app_activatable_get_property;
	g_object_class_override_property (object_class, APP_PROP_APP, "app");
}

static void
duplicate_line_app_activatable_init (DuplicateLineAppActivatable *self)
{
}

/* Window Activatable - handles the duplicate action */

#define DUPLICATE_LINE_TYPE_WINDOW_ACTIVATABLE (duplicate_line_window_activatable_get_type ())
G_DECLARE_FINAL_TYPE (DuplicateLineWindowActivatable, duplicate_line_window_activatable,
                      DUPLICATE_LINE, WINDOW_ACTIVATABLE, GObject)

struct _DuplicateLineWindowActivatable
{
	GObject parent;
	GeditWindow *window;
};

static void duplicate_line_window_activatable_iface_init (GeditWindowActivatableInterface *iface);
G_DEFINE_TYPE_WITH_CODE (DuplicateLineWindowActivatable, duplicate_line_window_activatable, G_TYPE_OBJECT,
                         G_IMPLEMENT_INTERFACE (GEDIT_TYPE_WINDOW_ACTIVATABLE, duplicate_line_window_activatable_iface_init))

enum { WIN_PROP_0, WIN_PROP_WINDOW };

static void
duplicate_line_window_activatable_set_property (GObject *object, guint prop_id,
                                               const GValue *value, GParamSpec *pspec)
{
	DuplicateLineWindowActivatable *self = DUPLICATE_LINE_WINDOW_ACTIVATABLE (object);
	if (prop_id == WIN_PROP_WINDOW)
		self->window = g_value_get_object (value);
	else
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
}

static void
duplicate_line_window_activatable_get_property (GObject *object, guint prop_id,
                                               GValue *value, GParamSpec *pspec)
{
	DuplicateLineWindowActivatable *self = DUPLICATE_LINE_WINDOW_ACTIVATABLE (object);
	if (prop_id == WIN_PROP_WINDOW)
		g_value_set_object (value, self->window);
	else
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
}

static void
on_duplicate_line (GSimpleAction *action, GVariant *parameter, gpointer user_data)
{
	DuplicateLineWindowActivatable *self = user_data;
	GeditDocument *doc;
	GtkTextBuffer *buf;
	GtkTextIter s, e;
	gchar *text;

	doc = gedit_window_get_active_document (self->window);
	if (doc == NULL)
		return;

	buf = GTK_TEXT_BUFFER (doc);

	if (gtk_text_buffer_get_has_selection (buf))
	{
		gint l1, l2;

		gtk_text_buffer_get_selection_bounds (buf, &s, &e);
		l1 = gtk_text_iter_get_line (&s);
		l2 = gtk_text_iter_get_line (&e);

		if (l1 != l2)
		{
			/* Multi-line selection: duplicate whole lines */
			gtk_text_iter_set_line_offset (&s, 0);
			if (!gtk_text_iter_ends_line (&e))
				gtk_text_iter_forward_to_line_end (&e);

			text = gtk_text_buffer_get_text (buf, &s, &e, FALSE);
			gchar *ins = g_strconcat ("\n", text, NULL);
			gtk_text_buffer_insert (buf, &e, ins, -1);
			g_free (ins);
			g_free (text);
		}
		else
		{
			/* Same-line selection: duplicate inline */
			text = gtk_text_buffer_get_text (buf, &s, &e, FALSE);
			gtk_text_buffer_place_cursor (buf, &s);
			/* re-get iter after place_cursor */
			gtk_text_buffer_get_selection_bounds (buf, &s, &e);
			gtk_text_buffer_insert (buf, &e, text, -1);
			g_free (text);
		}
	}
	else
	{
		/* No selection: duplicate current line */
		GtkTextMark *mark = gtk_text_buffer_get_insert (buf);
		gtk_text_buffer_get_iter_at_mark (buf, &s, mark);
		e = s;
		gtk_text_iter_set_line_offset (&s, 0);
		if (!gtk_text_iter_ends_line (&e))
			gtk_text_iter_forward_to_line_end (&e);

		text = gtk_text_buffer_get_text (buf, &s, &e, FALSE);
		gchar *ins = g_strconcat ("\n", text, NULL);
		gtk_text_buffer_insert (buf, &e, ins, -1);
		g_free (ins);
		g_free (text);
	}
}

static void
duplicate_line_window_activate (GeditWindowActivatable *activatable)
{
	DuplicateLineWindowActivatable *self = DUPLICATE_LINE_WINDOW_ACTIVATABLE (activatable);
	GSimpleAction *action;

	action = g_simple_action_new ("duplicate-line", NULL);
	g_signal_connect (action, "activate", G_CALLBACK (on_duplicate_line), self);
	g_action_map_add_action (G_ACTION_MAP (self->window), G_ACTION (action));
	g_object_unref (action);
}

static void
duplicate_line_window_deactivate (GeditWindowActivatable *activatable)
{
	DuplicateLineWindowActivatable *self = DUPLICATE_LINE_WINDOW_ACTIVATABLE (activatable);
	g_action_map_remove_action (G_ACTION_MAP (self->window), "duplicate-line");
}

static void
duplicate_line_window_update_state (GeditWindowActivatable *activatable)
{
	DuplicateLineWindowActivatable *self = DUPLICATE_LINE_WINDOW_ACTIVATABLE (activatable);
	GAction *action;

	action = g_action_map_lookup_action (G_ACTION_MAP (self->window), "duplicate-line");
	g_simple_action_set_enabled (G_SIMPLE_ACTION (action),
	                             gedit_window_get_active_document (self->window) != NULL);
}

static void
duplicate_line_window_activatable_iface_init (GeditWindowActivatableInterface *iface)
{
	iface->activate = duplicate_line_window_activate;
	iface->deactivate = duplicate_line_window_deactivate;
	iface->update_state = duplicate_line_window_update_state;
}

static void
duplicate_line_window_activatable_class_init (DuplicateLineWindowActivatableClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS (klass);
	object_class->set_property = duplicate_line_window_activatable_set_property;
	object_class->get_property = duplicate_line_window_activatable_get_property;
	g_object_class_override_property (object_class, WIN_PROP_WINDOW, "window");
}

static void
duplicate_line_window_activatable_init (DuplicateLineWindowActivatable *self)
{
}

/* Plugin registration */

G_MODULE_EXPORT void
peas_register_types (PeasObjectModule *module)
{
	peas_object_module_register_extension_type (module, GEDIT_TYPE_APP_ACTIVATABLE,
	                                           DUPLICATE_LINE_TYPE_APP_ACTIVATABLE);
	peas_object_module_register_extension_type (module, GEDIT_TYPE_WINDOW_ACTIVATABLE,
	                                           DUPLICATE_LINE_TYPE_WINDOW_ACTIVATABLE);
}
