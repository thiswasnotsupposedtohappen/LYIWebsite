#ifdef EMS
#include <emscripten.h>
#define EMSATTRIBUTE extern "C" EMSCRIPTEN_KEEPALIVE
#define FAULT {cout << "FAULT" << endl;while(1);}
#else
#define EMSCRIPTEN_KEEPALIVE
#define EMSATTRIBUTE
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define FAULT __debugbreak();
#endif
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;
#include "PoDefinition.h"
#include "PoUtilities.h"
#include "PoMath.h"
#include "libdxfrw.h"

struct Line
{
	float64x2 p0;
	float64x2 p1;
};
struct Block
{
	char name[240];
	LinkedList<Line> blockdata;
};
LinkedList<Block> block;
LinkedList<Line> drawing;
LinkedList<Line> *drawingcurrentblock = &drawing;
Heap<Line> drawingexport;

EMSCRIPTEN_KEEPALIVE int32 main()
{
	cout << "Hello World" << endl;

#ifndef EMS
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	int32 LoadDXF(char* file, uint32 length);
	LoadDXF((char*)"intermediated.txt", 0);

#endif

	return 0;
}

EMSATTRIBUTE int32 LoadDXF(char* file, uint32 length)
{
	cout << "LoadDXF In" << endl;
	block.Release();
	static Block* _block = 0;

	class DXFReader : public DRW_Interface
	{
		float64 test = 0;
	public:
		void addHeader(const DRW_Header* data) override
		{
			test++;
		}
		void addLType(const DRW_LType& data) override
		{
			test++;
		}
		void addLayer(const DRW_Layer& data) override
		{
			test++;
		}
		void addDimStyle(const DRW_Dimstyle& data) override
		{
			test++;
		}
		void addVport(const DRW_Vport& data) override
		{
			test++;
		}
		void addTextStyle(const DRW_Textstyle& data) override
		{
			test++;
		}
		void addAppId(const DRW_AppId& data) override
		{
			test++;
		}
		void addBlock(const DRW_Block& data) override
		{
			_block = new Block;
			for(uint32 i=0;i<data.name.size();i++)
				_block->name[i] = data.name[i];
			_block->name[data.name.size()] = 0;
			drawingcurrentblock = &_block->blockdata;
		}
		void setBlock(const int handle) override
		{
			test++;
		}
		void endBlock() override
		{
			if (_block->blockdata.count)
				block << *_block;
			_block = 0;
			drawingcurrentblock = &drawing;
		}
		void addPoint(const DRW_Point& data) override
		{
			test++;
		}
		void addLine(const DRW_Line& data) override
		{
			Line _line;
			_line.p0.x = data.basePoint.x;
			_line.p0.y = data.basePoint.y;
			_line.p1.x = data.secPoint.x;
			_line.p1.y = data.secPoint.y;
			*drawingcurrentblock << _line;
			return;
		}
		void addRay(const DRW_Ray& data) override
		{
			test++;
		}
		void addXline(const DRW_Xline& data) override
		{
			test++;
		}
		void addArc(const DRW_Arc& data) override
		{
			LinkedList<Line> _drawing;
			Line _line;
			float64 anglestart = data.staangle;
			float64 angleend = data.endangle;
			float64 inc = 0.5 / data.radious;
			if (anglestart > 2 * pi)anglestart -= 2 * pi;
			if (angleend > 2 * pi)angleend -= 2 * pi;

			if (data.isccw)
			{
				inc *= +1;
				if (anglestart > angleend)
					anglestart -= 2 * pi;
			}
			else
			{
				inc *= -1;
				if (anglestart < angleend)
					anglestart += 2 * pi;
			}

			_line.p0.x = data.basePoint.x + data.radious * cos(anglestart);
			_line.p0.y = data.basePoint.y + data.radious * sin(anglestart);
			for (float64 i = (anglestart + inc); i <= angleend; i += inc)
			{
				_line.p1.x = data.basePoint.x + data.radious * cos((i));
				_line.p1.y = data.basePoint.y + data.radious * sin((i));
				_drawing << _line;
				_line.p0 = _line.p1;
			}
			_drawing.tail->data.p1.x = data.basePoint.x + data.radious * cos(angleend);
			_drawing.tail->data.p1.y = data.basePoint.y + data.radious * sin(angleend);
			drawingcurrentblock->Append(_drawing);
			return;
		}
		void addCircle(const DRW_Circle& data) override
		{
			LinkedList<Line> _drawing;
			Line _line;
			_line.p0.x = data.basePoint.x + data.radious * cos(0);
			_line.p0.y = data.basePoint.y + data.radious * sin(0);
			float64 inc = 0.5 / data.radious;
			for (float64 i = inc; i <= 2 * pi; i += inc)
			{
				_line.p1.x = data.basePoint.x + data.radious * cos((i));
				_line.p1.y = data.basePoint.y + data.radious * sin((i));
				_drawing << _line;
				_line.p0 = _line.p1;
			}
			_drawing.tail->data.p1.x = data.basePoint.x + data.radious * cos(2 * pi);
			_drawing.tail->data.p1.y = data.basePoint.y + data.radious * sin(2 * pi);
			drawingcurrentblock->Append(_drawing);
			return;
		}
		void addEllipse(const DRW_Ellipse& data) override
		{
			LinkedList<Line> _drawing;
			Line _line;
			float64x2 centre;
			float64x2 startpoint;
			float64 radius;
			float64 ratio;
			float64 angle;
			float64 anglestart = data.staparam;
			float64 angleend = data.endparam;
			
			centre.x = data.basePoint.x;
			centre.y = data.basePoint.y;
			startpoint.x = data.secPoint.x;
			startpoint.y = data.secPoint.y;
			radius = Distance(float64x2(0,0), startpoint);
			ratio = data.ratio;
			angle = atan2(startpoint.y, startpoint.x);
			anglestart = data.staparam;
			angleend = data.endparam;
			float64 inc = 0.5 / radius;
			if (anglestart > 2 * pi)anglestart -= 2 * pi;
			if (angleend > 2 * pi)angleend -= 2 * pi;

			if (data.isccw)
			{
				inc *= +1;
				if (anglestart > angleend)
					anglestart -= 2 * pi;
			}
			else
			{
				inc *= -1;
				if (anglestart < angleend)
					anglestart += 2 * pi;
			}

			for (float64 i = (anglestart + inc); i <= angleend; i += inc)
			{
				_line.p0.x = radius * cos((i - inc));
				_line.p0.y = radius * sin((i - inc)) * ratio;
				_line.p1.x = radius * cos((i));
				_line.p1.y = radius * sin((i)) * ratio;

				float64 p0x = _line.p0.x;
				float64 p0y = _line.p0.y;
				float64 p1x = _line.p1.x;
				float64 p1y = _line.p1.y;

				_line.p0.x = p0x * cos(angle) - p0y * sin(angle);
				_line.p0.y = p0x * sin(angle) + p0y * cos(angle);
				_line.p1.x = p1x * cos(angle) - p1y * sin(angle);
				_line.p1.y = p1x * sin(angle) + p1y * cos(angle);

				_line.p0 = _line.p0 + centre;
				_line.p1 = _line.p1 + centre;

				_drawing << _line;
			}
			drawingcurrentblock->Append(_drawing);
			return;
		}
		void addLWPolyline(const DRW_LWPolyline& data) override
		{
			struct CustomCalculator
			{
				int32 CalculateCentre(float64x2 p1, float64x2 p2, float64 r,float64x2* c1, float64x2* c2)
				{
					float64x2 centre;

					// Calculate the distance between the two points
					double dx = p2.x - p1.x;
					double dy = p2.y - p1.y;
					double d_sq = dx * dx + dy * dy;
					double d = std::sqrt(d_sq);

					// Check if the circle is possible
					if (d > 2 * r) 
					{
						return -1;
					}

					// Compute the midpoint between p1 and p2
					float64x2 mid;
					mid.x = (p1.x + p2.x) / 2.0;
					mid.y = (p1.y + p2.y) / 2.0;

					// Calculate the distance from the midpoint to the circle centers
					double h = sqrt(r * r - (d / 2.0) * (d / 2.0));

					// Determine the direction vector perpendicular to the line segment
					double ux = -dy / d;
					double uy = dx / d;

					// Calculate the two possible centers
					c1->x = mid.x + h * ux;
					c1->y = mid.y + h * uy;

					c2->x = mid.x - h * ux;
					c2->y = mid.y - h * uy;

					return 0;
				}
			
				float64 CheckSide(float64x2 p1, float64x2 p2, float64x2 c)
				{
					float64x2 v1, v2;
					v1.x = p2.x - p1.x;
					v1.y = p2.y - p1.y;
					v2.x = c.x - p1.x;
					v2.y = c.y - p1.y;
					return (v1.x * v2.y - v1.y * v2.x);
				}
			}customcalculator;
			LinkedList<Line> _drawing;
			Line _line;
			float64x2 c1;
			float64x2 c2;
			float64x2 centre;
			float64 r;
			float64 d;
			float64 b;
			float64 anglestart;
			float64 angleend;
			float64 inc;

			_line.p0.x = data.vertex->x;
			_line.p0.y = data.vertex->y;

			for (uint32 i = 0; i < data.vertexnum; i++)
			{
				_line.p1.x = data.vertlist[i]->x;
				_line.p1.y = data.vertlist[i]->y;
				b = data.vertlist[i]->bulge;
				if (b)
				{
					d = Distance(_line.p0, _line.p1);
					b = b * d / 2;
					r = (d*d + 4*Absolute(b)* Absolute(b)) / (8* Absolute(b));
					customcalculator.CalculateCentre(_line.p0, _line.p1, r, &c1, &c2);
					inc = 0.5 / r;

					float64 side;
					side = customcalculator.CheckSide(_line.p0, _line.p1, c1);
					if (data.vertlist[i]->bulge > 0)
					{
						if (customcalculator.CheckSide(_line.p0, _line.p1, c1) > 0)
						{
							inc *= 1;
							if (data.vertlist[i]->bulge <= 1)
								centre = c1;
							else
								centre = c2;
						}
						else
						{
							inc *= -1;
							if (data.vertlist[i]->bulge <= 1)
								centre = c2;
							else
								centre = c1;
						}
					}
					else
					{
						if (customcalculator.CheckSide(_line.p0, _line.p1, c1) > 0)
						{
							inc *= -1;
							if (data.vertlist[i]->bulge >= -1)
								centre = c2;
							else
								centre = c1;
						}
						else
						{
							inc *= 1;
							if (data.vertlist[i]->bulge >= -1)
								centre = c1;
							else
								centre = c2;
							
						}
					}

					if (inc > 0)
					{
						anglestart = atan2(_line.p0.y - centre.y, _line.p0.x - centre.x);
						angleend = atan2(_line.p1.y - centre.y, _line.p1.x - centre.x);
						if (angleend < anglestart)angleend += 2 * pi;
					}
					else
					{
						anglestart = atan2(_line.p0.y - centre.y, _line.p0.x - centre.x);
						angleend = atan2(_line.p1.y - centre.y, _line.p1.x - centre.x);
						if (angleend > anglestart)angleend -= 2 * pi;
					}

					for (float64 i = (anglestart + inc); Absolute(i - angleend) > Absolute(inc); i += inc)
					{
						_line.p1.x = centre.x + r * cos((i));
						_line.p1.y = centre.y + r * sin((i));
						_drawing << _line;
						_line.p0 = _line.p1;
					}
					_drawing.tail->data.p1.x = data.vertlist[i]->x;
					_drawing.tail->data.p1.y = data.vertlist[i]->y;
					_line.p0.x = data.vertlist[i]->x;
					_line.p0.y = data.vertlist[i]->y;
				}
				else
				{
					_drawing << _line;
					_line.p0 = _line.p1;
				}
			}
			drawingcurrentblock->Append(_drawing);
			return;
		}
		void addPolyline(const DRW_Polyline& data) override
		{
			LinkedList<Line> _drawing;
			Line _line;
			_line.p0.x = data.vertlist[0]->basePoint.x;
			_line.p0.y = data.vertlist[0]->basePoint.y;
			_line.p1.x = data.vertlist[1]->basePoint.x;
			_line.p1.y = data.vertlist[1]->basePoint.y;
			_drawing << _line;
			for (uint32 i = 2; i < data.vertlist.size(); i++)
			{
				_line.p0.x = data.vertlist[i - 1]->basePoint.x;
				_line.p0.y = data.vertlist[i - 1]->basePoint.y;
				_line.p1.x = data.vertlist[i - 0]->basePoint.x;
				_line.p1.y = data.vertlist[i - 0]->basePoint.y;
				_drawing << _line;
			}
			drawingcurrentblock->Append(_drawing);
			return;
		}
		void addSpline(const DRW_Spline* data) override
		{
			struct SplineInterpolatorByGPT4o_EntireCodeWasWrittenByGPTItDidNotWorkTheFirstTimeSoIAskedGPTToFixItAndItDid_IHaveNoClueHowThisCodeWorksAndHonestlyIDontCare_GodThisShitIsAmazing_ItSavedMeAtLeast2DaysOfWork
			{
				float64 Basis(int32 ci, int32 degree, float64 u, float64* knots)
				{
					//if (degree == 0)
					//{
					//	return (knots[ci] <= u && u < knots[ci + 1]) ? 1.0 : 0.0;
					//}
					//else 
					//{
					//	float64 left = (knots[ci + degree] - knots[ci]) != 0 ? (u - knots[ci]) / (knots[ci + degree] - knots[ci]) : 0;
					//	float64 right = (knots[ci + degree + 1] - knots[ci + 1]) != 0 ? (knots[ci + degree + 1] - u) / (knots[ci + degree + 1] - knots[ci + 1]) : 0;
					//	return left * Basis(ci, degree - 1, u, knots) + right * Basis(ci + 1, degree - 1, u, knots);
					//}

					/*
					float64 N[4] = { 0.0, 0.0, 0.0, 0.0 };

					for (int i = 0; i <= degree; i++)
					{
						if (knots[ci + i] <= u && u < knots[ci + i + 1])
							N[i] = 1.0;
						else
							N[i] = 0.0;
					}

					for (int i = 1; i <= degree; i++)
					{
						for (int j = 0; j <= degree - i; j++)
						{
							float64 leftDenom = knots[ci + j + i] - knots[ci + j];
							float64 left = (leftDenom != 0.0) ? ((u - knots[ci + j]) / leftDenom) * N[j] : 0.0;

							float64 rightDenom = knots[ci + j + i + 1] - knots[ci + j + 1];
							float64 right = (rightDenom != 0.0) ? ((knots[ci + j + i + 1] - u) / rightDenom) * N[j + 1] : 0.0;

							N[j] = left + right;
						}
					}

					return N[0];
					*/

					// Since degree is always 3, we can unroll the loops for optimization
					// Initialize N0 to N3
					float64 N0 = (knots[ci + 0] <= u && u < knots[ci + 1]) ? 1.0 : 0.0;
					float64 N1 = (knots[ci + 1] <= u && u < knots[ci + 2]) ? 1.0 : 0.0;
					float64 N2 = (knots[ci + 2] <= u && u < knots[ci + 3]) ? 1.0 : 0.0;
					float64 N3 = (knots[ci + 3] <= u && u < knots[ci + 4]) ? 1.0 : 0.0;

					// First iteration (i = 1)
					{
						// Update N0
						float64 leftDenom = knots[ci + 1] - knots[ci + 0];
						float64 left = (leftDenom != 0.0) ? ((u - knots[ci + 0]) / leftDenom) * N0 : 0.0;

						float64 rightDenom = knots[ci + 2] - knots[ci + 1];
						float64 right = (rightDenom != 0.0) ? ((knots[ci + 2] - u) / rightDenom) * N1 : 0.0;

						N0 = left + right;

						// Update N1
						leftDenom = knots[ci + 2] - knots[ci + 1];
						left = (leftDenom != 0.0) ? ((u - knots[ci + 1]) / leftDenom) * N1 : 0.0;

						rightDenom = knots[ci + 3] - knots[ci + 2];
						right = (rightDenom != 0.0) ? ((knots[ci + 3] - u) / rightDenom) * N2 : 0.0;

						N1 = left + right;

						// Update N2
						leftDenom = knots[ci + 3] - knots[ci + 2];
						left = (leftDenom != 0.0) ? ((u - knots[ci + 2]) / leftDenom) * N2 : 0.0;

						rightDenom = knots[ci + 4] - knots[ci + 3];
						right = (rightDenom != 0.0) ? ((knots[ci + 4] - u) / rightDenom) * N3 : 0.0;

						N2 = left + right;
					}

					// Second iteration (i = 2)
					{
						// Update N0
						float64 leftDenom = knots[ci + 2] - knots[ci + 0];
						float64 left = (leftDenom != 0.0) ? ((u - knots[ci + 0]) / leftDenom) * N0 : 0.0;

						float64 rightDenom = knots[ci + 3] - knots[ci + 1];
						float64 right = (rightDenom != 0.0) ? ((knots[ci + 3] - u) / rightDenom) * N1 : 0.0;

						N0 = left + right;

						// Update N1
						leftDenom = knots[ci + 3] - knots[ci + 1];
						left = (leftDenom != 0.0) ? ((u - knots[ci + 1]) / leftDenom) * N1 : 0.0;

						rightDenom = knots[ci + 4] - knots[ci + 2];
						right = (rightDenom != 0.0) ? ((knots[ci + 4] - u) / rightDenom) * N2 : 0.0;

						N1 = left + right;
					}

					// Third iteration (i = 3)
					{
						// Update N0
						float64 leftDenom = knots[ci + 3] - knots[ci + 0];
						float64 left = (leftDenom != 0.0) ? ((u - knots[ci + 0]) / leftDenom) * N0 : 0.0;

						float64 rightDenom = knots[ci + 4] - knots[ci + 1];
						float64 right = (rightDenom != 0.0) ? ((knots[ci + 4] - u) / rightDenom) * N1 : 0.0;

						N0 = left + right;
					}

					return N0;
				}

				float64x2 InterpolateSpline(float64 u, int32 degree, float64x2* controlpoints,uint32 controlpointscount, float64* knots)
				{
					float64x2 result;
					for (uint32 ci = 0; ci < controlpointscount; ci++)
					{
						float64 b = Basis(ci, degree, u, knots);
						result.x += b * controlpoints[ci].x;
						result.y += b * controlpoints[ci].y;
					}
					return result;
				}
			}spline;

			float64x2* controlpoints = new float64x2[data->ncontrol];
			float64* knots = new float64[data->nknots];
			int32 degree = data->degree;
			float64 length = 0;

			for (uint32 i = 0; i < data->ncontrol; i++)
			{
				controlpoints[i].x = data->controllist[i]->x;
				controlpoints[i].y = data->controllist[i]->y;
			}

			for (uint32 i = 0; i < data->nknots; i++)
			{
				knots[i] = data->knotslist[i] / data->knotslist[data->nknots - 1];
			}

			for (uint32 i = 1; i < data->ncontrol; i++)
			{
				length += Distance(controlpoints[i - 1], controlpoints[i]);
			}

			LinkedList<Line> _drawing;
			Line _line;

			float64x2 p;
			float64x2 q;
			float64x2 w;
			float64 previousu = 0;
			p = spline.InterpolateSpline(0, degree, controlpoints, data->ncontrol, knots);
			_line.p0 = p;
			float64 inc = 0.1 / length;
			for (float64 u = 0; u <= 1.001; u+= inc)
			{
				q = spline.InterpolateSpline(u, degree, controlpoints, data->ncontrol, knots);
				if (p == q)
					continue;
				w = spline.InterpolateSpline((previousu + u)/2, degree, controlpoints, data->ncontrol, knots);
				if (DistanceOfaPointFromLine(w,p,q) < 0.001)
					continue;
				_line.p0 = p;
				_line.p1 = q;
				_drawing << _line;
				p = q;
				previousu = u;
			}
			if (_drawing.count == 0)
			{
				q.x = controlpoints[data->ncontrol - 1].x;
				q.y = controlpoints[data->ncontrol - 1].y;
				_line.p1 = q;
				_drawing << _line;
			}
			_drawing.tail->data.p1.x = controlpoints[data->ncontrol - 1].x;
			_drawing.tail->data.p1.y = controlpoints[data->ncontrol - 1].y;
			drawingcurrentblock->Append(_drawing);
			delete[] controlpoints;
			delete[] knots;
			return;		
		}
		void addKnot(const DRW_Entity& data) override
		{
			test++;
		}
		void addInsert(const DRW_Insert& data) override
		{
			LinkedList<Line> _drawing;
			char blockname[256];
			for (uint32 i = 0; i < data.name.size(); i++)
				blockname[i] = data.name[i];
			blockname[data.name.size()] = 0;

			uint32 i, j;
			for (i = 0, block.GotoHead(); i < block.count; i++, block.MoveRight())
			{				
				if (strcmp(blockname,block.current->data.name) == 0)
				{
					for (j = 0, block.current->data.blockdata.GotoHead(); j < block.current->data.blockdata.count;j++, block.current->data.blockdata.MoveRight())
					{
						Line line = block.current->data.blockdata.current->data;
						line.p0.x *= data.xscale;
						line.p0.y *= data.yscale;
						line.p1.x *= data.xscale;
						line.p1.y *= data.yscale;

						float64 cosangle = cos(data.angle);
						float64 sinangle = sin(data.angle);

						float64 p0x = line.p0.x;
						float64 p0y = line.p0.y;
						float64 p1x = line.p1.x;
						float64 p1y = line.p1.y;

						line.p0.x = p0x * cosangle - p0y * sinangle;
						line.p0.y = p0x * sinangle + p0y * cosangle;
						line.p1.x = p1x * cosangle - p1y * sinangle;
						line.p1.y = p1x * sinangle + p1y * cosangle;

						line.p0.x += data.basePoint.x;
						line.p0.y += data.basePoint.y;
						line.p1.x += data.basePoint.x;
						line.p1.y += data.basePoint.y;

						_drawing << line;
					}
				}
			}
			drawing.Append(_drawing);
		}
		void addTrace(const DRW_Trace& data) override
		{
			test++;
		}
		void add3dFace(const DRW_3Dface& data) override
		{
			test++;
		}
		void addSolid(const DRW_Solid& data) override
		{
			test++;
		}
		void addMText(const DRW_MText& data) override
		{
			test++;
		}
		void addText(const DRW_Text& data) override
		{
			test++;
		}
		void addDimAlign(const DRW_DimAligned* data) override
		{
			test++;
		}
		void addDimLinear(const DRW_DimLinear* data) override
		{
			test++;
		}
		void addDimRadial(const DRW_DimRadial* data) override
		{
			test++;
		}
		void addDimDiametric(const DRW_DimDiametric* data) override
		{
			test++;
		}
		void addDimAngular(const DRW_DimAngular* data) override
		{
			test++;
		}
		void addDimAngular3P(const DRW_DimAngular3p* data) override
		{
			test++;
		}
		void addDimOrdinate(const DRW_DimOrdinate* data) override
		{
			test++;
		}
		void addLeader(const DRW_Leader* data) override
		{
			test++;
		}
		void addHatch(const DRW_Hatch* data) override
		{
			test++;
		}
		void addViewport(const DRW_Viewport& data) override
		{
			test++;
		}
		void addImage(const DRW_Image* data) override
		{
			test++;
		}
		void linkImage(const DRW_ImageDef* data) override
		{
			test++;
		}
		void addComment(const char* comment) override
		{
			test++;
		}
		void addPlotSettings(const DRW_PlotSettings* data) override
		{
			test++;
		}
		void writeHeader(DRW_Header& data) override
		{
			test++;
		}
		void writeBlocks() override
		{
			test++;
		}
		void writeBlockRecords() override
		{
			test++;
		}
		void writeEntities() override
		{
			test++;
		}
		void writeLTypes() override
		{
			test++;
		}
		void writeLayers() override
		{
			test++;
		}
		void writeTextstyles() override
		{
			test++;
		}
		void writeVports() override
		{
			test++;
		}
		void writeDimstyles() override
		{
			test++;
		}
		void writeObjects() override
		{
			test++;
		}
		void writeAppId() override
		{
			test++;
		}
	};
	DXFReader reader;

#ifdef EMS
	fstream filestream;
	filestream.open("intermediated.txt", ios::out);
	for (uint32 i = 0; i < length; i++)
		filestream << file[i];
	filestream.close();

	dxfRW dxf("intermediated.txt");
#else
	//dxfRW dxf("debugspline.dxf");
	//dxfRW dxf("All Jali Designs.dxf");
	//dxfRW dxf("lwpoly.dxf");
	//dxfRW dxf("Ellipse.dxf");
	//dxfRW dxf("Lasercutting Cargo 2mm MS with material.dxf");
	//dxfRW dxf("Om Jali.dxf");
	//dxfRW dxf("spline.dxf");
	dxfRW dxf("Test.dxf");
#endif
	if (!dxf.read(&reader, false)) { return -1; }

	cout << "Exporting Drawing" << endl;
	drawingexport.data = new Line[drawing.count];
	drawingexport.size = drawing.count;
	uint32 i;
	for (i = 0, drawing.GotoHead(); i < drawing.count; i++, drawing.MoveRight())
		drawingexport.data[i] = drawing.Get();		

	for (i = 0, block.GotoHead(); i < block.count; i++, block.MoveRight())
		block.current->data.blockdata.Release();
	block.Release();	

	cout << "drawing = " << (uint32)(void*)drawingexport.data << endl;
	cout << "drawinglength = "<< drawingexport.size << endl;
	cout << "LoadDXF Out" << endl;
	return 0;
}

EMSATTRIBUTE void* GETdrawing()
{
	return (void*)drawingexport.data;
}

EMSATTRIBUTE uint32 GETdrawinglength()
{
	return drawingexport.size;
}	