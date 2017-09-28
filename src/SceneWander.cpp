#include "SceneWander.h"

using namespace std;

SceneWander::SceneWander()
{
	Agent *agent = new Agent;
	agent->setPosition(Vector2D(640,360));
	agent->setTarget(Vector2D(640, 360));
	agent->setMass(0.035);
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agent->setWanderOffset(70);
	agent->setWanderAngle(0.0f);
	agents.push_back(agent);
	target = Vector2D(640, 360);
	wanderMaxChange = 20;
	//wanderCircleOffset = 70;
	wanderCircleRadius = 80;
	//wanderAngle = 0.0f;
	wanderCircleCenter = {};
	wanderDisplacementVector = {};
}

SceneWander::~SceneWander()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void SceneWander::update(float dtime, SDL_Event *event)
{
	/* Keyboard & Mouse events */
	switch (event->type) {
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			target = Vector2D((float)(event->button.x), (float)(event->button.y));
			agents[0]->setTarget(target);
		}
		break;
	default:
		break;
	}
	Vector2D velocity = agents[0]->getVelocity();

	float angle = (float)(atan2(velocity.y, velocity.x) * RAD2DEG);

	Vector2D steering_force = agents[0]->Behavior()->Wander(agents[0], angle, wanderMaxChange, wanderCircleRadius, dtime);
	agents[0]->update(steering_force, dtime, event);
}

void SceneWander::draw()
{
	agents[0]->draw();
	draw_circle(TheApp::Instance()->getRenderer(), (int)agents[0]->getTarget().x, (int)agents[0]->getTarget().y, 15, 255, 0, 0, 255);

}

const char* SceneWander::getTitle()
{
	return "SDL Steering Behaviors :: Wander Demo";
}