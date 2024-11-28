struct GUIButton
{
	UINT32 x;
	UINT32 y;
	UINT32 width;
	UINT32 height;
	float4 color;

	char string[BUFFERSIZE];
	Graphics *graphics;
	Physics *physics;
	Mouse *mouse;
	Keyboard *keyboard;
	float4 unpressedcolor;
	float4 hoveredcolor;
	float4 pressedcolor;
	UINT32 textcolor;	
	Graphics::ComputeShader *computeshaderfill;
	Graphics::ConstantBuffer *constantbufferfill;	
	Graphics::Text *text;

	UINT8 Initialize(Graphics *_graphics, Mouse *_mouse, Keyboard *_keyboard, UINT32 _x, UINT32 _y, UINT32 _width, UINT32 _height, char *_string, float4 _unpressedcolor, float4 _hoveredcolor, float4 _pressedcolor, UINT32 _textcolor)
	{
		graphics = _graphics;
		mouse = _mouse;
		keyboard = _keyboard;
		x = _x;
		y = _y;
		width = _width;
		height = _height;
		unpressedcolor = _unpressedcolor;
		hoveredcolor = _hoveredcolor;
		pressedcolor = _pressedcolor;
		textcolor = _textcolor;
		strcpy_s(string, _string);
		if (graphics->ComputeShaderCreate(&computeshaderfill, "computeshaderguibutton.hlsl"))return 1;
		if (graphics->ConstantBufferCreate(&constantbufferfill, sizeof(float) * 8, this, VARIABLE))return 1;
		if (graphics->TextCreate(&text, L"Consolas", BOLD100, ITALIC_NORMAL, STREACH_NORMAL, 18, D2D1::ColorF(_textcolor))) return 1;
		return 0;
	}
	UINT8 Initialize(Graphics *_graphics, Mouse *_mouse, Keyboard *_keyboard, char *_string, float4 _unpressedcolor, float4 _hoveredcolor, float4 _pressedcolor, UINT32 _textcolor)
	{
		graphics = _graphics;
		mouse = _mouse;
		keyboard = _keyboard;
		unpressedcolor = _unpressedcolor;
		hoveredcolor = _hoveredcolor;
		pressedcolor = _pressedcolor;
		textcolor = _textcolor;
		strcpy_s(string, _string);
		if (graphics->ComputeShaderCreate(&computeshaderfill, "computeshaderguibutton.hlsl"))return 1;
		if (graphics->ConstantBufferCreate(&constantbufferfill, sizeof(float) * 8, this, VARIABLE))return 1;
		if (graphics->TextCreate(&text, L"Consolas", BOLD100, ITALIC_NORMAL, STREACH_NORMAL, 18, D2D1::ColorF(_textcolor))) return 1;
		return 0;
	}
	bool Update()
	{
		bool pressed = false;
		if (mouse->X() > x && mouse->X() < (x + width) && mouse->Y() > y && mouse->Y() < (y + height))
		{
			if (mouse->LeftMouseButton())
			{
				color = pressedcolor;
				if (mouse->LeftMouseButtonDown())
					pressed = true;
			}
			else
				color = hoveredcolor;
		}
		else
			color = unpressedcolor;
		return pressed;
	}
	bool Update(UINT32 _x, UINT32 _y, UINT32 _width, UINT32 _height)
	{
		x = _x;
		y = _y;
		width = _width;
		height = _height;
		bool pressed = false;
		if (mouse->X() > x && mouse->X() < (x + width) && mouse->Y() > y && mouse->Y() < (y + height))
		{
			if (mouse->LeftMouseButton())
			{
				color = pressedcolor;
				if (mouse->LeftMouseButtonDown())
					pressed = true;
			}
			else
				color = hoveredcolor;
		}
		else
			color = unpressedcolor;
		return pressed;
	}
	bool UpdateAlign(void *_guiobject,UINT32 _xoffset, INT32 _yoffset, UINT32 _width, UINT32 _height)
	{
		UINT32 *guiobject = (UINT32*)_guiobject;
		x = guiobject[0] + _xoffset;
		y = guiobject[1] + _yoffset;
		width = _width;
		height = _height;
		bool pressed = false;
		if (mouse->X() > x && mouse->X() < (x + width) && mouse->Y() > y && mouse->Y() < (y + height))
		{
			if (mouse->LeftMouseButton())
			{
				color = pressedcolor;
				if (mouse->LeftMouseButtonDown())
					pressed = true;
			}
			else
				color = hoveredcolor;
		}
		else
			color = unpressedcolor;
		return pressed;
	}
	bool UpdateAlignTrailing(void *_guiobject, INT32 _xoffset, INT32 _yoffset, UINT32 _width, UINT32 _height)
	{
		UINT32 *guiobject = (UINT32*)_guiobject;
		x = guiobject[0] + guiobject[2] + _xoffset;
		y = guiobject[1] + _yoffset;
		width = _width;
		height = _height;
		bool pressed = false;
		if (mouse->X() > x && mouse->X() < (x + width) && mouse->Y() > y && mouse->Y() < (y + height))
		{
			if (mouse->LeftMouseButton())
			{
				color = pressedcolor;
				if (mouse->LeftMouseButtonDown())
					pressed = true;
			}
			else
				color = hoveredcolor;
		}
		else
			color = unpressedcolor;
		return pressed;
	}
	bool UpdateAlignFollowing(void *_guiobject, INT32 _xoffset, INT32 _yoffset, UINT32 _width, UINT32 _height)
	{
		UINT32 *guiobject = (UINT32*)_guiobject;
		x = guiobject[0] + _xoffset;
		y = guiobject[1] + guiobject[3] + _yoffset;
		width = _width;
		height = _height;
		bool pressed = false;
		if (mouse->X() > x && mouse->X() < (x + width) && mouse->Y() > y && mouse->Y() < (y + height))
		{
			if (mouse->LeftMouseButton())
			{
				color = pressedcolor;
				if (mouse->LeftMouseButtonDown())
					pressed = true;
			}
			else
				color = hoveredcolor;
		}
		else
			color = unpressedcolor;
		return pressed;
	}
	void Render()
	{	
		graphics->ConstantBufferUpdate(constantbufferfill);
		graphics->ConstantBufferSet(constantbufferfill, 0, 0, 0, 0, 0, 0, 1);
		graphics->ComputeShaderSet(computeshaderfill);
		graphics->TextureSetUnorderedAccessView(graphics->backbuffer, 0);
		graphics->Compute((width/32)+1, (height/18)+1, 1);
		graphics->Write(text, string, (float)x, (float)y, (float)width, (float)height);
	}
	bool Pressed()
	{
		if (mouse->LeftMouseButtonDown() && mouse->X() > x && mouse->X() < (x + width) && mouse->Y() > y && mouse->Y() < (y + height))
			return true;
		return false;
	}
	bool Hovered()
	{
		if (mouse->X() > x && mouse->X() < (x + width) && mouse->Y() > y && mouse->Y() < (y + height))return true;
		return false;
	}

	GUIButton()
	{
		ZeroMemory(this, sizeof(GUIButton));
	}
	~GUIButton()
	{
		delete text;
		delete constantbufferfill;
		delete computeshaderfill;
		ZeroMemory(this, sizeof(GUIButton));
	}
};

