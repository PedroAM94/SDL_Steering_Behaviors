#pragma once
#include "Agent.h"
#include "Vector2D.h"
#include <vector>
class Agent;

class SteeringBehavior
{
public:
	SteeringBehavior();
	~SteeringBehavior();
	void DrawRadius(Vector2D target, int radius);
	Vector2D KinematicSeek(Agent *agent, Vector2D target, float dtime);
	Vector2D KinematicSeek(Agent *agent, Agent *target, float dtime);
	Vector2D KinematicFlee(Agent *agent, Vector2D target, float dtime);
	Vector2D KinematicFlee(Agent *agent, Agent *target, float dtime);

	/* Add here your own Steering Behavior functions declarations */
	Vector2D Seek(Agent *agent, Vector2D target, float dtime);
	Vector2D Seek(Agent *agent, Agent *target, float dtime);
	Vector2D Flee(Agent *agent, Vector2D target, float dtime);
	Vector2D Flee(Agent *agent, Agent *target, float dtime);
	Vector2D Arrival(Agent *agent, Vector2D target,int number , float dtime);
	Vector2D Arrival(Agent *agent, Agent *target,int number, float dtime);
	Vector2D Pursue(Agent *agent, Agent *target, float dtime);
	Vector2D Evade(Agent *agent, Agent *target, float dtime);
	Vector2D Wander(Agent*agent, float angle, float wanderMaxChange,float radius,float dtime);
	Vector2D PerimeterAvoidance(Agent* agent);
	Vector2D Flocking(Agent* agent, std::vector<Agent> agents, float NEIGHBOUR_RADIUS);
	Vector2D Separation(Agent* agent,std::vector<Agent> agents,float NEIGHBOUR_RADIUS);
	Vector2D Cohesion(Agent* agent, std::vector<Agent> agents, float NEIGHBOUR_RADIUS);
	Vector2D Allignment(Agent* agent, std::vector<Agent> agents, float NEIGHBOUR_RADIUS);
	//etc...

};
