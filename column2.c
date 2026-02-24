#include <gtk/gtk.h>
#include <stdbool.h>
/* =========================
   Your original enum
   ========================= */
enum DeptEnum {
    DEPT_NONE_SELECTED = 0,
    DEPT_ACCT = 1,
    DEPT_SALES = 2,
    DEPT_PLANT = 3,
    DEPT_SHIPPING = 4,
    DEPT_QC = 5
};
const char *dept_to_string(const enum DeptEnum dept) {
    switch (dept) {
    case DEPT_NONE_SELECTED:
        return "--NONE_SELECTED--";
    case DEPT_ACCT:
        return "Accounting";
    case DEPT_SALES:
        return "Sales";
    case DEPT_PLANT:
        return "Plant";
    case DEPT_SHIPPING:
        return "Shipping";
    case DEPT_QC:
        return "Quality Control";
    default:
        return "Unknown";
    }
}
/* =========================
   GObject Wrapper
   ========================= */
#define TYPE_USER (user_get_type())
G_DECLARE_FINAL_TYPE(User, user, USER, OBJECT, GObject)
struct _User {
    GObject parent_instance;
    char *username;
    char *first;
    char *last;
    char *email;
    char *password;
    int department;
};
G_DEFINE_TYPE(User, user, G_TYPE_OBJECT)
static GtkEntry *entry_username;
static GtkEntry *entry_first;
static GtkEntry *entry_last;
static GtkEntry *entry_email;
static GtkEntry *entry_password;
static GtkDropDown *entry_dept;
static GtkSingleSelection *single_selection;
static User *selected_user = NULL;
/* =========================
   Properties
   ========================= */
enum {
    PROP_0,
    PROP_USERNAME,
    PROP_FIRST,
    PROP_LAST,
    PROP_EMAIL,
    PROP_PASSWORD,
    PROP_DEPT,
    N_PROPS
};
static GParamSpec *properties[N_PROPS];
/* =========================
   Setter
   ========================= */
static void user_set_property(GObject *object, guint prop_id, const GValue *value, GParamSpec *pspec) {
    User *self = (User *)object;
    switch (prop_id) {
    case PROP_USERNAME:
        self->username = g_value_dup_string(value);
        break;
    case PROP_FIRST:
        self->first = g_value_dup_string(value);
        break;
    case PROP_LAST:
        self->last = g_value_dup_string(value);
        break;
    case PROP_EMAIL:
        self->email = g_value_dup_string(value);
        break;
    case PROP_PASSWORD:
        self->password = g_value_dup_string(value);
        break;
    case PROP_DEPT:
        self->department = g_value_get_int(value);
        break;
    }
}
/* =========================
   Getter
   ========================= */
static void user_get_property(GObject *object, guint prop_id, GValue *value, GParamSpec *pspec) {
    User *self = (User *)object;
    switch (prop_id) {
    case PROP_USERNAME:
        g_value_set_string(value, self->username);
        break;
    case PROP_FIRST:
        g_value_set_string(value, self->first);
        break;
    case PROP_LAST:
        g_value_set_string(value, self->last);
        break;
    case PROP_EMAIL:
        g_value_set_string(value, self->email);
        break;
    case PROP_PASSWORD:
        g_value_set_string(value, self->password);
        break;
    case PROP_DEPT:
        g_value_set_int(value, self->department);
        break;
    }
}
/* =========================
   Class Init
   ========================= */
static void user_class_init(UserClass *klass) {
    GObjectClass *object_class = G_OBJECT_CLASS(klass);
    object_class->set_property = user_set_property;
    object_class->get_property = user_get_property;
    properties[PROP_USERNAME] = g_param_spec_string("username", "", "", NULL, G_PARAM_READWRITE);
    properties[PROP_FIRST] = g_param_spec_string("first", "", "", NULL, G_PARAM_READWRITE);
    properties[PROP_LAST] = g_param_spec_string("last", "", "", NULL, G_PARAM_READWRITE);
    properties[PROP_EMAIL] = g_param_spec_string("email", "", "", NULL, G_PARAM_READWRITE);
    properties[PROP_PASSWORD] = g_param_spec_string("password", "", "", NULL, G_PARAM_READWRITE);
    properties[PROP_DEPT] = g_param_spec_int("department", "", "", 0, 10, 0, G_PARAM_READWRITE);
    g_object_class_install_properties(object_class, N_PROPS, properties);
}
static void user_init(User *self) {}
/* =========================
   Factory setup
   ========================= */
static void setup(GtkSignalListItemFactory *factory, GtkListItem *list_item, gpointer data) {
    GtkWidget *label = gtk_label_new(NULL);
    gtk_list_item_set_child(list_item, label);
}
/* =========================
   Bind functions
   ========================= */
