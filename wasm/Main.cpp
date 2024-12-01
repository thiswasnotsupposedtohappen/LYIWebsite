#ifdef EMS
#include <emscripten.h>
#define EMSATTRIBUTE extern "C" EMSCRIPTEN_KEEPALIVE
#else
#define EMSCRIPTEN_KEEPALIVE
#define EMSATTRIBUTE
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
Heap<Line> drawing;

EMSCRIPTEN_KEEPALIVE int32 main()
{
	cout << "Hello World" << endl;

#ifndef EMS
	int32 LoadDXF(char* file, uint32 length);
	LoadDXF((char*)"intermediated.txt", 0);
#endif
	return 0;
}

EMSATTRIBUTE int32 LoadDXF(char* file, uint32 length)
{
	cout << "LoadDXF In" << endl;
	drawing.Release();

	class DXFReader : public DRW_Interface
	{
		float64 test = 0;
	public:
		uint32 CopyData()
		{
			return test;
		}
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
			test++;
		}
		void setBlock(const int handle) override
		{
			test++;
		}
		void endBlock() override
		{
			test++;
		}
		void addPoint(const DRW_Point& data) override
		{
			test++;
		}
		void addLine(const DRW_Line& data) override
		{
			Line _drawing;
			_drawing.p0.x = data.basePoint.x;
			_drawing.p0.y = data.basePoint.y;
			_drawing.p1.x = data.secPoint.x;
			_drawing.p1.y = data.secPoint.y;
			drawing << _drawing;
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
			Heap<Line> _drawing;
			Line __drawing;
			__drawing.p0.x = data.basePoint.x + data.radious * cos(data.staangle);
			__drawing.p0.y = data.basePoint.y + data.radious * sin(data.staangle);
			float64 inc = 10 / data.radious;
			for (float64 i = inc; i < data.endangle; i += inc)
			{
				__drawing.p1.x = data.basePoint.x + data.radious * cos((i));
				__drawing.p1.y = data.basePoint.y + data.radious * sin((i));
				_drawing << __drawing;
				__drawing.p0 = __drawing.p1;
			}
			drawing.Append(_drawing.data, _drawing.size);
			drawing[drawing.size - 1].p1.x = data.basePoint.x + data.radious * cos(data.endangle);
			drawing[drawing.size - 1].p1.y = data.basePoint.y + data.radious * sin(data.endangle);
			return;
		}
		void addCircle(const DRW_Circle& data) override
		{
			Heap<Line> _drawing;
			Line __drawing;
			__drawing.p0.x = data.basePoint.x + data.radious * cos(0);
			__drawing.p0.y = data.basePoint.y + data.radious * sin(0);
			float64 inc = 10 / data.radious;
			for (float64 i = inc; i < 2 * pi; i += inc)
			{
				__drawing.p1.x = data.basePoint.x + data.radious * cos((i));
				__drawing.p1.y = data.basePoint.y + data.radious * sin((i));
				_drawing << __drawing;
				__drawing.p0 = __drawing.p1;
			}
			drawing.Append(_drawing.data, _drawing.size);
			drawing[drawing.size - 1].p1.x = data.basePoint.x + data.radious * cos(2 * pi);
			drawing[drawing.size - 1].p1.y = data.basePoint.y + data.radious * sin(2 * pi);
			return;
		}
		void addEllipse(const DRW_Ellipse& data) override
		{
			test++;
		}
		void addLWPolyline(const DRW_LWPolyline& data) override
		{
			Heap<Line> _drawing;
			Line __drawing;
			__drawing.p0.x = data.vertex->x;
			__drawing.p0.y = data.vertex->y;
			__drawing.p1.x = data.vertlist[0]->x;
			__drawing.p1.y = data.vertlist[0]->y;
			_drawing << __drawing;

			for (uint32 i = 1; i < data.vertexnum; i++)
			{
				__drawing.p0.x = data.vertlist[i - 1]->x;
				__drawing.p0.y = data.vertlist[i - 1]->y;
				__drawing.p1.x = data.vertlist[i - 0]->x;
				__drawing.p1.y = data.vertlist[i - 0]->y;
				_drawing << __drawing;
			}
			drawing.Append(_drawing.data, _drawing.size);
		}
		void addPolyline(const DRW_Polyline& data) override
		{
			Heap<Line> _drawing;
			Line __drawing;
			__drawing.p0.x = data.basePoint.x;
			__drawing.p0.y = data.basePoint.y;
			__drawing.p1.x = data.vertlist[0]->basePoint.x;
			__drawing.p1.y = data.vertlist[0]->basePoint.y;
			_drawing << __drawing;
			for (uint32 i = 1; i < data.vertexcount; i++)
			{
				__drawing.p0.x = data.vertlist[i - 1]->basePoint.x;
				__drawing.p0.y = data.vertlist[i - 1]->basePoint.y;
				__drawing.p1.x = data.vertlist[i - 0]->basePoint.x;
				__drawing.p1.y = data.vertlist[i - 0]->basePoint.y;
				_drawing << __drawing;
			}
			drawing.Append(_drawing.data, _drawing.size);
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

			for (uint32 i = 0; i < data->ncontrol; i++)
			{
				controlpoints[i].x = data->controllist[i]->x;
				controlpoints[i].y = data->controllist[i]->y;
			}

			for (uint32 i = 0; i < data->nknots; i++)
			{
				knots[i] = data->knotslist[i] / data->knotslist[data->nknots - 1];
			}

			Heap<Line> _drawing;
			Line __drawing;

			float64x2 p;
			float64x2 q;
			float64x2 w;
			float64 previousu = 0;
			p = spline.InterpolateSpline(0, degree, controlpoints, data->ncontrol, knots);
			for (float64 u = 0; u <= 1.001; u+=0.001)
			{
				q = spline.InterpolateSpline(u, degree, controlpoints, data->ncontrol, knots);
				if (p == q)
					continue;
				w = spline.InterpolateSpline((previousu + u)/2, degree, controlpoints, data->ncontrol, knots);
				if (DistanceOfaPointFromLine(w,p,q) < 0.1)
					continue;
				__drawing.p0 = p;
				__drawing.p1 = q;
				_drawing << __drawing;
				p = q;
				previousu = u;
			}
			drawing.Append(_drawing.data, _drawing.size);
			drawing[drawing.size - 1].p1.x = controlpoints[data->ncontrol - 1].x;
			drawing[drawing.size - 1].p1.y = controlpoints[data->ncontrol - 1].y;
			cout << "Spline" << endl;
			return;
			/*
						Heap<Line> _drawing;
			Line __drawing;
			float64 us = 0;
			float64 ue = 0;
			uint32 ks = 0;
			uint32 ke = 0;
			float64x2 p;
			float64x2 q;
			while (ue < 1)
			{
				for (uint32 k = ks; k < data->nknots; k++)
				{
					if ((knots[k + 0] == knots[k + 1]) && (knots[k + 1] == knots[k + 2]))
					{
						ke = k;
						if (knots[ks] == knots[ke])
							continue;		
						break;
					}					
				}
				us = knots[ks];
				ue = knots[ke];
				
				if (knots[ke - 1] == knots[ks])
				{
					p = spline.InterpolateSpline(us, degree, controlpoints, data->ncontrol, knots);
					q = spline.InterpolateSpline(ue, degree, controlpoints, data->ncontrol, knots);
					__drawing.p0 = p;
					__drawing.p1 = q;
					_drawing << __drawing;
				}
				else
				{
					p = spline.InterpolateSpline(us, degree, controlpoints, data->ncontrol, knots);
					float64 inc = (ue - us) / 100;
					for (float64 u = us; u < ue; u += inc)
					{
						float64x2 q = spline.InterpolateSpline(u, degree, controlpoints, data->ncontrol, knots);
						if (p == q)
							continue;
						__drawing.p0.x = p.x;
						__drawing.p0.y = p.y;
						__drawing.p1.x = q.x;
						__drawing.p1.y = q.y;
						_drawing << __drawing;

						p = q;
					}
					q = spline.InterpolateSpline(ue, degree, controlpoints, data->ncontrol, knots);
					_drawing[_drawing.size - 1].p1.x = q.x;
					_drawing[_drawing.size - 1].p1.y = q.y;
				}
				us = ue;
				ks = ke;
			}
			drawing.Append(_drawing.data, _drawing.size);
			drawing[drawing.size - 1].p1.x = controlpoints[data->ncontrol - 1].x;
			drawing[drawing.size - 1].p1.y = controlpoints[data->ncontrol - 1].y;
			*/
			
		}
		void addKnot(const DRW_Entity& data) override
		{
			test++;
		}
		void addInsert(const DRW_Insert& data) override
		{
			test++;
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
	dxfRW dxf("Om Jali.dxf");
	//dxfRW dxf("spline.dxf");
	//dxfRW dxf("TEST.dxf");
#endif
	if (!dxf.read(&reader, false)) { return -1; }
	cout << "drawing = " << (uint32)(void*)drawing.data << endl;
	cout << "drawinglength = "<< drawing.size << endl;
	cout << "LoadDXF Out" << endl;
	return 0;
}

EMSATTRIBUTE int32 ConvertToLineDrawing()
{
	if (drawing.size == 0)return -1;

	return 0;
}

EMSATTRIBUTE int32 Generate3DHalfDepth()
{
	if (drawing.size == 0)return -1;
	return 0;
}

EMSATTRIBUTE void* GETdrawing()
{
	return (void*)drawing.data;
}

EMSATTRIBUTE uint32 GETdrawinglength()
{
	return drawing.size;
}	