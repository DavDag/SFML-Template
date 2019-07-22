#pragma once

#include <SFML/Graphics.hpp>

#include "..//Utils/NonCopyable.h"
#include "..//Utils/NonMoveable.h"
#include "ResourceManager.h"

class ResourceHolder
{
	private:
		ResourceHolder() { }

	public:
		static ResourceHolder& get()
		{
			static ResourceHolder holder;
			return holder;
		}

		static void loadAll()
		{
			ResourceHolder::get().fonts.add("resources//fonts//RobotoMono-Regular.ttf", "default");
		}

	public:
		ResourceManager<sf::Font>			fonts;
		ResourceManager<sf::Texture>		textures;
//		ResourceManager<sf::SoundBuffer>	sounds;
};