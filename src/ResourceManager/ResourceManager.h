#pragma once

#include <string>
#include <iostream>
#include <unordered_map>

template<typename T>
class ResourceManager
{
	public:

		const T& get(const std::string& nickname)
		{
			if (m_resources.find(nickname) != m_resources.end())
			{
				return m_resources[nickname];
			}
			T r;
			return r;
		}

		void add(const std::string& name, const std::string& nickname)
		{
			T r;
			if (r.loadFromFile(name))
			{
				m_resources.insert(std::make_pair(nickname, r));
			}
		}

	private:
		std::unordered_map<std::string, T> m_resources;
};