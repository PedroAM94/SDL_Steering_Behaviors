#include "SceneFlocking.h"

using namespace std;

SceneFlocking::SceneFlocking()
{
	//Agent *agent = new Agent;
	//agent->setPosition(Vector2D(640, 360));
	//agent->setTarget(Vector2D(640, 360));
	//agent->loadSpriteTexture("../res/soldier.png", 4);
	//agents.push_back(agent);
	//target = Vector2D(640, 360);


	for (int i = 0; i < numZombies; i++) {
		Agent * agent = new Agent;
		agent->setTarget(Vector2D(100 + i*100, 100));
		agent->setPosition(Vector2D(300 + i * 100, 300));
		agent->setMass(0.3f);
		agent->setColor(0, 0, 255, 255);
		agent->loadSpriteTexture("../res/zombie1.png", 8);
		agents.push_back(agent);
	}

}

SceneFlocking::~SceneFlocking()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void SceneFlocking::update(float dtime, SDL_Event *event)
{
	/* Keyboard & Mouse events */
	switch (event->type) {
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			target = Vector2D((float)(event->button.x), (float)(event->button.y));
			for (int i = 0; i < numZombies; i++) {
				agents[i]->setTarget(target);
			}
		}
		break;
	default:
		break;
	}

	for (int i=0; i < numZombies;i++) {

		float angle = (float)(atan2(agents[i]->getVelocity().y, agents[i]->getVelocity().x) * RAD2DEG);

		//Vector2D steering_force = agents[i]->Behavior()->Wander(agents[i], angle, wanderMaxChange, wanderCircleRadius, dtime) + agents[i]->Behavior()->Flocking(agents[i], agents, 200);
		Vector2D steering_force = agents[i]->Behavior()->Arrival(agents[i], target,0, dtime);
		agents[i]->update(steering_force, dtime, event);

		steering_force = agents[i]->Behavior()->Flocking(agents[i], agents, 200)*0.2f;

		agents[i]->update(steering_force, dtime);

	}

}

void SceneFlocking::draw()
{
	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);
	for (int i = 0; i < numZombies; i++) {
		agents[i]->draw();
	}
}

const char* SceneFlocking::getTitle()
{
	return "SDL Steering Behaviors :: Flocking in the night";
}