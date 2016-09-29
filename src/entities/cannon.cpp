#include "cannon.hpp"

Cannon::Cannon(Vector p, Brain brain)
{
	this->p = p;
	this->brain = brain;

	rectangle.w = CANNON_WIDTH;
	rectangle.h = CANNON_HEIGHT;

	firing = false;
	best = false;
}

void Cannon::update(vector<Alien> &aliens)
{
	//TODO Shouldn't this matrix always be a constants size?
	Matrix matrix = Matrix(1,aliens.size()*2+1);//* bullets.size() * 2 + 1);

	int i = 0;
	for (Alien alien : aliens)
	{
		matrix.set(0,i++,alien.get().x);
		matrix.set(0,i++,alien.get().y);
	}	

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

	if (v.x > MAX_CANNON_SPEED) v.x = MAX_CANNON_SPEED; 
	else if (v.x < -MAX_CANNON_SPEED) v.x = -MAX_CANNON_SPEED; 

	p += v;
	if (p.x < 0) p.x = SCREEN_WIDTH;
	else if (p.x > SCREEN_WIDTH) p.x = 0;

	rectangle.x = round(p.x);
	rectangle.y = round(p.y);
}

void Cannon::draw(SDL_Renderer* renderer)
{
	if (is_best()) SDL_SetRenderDrawColor(renderer, RED, 255);
	else SDL_SetRenderDrawColor(renderer, BLUE, 255);
	SDL_RenderFillRect(renderer, &rectangle);
}

void Cannon::new_position()
{
	int rand_x = rand() % SCREEN_WIDTH;
	this->p = Vector(rand_x, CANNON_SPACER);
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

Cannon* Cannon::create(Vector p, Brain brain)
{
	return new Cannon(p, brain);
}

