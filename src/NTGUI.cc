#include "NetworkTesterButton.h"
#include <gtkmm-3.0/gtkmm/application.h>

int main(int argc, char * argv[]){

	
	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
	RunNetworkTester runApp;
	
	// shows the window and returns when it is closed
	return app->run(runApp);
}
