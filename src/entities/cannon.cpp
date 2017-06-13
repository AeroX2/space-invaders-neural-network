#include "cannon.hpp"

Cannon::Cannon(Vector p, Brain brain)
{
	this->p = p;
	this->brain = brain;

	rectangle.w = CANNON_WIDTH;
	rectangle.h = CANNON_HEIGHT;

	firing = false;
	fired = false;
	best = false;
}

void Cannon::update(Alien alien)
{
	//TODO Shouldn't this matrix always be a constants size?
	Matrix matrix = Matrix(1,7+1);//* bullets.size() * 2 + 1);

	Vector normalised_position = p;
	Vector normalised_velocity = v.normalise();

	normalised_position.x = (normalised_position.x) / (SCREEN_WIDTH);
	normalised_position.y = (normalised_position.y) / (SCREEN_HEIGHT);

	Vector normalised_alien = alien.get();

	normalised_alien.x = (normalised_alien.x) / (SCREEN_WIDTH);
	normalised_alien.y = (normalised_alien.y) / (SCREEN_HEIGHT);

	int i = 0;
	matrix.set(0,i++,normalised_position.x);
	matrix.set(0,i++,normalised_position.y);
	matrix.set(0,i++,normalised_velocity.x);
	matrix.set(0,i++,normalised_velocity.y);
	matrix.set(0,i++,fired);

	matrix.set(0,i++,normalised_alien.x);
	matrix.set(0,i++,normalised_alien.y);

	/*for (Bullet bullet: bullets)
	{
		matrix.set(0,i++,bullet.get().x);
		matrix.set(0,i++,bullet.get().y);
	}*/	
	
	matrix.set(0,i,-1); //faster than add_bias (probably)
	Matrix output = brain.update(matrix);
	if (output.get_matrix().size() != BRAIN_OUTPUT_LEN+1) throw;

	if (output.get(0,1) > 0.5) firing = true;
	float speed = (output.get(0,0) - 0.5) * CANNON_SPEED;
	v.x += speed;

	if (v.x < 0.01 && v.x > -0.01) get_fitness() *= 0.8;

	if (v.x > MAX_CANNON_SPEED) v.x = MAX_CANNON_SPEED; 
	else if (v.x < -MAX_CANNON_SPEED) v.x = -MAX_CANNON_SPEED; 

	p += v;
	if (p.x < 0) 
	{
		p.x = 0;
		touched = true;
	}
	else if (p.x > SCREEN_WIDTH) 
	{
		p.x = SCREEN_WIDTH;
		touched = true;
	}

	rectangle.x = round(p.x) - rectangle.w / 2;
	rectangle.y = round(p.y) - rectangle.h / 2;
}

void Cannon::draw(SDL_Renderer* renderer)
{
	if (is_best()) SDL_SetRenderDrawColor(renderer, RED, 255);
	else SDL_SetRenderDrawColor(renderer, BLUE, 255);
	SDL_RenderFillRect(renderer, &rectangle);
}

void Cannon::new_position()
{
	this->p = Vector(SCREEN_WIDTH / 2, SCREEN_HEIGHT - CANNON_HEIGHT - CANNON_SPACER);
}

Vector& Cannon::get()
{
	return p;
}

void Cannon::set(Vector p)
{
	this->p = p;
}

Brain& Cannon::get_brain()
{
	return brain;
}

void Cannon::set_brain(Brain brain)
{
	this->brain = brain;
}

bool Cannon::is_touched()
{
	return touched;
}

bool Cannon::is_best()
{
	return best;
}

void Cannon::set_best(bool best)
{
	this->best = best;
}

bool Cannon::is_firing()
{
	return firing;
}

void Cannon::set_firing(bool firing )
{
	this->firing = firing ;
}

bool Cannon::is_fired()
{
	return fired;
}

void Cannon::set_fired(bool fired)
{
	this->fired = fired;
}

float& Cannon::get_fitness()
{
	return brain.get_fitness();
}

void Cannon::set_fitness(float fitness)
{
	brain.set_fitness(fitness);
}

Cannon* Cannon::create(Vector p, Brain brain)
{
	return new Cannon(p, brain);
}

