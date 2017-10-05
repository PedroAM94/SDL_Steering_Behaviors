#include "SteeringBehavior.h"
#include <vector>


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
	return steering * agent->max_velocity + PerimeterAvoidance(agent);
}

Vector2D SteeringBehavior::KinematicSeek(Agent *agent, Agent *target, float dtime)
{
	return KinematicSeek(agent, target->position, dtime) + PerimeterAvoidance(agent);
}

Vector2D SteeringBehavior::KinematicFlee(Agent *agent, Vector2D target, float dtime)
{
	Vector2D steering = agent->position - target;
	steering.Normalize();
	return steering * agent->max_velocity + PerimeterAvoidance(agent);
}

Vector2D SteeringBehavior::KinematicFlee(Agent *agent, Agent *target, float dtime)
{
	return KinematicFlee(agent, target->position, dtime) + PerimeterAvoidance(agent);
}

/* Add here your own Steering Behavior functions definitions */

Vector2D SteeringBehavior::Seek(Agent *agent, Vector2D target, float dtime)
{
	Vector2D desiredVelocity = target - agent->getPosition();
	desiredVelocity.Normalize();
	desiredVelocity *= agent->getMaxVelocity();
	Vector2D steeringForce = (desiredVelocity - agent->getVelocity());
	steeringForce /= agent->getMaxVelocity();
	return steeringForce * agent->max_force + PerimeterAvoidance(agent);
}

Vector2D SteeringBehavior::Seek(Agent *agent, Agent *target, float dtime)
{
	return Seek(agent, target->position, dtime) + PerimeterAvoidance(agent);
}

Vector2D SteeringBehavior::Flee(Agent *agent, Vector2D target, float dtime)
{
	Vector2D desiredVelocity = agent->getPosition() - target;
	desiredVelocity.Normalize();
	desiredVelocity *= agent->getMaxVelocity();
	Vector2D steeringForce = (desiredVelocity - agent->getVelocity());
	steeringForce /= agent->getMaxVelocity();
	return steeringForce * agent->max_force + PerimeterAvoidance(agent);
}

Vector2D SteeringBehavior::Flee(Agent *agent, Agent *target, float dtime)
{
	return Flee(agent, target->position, dtime) + PerimeterAvoidance(agent);
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
	return steeringForce * agent->getMaxForce() + PerimeterAvoidance(agent);
}

Vector2D SteeringBehavior::Arrival(Agent *agent, Agent *target, int number, float dtime)
{
	return Arrival(agent, target->position, number, dtime) + PerimeterAvoidance(agent) + PerimeterAvoidance(agent);
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
	return steeringForce * agent->max_force + PerimeterAvoidance(agent);
}

Vector2D SteeringBehavior::Evade(Agent *agent, Agent *target, float dtime)
{
	float timePrediction = (target->getPosition() - agent->getPosition()).Length() / agent->getMaxVelocity();
	Vector2D targetPrediction = target->getPosition() + target->getVelocity() * timePrediction;
	Vector2D desiredVelocity = agent->getPosition() - targetPrediction;
	desiredVelocity.Normalize();
	desiredVelocity *= agent->getMaxVelocity();
	Vector2D steeringForce = (desiredVelocity - agent->getVelocity());
	steeringForce /= agent->getMaxVelocity();
	return (steeringForce * agent->max_force) +PerimeterAvoidance(agent);
}

Vector2D SteeringBehavior::Wander(Agent*agent, float angle, float wanderMaxChange, float radius, float dtime) 
{

		Vector2D circleCenter = agent->getPosition() + agent->getVelocity().Normalize()*agent->getWanderOffset();
		DrawRadius(circleCenter, radius);

	if (agent->timer > 0.5f)
	{
		//float randomMax = (rand() % (int)wanderMaxChange - rand() % (int)wanderMaxChange);
		float randomMax = (rand() % ((int)wanderMaxChange*2) - (int)wanderMaxChange);

		//float randomMax = rand()*wanderMaxChange;


		agent->setWanderAngle((agent->getWanderAngle() + randomMax));

		Vector2D newPos;
		//newPos.x = newPos.y = 0;
		//
		newPos.x = (agent->getPosition() + agent->getVelocity().Normalize()*agent->getWanderOffset()).x + radius*cos((agent->getWanderAngle())*DEG2RAD);
		newPos.y = (agent->getPosition() + agent->getVelocity().Normalize()*agent->getWanderOffset()).y + radius*sin((agent->getWanderAngle())*DEG2RAD);
		//
		agent->setTarget(newPos);

		agent->timer = 0;
		return Seek(agent, newPos, dtime) + PerimeterAvoidance(agent);
	}
	agent->timer += dtime;
	return Seek(agent, agent->getTarget(), dtime) + PerimeterAvoidance(agent);


}

