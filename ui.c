GtkWidget *window;
GtkWidget *grid;
GtkWidget *button;
GtkWidget *label;
GtkWidget *vbox;
GtkWidget *hbox;
GtkWidget *cbutton;

unsigned char button_str[30]= "";
unsigned char caption[150]= "";
unsigned char t9_str[35]= "";
unsigned char manual_str[35]= "";

int x1 = 0;
int x2 = 0;
int y = 0;
int z = 0;
int ytemp = 0;
int y2 = 0;

GDateTime *LastPressed = NULL;

int getDigit(const char* str) {
	int i = 0;
	while(isdigit(str[i]) == 0 || str[i] == '\0') {
		i++;
	}
	if(str[i] == '\0') return (-1);
	return (str[i] - '0');
}

/*int deleteChar(unsigned char* str, int *x) {
	g_print("%d\n", *x);
	if(str == NULL) return 0;
	if(x > 0) x--;
	str[*x] = '\0';
	if(str[*x-1] == 195) {
		x--;
		str[*x] = '\0';
	}
	return 1;
}*/

void button_clicked(GtkButton *button, gpointer data) {

	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cbutton))) {
		//Modo com algoritmo de previsão T9
		manual_str[0] = '\0';
		if(gtk_button_get_label(button)[0] == '<') {
			g_print("BACKSPACE\n");
			z /= 10;

			if(x2 > 0) x2--;
			t9_str[x2] = '\0';

			if(y > 0) y--;
			caption[y] = '\0';
			if(caption[y-1] == 195) {
				g_print("=195\n");
				y--;
				caption[y] = '\0';
			}
			g_print("%d\n", y);
			//deleteChar(t9_str, &x2);
			//deleteChar(caption, &y);

			g_print("%s\n", caption);
			searchWord(t9_str, z);
		} else if(getDigit(gtk_button_get_label(button)) == 0) {
			z = 0;
			x2 = 0;
			t9_str[0] = '\0';
			caption[y++] = ' ';
			ytemp = y;
		} else if(getDigit(gtk_button_get_label(button)) == 1) {
			contador++;
			searchWord(t9_str, z);
		} else {			
			z = (z * 10) + getDigit(gtk_button_get_label(button));
			searchWord(t9_str, z);
			g_print("x2_search_end: %d\n", x2);
		}

		y = ytemp;
		while(t9_str[x2] != '\0') {
			if(y>0 && caption[y-1]>192) {
				caption[y--] = 0;
				caption[y] = 0;
			}
			if(t9_str[x2] == 195) {
				caption[y++] = t9_str[x2++];
				caption[y] = t9_str[x2];
			} else {
				caption[y] = t9_str[x2];
			}
			y++;
			x2++;
		}
		g_print("x2: %d\n", x2);
		x2 = 0;
	} else {
		//Modo manual
		t9_str[0] = '\0';
		if(gtk_button_get_label(button)[0] == '<') {
			if(caption[y-1] == 195) {
				caption[y] = '\0';
				y--;
			}
			caption[y] = '\0';
			if(y != -1) y--;
		} else if(getDigit(gtk_button_get_label(button)) == 0) {
			//space
			manual_str[0] = '\0';
			caption[y++] = ' ';
			ytemp = y;
		} else if(gtk_button_get_label(button)[0] == '*') {
			//Adicionar palavra ao dicionário
			//if(strlen())
		} else if(getDigit(gtk_button_get_label(button)) != 1) {
			switch(getDigit(gtk_button_get_label(button))) {
				case 2:
					strcpy((char*) button_str, "abcàáãâçABCÀÁÃÂÇ2");
					break;
				case 3:
					strcpy((char*) button_str, "defèéêDEFÈÉÊ3");
					break;
				case 4:
					strcpy((char*) button_str, "ghiíìîGHIÌÍÎ4");
					break;
				case 5:
					strcpy((char*) button_str, "jklJKL5");
					break;
				case 6:
					strcpy((char*) button_str, "mnoòóõôMNOÒÓÕÔ6");
					break;
				case 7:
					strcpy((char*) button_str, "pqrsPQRS7");
					break;
				case 8:
					strcpy((char*) button_str, "tuvùúûTUVÙÚÛ8");
					break;
				case 9:
					strcpy((char*) button_str, "wxyzWXYZ9");
					break;
				case 0:
					strcpy((char*) button_str, " ");
					break;
				default:
					break;
			}

			GTimeSpan diff;
			GDateTime *now = g_date_time_new_now_local();

			if(LastPressed != NULL && (gtk_button_get_label(button)[0] != '<')) {
				diff = g_date_time_difference(now, LastPressed);
				if(diff<1000000 && button_str[x1]==caption[y]) {
					if(x1<strlen((const char*) button_str)-1 && button_str[x1]<128) x1++;
					else if(x1<strlen((const char*) button_str)-2 && button_str[x1]>127) x1++;
					else x1=0;
				} else {
					x1=0;
					y++;
				}
			}
			if(y>0 && caption[y-1]>192) {
				caption[y--] = 0;
				caption[y] = 0;
			}

			if(button_str[x1]>127) {
				caption[y++] = button_str[x1++];
				caption[y] = button_str[x1];
			} else {
				caption[y] = button_str[x1];
			}

			/*if(button_str[x1]>127) {
				manual_str[y2++] = button_str[x1++];
				manual_str[y2] = button_str[x1];
			} else {
				manual_str[y2] = button_str[x1];
			}

			if(manual_str[x1]>127) {
				caption[y++] = manual_str[x1++];
				caption[y] = manual_str[x1];
			} else {
				caption[y] = manual_str[x1];
			}*/

			LastPressed = g_date_time_new_now_local();
		}
	}
	gtk_label_set_text((GtkLabel *) label, (const gchar*) caption);
}

