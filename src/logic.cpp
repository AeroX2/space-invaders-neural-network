#include "logic.hpp"
#include "main.hpp"

Logic::Logic()
{
	ticks = 0;
	max_fitness = 0;
}

Logic::~Logic()
{
	for (auto reference : cannons)
	{
		delete &reference.get();
	}
}

void Logic::init()
{
	reset_aliens();

	Vector p;
	Brain new_brain;
	for (int i = 0; i < CANNON_POPULATION; i++)
	{
		int rand_x = rand() % SCREEN_WIDTH;
		p = Vector(rand_x, SCREEN_HEIGHT-CANNON_HEIGHT-CANNON_SPACER);
		new_brain = Brain();
		Cannon* new_cannon = Cannon::create(p, new_brain);
		cannons.push_back(reference_wrapper<Cannon>(*new_cannon));
	}

	/*rand_x = rand() % SCREEN_WIDTH;
	rand_y = rand() % SCREEN_HEIGHT;
	p = Vector(rand_x, rand_y);
	new_brain = Brain();

	//Control_Cannon* control_cannon = Control_Cannon::create(p,new_brain);
	//cannons.push_back(reference_wrapper<Cannon>(*control_cannon));*/

	ticks = 0;
	max_fitness = 0;
	current_player = 0;
}

void Logic::update()
{
	Cannon& cannon = cannons[current_player].get();
	Vector cannon_p = cannon.get();

	Alien closest_alien = aliens[0];
	float min_distance = (closest_alien.get() - cannon_p).distance();

	//I dont want current_player being updated and giving the wrong player id
	if (cannon.is_firing())
	{
		Bullet bullet = Bullet(cannon.get().copy(), current_player);

		if (!cannons[bullet.get_id()].get().is_fired())
		{
			cannons[bullet.get_id()].get().set_fired(true);
			bullets.push_back(bullet);
		}
	}

	vector<int> remove_bullets;
	vector<int> remove_aliens;
	ticks++;

	for (size_t alien_id = 0; alien_id < aliens.size(); alien_id++)
	{
		Alien& alien = aliens[alien_id];
		Vector alien_p = alien.get();
		SDL_Rect alien_box = alien.getbox();

		if (ticks > ALIEN_TICKS_TO_MOVE) alien.update();

		if (alien_p.x <= 0 || alien_p.x >= SCREEN_WIDTH)
		{
			for (Alien& alien2 : aliens)
			{
				alien2.getv().x *= -1;
				alien2.get().x += alien2.getv().x * 2;
				alien2.get().y += ALIEN_HEIGHT;
			}
		}
		if (alien_p.y >= SCREEN_HEIGHT) 
		{
			current_player++;
			remove_aliens.clear();
			remove_bullets.clear();
			reset_aliens();
			break;
		}

		for (size_t bullet_id = 0; bullet_id < bullets.size(); bullet_id ++) 
		{
			Bullet bullet = bullets[bullet_id];
			Vector bullet_p = bullet.get();
			SDL_Rect bullet_box = bullet.getbox();

			if (abs(alien_p.x - bullet_p.x) * 2 <= (alien_box.w + bullet_box.w) &&
				abs(alien_p.y - bullet_p.y) * 2 <= (alien_box.h + bullet_box.h))
			{
				for (Alien& alien2 : aliens) alien2.getv().x *= 1.02;

				cannons[bullet.get_id()].get().set_fired(false);
				cannons[bullet.get_id()].get().get_fitness() += 1;

				remove_bullets.push_back(bullet_id);
				remove_aliens.push_back(alien_id);
			}
		}

		float distancez = (alien_p - cannon_p).distance();
		if (distancez < min_distance)
		{
			min_distance = distancez;
			closest_alien = alien;
		}
	}
	
	if (ticks > ALIEN_TICKS_TO_MOVE) ticks = 0;

	for (size_t bullet_id = 0; bullet_id < bullets.size(); bullet_id ++) 
	{
		Bullet& bullet = bullets[bullet_id];
		bullet.update();
		if (bullet.get().y < 0) 
		{
			cannons[bullet.get_id()].get().set_fired(false);
			float& fitness = cannons[bullet.get_id()].get().get_fitness();
			if (fitness > 0.01) fitness *= 0.65;
			remove_bullets.push_back(bullet_id);
		}
	}

	//sort(remove_bullets.begin(), remove_bullets.end());
	remove_bullets.erase(unique(remove_bullets.begin(), remove_bullets.end()), remove_bullets.end());

	//sort(remove_aliens.begin(), remove_aliens.end());
	remove_aliens.erase(unique(remove_aliens.begin(), remove_aliens.end()), remove_aliens.end());

	//Remove bullets
	for (int bullet : remove_bullets) bullets.erase(bullets.begin()+bullet);
	for (int alien : remove_aliens) aliens.erase(aliens.begin()+alien);

	if (aliens.size() <= 0)
   	{
		current_player++;
		remove_aliens.clear();
		remove_bullets.clear();
		reset_aliens();
	}

	cannon.update(closest_alien);

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

	//Epoch
	if (current_player > cannons.size()-1)
	{
		max_fitness = 0;
		current_player = 0;

		vector<Brain> population = vector<Brain>();
		for (auto reference : cannons) 
		{
			Cannon& cannon = reference.get();	
			population.push_back(cannon.get_brain());
		}
		population = Controller::epoch(population);

		//Remember the minus 1 if you add a control cannon
		for (size_t i = 0; i < cannons.size(); i++) 
		{
			Cannon& cannon = cannons[i].get();
			cannon.set_brain(population[i]);
			cannon.get_fitness() = 0;
			cannon.set_best(false);
			cannon.set_fired(false);
			cannon.set_firing(false);
			cannon.new_position();
		}
		reset_aliens();
	}
}

void Logic::draw(SDL_Renderer* renderer)
{
	for (Alien alien : aliens) alien.draw(renderer);
	for (Bullet bullet : bullets) bullet.draw(renderer);
	Cannon& cannon = cannons[current_player].get();	
	cannon.draw(renderer);

	Main::draw_font("Current fitness: " + to_string(cannon.get_fitness()), 10, 10);
}

void Logic::reset_aliens()
{
	bullets.clear();
	aliens.clear();
	for (int i = 0; i < ALIEN_POP_HEIGHT; i++)
	{
		for (int ii = 0; ii < ALIEN_POP_WIDTH; ii++)
		{
			int x = ALIEN_STARTING_X + ii * (ALIEN_WIDTH + ALIEN_SPACING);
			int y = ALIEN_STARTING_Y + i * (ALIEN_HEIGHT + ALIEN_SPACING);
			Vector p = Vector(x,y);
			Alien new_alien = Alien(p);
			aliens.push_back(new_alien);
		}	
	}
}
