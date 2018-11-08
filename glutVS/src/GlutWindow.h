#pragma once

#include <vector>
#include <memory>

#include "Vector3.h"
#include "Drawable.h"

class GlutWindow
{
public:
	static void init() {
		INSTANCE = new GlutWindow();
	}

	static GlutWindow& get() {
		return *INSTANCE;
	}

	// glut triggered functions
	void display();
	void idleFunc();
	void keyboardFunc(unsigned char key, int x, int y);
	void mouseFunc(int button, int state, int x, int y);
	
private:
	static GlutWindow* INSTANCE;

	GlutWindow();
	~GlutWindow();

	std::vector<std::shared_ptr<Drawable> > drawables;

	void initialize();

	// bools for each key, init with all false
	std::vector<bool> keys;
	Vector3 cameraPos;
	Vector3 cameraLookAt;
	Vector3 cameraUp;
};

