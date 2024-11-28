struct UserInterface
{
	static const uint32 imagemaxcount = 20;
	static const uint32 tabmaxcount = 20;
	static const uint32 shapeboxmaxcount = 20;
	static const uint32 indicatormaxcount = 20;
	static const uint32 buttonmaxcount = 100;
	static const uint32 textboxmaxcount = 100;
	static const uint32 rollboxmaxcount = 20;

	static uint32 imagecount;
	static uint32 tabcount;
	static uint32 shapeboxcount;
	static uint32 indicatorcount;
	static uint32 buttoncount;
	static uint32 textboxcount;
	static uint32 rollboxcount;

	static Graphics* graphics;
	static Keyboard* keyboard;
	static Mouse* mouse;

	struct Geometrey
	{
		uint32 handle = 0;
		int32 posx = 0;
		int32 posy = 0;
		int32 width = 0;
		int32 height = 0;
	};
	
	uint32 NewHandleImage()
	{
		return imagecount++;
	}
	uint32 NewHandleTab()
	{
		return tabcount++;
	}
	uint32 NewHandleShapeBox()
	{
		return shapeboxcount++;
	}
	uint32 NewHandleIndicator()
	{
		return indicatorcount++;
	}
	uint32 NewHandleButton()
	{
		return buttoncount++;
	}
	uint32 NewHandleTextBox()
	{
		return textboxcount++;
	}
	uint32 NewHandleRollBox()
	{
		return rollboxcount++;
	}

	struct Text : Geometrey
	{
		uint32 threadx;
		uint32 thready;
		struct ConstantBufferData
		{
			int32 charx;
			int32 chary;
			int32 drawx;
			int32 drawy;
			float4 color;
			float32 size;
			float3 pad;
		}cbd;
		Graphics::ConstantBuffer* constantbuffer = 0;
		Graphics::Texture* texture = 0;
		Graphics::ComputeShader* computeshader = 0;
		bool Initialize()
		{
			if (graphics->ComputeShaderCreate(&computeshader, "ComputeShaderText.hlsl"))return 1;
			if (graphics->ConstantBufferCreate(&constantbuffer, sizeof(cbd), &cbd, VARIABLE))return 1;
			if (graphics->TextureCreate(&texture, "fontmonospace.jpg", R32G32B32A32_FLOAT, CONSTANT, 1))return 1;
			return 0;
		}
		void Draw(int32 x, int32 y, char* string, float64 _size, float4 _color)
		{
			posx = x;
			posy = y;
			width = _size * strnlen_s(string, 1024);
			height = _size;
			cbd.color = _color;
			cbd.size = (float32)(_size / 72.0);
			graphics->ComputeShaderSet(computeshader);
			graphics->SetUnorderedAccessView();
			graphics->ConstantBufferSet(constantbuffer, 0, 0, 0, 0, 0, 0, 1);
			graphics->TextureSetShaderResouceView(texture, 0, 0, 0, 0, 0, 0, 1);
			for (int i = 0; i < 1024; i++)
			{
				switch (string[i])
				{
					case '0': {cbd.charx = 72 *  0; cbd.chary = 144 * 0; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case '1': {cbd.charx = 72 *  1; cbd.chary = 144 * 0; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case '2': {cbd.charx = 72 *  2; cbd.chary = 144 * 0; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case '3': {cbd.charx = 72 *  3; cbd.chary = 144 * 0; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case '4': {cbd.charx = 72 *  4; cbd.chary = 144 * 0; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case '5': {cbd.charx = 72 *  5; cbd.chary = 144 * 0; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case '6': {cbd.charx = 72 *  6; cbd.chary = 144 * 0; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case '7': {cbd.charx = 72 *  7; cbd.chary = 144 * 0; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case '8': {cbd.charx = 72 *  8; cbd.chary = 144 * 0; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case '9': {cbd.charx = 72 *  9; cbd.chary = 144 * 0; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case 'a': {cbd.charx = 72 *  0; cbd.chary = 144 * 1; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case 'b': {cbd.charx = 72 *  1; cbd.chary = 144 * 1; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case 'c': {cbd.charx = 72 *  2; cbd.chary = 144 * 1; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case 'd': {cbd.charx = 72 *  3; cbd.chary = 144 * 1; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case 'e': {cbd.charx = 72 *  4; cbd.chary = 144 * 1; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case 'f': {cbd.charx = 72 *  5; cbd.chary = 144 * 1; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case 'g': {cbd.charx = 72 *  6; cbd.chary = 144 * 1; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case 'h': {cbd.charx = 72 *  7; cbd.chary = 144 * 1; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case 'i': {cbd.charx = 72 *  8; cbd.chary = 144 * 1; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case 'j': {cbd.charx = 72 *  9; cbd.chary = 144 * 1; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case 'k': {cbd.charx = 72 * 10; cbd.chary = 144 * 1; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case 'l': {cbd.charx = 72 * 11; cbd.chary = 144 * 1; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case 'm': {cbd.charx = 72 * 12; cbd.chary = 144 * 1; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case 'n': {cbd.charx = 72 * 13; cbd.chary = 144 * 1; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case 'o': {cbd.charx = 72 * 14; cbd.chary = 144 * 1; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case 'p': {cbd.charx = 72 * 15; cbd.chary = 144 * 1; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case 'q': {cbd.charx = 72 * 16; cbd.chary = 144 * 1; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case 'r': {cbd.charx = 72 * 17; cbd.chary = 144 * 1; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case 's': {cbd.charx = 72 * 18; cbd.chary = 144 * 1; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case 't': {cbd.charx = 72 * 19; cbd.chary = 144 * 1; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case 'u': {cbd.charx = 72 * 20; cbd.chary = 144 * 1; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case 'v': {cbd.charx = 72 * 21; cbd.chary = 144 * 1; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case 'w': {cbd.charx = 72 * 22; cbd.chary = 144 * 1; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case 'x': {cbd.charx = 72 * 23; cbd.chary = 144 * 1; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case 'y': {cbd.charx = 72 * 24; cbd.chary = 144 * 1; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case 'z': {cbd.charx = 72 * 25; cbd.chary = 144 * 1; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case 'A': {cbd.charx = 72 *  0; cbd.chary = 144 * 2; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case 'B': {cbd.charx = 72 *  1; cbd.chary = 144 * 2; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case 'C': {cbd.charx = 72 *  2; cbd.chary = 144 * 2; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case 'D': {cbd.charx = 72 *  3; cbd.chary = 144 * 2; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case 'E': {cbd.charx = 72 *  4; cbd.chary = 144 * 2; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case 'F': {cbd.charx = 72 *  5; cbd.chary = 144 * 2; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case 'G': {cbd.charx = 72 *  6; cbd.chary = 144 * 2; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case 'H': {cbd.charx = 72 *  7; cbd.chary = 144 * 2; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case 'I': {cbd.charx = 72 *  8; cbd.chary = 144 * 2; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case 'J': {cbd.charx = 72 *  9; cbd.chary = 144 * 2; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case 'K': {cbd.charx = 72 * 10; cbd.chary = 144 * 2; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case 'L': {cbd.charx = 72 * 11; cbd.chary = 144 * 2; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case 'M': {cbd.charx = 72 * 12; cbd.chary = 144 * 2; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case 'N': {cbd.charx = 72 * 13; cbd.chary = 144 * 2; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case 'O': {cbd.charx = 72 * 14; cbd.chary = 144 * 2; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case 'P': {cbd.charx = 72 * 15; cbd.chary = 144 * 2; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case 'Q': {cbd.charx = 72 * 16; cbd.chary = 144 * 2; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case 'R': {cbd.charx = 72 * 17; cbd.chary = 144 * 2; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case 'S': {cbd.charx = 72 * 18; cbd.chary = 144 * 2; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case 'T': {cbd.charx = 72 * 19; cbd.chary = 144 * 2; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case 'U': {cbd.charx = 72 * 20; cbd.chary = 144 * 2; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case 'V': {cbd.charx = 72 * 21; cbd.chary = 144 * 2; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case 'W': {cbd.charx = 72 * 22; cbd.chary = 144 * 2; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case 'X': {cbd.charx = 72 * 23; cbd.chary = 144 * 2; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case 'Y': {cbd.charx = 72 * 24; cbd.chary = 144 * 2; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case 'Z': {cbd.charx = 72 * 25; cbd.chary = 144 * 2; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case '`': {cbd.charx = 72 *  0; cbd.chary = 144 * 3; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case '-': {cbd.charx = 72 *  1; cbd.chary = 144 * 3; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case '=': {cbd.charx = 72 *  2; cbd.chary = 144 * 3; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case '[': {cbd.charx = 72 *  3; cbd.chary = 144 * 3; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case ']': {cbd.charx = 72 *  4; cbd.chary = 144 * 3; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case '\\':{cbd.charx = 72 *  5; cbd.chary = 144 * 3; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case ';': {cbd.charx = 72 *  6; cbd.chary = 144 * 3; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case '\'':{cbd.charx = 72 *  7; cbd.chary = 144 * 3; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case ',': {cbd.charx = 72 *  8; cbd.chary = 144 * 3; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case '.': {cbd.charx = 72 *  9; cbd.chary = 144 * 3; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case '/': {cbd.charx = 72 * 10; cbd.chary = 144 * 3; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case '~': {cbd.charx = 72 * 11; cbd.chary = 144 * 3; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case '!': {cbd.charx = 72 * 12; cbd.chary = 144 * 3; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case '@': {cbd.charx = 72 * 13; cbd.chary = 144 * 3; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case '#': {cbd.charx = 72 * 14; cbd.chary = 144 * 3; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case '$': {cbd.charx = 72 * 15; cbd.chary = 144 * 3; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case '%': {cbd.charx = 72 * 16; cbd.chary = 144 * 3; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case '^': {cbd.charx = 72 * 17; cbd.chary = 144 * 3; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case '&': {cbd.charx = 72 * 18; cbd.chary = 144 * 3; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case '*': {cbd.charx = 72 * 19; cbd.chary = 144 * 3; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case '(': {cbd.charx = 72 * 20; cbd.chary = 144 * 3; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case ')': {cbd.charx = 72 * 21; cbd.chary = 144 * 3; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case '_': {cbd.charx = 72 * 22; cbd.chary = 144 * 3; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case '+': {cbd.charx = 72 * 23; cbd.chary = 144 * 3; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case '{': {cbd.charx = 72 * 24; cbd.chary = 144 * 3; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case '}': {cbd.charx = 72 * 25; cbd.chary = 144 * 3; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case '|': {cbd.charx = 72 * 26; cbd.chary = 144 * 3; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case ':': {cbd.charx = 72 * 27; cbd.chary = 144 * 3; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case '"': {cbd.charx = 72 * 28; cbd.chary = 144 * 3; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case '<': {cbd.charx = 72 * 29; cbd.chary = 144 * 3; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case '>': {cbd.charx = 72 * 30; cbd.chary = 144 * 3; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case '?': {cbd.charx = 72 * 31; cbd.chary = 144 * 3; cbd.drawx = x + ((int32)(_size * (float64)i)); cbd.drawy = y; }break;
					case ' ': {}continue;
					default : return;
				}
				graphics->ConstantBufferUpdate(constantbuffer);
				graphics->Compute(5, 5, 1);
			}
		}
		void DrawRight(Geometrey geometry, int32 spacing, char* string, float64 _size, float4 _color)
		{
			Draw(geometry.posx + geometry.width + spacing, geometry.posy, string, _size, _color);
		}
		void DrawLeft(Geometrey geometry, int32 spacing, char* string, float64 _size, float4 _color)
		{
			Draw(geometry.posx - width - spacing, geometry.posy, string, _size, _color);
		}
		void DrawAbove(Geometrey geometry, int32 spacing, char* string, float64 _size, float4 _color)
		{
			Draw(geometry.posx, geometry.posy - height - spacing, string, _size, _color);
		}
		void DrawBelow(Geometrey geometry, int32 spacing, char* string, float64 _size, float4 _color)
		{
			Draw(geometry.posx, geometry.posy + geometry.height + spacing, string, _size, _color);
		}
		void Release()
		{
			delete texture;
			delete constantbuffer;
			delete computeshader;
			//delete this;
		}
	};static Text text;
	struct ShapeBox : Geometrey
	{
		float4 color;

		uint32 threadx;
		uint32 thready;
		struct ConstantBufferData
		{
			int32 posx;
			int32 posy;
			int32 width;
			int32 height;
			float4 color;
		}cbd;
		Graphics::ConstantBuffer* constantbuffer = 0;
		Graphics::ComputeShader* computeshader = 0;

		bool Initialize(uint32 _width,uint32 _height, float4 _color)
		{
			width = _width;
			height = _height;
			color = _color;

			threadx = (width / 32) + 1;
			thready = (height / 32) + 1;
			if (graphics->ComputeShaderCreate(&computeshader, "ComputeShaderShapeBox.hlsl"))return 1;
			if (graphics->ConstantBufferCreate(&constantbuffer, sizeof(ConstantBufferData), &cbd, VARIABLE))return 1;
			cbd.posx = 0;
			cbd.posy = 0;
			cbd.width = width;
			cbd.height = height;
			cbd.color = color;
			return 0;
		}
		void Draw(int32 x, int32 y, uint32 _width, uint32 _height)
		{
			posx = x;
			posy = y;
			width = _width;
			height = _height;

			cbd.posx = x;
			cbd.posy = y;	
			cbd.width = width;
			cbd.height = height;
			threadx = (width / 32) + 1;
			thready = (height / 32) + 1;
			graphics->ComputeShaderSet(computeshader);
			graphics->SetUnorderedAccessView();
			graphics->ConstantBufferUpdate(constantbuffer);
			graphics->ConstantBufferSet(constantbuffer, 0, 0, 0, 0, 0, 0, 1);
			graphics->Compute(threadx, thready, 1);
		}
		void Draw(int32 x, int32 y)
		{
			Draw(x, y, width, height);
		}
		void Release()
		{
			delete computeshader;
			delete constantbuffer;
			//delete this;
		}
	}shapebox[shapeboxmaxcount];
	struct Image : Geometrey
	{
		uint32 threadx;
		uint32 thready;
		struct ConstantBufferData
		{
			int32 posx;
			int32 posy;
			int32 width;
			int32 heigth;
			float32 scalex;
			float32 scaley;
			float2 pad;
		}cbd;
		Graphics::ConstantBuffer* constantbuffer = 0;
		Graphics::Texture* texture = 0;
		Graphics::ComputeShader* computeshader = 0;

		bool Initialize(int32 _width, int32 _height, char* _texturefilename, float64 _scalex, float64 _scaley)
		{
			width = (int32)((float64)_width * _scalex);
			height = (int32)((float64)_height * _scaley);

			threadx = (((uint32)(((float64)_width) * _scalex)) / 32) + 1;
			thready = (((uint32)(((float64)_height) * _scaley)) / 32) + 1;
			if (graphics->ComputeShaderCreate(&computeshader, "ComputeShaderimage.hlsl"))return 1;
			if (graphics->ConstantBufferCreate(&constantbuffer, sizeof(ConstantBufferData), &cbd, VARIABLE))return 1;
			if (graphics->TextureCreate(&texture, _texturefilename, R32G32B32A32_FLOAT, CONSTANT, 1))return 1;
			cbd.posx = 0;
			cbd.posy = 0;
			cbd.width = width;
			cbd.heigth = height;
			cbd.scalex = (float32)_scalex;
			cbd.scaley = (float32)_scaley;
			return 0;
		}
		void Draw(int32 x, int32 y)
		{
			cbd.posx = x;
			cbd.posy = y;
			graphics->ComputeShaderSet(computeshader);
			graphics->SetUnorderedAccessView();
			graphics->ConstantBufferUpdate(constantbuffer);
			graphics->ConstantBufferSet(constantbuffer, 0, 0, 0, 0, 0, 0, 1);
			graphics->TextureSetShaderResouceView(texture, 0, 0, 0, 0, 0, 0, 1);
			graphics->Compute(threadx, thready, 1);
		}
		void Release()
		{
			delete texture;
			delete computeshader;
			delete constantbuffer;
			//delete this;
		}
	}image[imagemaxcount];
	struct Button : Geometrey
	{
		float4 colornormal;
		float4 colorhover;
		float4 colorpressed;
		String string;
		float64 textsize;
		float4 textcolor;
		bool enable = 1;
		bool press = 0;

		uint32 threadx;
		uint32 thready;
		struct ConstantBufferData
		{
			int32 posx;
			int32 posy;
			int32 width;
			int32 height;
			float4 color;
		}cbd;
		Graphics::ConstantBuffer* constantbuffer = 0;
		Graphics::ComputeShader* computeshader = 0;

		bool Initialize(uint32 _width, uint32 _height,float4 _normalcolor,float4 _hovercolor,float4 _pressedcolor,char* _buttontext,float64 _textsize,float4 _textcolor)
		{
			width = _width;
			height = _height;
			colornormal = _normalcolor;
			colorhover = _hovercolor;
			colorpressed = _pressedcolor;
			string = _buttontext;
			textsize = _textsize;
			textcolor = _textcolor;

			threadx = (width / 32) + 1;
			thready = (height / 32) + 1;
			if (graphics->ComputeShaderCreate(&computeshader, "ComputeShaderButton.hlsl"))return 1;
			if (graphics->ConstantBufferCreate(&constantbuffer, sizeof(ConstantBufferData), &cbd, VARIABLE))return 1;
			cbd.posx = 0;
			cbd.posy = 0;
			cbd.width = width;
			cbd.height = height;
			cbd.color = _normalcolor;
			return 0;
		}
		void Draw(int32 x, int32 y)
		{
			posx = x;
			posy = y;

			cbd.posx = x;
			cbd.posy = y;
			if (enable)
			{
				cbd.color = colornormal;
				if (mouse->X() > posx && mouse->X() < (posx + width) && mouse->Y() > posy && mouse->Y() < (posy + height))
				{
					if (mouse->LeftMouseButton())
						cbd.color = colorpressed;
					else
						cbd.color = colorhover;
					if (mouse->LeftMouseButtonDown())press = true;
				}
			}
			else
			{
				cbd.color = float4(0.7f, 0.7f, 0.7f, 1.0f);
			}

			graphics->ComputeShaderSet(computeshader);
			graphics->SetUnorderedAccessView();
			graphics->ConstantBufferUpdate(constantbuffer);
			graphics->ConstantBufferSet(constantbuffer, 0, 0, 0, 0, 0, 0, 1);
			graphics->Compute(threadx, thready, 1);			

			int32 cookieposx = text.posx;
			int32 cookieposy = text.posy;
			int32 cookiewidth = text.width;
			int32 cookieheight = text.height;
			text.Draw(posx + (width / 2) - (int32)((float64)strlen(string.string) * textsize / 2.0), posy + (height / 2) - (int32)(textsize * 2.0 / 2.0) - 1, string.string, textsize, textcolor);
			text.posx = cookieposx;
			text.posy = cookieposy;
			text.width = cookiewidth;
			text.height = cookieheight;

		}
		void DrawRight(Geometrey geometry, int32 spacing)
		{
			Draw(geometry.posx + geometry.width + spacing, geometry.posy);
		}
		void DrawLeft(Geometrey geometry, int32 spacing)
		{
			Draw(geometry.posx - width - spacing, geometry.posy);
		}
		void DrawAbove(Geometrey geometry, int32 spacing)
		{
			Draw(geometry.posx, geometry.posy - height - spacing);
		}
		void DrawBelow(Geometrey geometry, int32 spacing)
		{
			Draw(geometry.posx, geometry.posy + geometry.height + spacing);
		}
		void Release()
		{
			delete computeshader;
			delete constantbuffer;
			//delete this;
		}
	}button[buttonmaxcount];
	struct Tab : Geometrey
	{
		float4 colornormal;
		float4 colorhover;
		float4 colorpressed;
		String string;
		float64 textsize;
		float4 textcolor;
		bool enable = 1;
		bool press = 0;

		uint32 threadx;
		uint32 thready;
		struct ConstantBufferData
		{
			int32 posx;
			int32 posy;
			int32 width;
			int32 height;
			float4 color;
		}cbd;
		Graphics::ConstantBuffer* constantbuffer = 0;
		Graphics::ComputeShader* computeshader = 0;

		bool Initialize(uint32 _width, uint32 _height, float4 _normalcolor, float4 _hovercolor, float4 _pressedcolor, char* _buttontext, float64 _textsize, float4 _textcolor)
		{
			width = _width;
			height = _height;
			colornormal = _normalcolor;
			colorhover = _hovercolor;
			colorpressed = _pressedcolor;
			string = _buttontext;
			textsize = _textsize;
			textcolor = _textcolor;

			threadx = (width / 32) + 1;
			thready = (height / 32) + 1;
			if (graphics->ComputeShaderCreate(&computeshader, "ComputeShaderTab.hlsl"))return 1;
			if (graphics->ConstantBufferCreate(&constantbuffer, sizeof(ConstantBufferData), &cbd, VARIABLE))return 1;
			cbd.posx = 0;
			cbd.posy = 0;
			cbd.width = width;
			cbd.height = height;
			cbd.color = _normalcolor;
			return 0;
		}
		void Draw(int32 x, int32 y)
		{
			posx = x;
			posy = y;

			cbd.posx = x;
			cbd.posy = y;
			if (enable)
			{
				cbd.color = colornormal;
				if (mouse->X() > posx && mouse->X() < (posx + width) && mouse->Y() > posy && mouse->Y() < (posy + height))
				{
					if (mouse->LeftMouseButton())
						cbd.color = colorpressed;
					else
						cbd.color = colorhover;
					if (mouse->LeftMouseButtonDown())press = true;
				}
			}
			else
			{
				cbd.color = float4(0.7f, 0.7f, 0.7f, 1.0f);
			}

			graphics->ComputeShaderSet(computeshader);
			graphics->SetUnorderedAccessView();
			graphics->ConstantBufferUpdate(constantbuffer);
			graphics->ConstantBufferSet(constantbuffer, 0, 0, 0, 0, 0, 0, 1);
			graphics->Compute(threadx, thready, 1);

			text.Draw(posx + (width / 2) - (int32)((float64)strlen(string.string) * textsize / 2.0), posy + (height / 2) - (int32)(textsize * 2.0 / 2.0) - 1, string.string, textsize, textcolor);
		}
		void DrawRight(Geometrey geometry, int32 spacing)
		{
			Draw(geometry.posx + geometry.width + spacing, geometry.posy);
		}
		void DrawLeft(Geometrey geometry, int32 spacing)
		{
			Draw(geometry.posx - width - spacing, geometry.posy);
		}
		void DrawAbove(Geometrey geometry, int32 spacing)
		{
			Draw(geometry.posx, geometry.posy - height - spacing);
		}
		void DrawBelow(Geometrey geometry, int32 spacing)
		{
			Draw(geometry.posx, geometry.posy + geometry.height + spacing);
		}
		void Release()
		{
			delete computeshader;
			delete constantbuffer;
			//delete this;
		}
	}tab[tabmaxcount];
	struct TextBox : Geometrey
	{
		float4 colorinactive;
		float4 coloractive;
		String string;
		float64 textsize;
		float4 textcolor;
		bool enable = 1;
		bool active = 0;
		bool press = 0;

		uint32 threadx;
		uint32 thready;
		struct ConstantBufferData
		{
			int32 posx;
			int32 posy;
			int32 width;
			int32 height;
			float4 color;
		}cbd;
		Graphics::ConstantBuffer* constantbuffer = 0;
		Graphics::ComputeShader* computeshader = 0;

		bool Initialize(uint32 _width, uint32 _height, float4 _colorinactive, float4 _coloractive, float64 _textsize, float4 _textcolor)
		{
			colorinactive = _colorinactive;
			coloractive = _coloractive;
			width = _width;
			height = _height;
			textsize = _textsize;
			textcolor = _textcolor;
			enable = 1;

			threadx = (width / 32) + 1;
			thready = (height / 32) + 1;
			if (graphics->ComputeShaderCreate(&computeshader, "ComputeShaderTextBox.hlsl"))return 1;
			if (graphics->ConstantBufferCreate(&constantbuffer, sizeof(ConstantBufferData), &cbd, VARIABLE))return 1;
			cbd.posx = 0;
			cbd.posy = 0;
			cbd.width = width;
			cbd.height = height;
			return 0;
		}
		void Draw(int32 x, int32 y,int32 _width,int32 _height)
		{
			posx = x;
			posy = y;
			width = _width;
			height = _height;
			if (mouse->LeftMouseButton())
			{
				if ((mouse->X() > posx) && (mouse->X() < (posx + width)) && (mouse->Y() > posy) && (mouse->Y() < (posy + height)))
					active = true;
				else
					active = false;
			}
			
			if (enable && active && keyboard->Key(DIK_LCONTROL) == 0)
			{
				if (keyboard->KeyDown(DIK_0))string + "0";
				if (keyboard->KeyDown(DIK_1))string + "1";
				if (keyboard->KeyDown(DIK_2))string + "2";
				if (keyboard->KeyDown(DIK_3))string + "3";
				if (keyboard->KeyDown(DIK_4))string + "4";
				if (keyboard->KeyDown(DIK_5))string + "5";
				if (keyboard->KeyDown(DIK_6))string + "6";
				if (keyboard->KeyDown(DIK_7))string + "7";
				if (keyboard->KeyDown(DIK_8))string + "8";
				if (keyboard->KeyDown(DIK_9))string + "9";
				if (keyboard->KeyDown(DIK_NUMPAD0))string + "0";
				if (keyboard->KeyDown(DIK_NUMPAD1))string + "1";
				if (keyboard->KeyDown(DIK_NUMPAD2))string + "2";
				if (keyboard->KeyDown(DIK_NUMPAD3))string + "3";
				if (keyboard->KeyDown(DIK_NUMPAD4))string + "4";
				if (keyboard->KeyDown(DIK_NUMPAD5))string + "5";
				if (keyboard->KeyDown(DIK_NUMPAD6))string + "6";
				if (keyboard->KeyDown(DIK_NUMPAD7))string + "7";
				if (keyboard->KeyDown(DIK_NUMPAD8))string + "8";
				if (keyboard->KeyDown(DIK_NUMPAD9))string + "9";
				if (keyboard->KeyDown(DIK_A))string + "A";
				if (keyboard->KeyDown(DIK_B))string + "B";
				if (keyboard->KeyDown(DIK_C))string + "C";
				if (keyboard->KeyDown(DIK_D))string + "D";
				if (keyboard->KeyDown(DIK_E))string + "E";
				if (keyboard->KeyDown(DIK_F))string + "F";
				if (keyboard->KeyDown(DIK_G))string + "G";
				if (keyboard->KeyDown(DIK_H))string + "H";
				if (keyboard->KeyDown(DIK_I))string + "I";
				if (keyboard->KeyDown(DIK_J))string + "J";
				if (keyboard->KeyDown(DIK_K))string + "K";
				if (keyboard->KeyDown(DIK_L))string + "L";
				if (keyboard->KeyDown(DIK_M))string + "M";
				if (keyboard->KeyDown(DIK_N))string + "N";
				if (keyboard->KeyDown(DIK_O))string + "O";
				if (keyboard->KeyDown(DIK_P))string + "P";
				if (keyboard->KeyDown(DIK_Q))string + "Q";
				if (keyboard->KeyDown(DIK_R))string + "R";
				if (keyboard->KeyDown(DIK_S))string + "S";
				if (keyboard->KeyDown(DIK_T))string + "T";
				if (keyboard->KeyDown(DIK_U))string + "U";
				if (keyboard->KeyDown(DIK_V))string + "V";
				if (keyboard->KeyDown(DIK_W))string + "W";
				if (keyboard->KeyDown(DIK_X))string + "X";
				if (keyboard->KeyDown(DIK_Y))string + "Y";
				if (keyboard->KeyDown(DIK_Z))string + "Z";
				if (keyboard->KeyDown(DIK_SPACE))string + " ";
				if (keyboard->KeyDown(DIK_PERIOD))string + ".";
				if (keyboard->KeyDown(DIK_MINUS))string + "-";
				if (keyboard->KeyDown(DIK_EQUALS))string + "+";
				if (keyboard->KeyDown(DIK_NUMPADPLUS))string + "+";
				if (keyboard->KeyDown(DIK_NUMPADMINUS))string + "-";
				if (keyboard->KeyDown(DIK_NUMPADPERIOD))string + ".";
				if (keyboard->KeyDown(DIK_NUMPADSTAR))string + "*";
				if (keyboard->KeyDown(DIK_BACKSLASH))string + "\\";
				if (keyboard->KeyDown(DIK_BACKSPACE) && string.length > 1)-string;
				if (keyboard->KeyDown(DIK_DELETE) && string.length > 1) string.Release();
				if (keyboard->KeyDown(DIK_RETURN) && string.length > 1)press = 1;
				if (keyboard->KeyDown(DIK_NUMPADENTER) && string.length > 1)press = 1;
			}

			cbd.posx = x;
			cbd.posy = y;
			cbd.width = width;
			cbd.height = height;
			threadx = (width / 32) + 1;
			thready = (height / 32) + 1;
			if (active && enable)cbd.color = coloractive; else cbd.color = colorinactive;
			graphics->ComputeShaderSet(computeshader);
			graphics->SetUnorderedAccessView();
			graphics->ConstantBufferUpdate(constantbuffer);
			graphics->ConstantBufferSet(constantbuffer, 0, 0, 0, 0, 0, 0, 1);
			graphics->Compute(threadx, thready, 1);

			int32 cookieposx = text.posx;
			int32 cookieposy = text.posy;
			int32 cookiewidth = text.width;
			int32 cookieheight = text.height;
			if(string.length)
				text.Draw(posx + 15, posy + (height / 2) - (int32)(textsize * 2.0 / 2.0), string.string, textsize, textcolor);
			text.posx = cookieposx;
			text.posy = cookieposy;
			text.width = cookiewidth;
			text.height = cookieheight;
		}
		void Draw(int32 x, int32 y)
		{
			Draw(x, y, width, height);
		}
		void DrawRight(Geometrey geometry, int32 spacing)
		{
			Draw(geometry.posx + geometry.width + spacing, geometry.posy);
		}
		void DrawLeft(Geometrey geometry, int32 spacing)
		{
			Draw(geometry.posx - width - spacing, geometry.posy);
		}
		void DrawAbove(Geometrey geometry, int32 spacing)
		{
			Draw(geometry.posx, geometry.posy - height - spacing);
		}
		void DrawBelow(Geometrey geometry, int32 spacing)
		{
			Draw(geometry.posx, geometry.posy + geometry.height + spacing);
		}
		void Release()
		{
			delete computeshader;
			delete constantbuffer;
			//delete this;
		}
	}textbox[textboxmaxcount];
	struct RollBox : Geometrey
	{
		float4 colorinactive;
		float4 coloractive;
		String string;
		float64 value;
		float64 stepsize;
		float64 rangemin;
		float64 rangemax;
		float64 textsize;
		float4 textcolor;
		bool enable = 1;
		bool active = 0;
		bool press = 0;
		bool change = 0;

		uint32 threadx;
		uint32 thready;
		struct ConstantBufferData
		{
			int32 posx;
			int32 posy;
			int32 width;
			int32 height;
			float4 color;
		}cbd;
		Graphics::ConstantBuffer* constantbuffer = 0;
		Graphics::ComputeShader* computeshader = 0;

		bool Initialize(uint32 _width, uint32 _height, float4 _colorinactive, float4 _coloractive, float64 _textsize, float4 _textcolor, float64 _value, float64 _stepsize, float64 _rangemin, float64 _rangemax)
		{
			char charbuffer[64];
			colorinactive = _colorinactive;
			coloractive = _coloractive;
			width = _width;
			height = _height;
			textsize = _textsize;
			textcolor = _textcolor;
			enable = 1;
			value = _value;
			stepsize = _stepsize;
			rangemin = _rangemin;
			rangemax = _rangemax;
			string = ftoa(value, charbuffer);

			threadx = (width / 32) + 1;
			thready = (height / 32) + 1;
			if (graphics->ComputeShaderCreate(&computeshader, "ComputeShaderTextBox.hlsl"))return 1;
			if (graphics->ConstantBufferCreate(&constantbuffer, sizeof(ConstantBufferData), &cbd, VARIABLE))return 1;
			cbd.posx = 0;
			cbd.posy = 0;
			cbd.width = width;
			cbd.height = height;
			return 0;
		}
		void Draw(int32 x, int32 y, int32 _width, int32 _height)
		{
			char charbuffer[64];
			posx = x;
			posy = y;
			width = _width;
			height = _height;
			if (mouse->LeftMouseButton())
			{
				if ((mouse->X() > posx) && (mouse->X() < (posx + width)) && (mouse->Y() > posy) && (mouse->Y() < (posy + height)))
					active = true;
				else
					active = false;
			}

			if (enable && active)
			{
				if (keyboard->KeyDown(DIK_UP))
				{
					if(keyboard->Key(DIK_LSHIFT))
						value += (stepsize * 10.0);
					else if (keyboard->Key(DIK_LCONTROL))
						value += (stepsize * 0.1);
					else
						value += stepsize;

					if (value < rangemin)
						value = rangemin;
					if (value > rangemax)
						value = rangemax;

					string = ftoa(value, charbuffer);

					change = 1;
				}
				if (keyboard->KeyDown(DIK_DOWN))
				{
					if (keyboard->Key(DIK_LSHIFT))
						value -= (stepsize * 10.0);
					else if (keyboard->Key(DIK_LCONTROL))
						value -= (stepsize * 0.1);
					else
						value -= stepsize;
					if (value < rangemin)
						value = rangemin;
					if (value > rangemax)
						value = rangemax;

					string = ftoa(value, charbuffer);

					change = 1;
				}
			}

			cbd.posx = x;
			cbd.posy = y;
			cbd.width = width;
			cbd.height = height;
			threadx = (width / 32) + 1;
			thready = (height / 32) + 1;
			if (active && enable)cbd.color = coloractive; else cbd.color = colorinactive;
			graphics->ComputeShaderSet(computeshader);
			graphics->SetUnorderedAccessView();
			graphics->ConstantBufferUpdate(constantbuffer);
			graphics->ConstantBufferSet(constantbuffer, 0, 0, 0, 0, 0, 0, 1);
			graphics->Compute(threadx, thready, 1);

			int32 cookieposx = text.posx;
			int32 cookieposy = text.posy;
			int32 cookiewidth = text.width;
			int32 cookieheight = text.height;
			if (string.length)
				text.Draw(posx + 15, posy + (height / 2) - (int32)(textsize * 2.0 / 2.0), string.string, textsize, textcolor);
			text.posx = cookieposx;
			text.posy = cookieposy;
			text.width = cookiewidth;
			text.height = cookieheight;
		}
		void Draw(int32 x, int32 y)
		{
			Draw(x, y, width, height);
		}
		void DrawRight(Geometrey geometry, int32 spacing)
		{
			Draw(geometry.posx + geometry.width + spacing, geometry.posy);
		}
		void DrawLeft(Geometrey geometry, int32 spacing)
		{
			Draw(geometry.posx - width - spacing, geometry.posy);
		}
		void DrawAbove(Geometrey geometry, int32 spacing)
		{
			Draw(geometry.posx, geometry.posy - height - spacing);
		}
		void DrawBelow(Geometrey geometry, int32 spacing)
		{
			Draw(geometry.posx, geometry.posy + geometry.height + spacing);
		}
		void Release()
		{
			delete computeshader;
			delete constantbuffer;
			//delete this;
		}
	}rollbox[rollboxmaxcount];
	struct Indicator : Geometrey
	{
		float4 colorinactive;
		float4 colorintermediate;
		float4 coloractive;
		int32* status;

		uint32 threadx;
		uint32 thready;
		struct ConstantBufferData
		{
			int32 posx;
			int32 posy;
			int32 width;
			int32 height;
			float4 color;
		}cbd;
		Graphics::ConstantBuffer* constantbuffer = 0;
		Graphics::ComputeShader* computeshader = 0;

		bool Initialize(uint32 _diameter, float4 _colorinactive, float4 _coloractive, int32*_status)
		{
			width = _diameter;
			height = _diameter;
			colorinactive = _colorinactive;
			coloractive = _coloractive;
			status = _status;

			threadx = (width / 32) + 1;
			thready = (height / 32) + 1;
			if (graphics->ComputeShaderCreate(&computeshader, "ComputeShaderIndicator.hlsl"))return 1;
			if (graphics->ConstantBufferCreate(&constantbuffer, sizeof(ConstantBufferData), &cbd, VARIABLE))return 1;
			cbd.posx = 0;
			cbd.posy = 0;
			cbd.width = width;
			cbd.height = height;
			cbd.color = colorinactive;
			return 0;
		}
		bool Initialize(uint32 _diameter, float4 _colorinactive, float4 _colorintermediate, float4 _coloractive, int32* _status)
		{
			colorintermediate = _colorintermediate;
			return Initialize(_diameter, _colorinactive, _coloractive, _status);
		}
		void Draw(int32 x, int32 y)
		{
			posx = x;
			posy = y;


			cbd.posx = x;
			cbd.posy = y;
			switch (*status)
			{
				case 0: cbd.color = colorinactive; break;
				case 1: cbd.color = coloractive; break;
				default :cbd.color = colorintermediate;
			}
			graphics->ComputeShaderSet(computeshader);
			graphics->SetUnorderedAccessView();
			graphics->ConstantBufferUpdate(constantbuffer);
			graphics->ConstantBufferSet(constantbuffer, 0, 0, 0, 0, 0, 0, 1);
			graphics->Compute(threadx, thready, 1);
		}
		void Release()
		{
			delete computeshader;
			delete constantbuffer;
			//delete this;
		}
	}indicator[indicatormaxcount];

	void Initialize(Graphics* _graphics, Keyboard* _keyboard, Mouse* _mouse)
	{
		graphics = _graphics;
		keyboard = _keyboard;
		mouse = _mouse;
		text.Initialize();
	}
	void Release()
	{
		for (uint32 i = 0; i < tabmaxcount; i++)tab[i].Release();
		for (uint32 i = 0; i < shapeboxmaxcount; i++)shapebox[i].Release();
		for (uint32 i = 0; i < indicatormaxcount; i++)indicator[i].Release();
		for (uint32 i = 0; i < buttonmaxcount; i++)button[i].Release();
		for (uint32 i = 0; i < textboxmaxcount; i++)textbox[i].Release();
		for (uint32 i = 0; i < rollboxmaxcount; i++)rollbox[i].Release();
		text.Release();
		delete this;
	}
};
Graphics* UserInterface::graphics;
Keyboard* UserInterface::keyboard;
Mouse* UserInterface::mouse;
UserInterface::Text UserInterface::text;
uint32 UserInterface::imagecount = 0;
uint32 UserInterface::tabcount = 0;
uint32 UserInterface::shapeboxcount = 0;
uint32 UserInterface::indicatorcount = 0;
uint32 UserInterface::buttoncount = 0;
uint32 UserInterface::textboxcount = 0;
uint32 UserInterface::rollboxcount = 0;