struct GUIText
{
	UINT32 x;
	UINT32 y;
	UINT32 width;
	UINT32 height;
	float4 color;

	UINT8 selected;
	char string[BUFFERSIZE];
	Graphics *graphics;
	Physics *physics;
	Mouse *mouse;
	Keyboard *keyboard;
	float4 unselectedcolor;
	float4 hoveredcolor;
	float4 selectedcolor;
	UINT32 textcolor;
	Graphics::ComputeShader *computeshaderfill;
	Graphics::ConstantBuffer *constantbufferfill;
	Graphics::Text *text;

	UINT8 Initialize(Graphics *_graphics, Mouse *_mouse, Keyboard *_keyboard, UINT32 _x, UINT32 _y, UINT32 _width, UINT32 _height, float4 _unselectedcolor, float4 _hoveredcolor, float4 _selectedcolor, UINT32 _textcolor)
	{
		graphics = _graphics;
		mouse = _mouse;
		keyboard = _keyboard;
		x = _x;
		y = _y;
		width = _width;
		height = _height;
		unselectedcolor = _unselectedcolor;
		hoveredcolor = _hoveredcolor;
		selectedcolor = _selectedcolor;
		textcolor = _textcolor;
		if (graphics->ComputeShaderCreate(&computeshaderfill, "computeshaderguitext.hlsl"))return 1;
		if (graphics->ConstantBufferCreate(&constantbufferfill, sizeof(float) * 8, this, VARIABLE))return 1;
		if (graphics->TextCreate(&text, L"Consolas", BOLD100, ITALIC_NORMAL, STREACH_NORMAL, 18, D2D1::ColorF(_textcolor))) return 1;
		return 0;
	}
	UINT8 Initialize(Graphics *_graphics, Mouse *_mouse, Keyboard *_keyboard, float4 _unselectedcolor, float4 _hoveredcolor, float4 _selectedcolor, UINT32 _textcolor)
	{
		graphics = _graphics;
		mouse = _mouse;
		keyboard = _keyboard;
		unselectedcolor = _unselectedcolor;
		hoveredcolor = _hoveredcolor;
		selectedcolor = _selectedcolor;
		textcolor = _textcolor;
		if (graphics->ComputeShaderCreate(&computeshaderfill, "computeshaderguitext.hlsl"))return 1;
		if (graphics->ConstantBufferCreate(&constantbufferfill, sizeof(float) * 8, this, VARIABLE))return 1;
		if (graphics->TextCreate(&text, L"Consolas", BOLD100, ITALIC_NORMAL, STREACH_NORMAL, 18, D2D1::ColorF(_textcolor))) return 1;
		return 0;
	}
	void Update()
	{
		if (mouse->LeftMouseButtonDown())
		{
			if (mouse->X() > x && mouse->X() < (x + width) && mouse->Y() > y && mouse->Y() < (y + height))
				selected = 1;
			else
				selected = 0;
		}
		if (selected)
		{
			keyboard->AppendKeyCharacterToString(string, sizeof(string));
		}
	}
	void Update(UINT32 _x, UINT32 _y, UINT32 _width, UINT32 _height)
	{
		x = _x;
		y = _y;
		width = _width;
		height = _height;
		if (mouse->LeftMouseButtonDown())
		{
			if (mouse->X() > x && mouse->X() < (x + width) && mouse->Y() > y && mouse->Y() < (y + height))
				selected = 1;
			else
				selected = 0;
		}
		if (selected)
			keyboard->AppendKeyCharacterToString(string, sizeof(string));
	}
	void UpdateAlign(void *_guiobject,INT32 _xoffset, INT32 _yoffset, UINT32 _width, UINT32 _height)
	{
		UINT32 *guiobject = (UINT32*)_guiobject;
		x = guiobject[0] + _xoffset;
		y = guiobject[1] + _yoffset;
		width = _width;
		height = _height;
		if (mouse->LeftMouseButtonDown())
		{
			if (mouse->X() > x && mouse->X() < (x + width) && mouse->Y() > y && mouse->Y() < (y + height))
				selected = 1;
			else
				selected = 0;
		}
		if (selected)
			keyboard->AppendKeyCharacterToString(string, sizeof(string));
	}
	void UpdateAlignTrailing(void *_guiobject,INT32 _xoffset, INT32 _yoffset, UINT32 _width, UINT32 _height)
	{
		UINT32 *guiobject = (UINT32*)_guiobject;
		x = guiobject[0] + guiobject[2] + _xoffset;
		y = guiobject[1] + _yoffset;
		width = _width;
		height = _height;
		if (mouse->LeftMouseButtonDown())
		{
			if (mouse->X() > x && mouse->X() < (x + width) && mouse->Y() > y && mouse->Y() < (y + height))
				selected = 1;
			else
				selected = 0;
		}
		if (selected)
			keyboard->AppendKeyCharacterToString(string, sizeof(string));
	}
	void UpdateAlignFollowing(void *_guiobject, INT32 _xoffset, INT32 _yoffset, UINT32 _width, UINT32 _height)
	{
		UINT32 *guiobject = (UINT32*)_guiobject;
		x = guiobject[0] + _xoffset;
		y = guiobject[1] + guiobject[3] + _yoffset;
		width = _width;
		height = _height;
		if (mouse->LeftMouseButtonDown())
		{
			if (mouse->X() > x && mouse->X() < (x + width) && mouse->Y() > y && mouse->Y() < (y + height))
				selected = 1;
			else
				selected = 0;
		}
		if (selected)
			keyboard->AppendKeyCharacterToString(string, sizeof(string));
	}
	void Render()
	{
		if (selected)
			color = selectedcolor;
		else
			color = unselectedcolor;
		if (mouse->X() > x && mouse->X() < (x + width) && mouse->Y() > y && mouse->Y() < (y + height))
			color = hoveredcolor;
		graphics->ConstantBufferUpdate(constantbufferfill);
		graphics->ConstantBufferSet(constantbufferfill, 0, 0, 0, 0, 0, 0, 1);
		graphics->ComputeShaderSet(computeshaderfill);
		graphics->TextureSetUnorderedAccessView(graphics->backbuffer, 0);
		graphics->Compute((width / 32) + 1, (height / 18) + 1, 1);
		graphics->Write(text, string, (float)x+5.0f, (float)y, (float)width, (float)height);
	}
	bool Pressed()
	{
		if (mouse->LeftMouseButtonDown() && mouse->X() > x && mouse->X() < (x + width) && mouse->Y() > y && mouse->Y() < (y + height))
			return true;
		return false;
	}
	bool Hovered()
	{
		if (mouse->X() > x && mouse->X() < (x + width) && mouse->Y() > y && mouse->Y() < (y + height))return true;
		return false;
	}