void closeFunction() {
	saveFile();
	gtk_main_quit();
}

void ui(int argc, char *argv[]) {

	gtk_init(&argc, &argv);

	gchar *values[12] = {
		"1\n∞", "  2\nabc", "  3\ndef",
		"  4\nghi", " 5\njkl", "   6\nmno",
		"    7\npqrs", "  8\ntuv", "    9\nwxyz",
		"*\n", "    0\nspace", "#\n"
	};

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Projeto 2");
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);

	label = gtk_label_new(NULL);

	grid = gtk_grid_new();
	gtk_grid_set_row_spacing(GTK_GRID(grid), 2);
	gtk_grid_set_column_spacing(GTK_GRID(grid), 2);

	int i = 0;
	int j = 0;
	int pos = 0;

	for(i=0; i<4; i++) {
		for(j=0; j<3; j++) {
			vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
			button = gtk_button_new_with_label(values[pos]);
			gtk_container_add(GTK_CONTAINER(vbox), button);
			gtk_grid_attach(GTK_GRID(grid), vbox, j, i, 1, 1);
			gtk_widget_set_size_request(button, 80, 70);
			g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(button_clicked), NULL);
			pos++;
		}
	}

	cbutton = gtk_check_button_new_with_label("T9 Toogle");
	vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	button = gtk_button_new_with_label("<-");
	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(button_clicked), NULL);
	gtk_widget_set_size_request(button, 0, 35);
	gtk_box_pack_start(GTK_BOX(vbox), label, TRUE, TRUE, 25);
	gtk_box_pack_start(GTK_BOX(hbox), button, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(hbox), cbutton, TRUE, TRUE, 0);
	gtk_box_set_spacing(GTK_BOX(hbox), 15);
	gtk_box_set_homogeneous(GTK_BOX(hbox), TRUE);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, TRUE, TRUE, 10);
	gtk_label_set_xalign(GTK_LABEL(label), 0);
	gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
	gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
	gtk_box_pack_start(GTK_BOX(vbox), grid, TRUE, TRUE, 0);
	gtk_container_add(GTK_CONTAINER(window), vbox);

	g_signal_connect(window, "destroy", G_CALLBACK(closeFunction), NULL);

	gtk_widget_show_all(window);	

	gtk_main();
}