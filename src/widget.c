#include <string.h>
#include <gtk/gtk.h>

#include "widget.h"

void setupWidgets()
{
   playerWidget = gtk_drawing_area_new() ;
   gtk_box_pack_start(GTK_BOX(box), playerWidget, TRUE, TRUE, 0) ;

   //setup progressbar
   progressBar = gtk_progress_bar_new() ;

   //setup buttons
   playpauseButton = gtk_button_new_from_icon_name("media-playback-pause", GTK_ICON_SIZE_BUTTON) ;
   gtk_button_set_relief(GTK_BUTTON(playpauseButton), GTK_RELIEF_NONE) ;
   stopButton = gtk_button_new_from_icon_name("media-playback-stop", GTK_ICON_SIZE_BUTTON) ;
   gtk_button_set_relief(GTK_BUTTON(stopButton), GTK_RELIEF_NONE) ;
   g_signal_connect(playpauseButton, "clicked", G_CALLBACK(onPlayPause), NULL) ;
   g_signal_connect(stopButton, "clicked", G_CALLBACK(onStop), NULL) ;

   buttonbox = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL) ;
   gtk_container_set_border_width(GTK_CONTAINER(buttonbox), BORDER_WIDTH) ;
   gtk_button_box_set_layout(GTK_BUTTON_BOX(buttonbox), GTK_BUTTONBOX_START) ;
   gtk_box_pack_start(GTK_BOX(buttonbox), playpauseButton, FALSE, FALSE, 0) ;
   gtk_box_pack_start(GTK_BOX(buttonbox), stopButton, FALSE, FALSE, 0) ;
   gtk_box_pack_start(GTK_BOX(buttonbox), progressBar, FALSE, FALSE, 0) ;
   gtk_box_pack_start(GTK_BOX(box), buttonbox, FALSE, FALSE, 0) ;

   return ;
}

void setButtonIcon(char *iconName)
{
   if (strcmp(iconName, "media-playback-pause") == 0)
   {
      image = gtk_image_new_from_icon_name("media-playback-pause", GTK_ICON_SIZE_BUTTON) ;
      gtk_button_set_image(GTK_BUTTON(playpauseButton), image) ;
   }
   else if (strcmp(iconName, "media-playback-start") == 0)
   {
      image = gtk_image_new_from_icon_name("media-playback-start", GTK_ICON_SIZE_BUTTON) ;
      gtk_button_set_image(GTK_BUTTON(playpauseButton), image) ;
   }

   return ;
}

GtkWidget *getPlayerWidget()
{
   return playerWidget ;
}

gboolean updateBar()
{

   gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progressBar),
                                 (double)getCurrentTime()/(double)getDuration()) ;
   if (gtk_progress_bar_get_fraction(GTK_PROGRESS_BAR(progressBar)) == 1)
      return FALSE ;
   return TRUE ;
}

void startProgressBar()
{
   g_timeout_add_seconds(1, G_SOURCE_FUNC(updateBar), NULL) ;
}




