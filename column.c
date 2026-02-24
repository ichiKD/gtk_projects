#include <gtk/gtk.h>

/* Your struct */
typedef struct {
    char *name;
    int age;
} people;

/* GObject wrapper for struct (REQUIRED by GTK) */
#define TYPE_PERSON (person_get_type())
G_DECLARE_FINAL_TYPE(Person, person, PERSON, OBJECT, GObject)

struct _Person {
    GObject parent_instance;
    char *name;
    int age;
};

G_DEFINE_TYPE(Person, person, G_TYPE_OBJECT)
enum {
    PROP_0,
    PROP_NAME,
    PROP_AGE,
    N_PROPS
};
static GParamSpec *properties[N_PROPS];

static void person_get_property(GObject *object, guint prop_id, GValue *value, GParamSpec *pspec) {
    Person *self = (Person *)object;
    switch (prop_id) {
    case PROP_NAME:
        g_value_set_string(value, self->name);
        break;
    case PROP_AGE:
        g_value_set_int(value, self->age);
        break;
    }
}

static void person_set_property(GObject *object, guint prop_id, const GValue *value, GParamSpec *pspec) {
    Person *self = (Person *)object;
    switch (prop_id) {
    case PROP_NAME:
        self->name = g_value_dup_string(value);
        break;
    case PROP_AGE:
        self->age = g_value_get_int(value);
        break;
    }
}

static void person_class_init(PersonClass *klass) {
    GObjectClass *object_class = G_OBJECT_CLASS(klass);
    object_class->get_property = person_get_property;
    object_class->set_property = person_set_property;
    properties[PROP_NAME] = g_param_spec_string("name", "Name", "Name", NULL, G_PARAM_READWRITE);
    properties[PROP_AGE] = g_param_spec_int("age", "Age", "Age", 0, 200, 0, G_PARAM_READWRITE);
    g_object_class_install_properties(object_class, N_PROPS, properties);
}

static void person_init(Person *self) {}

/* Factory setup */
static void setup(GtkSignalListItemFactory *factory, GtkListItem *list_item, gpointer data) {
    GtkWidget *label = gtk_label_new(NULL);
    gtk_list_item_set_child(list_item, label);
}

/* Factory bind name */
static void bind_name(GtkSignalListItemFactory *factory, GtkListItem *list_item, gpointer data) {
    GtkLabel *label = GTK_LABEL(gtk_list_item_get_child(list_item));
    Person *person = gtk_list_item_get_item(list_item);
    gtk_label_set_text(label, person->name);
}

/* Factory bind age */
static void bind_age(GtkSignalListItemFactory *factory, GtkListItem *list_item, gpointer data) {
    GtkLabel *label = GTK_LABEL(gtk_list_item_get_child(list_item));
    Person *person = gtk_list_item_get_item(list_item);
    char buffer[10];
    sprintf(buffer, "%d", person->age);
    gtk_label_set_text(label, buffer);
}

static void activate(GtkApplication *app) {
    /* Create data */
    Person *p1 = g_object_new(TYPE_PERSON, "name", "John", "age", 25, NULL);
    Person *p2 = g_object_new(TYPE_PERSON, "name", "Alice", "age", 30, NULL);
    Person *p3 = g_object_new(TYPE_PERSON, "name", "Bob", "age", 40, NULL);

    /* Store */
    GListStore *store = g_list_store_new(TYPE_PERSON);
    g_list_store_append(store, p1);
    g_list_store_append(store, p2);
    g_list_store_append(store, p3);

    /* Selection */
    GtkSelectionModel *selection = GTK_SELECTION_MODEL(gtk_single_selection_new(G_LIST_MODEL(store)));

    /* ColumnView */
    GtkWidget *view = gtk_column_view_new(selection);

    /* Name column */
    GtkListItemFactory *factory1 = gtk_signal_list_item_factory_new();
    g_signal_connect(factory1, "setup", G_CALLBACK(setup), NULL);
    g_signal_connect(factory1, "bind", G_CALLBACK(bind_name), NULL);
    GtkColumnViewColumn *col1 = gtk_column_view_column_new("Name", GTK_LIST_ITEM_FACTORY(factory1));
    gtk_column_view_append_column(GTK_COLUMN_VIEW(view), col1);

    /* Age column */
    GtkListItemFactory *factory2 = gtk_signal_list_item_factory_new();
    g_signal_connect(factory2, "setup", G_CALLBACK(setup), NULL);
    g_signal_connect(factory2, "bind", G_CALLBACK(bind_age), NULL);
    GtkColumnViewColumn *col2 = gtk_column_view_column_new("Age", GTK_LIST_ITEM_FACTORY(factory2));
    gtk_column_view_append_column(GTK_COLUMN_VIEW(view), col2);

    /* Window */
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Column View");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    gtk_window_set_child(GTK_WINDOW(window), view);
    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv) {

    GtkApplication *app = gtk_application_new("example.columnview", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}