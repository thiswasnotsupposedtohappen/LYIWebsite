#ifdef EMS
#include <emscripten.h>
#else
#define EMSCRIPTEN_KEEPALIVE
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
EMSCRIPTEN_KEEPALIVE Drawing* drawing = 0;
EMSCRIPTEN_KEEPALIVE uint32 drawinglength = 0;
uint32 drawingindex = 0;

int32 EMSCRIPTEN_KEEPALIVE main()
{
	cout << "Hello World" << endl;
	cout << "Size of Drawing: " << sizeof(Drawing) << endl;

#ifndef EMS
	int32 LoadDXF(char* file, uint32 length);
	LoadDXF((char*)"intermediated.txt", 0);
#endif
	return 0;
}

int32 EMSCRIPTEN_KEEPALIVE LoadDXF(char* file, uint32 length)
{
	cout << "LoadDXF In" << endl;

#ifdef EMS
	fstream filestream;
	filestream.open("intermediated.txt", ios::out);
	for (uint32 i = 0; i < length; i++)
		filestream << file[i];
	filestream.close();
#endif

	if (drawing)free(drawing);
	drawinglength = 0;
	drawingindex = 0;

	class DXFCounter : public DRW_Interface
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
			drawinglength++;
		}
		void addLine(const DRW_Line& data) override
		{
			drawinglength++;
		}
		void addRay(const DRW_Ray& data) override
		{
			drawinglength++;
		}
		void addXline(const DRW_Xline& data) override
		{
			drawinglength++;
		}
		void addArc(const DRW_Arc& data) override
		{
			drawinglength++;
		}
		void addCircle(const DRW_Circle& data) override
		{
			drawinglength++;
		}
		void addEllipse(const DRW_Ellipse& data) override
		{
			drawinglength++;
		}
		void addLWPolyline(const DRW_LWPolyline& data) override
		{
			drawinglength+= data.vertexnum;
		}
		void addPolyline(const DRW_Polyline& data) override
		{
			drawinglength+= data.vertexcount;
		}
		void addSpline(const DRW_Spline* data) override
		{
			test++;
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
			drawing[drawingindex].type = Drawing::LINE;
			drawing[drawingindex].geometrey.line.x1 = data.basePoint.x;
			drawing[drawingindex].geometrey.line.y1 = data.basePoint.y;
			drawing[drawingindex].geometrey.line.x2 = data.secPoint.x;
			drawing[drawingindex].geometrey.line.y2 = data.secPoint.y;
			drawingindex++;
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
			drawing[drawingindex].type = Drawing::ARC;
			drawing[drawingindex].geometrey.arc.x = data.basePoint.x;
			drawing[drawingindex].geometrey.arc.y = data.basePoint.y;
			drawing[drawingindex].geometrey.arc.r = data.radious;
			drawing[drawingindex].geometrey.arc.t1 = data.staangle;
			drawing[drawingindex].geometrey.arc.t2 = data.endangle;
			drawingindex++;
		}
		void addCircle(const DRW_Circle& data) override
		{
			drawing[drawingindex].type = Drawing::ARC;
			drawing[drawingindex].geometrey.arc.x = data.basePoint.x;
			drawing[drawingindex].geometrey.arc.y = data.basePoint.y;
			drawing[drawingindex].geometrey.arc.r = data.radious;
			drawing[drawingindex].geometrey.arc.t1 = 0;
			drawing[drawingindex].geometrey.arc.t2 = 0;
			drawingindex++;
		}
		void addEllipse(const DRW_Ellipse& data) override
		{
			test++;
		}
		void addLWPolyline(const DRW_LWPolyline& data) override
		{
			drawing[drawingindex].type = Drawing::LINE;
			drawing[drawingindex].geometrey.line.x1 = data.vertex->x;
			drawing[drawingindex].geometrey.line.y1 = data.vertex->y;
			drawing[drawingindex].geometrey.line.x2 = data.vertlist[0]->x;
			drawing[drawingindex].geometrey.line.y2 = data.vertlist[0]->y;
			drawingindex++;

			for (uint32 i = 1; i < data.vertexnum; i++)
			{
				drawing[drawingindex].type = Drawing::LINE;
				drawing[drawingindex].geometrey.line.x1 = data.vertlist[i - 1]->x;
				drawing[drawingindex].geometrey.line.y1 = data.vertlist[i - 1]->y;
				drawing[drawingindex].geometrey.line.x2 = data.vertlist[i - 0]->x;
				drawing[drawingindex].geometrey.line.y2 = data.vertlist[i - 0]->y;
				drawingindex++;
			}
		}
		void addPolyline(const DRW_Polyline& data) override
		{
			drawing[drawingindex].type = Drawing::LINE;
			drawing[drawingindex].geometrey.line.x1 = data.basePoint.x;
			drawing[drawingindex].geometrey.line.y1 = data.basePoint.y;
			drawing[drawingindex].geometrey.line.x2 = data.vertlist[0]->basePoint.x;
			drawing[drawingindex].geometrey.line.y2 = data.vertlist[0]->basePoint.y;
			drawingindex++;

			for (uint32 i = 1; i < data.vertexcount; i++)
			{
				drawing[drawingindex].type = Drawing::LINE;
				drawing[drawingindex].geometrey.line.x1 = data.vertlist[i - 1]->basePoint.x;
				drawing[drawingindex].geometrey.line.y1 = data.vertlist[i - 1]->basePoint.y;
				drawing[drawingindex].geometrey.line.x2 = data.vertlist[i - 0]->basePoint.x;
				drawing[drawingindex].geometrey.line.y2 = data.vertlist[i - 0]->basePoint.y;
				drawingindex++;
			}
		}
		void addSpline(const DRW_Spline* data) override
		{
			test++;
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
	DXFCounter counter;
	DXFReader reader;
	dxfRW dxf("intermediated.txt");
	if (!dxf.read(&counter, false)) { return -1; }
	drawing = (Drawing*)malloc(sizeof(Drawing) * drawinglength);
	
	if (!dxf.read(&reader, false)) { return -1; }

	cout << "drawing = " << (uint32)(void*)drawing << endl;
	cout << "drawinglength = "<< drawinglength << endl;
	cout << "LoadDXF Out" << endl;
	return 0;
}

extern "C"
{
	int32 EMSCRIPTEN_KEEPALIVE LoadDXFExport(char* file,uint32 length)
	{
		return LoadDXF(file,length);
	}

	uint32 EMSCRIPTEN_KEEPALIVE GETdrawing()
	{
		return (uint32)drawing;
	}
	uint32 EMSCRIPTEN_KEEPALIVE GETdrawinglength()
	{
		return drawinglength;
	}	
}