static void bind_username(GtkSignalListItemFactory *factory, GtkListItem *list_item, gpointer data) {
    GtkLabel *label = GTK_LABEL(gtk_list_item_get_child(list_item));
    User *user = gtk_list_item_get_item(list_item);
    GBinding *binding = g_object_bind_property(user, "username", label, "label", G_BINDING_SYNC_CREATE);
    g_object_set_data_full(G_OBJECT(label), "binding", binding, g_object_unref);
}
static void bind_first(GtkSignalListItemFactory *factory, GtkListItem *list_item, gpointer data) {
    GtkLabel *label = GTK_LABEL(gtk_list_item_get_child(list_item));
    User *user = gtk_list_item_get_item(list_item);
    GBinding *binding = g_object_bind_property(user, "first", label, "label", G_BINDING_SYNC_CREATE);
    g_object_set_data_full(G_OBJECT(label), "binding", binding, g_object_unref);
}
static void bind_last(GtkSignalListItemFactory *factory, GtkListItem *list_item, gpointer data) {
    GtkLabel *label = GTK_LABEL(gtk_list_item_get_child(list_item));
    User *user = gtk_list_item_get_item(list_item);
    GBinding *binding = g_object_bind_property(user, "last", label, "label", G_BINDING_SYNC_CREATE);
    g_object_set_data_full(G_OBJECT(label), "binding", binding, g_object_unref);
}
static void bind_email(GtkSignalListItemFactory *factory, GtkListItem *list_item, gpointer data) {
    GtkLabel *label = GTK_LABEL(gtk_list_item_get_child(list_item));
    User *user = gtk_list_item_get_item(list_item);
    GBinding *binding = g_object_bind_property(user, "email", label, "label", G_BINDING_SYNC_CREATE);
    g_object_set_data_full(G_OBJECT(label), "binding", binding, g_object_unref);
}
/* Department cannot bind directly (needs conversion) */
static void bind_dept(GtkSignalListItemFactory *factory, GtkListItem *list_item, gpointer data) {
    GtkLabel *label = GTK_LABEL(gtk_list_item_get_child(list_item));
    User *user = gtk_list_item_get_item(list_item);
    gtk_label_set_text(label, dept_to_string(user->department));
}
/* =========================
   Unbind functions
   ========================= */
static void unbind_all(GtkSignalListItemFactory *factory, GtkListItem *list_item, gpointer data) {
    GtkWidget *child = gtk_list_item_get_child(list_item);
    if (!child) return;
    /* DO NOTHING */
    /* binding will be unref automatically
       by g_object_set_data_full */
}
static void on_selection_changed(GtkSingleSelection *sel, GParamSpec *pspec, gpointer data) {
    selected_user = g_list_model_get_item(G_LIST_MODEL(sel), gtk_single_selection_get_selected(sel));
    if (!selected_user) return;
    gtk_editable_set_text(GTK_EDITABLE(entry_username), selected_user->username);
    gtk_editable_set_text(GTK_EDITABLE(entry_first), selected_user->first);
    gtk_editable_set_text(GTK_EDITABLE(entry_last), selected_user->last);
    gtk_editable_set_text(GTK_EDITABLE(entry_email), selected_user->email);
    gtk_editable_set_text(GTK_EDITABLE(entry_password), selected_user->password);
    gtk_drop_down_set_selected(entry_dept, selected_user->department);
}
static void on_update_clicked(GtkButton *btn, gpointer data) {
    if (!selected_user) return;
    g_object_set(selected_user, "username", gtk_editable_get_text(GTK_EDITABLE(entry_username)), "first", gtk_editable_get_text(GTK_EDITABLE(entry_first)), "last", gtk_editable_get_text(GTK_EDITABLE(entry_last)), "email", gtk_editable_get_text(GTK_EDITABLE(entry_email)), "password", gtk_editable_get_text(GTK_EDITABLE(entry_password)), "department", gtk_drop_down_get_selected(entry_dept), NULL);
}
/* =========================
   Activate
   ========================= */
