#include <gtk/gtk.h>
#include <stdio.h>

#define MAX_USERS 10

// ---------------- USER STRUCT ----------------

struct UserVO {
    const char *username;
    const char *first;
    const char *last;
    const char *email;
};

struct UserVO *users[MAX_USERS];


// ---------------- GObject wrapper ----------------

// Forward declarations REQUIRED
typedef struct _UserObject UserObject;
typedef struct _UserObjectClass UserObjectClass;


struct _UserObject {
    GObject parent_instance;
    struct UserVO *user;
};

struct _UserObjectClass {
    GObjectClass parent_class;
};


G_DEFINE_TYPE(UserObject, user_object, G_TYPE_OBJECT)


static void user_object_class_init(UserObjectClass *klass)
{
}

static void user_object_init(UserObject *self)
{
}

UserObject *user_object_new(struct UserVO *user)
{
    UserObject *obj =
        g_object_new(user_object_get_type(), NULL);

    obj->user = user;

    return obj;
}



// ---------------- Column setup ----------------

static void setup_cb(GtkSignalListItemFactory *factory,
                     GtkListItem *list_item)
{
    GtkWidget *label = gtk_label_new("");

    gtk_list_item_set_child(list_item, label);
}

static void bind_cb(GtkSignalListItemFactory *factory,
                    GtkListItem *list_item)
{
    UserObject *obj =
        gtk_list_item_get_item(list_item);

    GtkWidget *label =
        gtk_list_item_get_child(list_item);

    gtk_label_set_text(GTK_LABEL(label),
                       obj->user->username);
}


// ---------------- selection ----------------

static void selection_changed(GtkSingleSelection *sel,
                              GParamSpec *pspec,
                              gpointer data)
{
    UserObject *obj =
        gtk_single_selection_get_selected_item(sel);

    if(obj)
        printf("Selected: %s\n",
               obj->user->username);
}



// ---------------- activate ----------------

static void activate(GtkApplication *app,
                     gpointer data)
{

    GtkWidget *window =
        gtk_application_window_new(app);

    gtk_window_set_title(GTK_WINDOW(window),
                         "Users");

    gtk_window_set_default_size(GTK_WINDOW(window),
                                400,300);



    GListStore *store =
        g_list_store_new(user_object_get_type());


    for(int i=0;i<3;i++)
        g_list_store_append(store,
                            user_object_new(users[i]));



    GtkSingleSelection *selection =
        gtk_single_selection_new(G_LIST_MODEL(store));


    g_signal_connect(selection,
                     "notify::selected-item",
                     G_CALLBACK(selection_changed),
                     NULL);



    GtkWidget *view =
        gtk_column_view_new(GTK_SELECTION_MODEL(selection));



    GtkSignalListItemFactory *factory =
        GTK_SIGNAL_LIST_ITEM_FACTORY(
            gtk_signal_list_item_factory_new()
        );


    g_signal_connect(factory,
                     "setup",
                     G_CALLBACK(setup_cb),
                     NULL);

    g_signal_connect(factory,
                     "bind",
                     G_CALLBACK(bind_cb),
                     NULL);



    GtkColumnViewColumn *column =
        gtk_column_view_column_new(
            "Username",
            GTK_LIST_ITEM_FACTORY(factory)
        );


    gtk_column_view_append_column(
        GTK_COLUMN_VIEW(view),
        column);



    gtk_window_set_child(GTK_WINDOW(window),
                         view);


    gtk_window_present(GTK_WINDOW(window));

}



// ---------------- main ----------------

int main(int argc, char **argv)
{

    static struct UserVO u1 =
        {"john","John","Doe","john@mail"};

    static struct UserVO u2 =
        {"alice","Alice","Smith","alice@mail"};

    static struct UserVO u3 =
        {"bob","Bob","Brown","bob@mail"};



    users[0]=&u1;
    users[1]=&u2;
    users[2]=&u3;



    GtkApplication *app =
        gtk_application_new("example.users",
                            G_APPLICATION_DEFAULT_FLAGS);


    g_signal_connect(app,
                     "activate",
                     G_CALLBACK(activate),
                     NULL);



    int status =
        g_application_run(G_APPLICATION(app),
                          argc,
                          argv);


    g_object_unref(app);


    return status;
}