#include "collisionUtils.h"
#include <iostream>


bool checkCircleCircle(const Vec2& pos1, float radius1, const Vec2& pos2, float radius2)
{
	Vec2 vDist = pos2 - pos1;
	float fDist = vDist.length();
	float fSumRadios = radius1 + radius2;
	return fDist < fSumRadios;
}

bool checkRectRect(const Vec2& rectPos1, const Vec2& rectSize1, const Vec2& rectPos2, const Vec2& rectSize2)
{
	float iniX1 = rectPos1.m_x - rectSize1.m_x / 2.f;
	float finX1 = rectPos1.m_x + rectSize1.m_x / 2.f;
	float iniY1 = rectPos1.m_y - rectSize1.m_y / 2.f;
	float finY1 = rectPos1.m_y + rectSize1.m_y / 2.f;

	float iniX2 = rectPos2.m_x - rectSize2.m_x / 2.f;
	float finX2 = rectPos2.m_x + rectSize2.m_x / 2.f;
	float iniY2 = rectPos2.m_y - rectSize2.m_y / 2.f;
	float finY2 = rectPos2.m_y + rectSize2.m_y / 2.f;

	if (iniX1 >= iniX2 && iniX1 <= finX2 || (iniX2 >= iniX1 && iniX2 <= finX1))
	{
		if ((iniY1 >= iniY2 && iniY1 <= finY2) || (iniY2 >= iniY1 && iniY2 <= finY1))
		{
			return true;
		}
	}
	return false;
}

bool checkCircleRect(const Vec2& circlePos, float circleRadius, const Vec2& rectPos, const Vec2& rectSize)
{

	float iniX1 = rectPos.m_x - rectSize.m_x / 2.f;
	float finX1 = rectPos.m_x + rectSize.m_x / 2.f;
	float iniY1 = rectPos.m_y - rectSize.m_y / 2.f;
	float finY1 = rectPos.m_y + rectSize.m_y / 2.f;

	float fClosestX = clamp(circlePos.m_x, iniX1, finX1);
	float fClosestY = clamp(circlePos.m_y, iniY1, finY1);

	Vec2 vClosestPoint = Vec2(fClosestX, fClosestY);

	Vec2 vDist = circlePos - vClosestPoint;
	float fDist = vDist.length();

	return fDist < circleRadius;
	
}

bool checkCirclePixels(const Vec2& circlePos, float circleRadius, const Vec2& pixelsPos, const Vec2& pixelsSize,
	const uint8_t* pixels)
{
	if (checkCircleRect(circlePos, circleRadius, pixelsPos, pixelsSize))
	{
		float iniXC = circlePos.m_x - circleRadius;
		float finXC = circlePos.m_x + circleRadius;
		float iniYC = circlePos.m_y - circleRadius;
		float finYC = circlePos.m_y + circleRadius;

		float iniXP = pixelsPos.m_x - pixelsSize.m_x / 2.f;
		float finXP = pixelsPos.m_x + pixelsSize.m_x / 2.f;
		float iniYP = pixelsPos.m_y - pixelsSize.m_y / 2.f;
		float finYP = pixelsPos.m_y + pixelsSize.m_y / 2.f;

		float iniX = fmaxf(iniXC, iniXP);
		float iniY = fmaxf(iniYC, iniYP);
		float finX = fminf(finXC, finXP);
		float finY = fminf(finYC, finYP);


		Vec2 vCirPosN = Vec2(circleRadius, circleRadius);
		Vec2 vIniSolapamiento = Vec2(iniX, iniY) - Vec2(iniXP, iniYP);
		Vec2 vFinSolapamiento = Vec2(finX, finY) - Vec2(iniXP, iniYP);

		float fSolapamientoWidth = finX - iniX;
		float fSolapamientoHeight = finY - iniY;

		unsigned int x;
		unsigned int xEnd;

		for (unsigned int y = 0; y <= fSolapamientoHeight; y++)
		{
			x = ((static_cast<unsigned int>(vIniSolapamiento.m_y) * static_cast<unsigned int>(pixelsSize.m_x) + static_cast<unsigned int>(vIniSolapamiento.m_x))
				+ static_cast<unsigned int>(pixelsSize.m_x) * y) * 4 + 3;
			xEnd = ((static_cast<unsigned int>(vIniSolapamiento.m_y) * static_cast<unsigned int>(pixelsSize.m_x) + static_cast<unsigned int>(vFinSolapamiento.m_x))
				+ static_cast<unsigned int>(pixelsSize.m_x) * y) * 4 + 3;


			for (x; x <= xEnd; x += 4)
			{
				//printf("Alpha: %d \n", pixels[x]);
				if (pixels[x] == static_cast<uint8_t>(255))
				{
					float originalX = static_cast<float>(((x - 3) / 4) % static_cast<unsigned int>(pixelsSize.m_x)) + iniXP;
					float originalY = static_cast<float>((((x - 3)/4) / static_cast<unsigned int>(pixelsSize.m_x))) + iniYP;
					Vec2 dist = circlePos - Vec2(originalX, originalY);
					if (dist.length() <= circleRadius)
					{
						return true;
					}
				}
			}
		}

	}

	return false;
}

