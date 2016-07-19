#include "logic.hpp"

Logic::Logic()
{
	//Seed random number generator
	srand(time(NULL));	

	for (int i = 0; i < ALIEN_POP_HEIGHT; i++)
	{
		for (int ii = 0; ii < ALIEN_POP_WIDTH; ii++)
		{
			Vector p = Vector(ii * ALIEN_WIDTH + ALIEN_SPACING,i * ALIEN_HEIGHT + ALIEN_SPACING);
			Alien new_alien = Alien(p);
			aliens.push_back(new_alien);
		}	
	}

	Vector p;
	Brain new_brain;
	for (int i = 0; i < CANNON_POPULATION; i++)
	{
		int rand_x = rand() % SCREEN_WIDTH;
		p = Vector(rand_x, CANNON_SPACER);
		new_brain = Brain();
		Cannon new_cannon = Cannon(p, new_brain);
		cannons.push_back(new_cannon);
	}

	/*rand_x = rand() % SCREEN_WIDTH;
	rand_y = rand() % SCREEN_HEIGHT;
	p = Vector(rand_x, rand_y);
	new_brain = Brain();

	//Control_Cannon* control_cannon = Control_Cannon::create(p,new_brain);
	//cannons.push_back(reference_wrapper<Cannon>(*control_cannon));*/

	ticks = 0;
	max_fitness = 0;
}

void Logic::update(double delta)
{
	for (Bullet& bullet : bullets) bullet.update();

	for (Alien& alien : aliens)
	{
		alien.update();
		for (Bullet& bullet : bullets)
		{
			Vector alien_p = alien.get();
			Vector bullet_p = bullet.get();
			if (alien_p.x - 50 < bullet_p.x && 
				alien_p.x + 50 > bullet_p.x && 
				alien_p.y - 50 < bullet_p.y && 
				alien_p.y + 50 > bullet_p.y)
			{
				float distance = (alien_p - bullet_p).distance();
				//cout << "distance: " << distance << endl;
				if (distance < HIT_DISTANCE)
				{
					cannons[bullet.get_id()].get().get_brain().increase_fitness(1);
				}
			}	
		}
	}

	for (int i = 0; i < cannons.size(), i++)
	{
		Cannon& cannon = cannons[i].get();
		cannon.update(aliens);
		if (cannon.is_firing())
		{
			Vector p = Vector(cannon.get().x, cannon.get().y);
			Bullet bullet = Bullet(p, i);
		}
		
		if (cannon.get_brain().get_fitness() > max_fitness)
		{
			max_fitness = cannon.get_brain().get_fitness();
			for (auto reference : cannons) 
			{
				Cannon& cannon2 = reference.get();
				cannon2.set_best(false);
			}
			cannon.set_best(true);
		}

		cannon_p = cannon.get();
		if (cannon_p.x > SCREEN_WIDTH) cannon_p.x = 0;
		else if (cannon_p.x < 0) cannon_p.x = SCREEN_WIDTH;

		//TODO Probably don't need this test later
		cannon.set(cannon_p);
	}

	ticks += 1;
	if (ticks > EPOCH_TICK_OVER)
	{
		ticks = 0;
		max_fitness = 0;
		vector<Brain> population = vector<Brain>();
		for (auto reference : cannons) 
		{
			Cannon& cannon = reference.get();	
			population.push_back(cannon.get_brain());
		}
		population = Controller::epoch(population);

		//Remember the minus 1 if you add a control cannon
		for (int i = 0; i < cannons.size(); i++) 
		{
			Cannon& cannon = cannons[i].get();
			cannon.set_brain(population[i]);
			cannon.get_brain().set_fitness(0);
			cannon.set_best(false);
			cannon.new_position();
		}
		for (Alien& alien : aliens) alien.new_position();
	}
}

void Logic::draw(SDL_Renderer* renderer)
{
	for (Alien alien : aliens) alien.draw(renderer);
	for (Bullet bullet : bullets) bullet.draw(renderer);
	for (auto reference : cannons) 
	{
		Cannon& cannon = reference.get();	
		cannon.draw(renderer);
	}
}
