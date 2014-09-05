
#include <gtk/gtk.h>
#include <glib.h>
#include <stdio.h>
#include <wiringPi.h>
#include "temperature.h"

#define GREEN_LED 0
#define YELLOW_LED 2
#define RED_LED 3
#define OFF 0
#define ON 1

static void voToggleGreenLed(GtkWidget *widget, gpointer data);
static void voToggleYellowLed(GtkWidget *widget, gpointer data);
static void voToggleRedLed(GtkWidget *widget, gpointer data);
static gboolean voGetTemperature(gpointer data);

int main(int argc, char *argv[])
{
	wiringPiSetup ();

	/* setting GPIO's as output for controlling LEDS */
	pinMode (GREEN_LED, OUTPUT); // set pin 0 as OUTPUT
	pinMode (YELLOW_LED, OUTPUT); // set pin 2 as OUTPUT
	pinMode (RED_LED, OUTPUT); // set pin 3 as OUTPUT
	/* creating window and label object */
	GtkWidget *window, *button[3], *table, *label[4];
	
	gtk_init(&argc, &argv);
	/* window configuration */
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "LED Program");
	gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

	table = gtk_table_new(4, 2, TRUE);
	// check for LED status
	// add function to read value from gpio file
	button[0] = gtk_button_new_with_label("OFF");
	button[1] = gtk_button_new_with_label("OFF");
	button[2] = gtk_button_new_with_label("OFF");
	label[0] = gtk_label_new("Green:");
	label[1] = gtk_label_new("Yellow:");
	label[2] = gtk_label_new("Red:");
	label[3] = gtk_label_new("Temperature:");

	gtk_table_attach_defaults(GTK_TABLE(table), label[0], 0, 1, 0, 1);
	gtk_table_attach_defaults(GTK_TABLE(table), label[1], 0, 1, 1, 2);
	gtk_table_attach_defaults(GTK_TABLE(table), label[2], 0, 1, 2, 3);
	gtk_table_attach_defaults(GTK_TABLE(table), button[0], 1, 2, 0, 1);
	gtk_table_attach_defaults(GTK_TABLE(table), button[1], 1, 2, 1, 2);
	gtk_table_attach_defaults(GTK_TABLE(table), button[2], 1, 2, 2, 3);
	gtk_table_attach_defaults(GTK_TABLE(table), label[3], 0, 2, 3, 4);

	/* map callbackfunctions with buttons */
	g_signal_connect(button[0], "clicked", G_CALLBACK(voToggleGreenLed), NULL);
	g_signal_connect(button[1], "clicked", G_CALLBACK(voToggleYellowLed), NULL);
	g_signal_connect(button[2], "clicked", G_CALLBACK(voToggleRedLed), NULL);

	g_timeout_add_seconds(2, voGetTemperature, label[3]);
	gtk_container_add(GTK_CONTAINER(window), table);
	gtk_widget_show_all(window);
	gtk_main();

	return 0;
}

static void voToggleGreenLed(GtkWidget *widget, gpointer data)
{
	static int status = OFF;

	if(status != OFF)
	{
		gtk_button_set_label(GTK_BUTTON(widget), "OFF");
		status = OFF;
		digitalWrite (GREEN_LED, OFF);
	}
	else
	{
		gtk_button_set_label(GTK_BUTTON(widget), "ON");
		status = ON;
		digitalWrite (GREEN_LED, ON);
	}
}

static void voToggleYellowLed(GtkWidget *widget, gpointer data)
{
	static int status = OFF;

	if(status != OFF)
	{
		gtk_button_set_label(GTK_BUTTON(widget), "OFF");
		status = OFF;
		digitalWrite (YELLOW_LED, OFF);
	}
	else
	{
		gtk_button_set_label(GTK_BUTTON(widget), "ON");
		status = ON;
		digitalWrite (YELLOW_LED, ON);
	}
}

static void voToggleRedLed(GtkWidget *widget, gpointer data)
{
	static int status = OFF;

	if(status != OFF)
	{
		gtk_button_set_label(GTK_BUTTON(widget), "OFF");
		status = OFF;
		digitalWrite (RED_LED, OFF);
	}
	else
	{
		gtk_button_set_label(GTK_BUTTON(widget), "ON");
		status = ON;
		digitalWrite (RED_LED, ON);
	}
}

static gboolean voGetTemperature(gpointer data)
{
	double temperature;
	char temp[30];

	temperature = GetTemperature();
	sprintf(temp, "Temperature: %.2f°C", temperature);
	gtk_label_set_text(GTK_LABEL(data), temp);
	return 1;
}
