#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Animation
{
	public:
		// constructor/destructor
		Animation(); 
		~Animation(); 

		void setUp(sf::Texture& t, const int& x, const int& y,
			const int& width, const int& height, const int& tFrames);
		
		void setUp(sf::Texture& t, sf::Vector2i pos, sf::Vector2i size, const int& tFrames);

		void applyToSprite(sf::Sprite& s); 

		void applyToSprite(sf::Sprite& s, int x, int y); 

		void update(const float& dt); 

		void showOnce(); 

		int getCurrentFrame() const;
        
		int getFrameCount() const;
        
		void setFrame(const int&);

	private:
		// cycles to the next frame in frames
		void advance(); 

		// total number of frames in animation
		int nFrames; 
		// amount of time a single frame will be on screen
		static constexpr float HOLDTIME = 0.1f; 
		// image to pull sprite rects from 
		sf::Texture* texture; 
		// array of IntRects that contain boxes of each frame 
		sf::IntRect* frames;
		// current frames in cycle
		int iFrame;
		// counter to track how long a single frame has been on screen
		float time; 
		// looping var
		bool looping; 
};