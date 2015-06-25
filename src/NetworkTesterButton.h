#ifndef _RUN_NETWORK_TESTER_
#define _RUN_NETWORK_TESTER_

#include <gtkmm-3.0/gtkmm/button.h>
#include <gtkmm-3.0/gtkmm/window.h>
#include "callNetworkTester.h"
#include <iostream>

class RunNetworkTester : public Gtk::Window {

public:
	RunNetworkTester(); // this is the hello world button
	virtual ~RunNetworkTester();
protected:

	// signal handlers
	void on_button_clicked();
	
	//Member widgets
	Gtk::Button m_button;
};

// this is the hello world button. it inherits the button class
RunNetworkTester::RunNetworkTester() : m_button("Run NetworkTester") {
	// sets the border of the window
	set_border_width(10);
	
	// When the button recieves the "clicked" signal, it will call the
	// on_button_clicked() method defined below
	
	m_button.signal_clicked().connect(sigc::mem_fun(* this, &RunNetworkTester::on_button_clicked));
	
	// this packs the button into the Window (a container)
	add(m_button);
	
	// the final step is to display the newly created widget....
	m_button.show();
}

RunNetworkTester::~RunNetworkTester(){
	// we do nothing here	
}

// this is the action to be done when the button is clicked!
void RunNetworkTester::on_button_clicked(){
	
	callNetworkTester();
	std::cout << "Hello World" << std::endl;
}

#endif // GTKMM_EXAMPLE_HELLOWORLD_H