bool checkPixelsPixels(const Vec2& pixelsPos1, const Vec2& pixelsSize1, const uint8_t* pixels1, const Vec2& pixelsPos2,
	const Vec2& pixelsSize2, const uint8_t* pixels2)
{
	if (checkRectRect(pixelsPos1, pixelsSize1, pixelsPos2, pixelsSize2))
	{

		float iniXP1 = pixelsPos1.m_x - pixelsSize1.m_x / 2.f;
		float finXP1 = pixelsPos1.m_x + pixelsSize1.m_x / 2.f;
		float iniYP1 = pixelsPos1.m_y - pixelsSize1.m_y / 2.f;
		float finYP1 = pixelsPos1.m_y + pixelsSize1.m_y / 2.f;

		float iniXP2 = pixelsPos2.m_x - pixelsSize2.m_x / 2.f;
		float finXP2 = pixelsPos2.m_x + pixelsSize2.m_x / 2.f;
		float iniYP2 = pixelsPos2.m_y - pixelsSize2.m_y / 2.f;
		float finYP2 = pixelsPos2.m_y + pixelsSize2.m_y / 2.f;

		float iniX = fmaxf(iniXP1, iniXP2);
		float iniY = fmaxf(iniYP1, iniYP2);
		float finX = fminf(finXP1, finXP2);
		float finY = fminf(finYP1, finYP2);

		float fSolapamientoWidth = finX - iniX;
		float fSolapamientoHeight = finY - iniY;

		Vec2 vIniSolapamientoP1 = Vec2(iniX, iniY) - Vec2(iniXP1, iniYP1);
		Vec2 vFinSolapamientoP1 = Vec2(finX, finY) - Vec2(iniXP1, iniYP1);

		Vec2 vIniSolapamientoP2 = Vec2(iniX, iniY) - Vec2(iniXP2, iniYP2);
		Vec2 vFinSolapamientoP2 = Vec2(finX, finY) - Vec2(iniXP2, iniYP2);


		unsigned int xP1;
		unsigned int xP2;
		unsigned int xEnd;

		for (unsigned int y = 0; y <= fSolapamientoHeight; y++)
		{
			xP1 = ((static_cast<unsigned int>(vIniSolapamientoP1.m_y) * static_cast<unsigned int>(pixelsSize1.m_x) + static_cast<unsigned int>(vIniSolapamientoP1.m_x))
				+ static_cast<unsigned int>(pixelsSize1.m_x) * y) * 4u + 3u;
			xP2 = ((static_cast<unsigned int>(vIniSolapamientoP2.m_y) * static_cast<unsigned int>(pixelsSize2.m_x) + static_cast<unsigned int>(vIniSolapamientoP2.m_x))
				+ static_cast<unsigned int>(pixelsSize2.m_x) * y) * 4u + 3u;

			xEnd = ((static_cast<unsigned int>(vIniSolapamientoP1.m_y) * static_cast<unsigned int>(pixelsSize1.m_x) + static_cast<unsigned int>(vFinSolapamientoP1.m_x))
				+ static_cast<unsigned int>(pixelsSize1.m_x) * y) * 4u + 3u;


			for (xP1; xP1 <= xEnd; xP1 += 4u, xP2 +=  4u)
			{
				//printf("Alpha: %d \n", pixels[x]);
				if (pixels1[xP1] == static_cast<uint8_t>(255) && pixels2[xP2] == static_cast<uint8_t>(255))
				{
					return true;
				}
			}
		}

	}
	return false;
}

bool checkPixelsRect(const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels, const Vec2& rectPos,
	const Vec2& rectSize)
{

	if (checkRectRect(pixelsPos, pixelsSize, rectPos, rectSize))
	{
		float iniXR = rectPos.m_x - rectSize.m_x / 2.f;
		float finXR = rectPos.m_x + rectSize.m_x / 2.f;
		float iniYR = rectPos.m_y - rectSize.m_y / 2.f;
		float finYR = rectPos.m_y + rectSize.m_y / 2.f;

		float iniXP = pixelsPos.m_x - pixelsSize.m_x / 2.f;
		float finXP = pixelsPos.m_x + pixelsSize.m_x / 2.f;
		float iniYP = pixelsPos.m_y - pixelsSize.m_y / 2.f;
		float finYP = pixelsPos.m_y + pixelsSize.m_y / 2.f;

		float iniX = fmaxf(iniXR, iniXP);
		float iniY = fmaxf(iniYR, iniYP);
		float finX = fminf(finXR, finXP);
		float finY = fminf(finYR, finYP);

		Vec2 vIniSolapamiento = Vec2(iniX, iniY) - Vec2(iniXP, iniYP);
		Vec2 vFinSolapamiento = Vec2(finX, finY) - Vec2(iniXP, iniYP);

		float fSolapamientoWidth = finX - iniX;
		float fSolapamientoHeight = finY - iniY;

		unsigned int x;
		unsigned int xEnd;
		
		for (unsigned int y = 0; y <= fSolapamientoHeight; y++)
		{
			x = ((static_cast<unsigned int>(vIniSolapamiento.m_y) * static_cast<unsigned int>(pixelsSize.m_x) + static_cast<unsigned int>(vIniSolapamiento.m_x)) 
				+ static_cast<unsigned int>(pixelsSize.m_x) * y) * 4 + 3;
			xEnd = ((static_cast<unsigned int>(vIniSolapamiento.m_y) * static_cast<unsigned int>(pixelsSize.m_x) + static_cast<unsigned int>(vFinSolapamiento.m_x)) 
				+ static_cast<unsigned int>(pixelsSize.m_x) * y) * 4 + 3;

			for (x; x <= xEnd; x += 4)
			{
				//printf("Alpha: %d \n", pixels[x]);
				if (pixels[x] == static_cast<uint8_t>(255))
				{ 
					return true; 
				}
			}
		}
	}
	return false;
}
