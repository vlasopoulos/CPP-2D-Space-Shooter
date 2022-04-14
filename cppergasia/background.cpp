#include "background.h"
#include <random>

void Background::update()
{
	for (int i = 0; i < rand() % 10; i++)
	{
		stars.push_back(new Star());
	}
	
	auto star = begin(stars);
	while (star != end(stars)) 
	{
		if ((*star)->isOutsideCanvas()) 
		{
			delete * star;
			star = stars.erase(star);
		}
		else 
		{
			(*star)->update();
			++star;
		}
	}
}

void Background::draw()
{
	for (auto star : stars) 
		if(star)
			star->draw();     
}

void Background::init()
{
}
