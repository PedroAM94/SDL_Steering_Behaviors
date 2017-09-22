#include "SteeringBehavior.h"



SteeringBehavior::SteeringBehavior()
{
}


SteeringBehavior::~SteeringBehavior()
{
}

Vector2D SteeringBehavior::KinematicSeek(Agent *agent, Vector2D target, float dtime)
{
	Vector2D steering = target - agent->position;
	steering.Normalize();
	return steering * agent->max_velocity;
}

Vector2D SteeringBehavior::KinematicSeek(Agent *agent, Agent *target, float dtime)
{
	return KinematicSeek(agent, target->position, dtime);
}

Vector2D SteeringBehavior::KinematicFlee(Agent *agent, Vector2D target, float dtime)
{
	Vector2D steering = agent->position - target;
	steering.Normalize();
	return steering * agent->max_velocity;
}

Vector2D SteeringBehavior::KinematicFlee(Agent *agent, Agent *target, float dtime)
{
	return KinematicFlee(agent, target->position, dtime);
}

/* Add here your own Steering Behavior functions definitions */

Vector2D SteeringBehavior::Seek(Agent *agent, Vector2D target, float dtime)
{
	Vector2D desiredVelocity = target - agent->getPosition();
	desiredVelocity.Normalize();
	desiredVelocity *= agent->getMaxVelocity();
	Vector2D steeringForce = (desiredVelocity - agent->getVelocity());
	steeringForce /= agent->getMaxVelocity();
	return steeringForce * agent->max_force;
}

Vector2D SteeringBehavior::Seek(Agent *agent, Agent *target, float dtime)
{
	return Seek(agent, target->position, dtime);
}

Vector2D SteeringBehavior::Flee(Agent *agent, Vector2D target, float dtime)
{
	Vector2D desiredVelocity = agent->getPosition() - target;
	desiredVelocity.Normalize();
	desiredVelocity *= agent->getMaxVelocity();
	Vector2D steeringForce = (desiredVelocity - agent->getVelocity());
	steeringForce /= agent->getMaxVelocity();
	return steeringForce * agent->max_force;
}

Vector2D SteeringBehavior::Flee(Agent *agent, Agent *target, float dtime)
{
	return Flee(agent, target->position, dtime);
}

Vector2D SteeringBehavior::Arrival(Agent *agent, Vector2D target, int number, float dtime)
{
	float slowingRadius = 55;
	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, slowingRadius, 0, 255, 0, 255);
	Vector2D desiredVelocity = agent->getPosition() - target;
	float magnitude = sqrt((desiredVelocity.x * desiredVelocity.x) + (desiredVelocity.y * desiredVelocity.y));
	float factor = magnitude / slowingRadius;
	if (magnitude < slowingRadius) {
		desiredVelocity.Normalize();
		desiredVelocity *= agent->getMaxVelocity() * factor;
	}
	else{
		desiredVelocity.Normalize();
		desiredVelocity *= agent->getMaxVelocity();
	}
	Vector2D steeringForce = (agent->getVelocity()- desiredVelocity);
	steeringForce /= agent->getMaxVelocity();
	return steeringForce * agent->max_force;
}

Vector2D SteeringBehavior::Arrival(Agent *agent, Agent *target, int number, float dtime)
{
	return Arrival(agent, target->position, number, dtime);
}
