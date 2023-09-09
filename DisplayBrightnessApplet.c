// DisplayBrightnessApplet.c

#include <lxpanel/plugin.h>
#include <ddcutil_types.h>
#include <ddcutil_c_api.h>
#include <ddcutil_status_codes.h>
#include <ddcutil_macros.h>
#include <stdio.h>

// internal to the plugin source, not used by the 'priv' variable
static int iInstanceCount = 0;
GtkWidget *pLabel;

/* the plugin's id – an instance of this struct 
   is what will be assigned to 'priv' */
typedef struct 
{
  gint iMyId;
} DisplayBrightnessApplet;

static gboolean on_button_press (GtkWidget* widget, GdkEventButton* evt, LXPanel* p)
{
   switch ( evt->button ) {
      case 1: 
      {	/*  Left click */
         gtk_label_set_text((GtkLabel *)pLabel, "AAA");
         break;
      }
      case 2:
      {
         gtk_label_set_text((GtkLabel *)pLabel, "BBB");
         break;
      }
      default:
      {
         break;
      }
   }
   return FALSE;
}

GtkWidget *DisplayBrightnessApplet_constructor(LXPanel *panel, config_setting_t *settings)
{
 /* panel is a pointer to the panel and
     settings is a pointer to the configuration data
     since we don't use it, we'll make sure it doesn't
     give us an error at compilation time */
 (void)panel;
 (void)settings;

 // allocate our private structure instance
 DisplayBrightnessApplet *pApplet = g_new0(DisplayBrightnessApplet, 1);

 // update the instance count
 pApplet->iMyId = ++iInstanceCount;

 // make a label out of the ID
 char cIdBuf[10] = {'\0'};

 snprintf(cIdBuf, sizeof(cIdBuf), "TP-%d", pApplet->iMyId);

 // create a label widget instance 
 pLabel = gtk_label_new(cIdBuf);

 // set the label to be visible
 gtk_widget_show(pLabel);

 // need to create a container to be able to set a border
 GtkWidget *p = gtk_event_box_new();

 // our widget doesn't have a window...
 // it is usually illegal to call gtk_widget_set_has_window() from application but for GtkEventBox it doesn't hurt
 gtk_widget_set_has_window(p, FALSE);

 // bind private structure to the widget assuming it should be freed using g_free()
 lxpanel_plugin_set_data(p, pApplet, g_free);

 // set border width
 gtk_container_set_border_width(GTK_CONTAINER(p), 1);

 // add the label to the container
 gtk_container_add(GTK_CONTAINER(p), pLabel);

 // set the size we want
 gtk_widget_set_size_request(p, 40, 25);

 // success!!!
 return p;
}

FM_DEFINE_MODULE(lxpanel_gtk, test)

/* Plugin descriptor. */
LXPanelPluginInit fm_module_init_lxpanel_gtk = {
   .name = "Display Brightness",
   .description = "Control Brightness of DDC/CI Capable Display",

   // assigning our functions to provided pointers.
   .new_instance = DisplayBrightnessApplet_constructor,
   .button_press_event = on_button_press
};
