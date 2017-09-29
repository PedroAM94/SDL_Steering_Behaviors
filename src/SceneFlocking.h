#pragma once
#include <vector>
#include "Scene.h"
#include "Agent.h"

class SceneFlocking :
	public Scene
{
public:
	SceneFlocking();
	~SceneFlocking();
	void update(float dtime, SDL_Event *event);
	void draw();
	int wanderMaxChange = 80;
	int wanderCircleOffset = 80;
	int wanderCircleRadius = 70;
	float wanderAngle = 0.0f;
	const char* getTitle();
private:
	std::vector<Agent*> agents;
	Vector2D target;

};