	GUIText()
	{
		ZeroMemory(this, sizeof(GUIText));
	}
	~GUIText()
	{
		delete text;
		delete constantbufferfill;
		delete computeshaderfill;
		ZeroMemory(this, sizeof(GUIText));
	}
};

struct GUILabel
{
	UINT32 x;
	UINT32 y;
	UINT32 width;
	UINT32 height;
	float4 color;

	char string[BUFFERSIZE];
	Graphics *graphics;
	Physics *physics;
	UINT32 textcolor;
	Graphics::ComputeShader *computeshaderfill;
	Graphics::ConstantBuffer *constantbufferfill;
	Graphics::Text *text;

	UINT8 Initialize(Graphics *_graphics, UINT32 _x, UINT32 _y, UINT32 _width, UINT32 _height,float4 _color, char *_string, UINT32 _textcolor)
	{
		graphics = _graphics;
		x = _x;
		y = _y;
		width = _width;
		height = _height;
		color = _color;
		textcolor = _textcolor;
		strcpy_s(string, _string);
		if (graphics->ComputeShaderCreate(&computeshaderfill, "computeshaderguitext.hlsl"))return 1;
		if (graphics->ConstantBufferCreate(&constantbufferfill, sizeof(float) * 8, this, VARIABLE))return 1;
		if (graphics->TextCreate(&text, L"Consolas", BOLD100, ITALIC_NORMAL, STREACH_NORMAL, 18, D2D1::ColorF(_textcolor))) return 1;
		return 0;
	}
	UINT8 Initialize(Graphics *_graphics, float4 _color, char *_string, UINT32 _textcolor)
	{
		graphics = _graphics;
		color = _color;
		textcolor = _textcolor;
		strcpy_s(string, _string);
		if (graphics->ComputeShaderCreate(&computeshaderfill, "computeshaderguitext.hlsl"))return 1;
		if (graphics->ConstantBufferCreate(&constantbufferfill, sizeof(float) * 8, this, VARIABLE))return 1;
		if (graphics->TextCreate(&text, L"Consolas", BOLD100, ITALIC_NORMAL, STREACH_NORMAL, 18, D2D1::ColorF(_textcolor))) return 1;
		return 0;
	}
	void Update(UINT32 _x, UINT32 _y, UINT32 _width, UINT32 _height)
	{
		x = _x;
		y = _y;
		width = _width;
		height = _height;
	}
	void UpdateAlign(void *_guiobject, INT32 _xoffset, INT32 _yoffset, UINT32 _width, UINT32 _height)
	{
		UINT32 *guiobject = (UINT32*)_guiobject;
		x = guiobject[0] + _xoffset;
		y = guiobject[1] + _yoffset;
		width = _width;
		height = _height;
	}
	void UpdateAlignTrailing(void *_guiobject, INT32 _xoffset, INT32 _yoffset, UINT32 _width, UINT32 _height)
	{
		UINT32 *guiobject = (UINT32*)_guiobject;
		x = guiobject[0] + guiobject[2] + _xoffset;
		y = guiobject[1] + _yoffset;
		width = _width;
		height = _height;
	}
	void UpdateAlignFollowing(void *_guiobject, INT32 _xoffset, INT32 _yoffset, UINT32 _width, UINT32 _height)
	{
		UINT32 *guiobject = (UINT32*)_guiobject;
		x = guiobject[0] + _xoffset;
		y = guiobject[1] + guiobject[3] + _yoffset;
		width = _width;
		height = _height;
	}
	void Render()
	{
		graphics->ConstantBufferUpdate(constantbufferfill);
		graphics->ConstantBufferSet(constantbufferfill, 0, 0, 0, 0, 0, 0, 1);
		graphics->ComputeShaderSet(computeshaderfill);
		graphics->TextureSetUnorderedAccessView(graphics->backbuffer, 0);
		graphics->Compute((width / 32) + 1, (height / 18) + 1, 1);
		graphics->Write(text, string, (float)x, (float)y+3.0f, (float)width, (float)height);
	}
	GUILabel()
	{
		ZeroMemory(this, sizeof(GUILabel));
	}
	~GUILabel()
	{
		delete text;
		delete constantbufferfill;
		delete computeshaderfill;
		ZeroMemory(this, sizeof(GUILabel));
	}
};