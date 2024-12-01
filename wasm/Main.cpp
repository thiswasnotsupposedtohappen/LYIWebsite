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

struct VideoBuffer
{
	uint8 r;
	uint8 g;
	uint8 b;
	uint8 a;

	VideoBuffer()
	{
		ZeroMemory(this, sizeof(VideoBuffer));
	}
	VideoBuffer(uint8 r, uint8 g, uint8 b, uint8 a)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}
	~VideoBuffer()
	{
		ZeroMemory(this, sizeof(VideoBuffer));
	}
	VideoBuffer(VideoBuffer& video)
	{
		MemoryCopy(this, &video, sizeof(VideoBuffer));
	}
	void operator=(VideoBuffer& video)
	{
		MemoryCopy(this, &video, sizeof(VideoBuffer));
	}
	bool operator==(VideoBuffer& video)
	{
		if (r != video.r)return false;
		if (g != video.g)return false;
		if (b != video.b)return false;
		if (a != video.a)return false;
		return true;
	}
};
VideoBuffer* video = 0;
uint32 videowidth = 0;
uint32 videoheight = 0;

struct Drawing
{
	enum Type
	{
		EMPTY = 0,
		POINT = 1,
		LINE = 2,
		ARC = 3,
		ELLIPSE = 4,
		SPLINE = 5,
		MAX = 0xFFFFFFF
	};
	union Geometrey
	{
		struct Point
		{
			float64 x;
			float64 y;
		}point;
		struct Line
		{
			float64 x1;
			float64 y1;
			float64 x2;
			float64 y2;
		}line;
		struct Arc
		{
			float64 x;
			float64 y;
			float64 r;
			float64 t1;
			float64 t2;
		}arc;
		struct Elliplse
		{
			float64 x;
			float64 y;
			float64 r1;
			float64 r2;
			float64 t1;
			float64 t2;
		}ellipse;
		struct Spline
		{

		}spline;
		struct Empty
		{

		}empty;
	};
	Type type;
	Geometrey geometrey;
	uint32 padding;

	Drawing()
	{
		type = EMPTY;
		ZeroMemory(&geometrey, sizeof(Geometrey));
	}
	~Drawing()
	{
		ZeroMemory(&geometrey, sizeof(Geometrey));
	}
	Drawing(Drawing& drawing)
	{
		type = drawing.type;
		MemoryCopy(&geometrey, &drawing.geometrey, sizeof(Geometrey));
	}
	void operator=(Drawing& drawing)
	{
		type = drawing.type;
		MemoryCopy(&geometrey, &drawing.geometrey, sizeof(Geometrey));
	}
	bool operator==(Drawing& drawing)
	{
		if (type != drawing.type)return false;
		if (type == EMPTY)return true;
		if (type == POINT)
		{
			if (geometrey.point.x != drawing.geometrey.point.x)return false;
			if (geometrey.point.y != drawing.geometrey.point.y)return false;
		}
		else if (type == LINE)
		{
			if (geometrey.line.x1 != drawing.geometrey.line.x1)return false;
			if (geometrey.line.y1 != drawing.geometrey.line.y1)return false;
			if (geometrey.line.x2 != drawing.geometrey.line.x2)return false;
			if (geometrey.line.y2 != drawing.geometrey.line.y2)return false;
		}
		else if (type == ARC)
		{
			if (geometrey.arc.x != drawing.geometrey.arc.x)return false;
			if (geometrey.arc.y != drawing.geometrey.arc.y)return false;
			if (geometrey.arc.r != drawing.geometrey.arc.r)return false;
			if (geometrey.arc.t1 != drawing.geometrey.arc.t1)return false;
			if (geometrey.arc.t2 != drawing.geometrey.arc.t2)return false;
		}
		else if (type == ELLIPSE)
		{
			if (geometrey.ellipse.x != drawing.geometrey.ellipse.x)return false;
			if (geometrey.ellipse.y != drawing.geometrey.ellipse.y)return false;
			if (geometrey.ellipse.r1 != drawing.geometrey.ellipse.r1)return false;
			if (geometrey.ellipse.r2 != drawing.geometrey.ellipse.r2)return false;
			if (geometrey.ellipse.t1 != drawing.geometrey.ellipse.t1)return false;
			if (geometrey.ellipse.t2 != drawing.geometrey.ellipse.t2)return false;
		}
		else if (type == SPLINE)
		{
			return true;
		}
		else if (type == EMPTY)
		{
			return true;
		}
		else
		{
			return false;
		}
		return true;
	}
};
Heap<Drawing> drawing;