Vector2D SteeringBehavior::PerimeterAvoidance(Agent* agent) {
	Vector2D perimeter = TheApp::Instance()->getWinSize();
	float perimeterBorder = 100;
	Vector2D desiredVelocity = (0, 0);
	Vector2D steeringForce = (0,0);

	if (agent->position.x < perimeterBorder) {
		desiredVelocity.x = agent->getMaxVelocity();
	}
	else if (agent->position.x>perimeter.x - perimeterBorder) {
		desiredVelocity.x = -agent->getMaxVelocity();

	}
	if (agent->position.y<perimeterBorder) {
		desiredVelocity.y = agent->getMaxVelocity();
	}
	else if (agent->position.y>perimeter.y-perimeterBorder) {
		desiredVelocity.y = -agent->getMaxVelocity();

	}
	if (desiredVelocity.Length()>0.0f){
		steeringForce = desiredVelocity - agent->getVelocity();
		steeringForce /= agent->getMaxVelocity();
		steeringForce *= agent->getMaxForce();
	}
	return steeringForce;
}

Vector2D SteeringBehavior::Separation( Agent* agent,std::vector<Agent*> agents,float NEIGHBOUR_RADIUS) {
	int neighbourCount = 0;
	Vector2D separationVector = {};
	for (int i = 0; i < (int)agents.size(); i++) {
		if (agents[i]->getPosition() != agent->getPosition() || agents[i]->getVelocity() != agent->getVelocity()) {
			if (Vector2D::Distance(agents[i]->getPosition(), agent->getPosition()) < NEIGHBOUR_RADIUS) {
				separationVector += agent->getPosition() - agents[i]->getPosition();
				++neighbourCount;
			}
		}
	}
	if (neighbourCount != 0)
	separationVector /= neighbourCount;

	return separationVector.Normalize();
}

Vector2D SteeringBehavior::Cohesion(Agent* agent, std::vector<Agent*> agents, float NEIGHBOUR_RADIUS) {
	int neighbourCount = 0;
	Vector2D averagePosition = {};
	for (int i = 0; i < (int)agents.size(); i++) {
		if (agents[i]->getPosition() != agent->getPosition() || agents[i]->getVelocity() != agent->getVelocity()) {
			if (Vector2D::Distance(agents[i]->getPosition(), agent->getPosition()) < NEIGHBOUR_RADIUS) {
				averagePosition += agent->getPosition();
				++neighbourCount;
			}
		}
	}

	if (neighbourCount != 0)
	averagePosition /= neighbourCount;

	averagePosition -= agent->getPosition();
	return averagePosition.Normalize();
}
Vector2D SteeringBehavior::Allignment(Agent* agent, std::vector<Agent*> agents, float NEIGHBOUR_RADIUS) {
	int neighbourCount = 0;
	Vector2D averageVelocity = {};
	for (int i = 0; i < (int)agents.size(); i++) {
		if (agents[i]->getPosition() != agent->getPosition() || agents[i]->getVelocity() != agent->getVelocity()) {
			if (Vector2D::Distance(agents[i]->getPosition(), agent->getPosition()) < NEIGHBOUR_RADIUS) {
				averageVelocity += agent->getVelocity();
				++neighbourCount;
			}
		}
	}

	if(neighbourCount!=0)
	averageVelocity /= neighbourCount;

	return averageVelocity.Normalize();
}

Vector2D SteeringBehavior::Flocking(Agent* agent, std::vector<Agent*> agents, float NEIGHBOUR_RADIUS) {
	float K_SEPARATION_FORCE = 1.9f;
	float K_COHESION_FORCE = 0.8f;
	float K_ALIGNMENT_FORCE = 0.6f;

	//DrawRadius(agent->position,NEIGHBOUR_RADIUS);

	return (Separation(agent, agents, NEIGHBOUR_RADIUS)*K_SEPARATION_FORCE + Cohesion(agent, agents, NEIGHBOUR_RADIUS) * K_COHESION_FORCE + Allignment(agent, agents, NEIGHBOUR_RADIUS)* K_ALIGNMENT_FORCE)*agent->getMaxForce();
}
