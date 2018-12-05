#pragma once

#include <vector>
#include <set>
#include <memory>
#include <ctime>

#include "Camera.h"
#include "Drawable.h"
#include "Axis.h"
#include "ViewSettings.h"


enum WindowType {
	TOPDOWN = 0, PLAYERVIEW = 1
};

class GlutWindow
{
public:
	static void init(){
		INSTANCES.push_back(GlutWindow(INSTANCES.size()));
	}

	static GlutWindow& get(size_t index = 0) {
		return INSTANCES[index];
	}

	static void toggle() {
		activeWindow++;
		activeWindow %= INSTANCES.size();
		glutSetWindow(activeWindow + 1);
	}


	~GlutWindow();

	// glut triggered functions
	void display();
	void idleFunc();
	void keyboardFunc(unsigned char key, int x, int y);
	void keyboardUpFunc(unsigned char key, int x, int y);
	void specialFunc(unsigned char key, int x, int y);
	void specialUpFunc(unsigned char key, int x, int y);
	void mouseFunc(int button, int state, int x, int y);


	const ViewSettings& getViewSettings() {
		return viewSettings;
	}
private:
	static std::vector<GlutWindow> INSTANCES;
	void initialize();
	GlutWindow(size_t index);
	static int activeWindow;
	WindowType windowType;
	std::string windowTitle;

	ViewSettings viewSettings;
	
	clock_t clock_ticks_draw;
	size_t drawDelta;
	clock_t clock_ticks_update;
	size_t updateDelta;

	// previously: list of bools for each key, init with all false
	// replaced with set of keys with 'true' value
	std::set<unsigned char> keys; 
	std::set<unsigned char> specialkeys;

	std::shared_ptr<Camera> camera;

	Axis axis;
};