EMSCRIPTEN_KEEPALIVE int32 main()
{
	cout << "Hello World" << endl;
	cout << "Size of Drawing: " << sizeof(Drawing) << endl;
	video = 0;
	videowidth = 0;
	videoheight = 0;

#ifndef EMS
	int32 LoadDXF(char* file, uint32 length);
	int32 InitizalizeVideo(uint32 width, uint32 height);
	LoadDXF((char*)"intermediated.txt", 0);
	InitizalizeVideo(500,500);
#endif
	return 0;
}

EMSATTRIBUTE int32 LoadDXF(char* file, uint32 length)
{
	cout << "LoadDXF In" << endl;

#ifdef EMS
	fstream filestream;
	filestream.open("intermediated.txt", ios::out);
	for (uint32 i = 0; i < length; i++)
		filestream << file[i];
	filestream.close();
#endif

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
			Drawing _drawing;
			_drawing.type = Drawing::LINE;
			_drawing.geometrey.line.x1 = data.basePoint.x;
			_drawing.geometrey.line.y1 = data.basePoint.y;
			_drawing.geometrey.line.x2 = data.secPoint.x;
			_drawing.geometrey.line.y2 = data.secPoint.y;
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
			Drawing _drawing;
			_drawing.type = Drawing::ARC;
			_drawing.geometrey.arc.x = data.basePoint.x;
			_drawing.geometrey.arc.y = data.basePoint.y;
			_drawing.geometrey.arc.r = data.radious;
			_drawing.geometrey.arc.t1 = data.staangle;
			_drawing.geometrey.arc.t2 = data.endangle;
			drawing << _drawing;
		}
		void addCircle(const DRW_Circle& data) override
		{
			Drawing _drawing;
			_drawing.type = Drawing::ARC;
			_drawing.geometrey.arc.x = data.basePoint.x;
			_drawing.geometrey.arc.y = data.basePoint.y;
			_drawing.geometrey.arc.r = data.radious;
			_drawing.geometrey.arc.t1 = 0;
			_drawing.geometrey.arc.t2 = 0;
			drawing << _drawing;
		}
		void addEllipse(const DRW_Ellipse& data) override
		{
			test++;
		}
		void addLWPolyline(const DRW_LWPolyline& data) override
		{
			Heap<Drawing> _drawing;
			Drawing __drawing;
			__drawing.type = Drawing::LINE;
			__drawing.geometrey.line.x1 = data.vertex->x;
			__drawing.geometrey.line.y1 = data.vertex->y;
			__drawing.geometrey.line.x2 = data.vertlist[0]->x;
			__drawing.geometrey.line.y2 = data.vertlist[0]->y;
			_drawing << __drawing;

			for (uint32 i = 1; i < data.vertexnum; i++)
			{
				__drawing.type = Drawing::LINE;
				__drawing.geometrey.line.x1 = data.vertlist[i - 1]->x;
				__drawing.geometrey.line.y1 = data.vertlist[i - 1]->y;
				__drawing.geometrey.line.x2 = data.vertlist[i - 0]->x;
				__drawing.geometrey.line.y2 = data.vertlist[i - 0]->y;
				_drawing << __drawing;
			}
			drawing.Append(_drawing.data, _drawing.size);
		}
		void addPolyline(const DRW_Polyline& data) override
		{
			Heap<Drawing> _drawing;
			Drawing __drawing;
			__drawing.type = Drawing::LINE;
			__drawing.geometrey.line.x1 = data.basePoint.x;
			__drawing.geometrey.line.y1 = data.basePoint.y;
			__drawing.geometrey.line.x2 = data.vertlist[0]->basePoint.x;
			__drawing.geometrey.line.y2 = data.vertlist[0]->basePoint.y;
			_drawing << __drawing;
			for (uint32 i = 1; i < data.vertexcount; i++)
			{
				__drawing.type = Drawing::LINE;
				__drawing.geometrey.line.x1 = data.vertlist[i - 1]->basePoint.x;
				__drawing.geometrey.line.y1 = data.vertlist[i - 1]->basePoint.y;
				__drawing.geometrey.line.x2 = data.vertlist[i - 0]->basePoint.x;
				__drawing.geometrey.line.y2 = data.vertlist[i - 0]->basePoint.y;
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
					if (degree == 0)
					{
						return (knots[ci] <= u && u < knots[ci + 1]) ? 1.0 : 0.0;
					}
					else 
					{
						float64 left = (knots[ci + degree] - knots[ci]) != 0 ? (u - knots[ci]) / (knots[ci + degree] - knots[ci]) : 0;
						float64 right = (knots[ci + degree + 1] - knots[ci + 1]) != 0 ? (knots[ci + degree + 1] - u) / (knots[ci + degree + 1] - knots[ci + 1]) : 0;
						return left * Basis(ci, degree - 1, u, knots) + right * Basis(ci + 1, degree - 1, u, knots);
					}
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

			Heap<Drawing> _drawing;
			Drawing __drawing;
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
				

				p = spline.InterpolateSpline(us, degree, controlpoints, data->ncontrol, knots);
				for (float64 u = us; u < ue; u+=0.1)
				{
					float64x2 q = spline.InterpolateSpline(u, degree, controlpoints, data->ncontrol, knots);
					if (p == q)
						continue;
					__drawing.type = Drawing::LINE;
					__drawing.geometrey.line.x1 = p.x;
					__drawing.geometrey.line.y1 = p.y;
					__drawing.geometrey.line.x2 = q.x;
					__drawing.geometrey.line.y2 = q.y;
					_drawing << __drawing;

					p = q;
				}
				q = spline.InterpolateSpline(ue, degree, controlpoints, data->ncontrol, knots);
				_drawing[_drawing.size - 1].geometrey.line.x2 = q.x;
				_drawing[_drawing.size - 1].geometrey.line.y2 = q.y;
				us = ue;
				ks = ke;
			}
			drawing.Append(_drawing.data, _drawing.size);
			drawing[drawing.size - 1].geometrey.line.x2 = controlpoints[data->ncontrol - 1].x;
			drawing[drawing.size - 1].geometrey.line.y2 = controlpoints[data->ncontrol - 1].y;
			return;
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
	//dxfRW dxf("Om Jali.dxf");
	//dxfRW dxf("spline.dxf");
	dxfRW dxf("TEST.dxf");
	//dxfRW dxf("intermediated.txt");
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

EMSATTRIBUTE int32 InitizalizeVideo(uint32 width, uint32 height)
{
	if (video)delete[] video;

	if (width <= 1 || height <= 1)return -1;

	videowidth = width;
	videoheight = height;
	video = new VideoBuffer[videowidth * videoheight];

	VideoBuffer clear(0, 0, 0, 255);
	for (uint32 h = 0; h < videoheight; h++)
		for (uint32 w = 0; w < videowidth; w++)
			video[h * videowidth + w] = clear;

	return 0;
}

EMSATTRIBUTE void* GETvideo()
{
	return (void*)video;
}

EMSATTRIBUTE void* GETdrawing()
{
	return (void*)drawing.data;
}

EMSATTRIBUTE uint32 GETdrawinglength()
{
	return drawing.size;
}	