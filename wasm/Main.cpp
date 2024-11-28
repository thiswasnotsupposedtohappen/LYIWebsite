#include <emscripten.h>
#include <iostream>
#include <fstream>
extern "C"
{
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
}
using namespace std;
#include "PoDefinition.h"
#include "PoUtilities.h"
#include "PoMath.h"
#include "libdxfrw.h"
#include "intern/drw_dbg.h"
#pragma comment (lib, "dxfrw.lib")

EMSCRIPTEN_KEEPALIVE
int main() 
{
	cout << "Hello World" << endl;
	return 0;
}

EMSCRIPTEN_KEEPALIVE
uint32 LoadDXF(char* filepath)
{
	cout << "LoadDXF In" << endl;
	uint32 entities = 0;
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
			test++;
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
			test++;
		}
		void addCircle(const DRW_Circle& data) override
		{
			test++;
		}
		void addEllipse(const DRW_Ellipse& data) override
		{
			test++;
		}
		void addLWPolyline(const DRW_LWPolyline& data) override
		{
			test++;
		}
		void addPolyline(const DRW_Polyline& data) override
		{
			test++;
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

	DXFReader reader;
	dxfRW dxf(filepath);
	dxf.setDebug(DRW::DebugLevel::Debug);
	if (!dxf.read(&reader, false))
	{
		cout << "Failed load: " << filepath << endl;
		return -1;
	}
	entities = reader.CopyData();
	cout << entities << endl;
	cout << "LoadDXF Out" << endl;
	return entities;
}

EMSCRIPTEN_KEEPALIVE
uint32 TestData(uint32 length, uint8* data)
{
	cout << "TestData In" << endl;
	for (uint32 i = 0; i < length; i++)
	{
		cout << data[i];
	}
	cout << endl;
	cout << "TestData Out" << endl;
	return length;
}


extern "C"
{
	EMSCRIPTEN_KEEPALIVE uint32 LoadDXFExport()
	{
		cout << "LoadDXFExport In" << endl;
		uint32 entities = LoadDXF((char*)"/input.dxf");		
		cout << "LoadDXFExport Out" << endl;
		return entities;
	}

	EMSCRIPTEN_KEEPALIVE uint32 TestDataExport(uint32 length, uint8* data)
	{
		cout << "TestDataExport In" << endl;
		uint32 entities = TestData(length, data);
		cout << "TestDataExport Out" << endl;
		return entities;
	}
}

//-s NO_EXIT_RUNTIME=1 -s EXPORTED_RUNTIME_METHODS=ccall,cwrap --preload-file Test.dxf 