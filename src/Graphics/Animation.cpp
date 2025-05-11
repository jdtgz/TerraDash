#include "Animation.h"


Animation::Animation()
{  
	texture = nullptr; 
	frames = nullptr; 
	nFrames = 0; 
	iFrame = 0;
	time = 0.0f; 
	looping = true; 
}


Animation::~Animation()
{
	delete[] frames;
}


// Initializes the TextureRects of the animation
void Animation::setUp(sf::Texture& t, const int& x, const int& y,
	const int& width, const int& height, const int& tFrames)
{
	texture = &t;
	nFrames = tFrames;
	frames = new sf::IntRect[nFrames];

	// cycle through and initialize all the frames 
	// *No spacing between sprite boxes 
	for (int i = 0; i < nFrames; i++)
	{
		frames[i] = sf::IntRect({x + i * width, y}, {width, height});
	}
}


void Animation::setUp(sf::Texture& t, sf::Vector2i pos, sf::Vector2i size, const int& tFrames)
{
	texture = &t;
	nFrames = tFrames;
	frames = new sf::IntRect[nFrames];

	// cycle through and initialize all the frames 
	// *No spacing between sprite boxes 
	for (int i = 0; i < nFrames; i++)
	{
		frames[i] = sf::IntRect({pos.x + i * size.x, pos.y}, {size.x, size.y});
	}
}


// applies the right textureRect to the animation and scales it
void Animation::applyToSprite(sf::Sprite& s)
{
	s.setTexture(*texture);
	s.setTextureRect(frames[iFrame]);
	s.setOrigin({s.getLocalBounds().size.x / 2,s.getLocalBounds().size.y / 2});
	s.setScale({1, 2});
}


// applies the right textureRect to the animation and scales it by {x ,y}
void Animation::applyToSprite(sf::Sprite& s, int x, int y)
{
	s.setTexture(*texture);
	s.setTextureRect(frames[iFrame]);
	s.setOrigin({s.getLocalBounds().size.x / 2,s.getLocalBounds().size.y / 2});
	s.setScale({float(x), float(y)});
}


// cycle animation based on dt
void Animation::update(const float& dt)
{
	time += dt; 
	while (time >= HOLDTIME)
	{
		time -= HOLDTIME; 
		advance(); 
	}
}


// Prevents the animation to loop 
void Animation::showOnce()
{
	looping = false; 
}


void Animation::setFrame(const int& f)
{
	iFrame = f % nFrames;
}


int Animation::getCurrentFrame() const
{
	return iFrame; 
}


int Animation::getFrameCount() const
{
	return nFrames;
}


// advances the frame of the animation
void Animation::advance()
{
	if (++iFrame >= nFrames)
	{
		if(looping)
			iFrame = 0; 
	}
}