static void activate(GtkApplication *app) {
    /* Create users */
    User *u1 = g_object_new(TYPE_USER, "username", "jsmith", "first", "John", "last", "Smith", "email", "john@gmail.com", "password", "1234", "department", DEPT_SALES, NULL);
    User *u2 = g_object_new(TYPE_USER, "username", "adoe", "first", "Alice", "last", "Doe", "email", "alice@gmail.com", "password", "1234", "department", DEPT_ACCT, NULL);
    User *u3 = g_object_new(TYPE_USER, "username", "bwayne", "first", "Bruce", "last", "Wayne", "email", "bruce@gmail.com", "password", "1234", "department", DEPT_SHIPPING, NULL);
    /* Store */
    GListStore *store = g_list_store_new(TYPE_USER);
    g_list_store_append(store, u1);
    g_list_store_append(store, u2);
    g_list_store_append(store, u3);
    single_selection = gtk_single_selection_new(G_LIST_MODEL(store));
    g_signal_connect(single_selection, "notify::selected", G_CALLBACK(on_selection_changed), NULL);
    GtkSelectionModel *selection = GTK_SELECTION_MODEL(single_selection);
    GtkWidget *view = gtk_column_view_new(selection);
    /* Username column */
    GtkListItemFactory *f1 = gtk_signal_list_item_factory_new();
    g_signal_connect(f1, "setup", G_CALLBACK(setup), NULL);
    g_signal_connect(f1, "bind", G_CALLBACK(bind_username), NULL);
    g_signal_connect(f1, "unbind", G_CALLBACK(unbind_all), NULL);
    gtk_column_view_append_column(GTK_COLUMN_VIEW(view), gtk_column_view_column_new("Username", f1));
    /* First */
    GtkListItemFactory *f2 = gtk_signal_list_item_factory_new();
    g_signal_connect(f2, "setup", G_CALLBACK(setup), NULL);
    g_signal_connect(f2, "bind", G_CALLBACK(bind_first), NULL);
    g_signal_connect(f2, "unbind", G_CALLBACK(unbind_all), NULL);
    gtk_column_view_append_column(GTK_COLUMN_VIEW(view), gtk_column_view_column_new("First", f2));
    /* Last */
    GtkListItemFactory *f3 = gtk_signal_list_item_factory_new();
    g_signal_connect(f3, "setup", G_CALLBACK(setup), NULL);
    g_signal_connect(f3, "bind", G_CALLBACK(bind_last), NULL);
    g_signal_connect(f3, "unbind", G_CALLBACK(unbind_all), NULL);
    gtk_column_view_append_column(GTK_COLUMN_VIEW(view), gtk_column_view_column_new("Last", f3));
    /* Email */
    GtkListItemFactory *f4 = gtk_signal_list_item_factory_new();
    g_signal_connect(f4, "setup", G_CALLBACK(setup), NULL);
    g_signal_connect(f4, "bind", G_CALLBACK(bind_email), NULL);
    g_signal_connect(f4, "unbind", G_CALLBACK(unbind_all), NULL);
    gtk_column_view_append_column(GTK_COLUMN_VIEW(view), gtk_column_view_column_new("Email", f4));
    /* Department */
    GtkListItemFactory *f5 = gtk_signal_list_item_factory_new();
    g_signal_connect(f5, "setup", G_CALLBACK(setup), NULL);
    g_signal_connect(f5, "bind", G_CALLBACK(bind_dept), NULL);
    g_signal_connect(f5, "unbind", G_CALLBACK(unbind_all), NULL);
    gtk_column_view_append_column(GTK_COLUMN_VIEW(view), gtk_column_view_column_new("Department", f5));
    /**/
    entry_username = GTK_ENTRY(gtk_entry_new());
    entry_first = GTK_ENTRY(gtk_entry_new());
    entry_last = GTK_ENTRY(gtk_entry_new());
    entry_email = GTK_ENTRY(gtk_entry_new());
    entry_password = GTK_ENTRY(gtk_entry_new());
    entry_dept = GTK_DROP_DOWN(gtk_drop_down_new_from_strings((const char *[]){"--NONE_SELECTED--", "Accounting", "Sales", "Plant", "Shipping", "Quality Control", NULL}));
    GtkWidget *update_btn = gtk_button_new_with_label("Update");
    g_signal_connect(update_btn, "clicked", G_CALLBACK(on_update_clicked), NULL);
    /* layout */
    GtkWidget *form = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_append(GTK_BOX(form), GTK_WIDGET(entry_username));
    gtk_box_append(GTK_BOX(form), GTK_WIDGET(entry_first));
    gtk_box_append(GTK_BOX(form), GTK_WIDGET(entry_last));
    gtk_box_append(GTK_BOX(form), GTK_WIDGET(entry_email));
    gtk_box_append(GTK_BOX(form), GTK_WIDGET(entry_password));
    gtk_box_append(GTK_BOX(form), GTK_WIDGET(entry_dept));
    gtk_box_append(GTK_BOX(form), update_btn);
    /* main layout */
    GtkWidget *mainbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_box_append(GTK_BOX(mainbox), view);
    gtk_box_append(GTK_BOX(mainbox), form);
    /* Window */
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "User Admin");
    gtk_window_set_default_size(GTK_WINDOW(window), 700, 400);
    gtk_window_set_child(GTK_WINDOW(window), mainbox);
    gtk_window_present(GTK_WINDOW(window));
}
/* =========================
   Main
   ========================= */
int main(int argc, char **argv) {
    GtkApplication *app = gtk_application_new("example.useradmin", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}