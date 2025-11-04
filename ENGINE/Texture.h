//JORGE DUART MARZO
#pragma once
#include "tigr.h"
#include <vector>
#include "pugixml/pugixml.hpp"

class Sprite 
{

public:

	Sprite(){}
	Sprite(const char* file)
	{
		m_textureFile = file;
		m_image = tigrLoadImage(file);
	}

	~Sprite()
	{
		if (m_image)
		{
			tigrFree(m_image);
		}
	}

	void setX(float x)
	{
		m_x = x;
	}

	void setY(float y)
	{
		m_y = y;
	}

	Tigr* getImage()
	{
		return m_image;
	}

	void Draw(Tigr* window)
	{
		int dx = static_cast<int>(m_x), dy = static_cast<int>(m_y);
		int sx = 0, sy = 0;
		int tw = m_image->w, th = m_image->h;

		tigrBlit(window, m_image, dx, dy, sx, sy, tw, th);
	}

	static bool Load(Sprite &obj, std::string data)
	{
		try {
			pugi::xml_document doc;
			pugi::xml_parse_result result = doc.load_string(data.c_str());

			if (result)
			{
				pugi::xml_node node = doc.child("sprite");

				std::string textureFile = node.attribute("texture").as_string();

				if (obj.m_image) { tigrFree(obj.m_image); }
				obj.m_textureFile = textureFile.c_str();
				obj.m_image = tigrLoadImage(obj.m_textureFile);
				obj.m_x = node.attribute("x").as_float();
				obj.m_y = node.attribute("y").as_float();
				
				return true;
			}
		}
		catch (...)
		{
			return false;
		}
	
	}

	static bool Save(std::string &out, const Sprite& obj)
	{
		pugi::xml_document doc;
		pugi::xml_node node = doc.append_child("sprite");
		node.append_attribute("x").set_value(obj.m_x);
		node.append_attribute("y").set_value(obj.m_y);
		node.append_attribute("texture").set_value(obj.m_textureFile);
		try {
			std::stringstream ss;
			doc.save(ss);
			out = ss.str();
			return true;
		}
		catch(...){
			return false;
		}
	}

private:
	float m_x = 0.f;
	float m_y = 0.f;
	const char* m_textureFile = nullptr;
	Tigr* m_image = nullptr;
};