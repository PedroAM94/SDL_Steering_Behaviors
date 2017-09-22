#include "SteeringBehavior.h"



SteeringBehavior::SteeringBehavior()
{
}


SteeringBehavior::~SteeringBehavior()
{
}

void SteeringBehavior::DrawRadius(Vector2D target, int radius) {
	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, radius, 0, 255, 0, 255);
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
	float slowingRadius = 150;
	Vector2D steeringForce;
	//DrawRadius(target, slowingRadius);
	Vector2D desiredVelocity = target - agent->getPosition();
	
	float magnitude = sqrt((desiredVelocity.x * desiredVelocity.x) + (desiredVelocity.y * desiredVelocity.y));

	if (magnitude > slowingRadius) {
		desiredVelocity.Normalize();
		desiredVelocity *= agent->getMaxVelocity();	
		//Seek(agent, target, dtime);
		draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, slowingRadius, 0, 255, 0, 255);
	}
	else{
		float factor = magnitude / slowingRadius;
		desiredVelocity.Normalize();
		desiredVelocity *= agent->getMaxVelocity() * factor;
		draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, slowingRadius, 0, 0, 255, 255);
	}
	steeringForce = (desiredVelocity - agent->getVelocity());
	steeringForce /= agent->getMaxVelocity();
	return steeringForce * agent->getMaxForce();
}

Vector2D SteeringBehavior::Arrival(Agent *agent, Agent *target, int number, float dtime)
{
	return Arrival(agent, target->position, number, dtime);
}

Vector2D SteeringBehavior::Pursue(Agent *agent, Agent *target, float dtime)
{
	float timePrediction = (target->getPosition() - agent->getPosition()).Length() / agent->getMaxVelocity();
	Vector2D targetPrediction = target->getPosition() + target->getVelocity() * timePrediction;
	Vector2D desiredVelocity = targetPrediction - agent->getPosition();
	desiredVelocity.Normalize();
	desiredVelocity *= agent->getMaxVelocity();
	Vector2D steeringForce = (desiredVelocity - agent->getVelocity());
	steeringForce /= agent->getMaxVelocity();
	return steeringForce * agent->max_force;
}
