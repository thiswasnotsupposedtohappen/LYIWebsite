static bool resizewindow;
struct Graphics
{
private:
	ID3D11Device				*device;
	ID3D11DeviceContext			*context;
	IDXGISwapChain				*swapchain;
	D3D_FEATURE_LEVEL			featurelevel;
	ID3D11Debug					*debug;

public:	

	struct Sampler
	{
		ID3D11SamplerState *sampler;
		Sampler()
		{
			ZeroMemory(this, sizeof(Sampler));
		}
		~Sampler()
		{
			if (sampler)sampler->Release(); sampler = NULL;
		}
	};
	struct Rasterizer
	{
		ID3D11RasterizerState *rasterizer;
		Rasterizer()
		{
			ZeroMemory(this, sizeof(Rasterizer));
		}
		~Rasterizer()
		{
			if (rasterizer)rasterizer->Release(); rasterizer = NULL;
		}
	};
	struct BlendState
	{
		ID3D11BlendState *blendstate;
		BlendState()
		{
			ZeroMemory(this, sizeof(BlendState));
		}
		~BlendState()
		{
			if (blendstate)blendstate->Release(); blendstate = NULL;
		}
	};
	struct ConstantBuffer
	{
		ID3D11Buffer *constantbuffer;
		void* dataptr;
		ConstantBuffer()
		{
			ZeroMemory(this, sizeof(ConstantBuffer));
		}
		~ConstantBuffer()
		{
			dataptr = 0;
			if (constantbuffer)constantbuffer->Release(); constantbuffer = NULL;
		}
	};
	struct IndexBuffer
	{
		ID3D11Buffer *indexbuffer;
		UINT32 count;
		IndexBuffer()
		{
			ZeroMemory(this, sizeof(IndexBuffer));
		}
		~IndexBuffer()
		{
			if (indexbuffer)indexbuffer->Release(); indexbuffer = 0;
			count = 0;
		}
	};
	struct Buffer
	{
		ID3D11Buffer *buffer;
		ID3D11ShaderResourceView *shaderresourceview;
		ID3D11UnorderedAccessView  *unorderedaccessview;
		ID3D11Buffer *getbuffer;
		void* dataptr;
		size_t size;
		UINT32 count;
		Buffer()
		{
			ZeroMemory(this, sizeof(Buffer));
		}
		~Buffer()
		{
			if (buffer)buffer->Release(); buffer = 0;
			if (shaderresourceview)shaderresourceview->Release(); shaderresourceview = 0;
			if (unorderedaccessview)unorderedaccessview->Release(); unorderedaccessview = 0;
			if (getbuffer)getbuffer->Release(); getbuffer = 0;
			size = 0;
			dataptr = 0;
			count = 0;
		}
	};
	struct Texture
	{
		ID3D11Texture2D *texture;
		ID3D11RenderTargetView* rendertargetview;
		ID3D11ShaderResourceView *shaderrecourceview;
		ID3D11UnorderedAccessView *unorderedaccessview;
		ID3D11Texture2D *gettexture;
		ID3D11Texture2D	*depthstenciltexture;
		ID3D11DepthStencilView *depthstencilview;
		size_t elementsize;
		unsigned int width;
		unsigned int height;
		Texture()
		{
			ZeroMemory(this, sizeof(Texture));
		}
		~Texture()
		{
			width = 0;
			height = 0;
			if (depthstenciltexture)depthstenciltexture->Release(); depthstenciltexture = 0;
			if (depthstencilview)depthstencilview->Release(); depthstencilview = 0;
			if (texture)texture->Release(); texture = 0;
			if (rendertargetview)rendertargetview->Release(); rendertargetview = 0;
			if (shaderrecourceview)shaderrecourceview->Release(); shaderrecourceview = 0;
			if (unorderedaccessview)unorderedaccessview->Release(); unorderedaccessview = 0;
			if (gettexture)gettexture->Release(); gettexture = 0;			
		}
	};
	struct VertexShader
	{
		ID3D11VertexShader *vertexshader;
		ID3D11InputLayout *layout;
		VertexShader()
		{
			ZeroMemory(this, sizeof(VertexShader));
		}
		~VertexShader()
		{
			if (layout)layout->Release(); layout = 0;
			if (vertexshader)vertexshader->Release(); vertexshader = 0;
		}
	};
	struct HullShader
	{
		ID3D11HullShader *hullshader;
		HullShader()
		{
			ZeroMemory(this, sizeof(HullShader));
		}
		~HullShader()
		{
			if (hullshader)hullshader->Release(); hullshader = 0;
		}
	};
	struct DomainShader
	{
		ID3D11DomainShader *domainshader;
		DomainShader()
		{
			ZeroMemory(this, sizeof(DomainShader));
		}
		~DomainShader()
		{
			if (domainshader)domainshader->Release(); domainshader = 0;
		}
	};
	struct GeometryShader
	{
		ID3D11GeometryShader *geometryshader;
		GeometryShader()
		{
			ZeroMemory(this, sizeof(GeometryShader));
		}
		~GeometryShader()
		{
			if (geometryshader)geometryshader->Release(); geometryshader = 0;
		}
	};
	struct PixelShader
	{
		ID3D11PixelShader *pixelshader;
		PixelShader()
		{
			ZeroMemory(this, sizeof(PixelShader));
		}
		~PixelShader()
		{
			if (pixelshader)pixelshader->Release(); pixelshader = 0;
		}
	};
	struct ComputeShader
	{
		ID3D11ComputeShader *computeshader;
		ComputeShader()
		{
			ZeroMemory(this, sizeof(ComputeShader));
		}
		~ComputeShader()
		{
			if (computeshader)computeshader->Release(); computeshader = 0;
		}
	};
	struct Text
	{
		IDWriteFactory1			*writefactory;
		IDWriteTextFormat		*format;
		ID2D1SolidColorBrush	*brush;
		Text()
		{
			ZeroMemory(this, sizeof(Text));
		}
		~Text()
		{
			if (brush)brush->Release(); brush = 0;
			if (format)format->Release(); format = 0;
			if (writefactory)writefactory->Release(); writefactory = 0;
		}
	};

	Texture						*backbuffer;

	UINT8				Initialize(HWND _hWnd, UINT32 _screenwidth, UINT32 _screenheight, UINT8 _antializing, BOOL _fullscreen)
	{
		HRESULT hr = S_OK;

		DXGI_SWAP_CHAIN_DESC swapchaindesc;
		ZeroMemory(&swapchaindesc, sizeof(DXGI_SWAP_CHAIN_DESC));
		swapchaindesc.BufferCount = 2;
		swapchaindesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapchaindesc.BufferDesc.Width = _screenwidth;
		swapchaindesc.BufferDesc.Height = _screenheight;
		swapchaindesc.BufferDesc.RefreshRate.Numerator = 60;
		swapchaindesc.BufferDesc.RefreshRate.Denominator = 1;
		if(_antializing>1)
		swapchaindesc.BufferUsage = DXGI_USAGE_SHADER_INPUT | DXGI_USAGE_RENDER_TARGET_OUTPUT;
		else
		swapchaindesc.BufferUsage = DXGI_USAGE_SHADER_INPUT| DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_UNORDERED_ACCESS;
		swapchaindesc.OutputWindow = _hWnd;
		swapchaindesc.SampleDesc.Count = _antializing;
		swapchaindesc.SampleDesc.Quality = 0;
		swapchaindesc.Windowed = TRUE;
		swapchaindesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, D3D11_CREATE_DEVICE_BGRA_SUPPORT | DEBUGFLAG, NULL, NULL, D3D11_SDK_VERSION, &swapchaindesc, &swapchain, &device, &featurelevel, &context);
		if (hr != S_OK) { print("Graphics: Failed to ceate device and swapchain\n"); return 1; }
		if (featurelevel < 0xa000) { print("Graphics: Failed to device and swapchain, graphics hardware not supported need atleast DirectX 10\n"); return 1; }

#ifdef DEBUGD3D
		ID3D11InfoQueue *infoqueue = 0;
		hr = device->QueryInterface(__uuidof(ID3D11Debug), (void**)&debug);
		if (hr != S_OK) { print("Graphics: Failed To Create Debug\n"); }
		debug->QueryInterface(__uuidof(ID3D11InfoQueue), (void**)&infoqueue);
		if (hr != S_OK) { print("Graphics: Failed To Create Debug\n"); }
		infoqueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_CORRUPTION, true);
		infoqueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_ERROR, true);
		D3D11_MESSAGE_ID hide[] = { 			
			D3D11_MESSAGE_ID_SETPRIVATEDATA_CHANGINGPARAMS,												
			D3D11_MESSAGE_ID_DEVICE_DRAW_CONSTANT_BUFFER_TOO_SMALL , 											
			D3D11_MESSAGE_ID_DEVICE_OMSETRENDERTARGETS_HAZARD ,  												
			D3D11_MESSAGE_ID_DEVICE_PSSETSHADERRESOURCES_HAZARD ,											
			D3D11_MESSAGE_ID_DEVICE_CSSETUNORDEREDACCESSVIEWS_HAZARD };
		D3D11_INFO_QUEUE_FILTER filter;
		memset(&filter, 0, sizeof(filter));
		filter.DenyList.NumIDs = _countof(hide);
		filter.DenyList.pIDList = hide;
		infoqueue->AddStorageFilterEntries(&filter);
		infoqueue->Release();
#endif
	
		backbuffer = new Texture;
		D3D11_TEXTURE2D_DESC texturedesc;
		D3D11_TEXTURE2D_DESC depthstenciltexturedesc;
		D3D11_RENDER_TARGET_VIEW_DESC rendertargetviewdesc;
		D3D11_SHADER_RESOURCE_VIEW_DESC shaderresourceviewdesc;
		D3D11_UNORDERED_ACCESS_VIEW_DESC uavdesc;
		swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backbuffer->texture);
		backbuffer->texture->GetDesc(&texturedesc);
		if (_antializing>1) 
		{
			shaderresourceviewdesc.Format = texturedesc.Format;
			shaderresourceviewdesc.ViewDimension = D3D_SRV_DIMENSION_TEXTURE2DMS;
			hr = device->CreateShaderResourceView(backbuffer->texture, &shaderresourceviewdesc, &backbuffer->shaderrecourceview);
			if (hr != S_OK) { print("Graphics: Failed to create back buffer shader resource view\n"); return 1; }
			rendertargetviewdesc.Format = texturedesc.Format;
			rendertargetviewdesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DMS;
			hr = device->CreateRenderTargetView(backbuffer->texture, &rendertargetviewdesc, &backbuffer->rendertargetview);
			if (hr != S_OK) { print("\n"); return 1; }
		}
		else
		{
			shaderresourceviewdesc.Format = texturedesc.Format;
			shaderresourceviewdesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
			shaderresourceviewdesc.Texture2D.MostDetailedMip = 0;
			shaderresourceviewdesc.Texture2D.MipLevels = 1;
			hr = device->CreateShaderResourceView(backbuffer->texture, &shaderresourceviewdesc, &backbuffer->shaderrecourceview);
			if (hr != S_OK) { print("Graphics: Failed to create back buffer shader resource view\n"); return 1; }
			rendertargetviewdesc.Format = texturedesc.Format;
			rendertargetviewdesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
			rendertargetviewdesc.Texture2D.MipSlice = 0;
			hr = device->CreateRenderTargetView(backbuffer->texture, &rendertargetviewdesc, &backbuffer->rendertargetview);
			if (hr != S_OK) { print("Graphics: Failed to create back buffer render target view\n"); return 1; }
			uavdesc.Format = texturedesc.Format;
			uavdesc.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE2D;
			uavdesc.Texture2D.MipSlice = 0;
			if (featurelevel >= 0xb000)
				hr = device->CreateUnorderedAccessView(backbuffer->texture, &uavdesc, &backbuffer->unorderedaccessview);
			if (hr != S_OK) { print("Graphics: Failed to create back buffer unordered access view\n"); return 1; }
			texturedesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
			texturedesc.Usage = D3D11_USAGE_STAGING;
			texturedesc.BindFlags = 0;
			hr = device->CreateTexture2D(&texturedesc, NULL, &backbuffer->gettexture);
			if (hr != S_OK) { print("Graphics: Failed to create back buffer get texture\n"); return 1; }
		}

		backbuffer->width = screenwidth;
		backbuffer->height = screenheight;
		backbuffer->elementsize = sizeof(UINT8) * 4;

		ZeroMemory(&depthstenciltexturedesc, sizeof(D3D11_TEXTURE2D_DESC));
		depthstenciltexturedesc.Width = backbuffer->width;
		depthstenciltexturedesc.Height = backbuffer->height;
		depthstenciltexturedesc.MipLevels = 1;
		depthstenciltexturedesc.ArraySize = 1;
		depthstenciltexturedesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthstenciltexturedesc.SampleDesc.Count = _antializing;
		depthstenciltexturedesc.SampleDesc.Quality = 0;
		depthstenciltexturedesc.Usage = D3D11_USAGE_DEFAULT;
		depthstenciltexturedesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthstenciltexturedesc.CPUAccessFlags = 0;
		depthstenciltexturedesc.MiscFlags = 0;
		hr = device->CreateTexture2D(&depthstenciltexturedesc, NULL, &backbuffer->depthstenciltexture);
		if (hr != S_OK) { print("Graphics: Failed to create depth stencil texture\n"); return 1; }

		D3D11_DEPTH_STENCIL_VIEW_DESC depthstencilviewdsec;
		ZeroMemory(&depthstencilviewdsec, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
		depthstencilviewdsec.Format = depthstenciltexturedesc.Format;
		depthstencilviewdsec.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
		depthstencilviewdsec.Texture2D.MipSlice = 0;
		hr = device->CreateDepthStencilView(backbuffer->depthstenciltexture, &depthstencilviewdsec, &backbuffer->depthstencilview);
		if (hr != S_OK) { print("Graphics: Failed to create depth stencil view\n"); return 1; }

		ID3D11BlendState *blendstate=0;
		D3D11_BLEND_DESC blenddesc;
		ZeroMemory(&blenddesc, sizeof(D3D11_BLEND_DESC));
		blenddesc.RenderTarget[0].BlendEnable = TRUE;
		blenddesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blenddesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		blenddesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		blenddesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		blenddesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		blenddesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		blenddesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		hr = device->CreateBlendState(&blenddesc, &blendstate);
		if (hr != S_OK) { print("Graphics: Failed to create blend state\n"); return 1; }
		float blendFactor[] = { 0, 0, 0, 0 };
		context->OMSetBlendState(blendstate, blendFactor, 0xffffffff);
		blendstate->Release();	
		
		swapchain->SetFullscreenState(_fullscreen, NULL);
		print("Graphics: Initialized\n");
		return 0;
	}
	void				Resize()
	{
		resizewindow = 0;
		
		HRESULT hr = S_OK;		
		int _antializing = 1;
		delete backbuffer;

		swapchain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);

		backbuffer = new Texture;
		D3D11_TEXTURE2D_DESC texturedesc;
		D3D11_TEXTURE2D_DESC depthstenciltexturedesc;
		D3D11_RENDER_TARGET_VIEW_DESC rendertargetviewdesc;
		D3D11_SHADER_RESOURCE_VIEW_DESC shaderresourceviewdesc;
		D3D11_UNORDERED_ACCESS_VIEW_DESC uavdesc;
		swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backbuffer->texture);
		backbuffer->texture->GetDesc(&texturedesc);
		screenwidth = texturedesc.Width;
		screenheight = texturedesc.Height;
		if (_antializing > 1)
		{
			shaderresourceviewdesc.Format = texturedesc.Format;
			shaderresourceviewdesc.ViewDimension = D3D_SRV_DIMENSION_TEXTURE2DMS;
			hr = device->CreateShaderResourceView(backbuffer->texture, &shaderresourceviewdesc, &backbuffer->shaderrecourceview);
			if (hr != S_OK) { print("Graphics: Failed to create back buffer shader resource view\n"); DebugBreak(); }
			rendertargetviewdesc.Format = texturedesc.Format;
			rendertargetviewdesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DMS;
			hr = device->CreateRenderTargetView(backbuffer->texture, &rendertargetviewdesc, &backbuffer->rendertargetview);
			if (hr != S_OK) DebugBreak();
		}
		else
		{
			shaderresourceviewdesc.Format = texturedesc.Format;
			shaderresourceviewdesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
			shaderresourceviewdesc.Texture2D.MostDetailedMip = 0;
			shaderresourceviewdesc.Texture2D.MipLevels = 1;
			hr = device->CreateShaderResourceView(backbuffer->texture, &shaderresourceviewdesc, &backbuffer->shaderrecourceview);
			if (hr != S_OK) { print("Graphics: Failed to create back buffer shader resource view\n"); DebugBreak(); }
			rendertargetviewdesc.Format = texturedesc.Format;
			rendertargetviewdesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
			rendertargetviewdesc.Texture2D.MipSlice = 0;
			hr = device->CreateRenderTargetView(backbuffer->texture, &rendertargetviewdesc, &backbuffer->rendertargetview);
			if (hr != S_OK) { print("Graphics: Failed to create back buffer render target view\n"); DebugBreak(); }
			uavdesc.Format = texturedesc.Format;
			uavdesc.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE2D;
			uavdesc.Texture2D.MipSlice = 0;
			if (featurelevel >= 0xb000)
				hr = device->CreateUnorderedAccessView(backbuffer->texture, &uavdesc, &backbuffer->unorderedaccessview);
			if (hr != S_OK) { print("Graphics: Failed to create back buffer unordered access view\n"); DebugBreak(); }
			texturedesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
			texturedesc.Usage = D3D11_USAGE_STAGING;
			texturedesc.BindFlags = 0;
			hr = device->CreateTexture2D(&texturedesc, NULL, &backbuffer->gettexture);
			if (hr != S_OK) { print("Graphics: Failed to create back buffer get texture\n"); DebugBreak(); }
		}

		backbuffer->width = screenwidth;
		backbuffer->height = screenheight;
		backbuffer->elementsize = sizeof(UINT8) * 4;

		ZeroMemory(&depthstenciltexturedesc, sizeof(D3D11_TEXTURE2D_DESC));
		depthstenciltexturedesc.Width = backbuffer->width;
		depthstenciltexturedesc.Height = backbuffer->height;
		depthstenciltexturedesc.MipLevels = 1;
		depthstenciltexturedesc.ArraySize = 1;
		depthstenciltexturedesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthstenciltexturedesc.SampleDesc.Count = _antializing;
		depthstenciltexturedesc.SampleDesc.Quality = 0;
		depthstenciltexturedesc.Usage = D3D11_USAGE_DEFAULT;
		depthstenciltexturedesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthstenciltexturedesc.CPUAccessFlags = 0;
		depthstenciltexturedesc.MiscFlags = 0;
		hr = device->CreateTexture2D(&depthstenciltexturedesc, NULL, &backbuffer->depthstenciltexture);
		if (hr != S_OK) { print("Graphics: Failed to create depth stencil texture\n"); DebugBreak();}
	

		D3D11_DEPTH_STENCIL_VIEW_DESC depthstencilviewdsec;
		ZeroMemory(&depthstencilviewdsec, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
		depthstencilviewdsec.Format = depthstenciltexturedesc.Format;
		depthstencilviewdsec.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
		depthstencilviewdsec.Texture2D.MipSlice = 0;
		hr = device->CreateDepthStencilView(backbuffer->depthstenciltexture, &depthstencilviewdsec, &backbuffer->depthstencilview);
		if (hr != S_OK) { print("Graphics: Failed to create depth stencil view\n"); DebugBreak(); }	
	}
	void				Resize(uint32 width, uint32 height)
	{
		resizewindow = 0;

		HRESULT hr = S_OK;
		int _antializing = 1;
		delete backbuffer;

		swapchain->ResizeBuffers(0, width, height, DXGI_FORMAT_UNKNOWN, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH);

		backbuffer = new Texture;
		D3D11_TEXTURE2D_DESC texturedesc;
		D3D11_TEXTURE2D_DESC depthstenciltexturedesc;
		D3D11_RENDER_TARGET_VIEW_DESC rendertargetviewdesc;
		D3D11_SHADER_RESOURCE_VIEW_DESC shaderresourceviewdesc;
		D3D11_UNORDERED_ACCESS_VIEW_DESC uavdesc;
		swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backbuffer->texture);
		backbuffer->texture->GetDesc(&texturedesc);
		screenwidth = width;
		screenheight = height;
		if (_antializing > 1)
		{
			shaderresourceviewdesc.Format = texturedesc.Format;
			shaderresourceviewdesc.ViewDimension = D3D_SRV_DIMENSION_TEXTURE2DMS;
			hr = device->CreateShaderResourceView(backbuffer->texture, &shaderresourceviewdesc, &backbuffer->shaderrecourceview);
			if (hr != S_OK) { print("Graphics: Failed to create back buffer shader resource view\n"); DebugBreak(); }
			rendertargetviewdesc.Format = texturedesc.Format;
			rendertargetviewdesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DMS;
			hr = device->CreateRenderTargetView(backbuffer->texture, &rendertargetviewdesc, &backbuffer->rendertargetview);
			if (hr != S_OK) DebugBreak();
		}
		else
		{
			shaderresourceviewdesc.Format = texturedesc.Format;
			shaderresourceviewdesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
			shaderresourceviewdesc.Texture2D.MostDetailedMip = 0;
			shaderresourceviewdesc.Texture2D.MipLevels = 1;
			hr = device->CreateShaderResourceView(backbuffer->texture, &shaderresourceviewdesc, &backbuffer->shaderrecourceview);
			if (hr != S_OK) { print("Graphics: Failed to create back buffer shader resource view\n"); DebugBreak(); }
			rendertargetviewdesc.Format = texturedesc.Format;
			rendertargetviewdesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
			rendertargetviewdesc.Texture2D.MipSlice = 0;
			hr = device->CreateRenderTargetView(backbuffer->texture, &rendertargetviewdesc, &backbuffer->rendertargetview);
			if (hr != S_OK) { print("Graphics: Failed to create back buffer render target view\n"); DebugBreak(); }
			uavdesc.Format = texturedesc.Format;
			uavdesc.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE2D;
			uavdesc.Texture2D.MipSlice = 0;
			if (featurelevel >= 0xb000)
				hr = device->CreateUnorderedAccessView(backbuffer->texture, &uavdesc, &backbuffer->unorderedaccessview);
			if (hr != S_OK) { print("Graphics: Failed to create back buffer unordered access view\n"); DebugBreak(); }
			texturedesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
			texturedesc.Usage = D3D11_USAGE_STAGING;
			texturedesc.BindFlags = 0;
			hr = device->CreateTexture2D(&texturedesc, NULL, &backbuffer->gettexture);
			if (hr != S_OK) { print("Graphics: Failed to create back buffer get texture\n"); DebugBreak(); }
		}

		backbuffer->width = screenwidth;
		backbuffer->height = screenheight;
		backbuffer->elementsize = sizeof(UINT8) * 4;

		ZeroMemory(&depthstenciltexturedesc, sizeof(D3D11_TEXTURE2D_DESC));
		depthstenciltexturedesc.Width = backbuffer->width;
		depthstenciltexturedesc.Height = backbuffer->height;
		depthstenciltexturedesc.MipLevels = 1;
		depthstenciltexturedesc.ArraySize = 1;
		depthstenciltexturedesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthstenciltexturedesc.SampleDesc.Count = _antializing;
		depthstenciltexturedesc.SampleDesc.Quality = 0;
		depthstenciltexturedesc.Usage = D3D11_USAGE_DEFAULT;
		depthstenciltexturedesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthstenciltexturedesc.CPUAccessFlags = 0;
		depthstenciltexturedesc.MiscFlags = 0;
		hr = device->CreateTexture2D(&depthstenciltexturedesc, NULL, &backbuffer->depthstenciltexture);
		if (hr != S_OK) { print("Graphics: Failed to create depth stencil texture\n"); DebugBreak(); }


		D3D11_DEPTH_STENCIL_VIEW_DESC depthstencilviewdsec;
		ZeroMemory(&depthstencilviewdsec, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
		depthstencilviewdsec.Format = depthstenciltexturedesc.Format;
		depthstencilviewdsec.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
		depthstencilviewdsec.Texture2D.MipSlice = 0;
		hr = device->CreateDepthStencilView(backbuffer->depthstenciltexture, &depthstencilviewdsec, &backbuffer->depthstencilview);
		if (hr != S_OK) { print("Graphics: Failed to create depth stencil view\n"); DebugBreak(); }
	}
	bool				GetFullScreenState()
	{
		BOOL state;
		swapchain->GetFullscreenState(&state, 0);
		return state;
	}
	void __forceinline  Clear(float _r, float _g, float _b, float _a)
	{
		float color[4] = { _r, _g, _b, _a };
		context->ClearRenderTargetView(backbuffer->rendertargetview, color);
		context->ClearDepthStencilView(backbuffer->depthstencilview, D3D11_CLEAR_DEPTH, 1.0f, 0);
	}
	void __forceinline  Clear(uint8 _r, uint8 _g, uint8 _b)
	{
		float color[4] = { (float32)_r / 255.0f, (float32)_g / 255.0f,(float32)_b / 255.0f, 1.0 };
		context->ClearRenderTargetView(backbuffer->rendertargetview, color);
		context->ClearDepthStencilView(backbuffer->depthstencilview, D3D11_CLEAR_DEPTH, 1.0f, 0);
	}
	void __forceinline  Clear(Texture* _texture,float _r, float _g, float _b, float _a)
	{
		float color[4] = { _r, _g, _b, _a };
		context->ClearRenderTargetView(_texture->rendertargetview, color);
		context->ClearDepthStencilView(_texture->depthstencilview, D3D11_CLEAR_DEPTH, 1.0f, 0);
	}
	void __forceinline  SetViewPort(FLOAT _x, FLOAT _y, FLOAT _width, FLOAT _height)
	{
		D3D11_VIEWPORT viewport;
		ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		viewport.TopLeftX = _x;
		viewport.TopLeftY = _y;
		viewport.Width = (FLOAT)_width;
		viewport.Height = (FLOAT)_height;
		context->RSSetViewports(1, &viewport);
	}
	void __forceinline  SetViewPort(Texture *_texture)
	{
		D3D11_VIEWPORT viewport;
		ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.Width = (FLOAT)_texture->width;
		viewport.Height = (FLOAT)_texture->height;
		context->RSSetViewports(1, &viewport);
	}
	void __forceinline  SetRenderTarget()
	{
		context->OMSetRenderTargets(1, &backbuffer->rendertargetview, backbuffer->depthstencilview);
	}
	void __forceinline  SetRenderTarget(Texture **_texture, UINT8 _numviews)
	{
		ID3D11RenderTargetView *rendertargetviews[8] = { 0,0,0,0,0,0,0,0 };
		for (UINT8 i = 0; i < _numviews; i++)
			rendertargetviews[i] = _texture[i]->rendertargetview;
		context->OMSetRenderTargets(_numviews, rendertargetviews, _texture[0]->depthstencilview);
	}
	void __forceinline  SetUnorderedAccessView()
	{
		context->CSSetUnorderedAccessViews(0, 1, &backbuffer->unorderedaccessview, 0);
	}
	void __forceinline  SetUnorderedAccessView(Texture *_texture, UINT8 _slot)
	{
		context->CSSetUnorderedAccessViews(_slot, 1, &_texture->unorderedaccessview, 0);
	}
	void __forceinline  SetRenderTargetUnorderedAccessView()
	{
		static const UINT dummy[] = { 0 };
		context->OMSetRenderTargetsAndUnorderedAccessViews(1, &backbuffer->rendertargetview, backbuffer->depthstencilview, 1, 1, &backbuffer->unorderedaccessview, dummy);
	}
	void __forceinline  SetRenderTargetUnorderedAccessView(Texture **_rendertarget, UINT8 _numrtvs, Texture **_unorderedaccessview, UINT8 _numuavs)
	{
		static const UINT dummy[] = { 0 };
		ID3D11RenderTargetView *rendertargetviews[8] = { 0,0,0,0,0,0,0,0 };
		for (UINT8 i = 1; i < _numrtvs; i++)
			rendertargetviews[i] = _rendertarget[i]->rendertargetview;
		ID3D11UnorderedAccessView *unorderedaccessviews[8] = { 0,0,0,0,0,0,0,0 };
		for (UINT8 i = 1; i < _numuavs; i++)
			unorderedaccessviews[i] = _unorderedaccessview[i]->unorderedaccessview;
		context->OMSetRenderTargetsAndUnorderedAccessViews(_numrtvs, rendertargetviews, _rendertarget[0]->depthstencilview, 1, _numuavs, unorderedaccessviews, dummy);
	}
	void __forceinline  SetPrimitiveTopology()
	{
		ID3D11HullShader *hullshadertest;
		ID3D11DomainShader *domainshadertest;
		context->HSGetShader(&hullshadertest, 0, 0);
		context->DSGetShader(&domainshadertest, 0, 0);
		if(hullshadertest&&domainshadertest)context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST);
		else context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);		
	}
	void __forceinline  Render(UINT8 vsync)
	{
		swapchain->Present(vsync, 0);
	}
	void __forceinline  ReportAllLiveObjects()
	{
		if(debug)debug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
	}

	UINT8				SamplerCreate(Sampler **_sampler, PO_TYPES _operation, float4 _border, PO_TYPES _filter)
	{
		Sampler *sampler = new Sampler;
		HRESULT hr = S_OK;
		D3D11_SAMPLER_DESC samplerdesc;
		ZeroMemory(&samplerdesc, sizeof(D3D11_SAMPLER_DESC));

		switch (_operation)
		{
			case WRAP:
				samplerdesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
				samplerdesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
				samplerdesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
				break;
			case CLAMP:
				samplerdesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
				samplerdesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
				samplerdesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
				break;
			case BORDER:
				samplerdesc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
				samplerdesc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
				samplerdesc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
				samplerdesc.BorderColor[0] = _border.x;
				samplerdesc.BorderColor[1] = _border.y;
				samplerdesc.BorderColor[2] = _border.z;
				samplerdesc.BorderColor[3] = _border.w;
				break;
			default: print("Graphics: Sampler: Failed to create sampler, invalid operation parameter \n"); return 1;
		}
		switch (_filter)
		{
			case FILTER_POINT:samplerdesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT; break;
			case FILTER_LINEAR:samplerdesc.Filter = D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT; break;
			case FILTER_TRILINEAR:samplerdesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR; break;
			case FILTER_ANISOTROPIC:samplerdesc.Filter = D3D11_FILTER_ANISOTROPIC; break;
			default: print("Graphics: Sampler: Failed to create sampler, invalid filter parameter \n"); return 1;
		}

		samplerdesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		samplerdesc.MinLOD = 0;
		samplerdesc.MaxLOD = D3D11_FLOAT32_MAX;

		samplerdesc.MaxAnisotropy = 16;
		hr = device->CreateSamplerState(&samplerdesc, &sampler->sampler);
		if (hr != S_OK) { print("Graphics: Sampler: Failed to create sampler \n"); return 1; }

		print("Graphics: Sampler: Initialized \n");
		*_sampler = sampler;
		return 0;
	}
	void __forceinline  SamplerSet(Sampler *_sampler, UINT8 _slot,bool _VS,bool _HS,bool _DS,bool _GS,bool _PS,bool _CS)
	{
		if (_VS)context->VSSetSamplers(_slot, 1, &_sampler->sampler);
		if (_HS)context->HSSetSamplers(_slot, 1, &_sampler->sampler);
		if (_DS)context->DSSetSamplers(_slot, 1, &_sampler->sampler);
		if (_GS)context->GSSetSamplers(_slot, 1, &_sampler->sampler);
		if (_PS)context->PSSetSamplers(_slot, 1, &_sampler->sampler);
		if (_CS)context->CSSetSamplers(_slot, 1, &_sampler->sampler);
	}
	UINT8				RasterizerCreate(Rasterizer **_rasterizer, PO_TYPES _fill, PO_TYPES _culling)
	{
		Rasterizer *rasterizer = new Rasterizer;
		HRESULT hr = S_OK;
		D3D11_RASTERIZER_DESC rasterizerdesc;

		switch (_fill)
		{
		case SOLID:			rasterizerdesc.FillMode = D3D11_FILL_SOLID;		break;
		case WIREFRAME:		rasterizerdesc.FillMode = D3D11_FILL_WIREFRAME;	break;
		default:		print("Graphics: Rasterizer: Failed to create rasterizer, invalid fillmode parameter \n");	return 1;
		}
		switch (_culling)
		{
		case CULLNONE:		rasterizerdesc.CullMode = D3D11_CULL_NONE;			break;
		case CULLBACK:		rasterizerdesc.CullMode = D3D11_CULL_BACK;			break;
		case CULLFRONT:		rasterizerdesc.CullMode = D3D11_CULL_FRONT;		break;
		default:		print("Graphics: Rasterizer: Failed to create rasterizer, invalid culling parameter \n");	return 1;
		}
		rasterizerdesc.FrontCounterClockwise = FALSE;
		rasterizerdesc.DepthBias = 0;
		rasterizerdesc.SlopeScaledDepthBias = 0.0f;
		rasterizerdesc.DepthBiasClamp = 0.0f;
		rasterizerdesc.DepthClipEnable = TRUE;
		rasterizerdesc.ScissorEnable = FALSE;
		rasterizerdesc.MultisampleEnable = FALSE;
		rasterizerdesc.AntialiasedLineEnable = FALSE;
		hr = device->CreateRasterizerState(&rasterizerdesc, &rasterizer->rasterizer);
		if (hr != S_OK) { print("Graphics: Rasterizer: Failed to rasterizer sampler\n"); return 1; }

		print("Graphics: Rasterizer: Initialized \n");
		*_rasterizer = rasterizer;
		return 0;
	}
	void __forceinline  RasterizerSet(Rasterizer *_rasterizer)
	{
		context->RSSetState(_rasterizer->rasterizer);
	}

	UINT8				BlendStateCreate(BlendState **_blendstate,bool enable)
	{
		BlendState *blendstate = new BlendState;
		HRESULT hr = S_OK;
		D3D11_BLEND_DESC blenddesc;

		ZeroMemory(&blenddesc, sizeof(D3D11_BLEND_DESC));
		for (UINT8 i = 0; i < 8; i++) 
		{
			blenddesc.RenderTarget[i].BlendEnable = enable;
			blenddesc.RenderTarget[i].SrcBlend = D3D11_BLEND_SRC_ALPHA;
			blenddesc.RenderTarget[i].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
			blenddesc.RenderTarget[i].BlendOp = D3D11_BLEND_OP_ADD;
			blenddesc.RenderTarget[i].SrcBlendAlpha = D3D11_BLEND_ONE;
			blenddesc.RenderTarget[i].DestBlendAlpha = D3D11_BLEND_ZERO;
			blenddesc.RenderTarget[i].BlendOpAlpha = D3D11_BLEND_OP_ADD;
			blenddesc.RenderTarget[i].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		}
		hr = device->CreateBlendState(&blenddesc, &blendstate->blendstate);
		if (hr != S_OK) { print("Graphics: Failed to create blend state\n"); return 1; }

		print("Graphics: BlendState: Initialized \n");
		*_blendstate = blendstate;
		return 0;
	}
	void __forceinline  BlendStateSet(BlendState *_rasterizer)
	{
		float blendfactor[] = { 0,0,0,0 };
		context->OMSetBlendState(_rasterizer->blendstate, blendfactor, 0xffffffff);
	}

	UINT8				ConstantBufferCreate(ConstantBuffer **_constantbuffer, size_t _structuresize, void* _dataptr, PO_TYPES _usage)
	{
		ConstantBuffer *constantbuffer = new ConstantBuffer;
		HRESULT hr;
		D3D11_BUFFER_DESC bufferdesc;
		D3D11_SUBRESOURCE_DATA InitData;
		ZeroMemory(&bufferdesc, sizeof(D3D11_BUFFER_DESC));		
		switch (_usage)
		{			
			case VARIABLE:	bufferdesc.Usage = D3D11_USAGE_DEFAULT;									break;
			case CONSTANT: 	bufferdesc.Usage = D3D11_USAGE_IMMUTABLE; 
				if (_dataptr == 0) { print("Graphics: Constant buffer: Failed to create constant buffer, invalid parameter, pointer to data is mandatory if usage is of type constant \n"); return 1; }					
				break;
		}
		bufferdesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bufferdesc.ByteWidth = (UINT)_structuresize;
		bufferdesc.CPUAccessFlags = 0;
		bufferdesc.StructureByteStride = (UINT)_structuresize;
		bufferdesc.MiscFlags = 0;
		if (_dataptr)
		{
			InitData.pSysMem = _dataptr;
			hr = device->CreateBuffer(&bufferdesc, &InitData, &constantbuffer->constantbuffer);
		}
		else
			hr = device->CreateBuffer(&bufferdesc, 0, &constantbuffer->constantbuffer);
		
		if (hr != S_OK) { print("Graphics: Constant buffer: Failed to create constant buffer\n"); return 1; }

		constantbuffer->dataptr = _dataptr;
		print("Graphics: Constant buffer: Initialized \n");
		*_constantbuffer = constantbuffer;
		return 0;
	}
	void __forceinline  ConstantBufferSet(ConstantBuffer *_constantbuffer, UINT8 _slot, bool _VS, bool _HS, bool _DS, bool _GS, bool _PS, bool _CS)
	{
		if (_VS)context->VSSetConstantBuffers(_slot, 1, &_constantbuffer->constantbuffer);
		if (_HS)context->HSSetConstantBuffers(_slot, 1, &_constantbuffer->constantbuffer);
		if (_DS)context->DSSetConstantBuffers(_slot, 1, &_constantbuffer->constantbuffer);
		if (_GS)context->GSSetConstantBuffers(_slot, 1, &_constantbuffer->constantbuffer);
		if (_PS)context->PSSetConstantBuffers(_slot, 1, &_constantbuffer->constantbuffer);
		if (_CS)context->CSSetConstantBuffers(_slot, 1, &_constantbuffer->constantbuffer);
	}
	void __forceinline  ConstantBufferUpdate(ConstantBuffer *_constantbuffer)
	{
		context->UpdateSubresource(_constantbuffer->constantbuffer, 0, NULL, _constantbuffer->dataptr, 0, 0);
	}
	void __forceinline  ConstantBufferUpload(ConstantBuffer *_constantbuffer, void *_data)
	{
		context->UpdateSubresource(_constantbuffer->constantbuffer, 0, NULL, _data, 0, 0);
	}
	void __forceinline  ConstantBufferCopy(ConstantBuffer *_destination, ConstantBuffer *_source)
	{
		context->CopyResource(_destination->constantbuffer, _source->constantbuffer);
	}
	UINT8				IndexBufferCreate(IndexBuffer **_indexbuffer, unsigned int _count, void* _dataptr, PO_TYPES _usage)
	{
		IndexBuffer *indexbuffer = new IndexBuffer;
		HRESULT hr;
		D3D11_SUBRESOURCE_DATA subresource;
		D3D11_BUFFER_DESC bufferdesc;
		indexbuffer->count = _count;		
		ZeroMemory(&bufferdesc, sizeof(D3D11_BUFFER_DESC));
		switch (_usage)
		{
			case CONSTANT: bufferdesc.Usage = D3D11_USAGE_IMMUTABLE; break;
			case VARIABLE: bufferdesc.Usage = D3D11_USAGE_DEFAULT;
				if (_dataptr == 0) { print("Graphics: Index buffer: Failed to create index buffer, invalid parameter, pointer to data is mandatory if usage is of type constant \n"); return 1; }
				break;
		}
		bufferdesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bufferdesc.ByteWidth = sizeof(UINT32)*_count;
		bufferdesc.CPUAccessFlags = 0;
		bufferdesc.MiscFlags = 0;
		subresource.pSysMem = _dataptr;
		hr = device->CreateBuffer(&bufferdesc, &subresource, &indexbuffer->indexbuffer);
		if (hr != S_OK) { print("Graphics: Index buffer: Failed to create index buffer\n"); return 1; }
		print("Graphics: Index buffer: Initialized\n");
		*_indexbuffer = indexbuffer;
		return 0;
	}
	void __forceinline  IndexBufferSet(IndexBuffer *_indexbuffer)
	{
		context->IASetIndexBuffer(_indexbuffer->indexbuffer, DXGI_FORMAT_R32_UINT, 0);
	}
	void __forceinline  IndexBufferUpload(IndexBuffer *_indexbuffer, void *_dataptr)
	{
		context->UpdateSubresource(_indexbuffer->indexbuffer, 0, NULL, _dataptr, 0, 0);
	}
	void __forceinline  IndexBufferCopy(IndexBuffer *_destination, IndexBuffer *_source)
	{
		context->CopyResource(_destination->indexbuffer, _source->indexbuffer);
	}
	UINT8				BufferCreate(Buffer **_buffer, size_t _structuresize, unsigned int _count, void* _dataptr, PO_TYPES _usage)
	{
		Buffer *buffer = new Buffer;
		HRESULT hr;
		D3D11_BUFFER_DESC bufferdesc;
		D3D11_SHADER_RESOURCE_VIEW_DESC shaderresourceviewdesc;
		D3D11_UNORDERED_ACCESS_VIEW_DESC unorderedaccessviewdesc;
		D3D11_SUBRESOURCE_DATA InitData;
		buffer->size = _structuresize;
		buffer->count = _count;
		buffer->dataptr = _dataptr;
		ZeroMemory(&bufferdesc, sizeof(D3D11_BUFFER_DESC));
		ZeroMemory(&shaderresourceviewdesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
		ZeroMemory(&unorderedaccessviewdesc, sizeof(D3D11_UNORDERED_ACCESS_VIEW_DESC));
		switch (_usage)
		{
			case VARIABLE: bufferdesc.Usage = D3D11_USAGE_DEFAULT;  bufferdesc.BindFlags = D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE; break;
			case CONSTANT: bufferdesc.Usage = D3D11_USAGE_IMMUTABLE; bufferdesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
				if (_dataptr == 0) { print("Graphics: Buffer: Failed to create Buffer, invalid parameter, pointer to data is mandatory if usage is of type constant \n"); return 1; }
				break;
		}
		bufferdesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		bufferdesc.ByteWidth = (UINT)_structuresize*buffer->count;
		bufferdesc.StructureByteStride = (UINT)_structuresize;
		InitData.pSysMem = _dataptr;
		hr = device->CreateBuffer(&bufferdesc, &InitData, &buffer->buffer);
		if (hr != S_OK) { print("Graphics: Buffer: Failed to create buffer \n"); return 1; }

		shaderresourceviewdesc.Format = DXGI_FORMAT_UNKNOWN;
		shaderresourceviewdesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
		shaderresourceviewdesc.Buffer.ElementWidth = (UINT)_structuresize;
		shaderresourceviewdesc.Buffer.NumElements = buffer->count;
		hr = device->CreateShaderResourceView(buffer->buffer, &shaderresourceviewdesc, &buffer->shaderresourceview);
		if (hr != S_OK) { print("Graphics: Buffer: Failed to create buffer shader resource view \n"); return 1; }

		if(featurelevel >= 0xb000)
			if (_usage == VARIABLE)
			{
				unorderedaccessviewdesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
				unorderedaccessviewdesc.Buffer.FirstElement = 0;
				unorderedaccessviewdesc.Format = DXGI_FORMAT_UNKNOWN;
				unorderedaccessviewdesc.Buffer.NumElements = buffer->count;
				hr = device->CreateUnorderedAccessView(buffer->buffer, &unorderedaccessviewdesc, &buffer->unorderedaccessview);
				if (hr != S_OK) { print("Graphics: Buffer: Failed to create buffer unordered access view \n"); return 1; }
			}

		bufferdesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
		bufferdesc.Usage = D3D11_USAGE_STAGING;
		bufferdesc.BindFlags = 0;
		bufferdesc.MiscFlags = 0;
		hr = device->CreateBuffer(&bufferdesc, NULL, &buffer->getbuffer);
		if (hr != S_OK) { print("Graphics: Buffer: Failed to create get buffer \n"); return 1; }

		print("Graphics: Buffer: Initialized \n");
		*_buffer = buffer;
		return 0;
	}
	void __forceinline  BufferSetShaderResouceView(Buffer* _buffer, UINT8 _slot, bool _VS, bool _HS, bool _DS, bool _GS, bool _PS, bool _CS)
	{
		if (_VS)context->VSSetShaderResources(_slot, 1, &_buffer->shaderresourceview);
		if (_HS)context->HSSetShaderResources(_slot, 1, &_buffer->shaderresourceview);
		if (_DS)context->DSSetShaderResources(_slot, 1, &_buffer->shaderresourceview);
		if (_GS)context->GSSetShaderResources(_slot, 1, &_buffer->shaderresourceview);
		if (_PS)context->PSSetShaderResources(_slot, 1, &_buffer->shaderresourceview);
		if (_CS)context->CSSetShaderResources(_slot, 1, &_buffer->shaderresourceview);
	}
	void __forceinline  BufferSetUnorderedAccessView(Buffer* _buffer, UINT8 _slot)
	{
		context->CSSetUnorderedAccessViews(_slot, 1, &_buffer->unorderedaccessview,0);
	}
	void __forceinline  BufferUpdate(Buffer* _buffer)
	{
		context->UpdateSubresource(_buffer->buffer, 0, 0, _buffer->dataptr, 0, 0);
	}
	void __forceinline  BufferUpload(Buffer* _buffer, void *_dataptr)
	{
		context->UpdateSubresource(_buffer->buffer, 0, NULL, _dataptr, 0, 0);
	}
	void __forceinline  BufferDownload(Buffer* _buffer,void *_destination)
	{
		D3D11_MAPPED_SUBRESOURCE mappedresource;
		context->CopyResource(_buffer->getbuffer, _buffer->buffer);
		context->Map(_buffer->getbuffer, 0, D3D11_MAP_READ, 0, &mappedresource);
		memcpy(_destination, mappedresource.pData, _buffer->size*_buffer->count);
		context->Unmap(_buffer->getbuffer, 0);
	}
	void __forceinline  BufferCopy(Buffer* _destination, Buffer* _source)
	{
		context->CopyResource(_destination->buffer, _source->buffer);
	}
	UINT8				TextureCreate(Texture **_texture, char* _filename, PO_TYPES _format, PO_TYPES _usage, UINT8 _mipmaps)
	{
		char filepath[256];
		strcpy_s(filepath, OBJECTPATH);
		strcat_s(filepath, _filename);

		Texture *texture = new Texture;
		HRESULT hr;
		D3D11_TEXTURE2D_DESC texturedesc;
		D3D11_TEXTURE2D_DESC depthstenciltexturedesc;
		D3D11_RENDER_TARGET_VIEW_DESC rendertargetviewdesc;

		D3D11_SHADER_RESOURCE_VIEW_DESC shaderresourceviewdesc;
		D3D11_UNORDERED_ACCESS_VIEW_DESC unorderedaccessviewdesc;
		D3DX11_IMAGE_LOAD_INFO loadinfo;
		ZeroMemory(&loadinfo, sizeof(D3DX11_IMAGE_LOAD_INFO));
		switch (_format)
		{
			case R32G32B32A32_FLOAT:	loadinfo.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;	texture->elementsize = sizeof(FLOAT) * 4;	break;
			case R32G32B32A32_UINT:		loadinfo.Format = DXGI_FORMAT_R32G32B32A32_UINT;	texture->elementsize = sizeof(UINT32) * 4;	break;
			case R32G32B32A32_SINT:		loadinfo.Format = DXGI_FORMAT_R32G32B32A32_SINT;	texture->elementsize = sizeof(INT32) * 4;	break;
			case R32G32B32_FLOAT:		loadinfo.Format = DXGI_FORMAT_R32G32B32_FLOAT;		texture->elementsize = sizeof(FLOAT) * 3;	break;
			case R32G32B32_UINT:		loadinfo.Format = DXGI_FORMAT_R32G32B32_UINT;		texture->elementsize = sizeof(UINT32) * 3;	break;
			case R32G32B32_SINT:		loadinfo.Format = DXGI_FORMAT_R32G32B32_SINT;		texture->elementsize = sizeof(INT32) * 3;	break;
			case R16G16B16A16_UINT:		loadinfo.Format = DXGI_FORMAT_R16G16B16A16_UINT;	texture->elementsize = sizeof(UINT16) * 4;	break;
			case R16G16B16A16_SINT:		loadinfo.Format = DXGI_FORMAT_R16G16B16A16_SINT;	texture->elementsize = sizeof(INT16) * 4;	break;
			case R16G16B16A16_UNORM:	loadinfo.Format = DXGI_FORMAT_R16G16B16A16_UNORM;	texture->elementsize = sizeof(UINT16) * 4;	break;
			case R16G16B16A16_SNORM:	loadinfo.Format = DXGI_FORMAT_R16G16B16A16_SNORM;	texture->elementsize = sizeof(INT16) * 4;	break;
			case R32G32_FLOAT:			loadinfo.Format = DXGI_FORMAT_R32G32_FLOAT;			texture->elementsize = sizeof(FLOAT) * 2;	break;
			case R32G32_UINT:			loadinfo.Format = DXGI_FORMAT_R32G32_UINT;			texture->elementsize = sizeof(UINT32) * 2;	break;
			case R32G32_SINT:			loadinfo.Format = DXGI_FORMAT_R32G32_SINT;			texture->elementsize = sizeof(INT32) * 2;	break;
			case R8G8B8A8_UINT:			loadinfo.Format = DXGI_FORMAT_R8G8B8A8_UINT;		texture->elementsize = sizeof(UINT8) * 4;	break;
			case R8G8B8A8_SINT:			loadinfo.Format = DXGI_FORMAT_R8G8B8A8_SINT;		texture->elementsize = sizeof(INT8) * 4;	break;
			case R8G8B8A8_UNORM:		loadinfo.Format = DXGI_FORMAT_R8G8B8A8_UNORM;		texture->elementsize = sizeof(UINT8) * 4;	break;
			case R8G8B8A8_SNORM:		loadinfo.Format = DXGI_FORMAT_R8G8B8A8_SNORM;		texture->elementsize = sizeof(INT8) * 4;	break;
			case R16G16_UINT:			loadinfo.Format = DXGI_FORMAT_R16G16_UINT;			texture->elementsize = sizeof(UINT16) * 2;	break;
			case R16G16_SINT:			loadinfo.Format = DXGI_FORMAT_R16G16_SINT;			texture->elementsize = sizeof(INT16) * 2;	break;
			case R16G16_UNORM:			loadinfo.Format = DXGI_FORMAT_R16G16_UNORM;			texture->elementsize = sizeof(UINT16) * 2;	break;
			case R16G16_SNORM:			loadinfo.Format = DXGI_FORMAT_R16G16_SNORM;			texture->elementsize = sizeof(INT16) * 2;	break;
			case R32_FLOAT:				loadinfo.Format = DXGI_FORMAT_R32_FLOAT;			texture->elementsize = sizeof(FLOAT);		break;
			case R32_UINT:				loadinfo.Format = DXGI_FORMAT_R32_UINT;				texture->elementsize = sizeof(UINT);		break;
			case R32_SINT:				loadinfo.Format = DXGI_FORMAT_R32_SINT;				texture->elementsize = sizeof(INT);			break;
			case R8G8_UINT:				loadinfo.Format = DXGI_FORMAT_R8G8_UINT;			texture->elementsize = sizeof(UINT8) * 2;	break;
			case R8G8_SINT:				loadinfo.Format = DXGI_FORMAT_R8G8_SINT;			texture->elementsize = sizeof(INT8) * 2;	break;
			case R8G8_UNORM:			loadinfo.Format = DXGI_FORMAT_R8G8_UNORM;			texture->elementsize = sizeof(UINT8) * 2;	break;
			case R8G8_SNORM:			loadinfo.Format = DXGI_FORMAT_R8G8_SNORM;			texture->elementsize = sizeof(INT8) * 2;	break;
			case R16_UINT:				loadinfo.Format = DXGI_FORMAT_R16_UINT;				texture->elementsize = sizeof(UINT16);		break;
			case R16_SINT:				loadinfo.Format = DXGI_FORMAT_R16_SINT;				texture->elementsize = sizeof(INT16);		break;
			case R16_UNORM:				loadinfo.Format = DXGI_FORMAT_R16_UNORM;			texture->elementsize = sizeof(UINT16);		break;
			case R16_SNORM:				loadinfo.Format = DXGI_FORMAT_R16_SNORM;			texture->elementsize = sizeof(INT16);		break;
			case R8_UINT:				loadinfo.Format = DXGI_FORMAT_R8_UINT;				texture->elementsize = sizeof(UINT8);		break;
			case R8_SINT:				loadinfo.Format = DXGI_FORMAT_R8_SINT;				texture->elementsize = sizeof(INT8);		break;
			case R8_UNORM:				loadinfo.Format = DXGI_FORMAT_R8_UNORM;				texture->elementsize = sizeof(UINT8);		break;
			case R8_SNORM:				loadinfo.Format = DXGI_FORMAT_R8_SNORM;				texture->elementsize = sizeof(INT8);		break;
			default:					print("Graphics: Texture: Failed to create texture, invalid format parameter \n");				return 1;
		}
		switch (_usage)
		{
			case CONSTANT: loadinfo.Usage = D3D11_USAGE_IMMUTABLE;	  loadinfo.BindFlags = D3D11_BIND_SHADER_RESOURCE;	break;
			case VARIABLE: 
				loadinfo.Usage = D3D11_USAGE_DEFAULT;	  
				if (featurelevel >= 0xb000)loadinfo.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET | D3D11_BIND_UNORDERED_ACCESS;
				else loadinfo.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;	
				break;
			default:       print("Graphics: Texture: Failed to create texture, invalid usage parameter \n");
		}
		loadinfo.MipLevels = _mipmaps;
		ID3D11Resource *resource;
		hr = D3DX11CreateTextureFromFile(device, filepath, &loadinfo, 0, &resource, 0);
		if (hr != S_OK) { print("Graphics: Texture: Failed to create texture (%s) \n", filepath); return 1; }
		resource->QueryInterface(__uuidof(ID3D11Texture2D), (VOID**)&texture->texture);
		resource->Release();
		texture->texture->GetDesc(&texturedesc);
		texture->width = texturedesc.Width;
		texture->height = texturedesc.Height;

		shaderresourceviewdesc.Format = texturedesc.Format;
		shaderresourceviewdesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		shaderresourceviewdesc.Texture2D.MostDetailedMip = 0;
		shaderresourceviewdesc.Texture2D.MipLevels = texturedesc.MipLevels;
		hr = device->CreateShaderResourceView(texture->texture, &shaderresourceviewdesc, &texture->shaderrecourceview);
		if (hr != S_OK) { print("Graphics: Texture: Failed to create texture shader resource view\n"); return 1; }

		rendertargetviewdesc.Format = texturedesc.Format;
		rendertargetviewdesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		rendertargetviewdesc.Texture2D.MipSlice = 0;
		if (_usage == VARIABLE)
			hr = device->CreateRenderTargetView(texture->texture, &rendertargetviewdesc, &texture->rendertargetview);
		if (hr != S_OK) { print("Graphics: Texture: Failed to create texture render target view \n"); return 1; }

		unorderedaccessviewdesc.Format = texturedesc.Format;
		unorderedaccessviewdesc.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE2D;
		unorderedaccessviewdesc.Texture2D.MipSlice = 0;
		if (featurelevel >= 0xb000)
			if (_usage == VARIABLE)
				hr = device->CreateUnorderedAccessView(texture->texture, &unorderedaccessviewdesc, &texture->unorderedaccessview);
		if (hr != S_OK) { print("Graphics: Texture: Failed to create texture unordered access view \n"); return 1; }

		texturedesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
		texturedesc.Usage = D3D11_USAGE_STAGING;
		texturedesc.BindFlags = 0;
		hr = device->CreateTexture2D(&texturedesc, NULL, &texture->gettexture);
		if (hr != S_OK) { print("Graphics: Texture: Failed to create texture get texture \n"); return 1; }

		ZeroMemory(&depthstenciltexturedesc, sizeof(D3D11_TEXTURE2D_DESC));
		depthstenciltexturedesc.Width = texture->width;
		depthstenciltexturedesc.Height = texture->height;
		depthstenciltexturedesc.MipLevels = 1;
		depthstenciltexturedesc.ArraySize = 1;
		depthstenciltexturedesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthstenciltexturedesc.SampleDesc.Count = 1;
		depthstenciltexturedesc.SampleDesc.Quality = 0;
		depthstenciltexturedesc.Usage = D3D11_USAGE_DEFAULT;
		depthstenciltexturedesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthstenciltexturedesc.CPUAccessFlags = 0;
		depthstenciltexturedesc.MiscFlags = 0;
		hr = device->CreateTexture2D(&depthstenciltexturedesc, NULL, &texture->depthstenciltexture);
		if (hr != S_OK) { print("Graphics: Texture: Failed to create texture depth stencil texture \n"); return 1; }

		D3D11_DEPTH_STENCIL_VIEW_DESC depthstencilviewdsec;
		ZeroMemory(&depthstencilviewdsec, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
		depthstencilviewdsec.Format = depthstenciltexturedesc.Format;
		depthstencilviewdsec.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
		depthstencilviewdsec.Texture2D.MipSlice = 0;
		hr = device->CreateDepthStencilView(texture->depthstenciltexture, &depthstencilviewdsec, &texture->depthstencilview);
		if (hr != S_OK) { print("Graphics: Texture: Failed to create texture depth stencil view \n"); return 1; }

		print("Graphics: Texture: Initialized \n");
		*_texture = texture;
		return 0;
	}
	UINT8				TextureCreate(Texture **_texture, PO_TYPES _format, unsigned int _width, unsigned int _height, UINT8 _mipmaps, UINT8 _antializing)
	{
		if (_antializing > 1 && _mipmaps != 1)
		{print("Graphics: Texture: Failed to create texture invalid parameter! cannot have mipmaps for multisampled texture\n"); return 1;}
		Texture *texture = new Texture;
		HRESULT hr;
		D3D11_TEXTURE2D_DESC texturedesc;
		D3D11_TEXTURE2D_DESC depthstenciltexturedesc;
		D3D11_RENDER_TARGET_VIEW_DESC rendertargetviewdesc;
		D3D11_SHADER_RESOURCE_VIEW_DESC shaderresourceviewdesc;
		D3D11_UNORDERED_ACCESS_VIEW_DESC uavdesc;
		texture->width = _width;
		texture->height = _height;
		ZeroMemory(&texturedesc, sizeof(texturedesc));
		texturedesc.Width = _width;
		texturedesc.Height = _height;
		switch (_format)
		{
			case R32G32B32A32_FLOAT:	texturedesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;	texture->elementsize = sizeof(FLOAT) * 4;	break;
			case R32G32B32A32_UINT:		texturedesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;		texture->elementsize = sizeof(UINT32) * 4;	break;
			case R32G32B32A32_SINT:		texturedesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;		texture->elementsize = sizeof(INT32) * 4;	break;
			case R32G32B32_FLOAT:		texturedesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;		texture->elementsize = sizeof(FLOAT) * 3;	break;
			case R32G32B32_UINT:		texturedesc.Format = DXGI_FORMAT_R32G32B32_UINT;		texture->elementsize = sizeof(UINT32) * 3;	break;
			case R32G32B32_SINT:		texturedesc.Format = DXGI_FORMAT_R32G32B32_SINT;		texture->elementsize = sizeof(INT32) * 3;	break;
			case R16G16B16A16_UINT:		texturedesc.Format = DXGI_FORMAT_R16G16B16A16_UINT;		texture->elementsize = sizeof(UINT16) * 4;	break;
			case R16G16B16A16_SINT:		texturedesc.Format = DXGI_FORMAT_R16G16B16A16_SINT;		texture->elementsize = sizeof(INT16) * 4;	break;
			case R16G16B16A16_UNORM:	texturedesc.Format = DXGI_FORMAT_R16G16B16A16_UNORM;	texture->elementsize = sizeof(UINT16) * 4;	break;
			case R16G16B16A16_SNORM:	texturedesc.Format = DXGI_FORMAT_R16G16B16A16_SNORM;	texture->elementsize = sizeof(INT16) * 4;	break;
			case R32G32_FLOAT:			texturedesc.Format = DXGI_FORMAT_R32G32_FLOAT;			texture->elementsize = sizeof(FLOAT) * 2;	break;
			case R32G32_UINT:			texturedesc.Format = DXGI_FORMAT_R32G32_UINT;			texture->elementsize = sizeof(UINT32) * 2;	break;
			case R32G32_SINT:			texturedesc.Format = DXGI_FORMAT_R32G32_SINT;			texture->elementsize = sizeof(INT32) * 2;	break;
			case R8G8B8A8_UINT:			texturedesc.Format = DXGI_FORMAT_R8G8B8A8_UINT;			texture->elementsize = sizeof(UINT8) * 4;	break;
			case R8G8B8A8_SINT:			texturedesc.Format = DXGI_FORMAT_R8G8B8A8_SINT;			texture->elementsize = sizeof(INT8) * 4;	break;
			case R8G8B8A8_UNORM:		texturedesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;		texture->elementsize = sizeof(UINT8) * 4;	break;
			case R8G8B8A8_SNORM:		texturedesc.Format = DXGI_FORMAT_R8G8B8A8_SNORM;		texture->elementsize = sizeof(INT8) * 4;	break;
			case R16G16_UINT:			texturedesc.Format = DXGI_FORMAT_R16G16_UINT;			texture->elementsize = sizeof(UINT16) * 2;	break;
			case R16G16_SINT:			texturedesc.Format = DXGI_FORMAT_R16G16_SINT;			texture->elementsize = sizeof(INT16) * 2;	break;
			case R16G16_UNORM:			texturedesc.Format = DXGI_FORMAT_R16G16_UNORM;			texture->elementsize = sizeof(UINT16) * 2;	break;
			case R16G16_SNORM:			texturedesc.Format = DXGI_FORMAT_R16G16_SNORM;			texture->elementsize = sizeof(INT16) * 2;	break;
			case R32_FLOAT:				texturedesc.Format = DXGI_FORMAT_R32_FLOAT;				texture->elementsize = sizeof(FLOAT);		break;
			case R32_UINT:				texturedesc.Format = DXGI_FORMAT_R32_UINT;				texture->elementsize = sizeof(UINT);		break;
			case R32_SINT:				texturedesc.Format = DXGI_FORMAT_R32_SINT;				texture->elementsize = sizeof(INT);			break;
			case R8G8_UINT:				texturedesc.Format = DXGI_FORMAT_R8G8_UINT;				texture->elementsize = sizeof(UINT8) * 2;	break;
			case R8G8_SINT:				texturedesc.Format = DXGI_FORMAT_R8G8_SINT;				texture->elementsize = sizeof(INT8) * 2;	break;
			case R8G8_UNORM:			texturedesc.Format = DXGI_FORMAT_R8G8_UNORM;			texture->elementsize = sizeof(UINT8) * 2;	break;
			case R8G8_SNORM:			texturedesc.Format = DXGI_FORMAT_R8G8_SNORM;			texture->elementsize = sizeof(INT8) * 2;	break;
			case R16_UINT:				texturedesc.Format = DXGI_FORMAT_R16_UINT;				texture->elementsize = sizeof(UINT16);		break;
			case R16_SINT:				texturedesc.Format = DXGI_FORMAT_R16_SINT;				texture->elementsize = sizeof(INT16);		break;
			case R16_UNORM:				texturedesc.Format = DXGI_FORMAT_R16_UNORM;				texture->elementsize = sizeof(UINT16);		break;
			case R16_SNORM:				texturedesc.Format = DXGI_FORMAT_R16_SNORM;				texture->elementsize = sizeof(INT16);		break;
			case R8_UINT:				texturedesc.Format = DXGI_FORMAT_R8_UINT;				texture->elementsize = sizeof(UINT8);		break;
			case R8_SINT:				texturedesc.Format = DXGI_FORMAT_R8_SINT;				texture->elementsize = sizeof(INT8);		break;
			case R8_UNORM:				texturedesc.Format = DXGI_FORMAT_R8_UNORM;				texture->elementsize = sizeof(UINT8);		break;
			case R8_SNORM:				texturedesc.Format = DXGI_FORMAT_R8_SNORM;				texture->elementsize = sizeof(INT8);		break;
			default:					print("Graphics: Texture: Failed to create texture, invalid format parameter \n");					return 1;
		}
		texturedesc.MipLevels = _mipmaps;
		texturedesc.ArraySize = 1;
		texturedesc.SampleDesc.Count = _antializing;
		texturedesc.SampleDesc.Quality = 0;
		texturedesc.Usage = D3D11_USAGE_DEFAULT;
		if (featurelevel >= 0xb000 && _antializing==1)texturedesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;
		else texturedesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
		texturedesc.CPUAccessFlags = 0;
		texturedesc.MiscFlags = 0;
		hr = device->CreateTexture2D(&texturedesc, NULL, &texture->texture);
		if (hr != S_OK) { print("Graphics: Texture: Failed to create texture\n"); return 1; }

		if (_antializing > 1)
		{
			shaderresourceviewdesc.Format = texturedesc.Format;
			shaderresourceviewdesc.ViewDimension = D3D_SRV_DIMENSION_TEXTURE2DMS;
			hr = device->CreateShaderResourceView(texture->texture, &shaderresourceviewdesc, &texture->shaderrecourceview);
			if (hr != S_OK) { print("Graphics: Texture: Failed to create texture shader resource view\n"); return 1; }
			rendertargetviewdesc.Format = texturedesc.Format;
			rendertargetviewdesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DMS;
			hr = device->CreateRenderTargetView(texture->texture, &rendertargetviewdesc, &texture->rendertargetview);
			if (hr != S_OK) { print("Graphics: Texture: Failed to create texture render target view \n"); return 1; }
		}
		else
		{
			shaderresourceviewdesc.Format = texturedesc.Format;
			shaderresourceviewdesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
			shaderresourceviewdesc.Texture2D.MostDetailedMip = 0;
			shaderresourceviewdesc.Texture2D.MipLevels = _mipmaps;
			hr = device->CreateShaderResourceView(texture->texture, &shaderresourceviewdesc, &texture->shaderrecourceview);
			if (hr != S_OK) { print("Graphics: Texture: Failed to create texture shader resource view\n"); return 1; }
			rendertargetviewdesc.Format = texturedesc.Format;
			rendertargetviewdesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
			rendertargetviewdesc.Texture2D.MipSlice = 0;
			hr = device->CreateRenderTargetView(texture->texture, &rendertargetviewdesc, &texture->rendertargetview);
			if (hr != S_OK) { print("Graphics: Texture: Failed to create texture render target view \n"); return 1; }
			uavdesc.Format = texturedesc.Format;
			uavdesc.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE2D;
			uavdesc.Texture2D.MipSlice = 0;
			if (featurelevel >= 0xb000)
				hr = device->CreateUnorderedAccessView(texture->texture, &uavdesc, &texture->unorderedaccessview);
			if (hr != S_OK) { print("Graphics: Texture: Failed to create texture unordered access view \n"); return 1; }
			texturedesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
			texturedesc.Usage = D3D11_USAGE_STAGING;
			texturedesc.BindFlags = 0;
			hr = device->CreateTexture2D(&texturedesc, NULL, &texture->gettexture);
			if (hr != S_OK) { print("Graphics: Texture: Failed to create texture get texture \n"); return 1; }
		}

		ZeroMemory(&depthstenciltexturedesc, sizeof(D3D11_TEXTURE2D_DESC));
		depthstenciltexturedesc.Width = _width;
		depthstenciltexturedesc.Height = _height;
		depthstenciltexturedesc.MipLevels = 1;
		depthstenciltexturedesc.ArraySize = 1;
		depthstenciltexturedesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthstenciltexturedesc.SampleDesc.Count = _antializing;
		depthstenciltexturedesc.SampleDesc.Quality = 0;
		depthstenciltexturedesc.Usage = D3D11_USAGE_DEFAULT;
		depthstenciltexturedesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthstenciltexturedesc.CPUAccessFlags = 0;
		depthstenciltexturedesc.MiscFlags = 0;
		hr = device->CreateTexture2D(&depthstenciltexturedesc, NULL, &texture->depthstenciltexture);
		if (hr != S_OK) { print("Graphics: Texture: Failed to create texture depth stencil texture \n"); return 1; }

		D3D11_DEPTH_STENCIL_VIEW_DESC depthstencilviewdsec;
		ZeroMemory(&depthstencilviewdsec, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
		depthstencilviewdsec.Format = depthstenciltexturedesc.Format;
		depthstencilviewdsec.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
		depthstencilviewdsec.Texture2D.MipSlice = 0;
		hr = device->CreateDepthStencilView(texture->depthstenciltexture, &depthstencilviewdsec, &texture->depthstencilview);
		if (hr != S_OK) { print("Graphics: Texture: Failed to create texture depth stencil view \n"); return 1; }

		print("Graphics: Texture: Initialized \n");
		*_texture = texture;
		return 0;
	}
	void __forceinline  TextureSetShaderResouceView(Texture* _texture, UINT8 _slot, bool _VS, bool _HS, bool _DS, bool _GS, bool _PS, bool _CS)
	{
		if (_VS)context->VSSetShaderResources(_slot, 1, &_texture->shaderrecourceview);
		if (_HS)context->HSSetShaderResources(_slot, 1, &_texture->shaderrecourceview);
		if (_DS)context->DSSetShaderResources(_slot, 1, &_texture->shaderrecourceview);
		if (_GS)context->GSSetShaderResources(_slot, 1, &_texture->shaderrecourceview);
		if (_PS)context->PSSetShaderResources(_slot, 1, &_texture->shaderrecourceview);
		if (_CS)context->CSSetShaderResources(_slot, 1, &_texture->shaderrecourceview);
	}
	void __forceinline  TextureSetUnorderedAccessView(Texture* _buffer, UINT8 _slot)
	{
		context->CSSetUnorderedAccessViews(_slot, 1, &_buffer->unorderedaccessview, 0);
	}
	void __forceinline  TextureUpload(Texture* _texture, void *_dataptr)
	{
		D3D11_BOX box;
		box.left = 0; box.right = _texture->width;
		box.top = 0; box.bottom = _texture->height;
		box.front = 0; box.back = 1;
		context->UpdateSubresource(_texture->texture, 0, &box, _dataptr, (UINT)_texture->elementsize*_texture->width, (UINT)_texture->elementsize*_texture->width*_texture->height);
	}
	void __forceinline  TextureUploadPixel(Texture* _texture, int _x, int _y, void* _color)
	{
		D3D11_BOX box;
		box.left = _x; box.right = _x + 1;
		box.top = _y; box.bottom = _y + 1;
		box.front = 0; box.back = 1;
		context->UpdateSubresource(_texture->texture, 0, &box, _color, 0, 0);
	}
	void __forceinline  TextureDownload(Texture* _texture,void* _destination)
	{
		D3D11_MAPPED_SUBRESOURCE mappedresource;
		context->CopyResource(_texture->gettexture, _texture->texture);
		context->Map(_texture->gettexture, 0, D3D11_MAP_READ, 0, &mappedresource);
		memcpy(_destination, mappedresource.pData, (sizeof(_texture->elementsize)*(_texture->width)*(_texture->height)));
		context->Unmap(_texture->gettexture, 0);
	}
	void __forceinline  TextureCopy(Texture* _destination, Texture* _source)
	{
		context->CopyResource(_destination->texture, _source->texture);
	}
	UINT8				VertexShaderCreate(VertexShader **_verstexshader, char* _filename)
	{
		VertexShader *verstexshader = new VertexShader;
		HRESULT hr;
		ID3D10Blob *VS, *VError;
		LPVOID verror = NULL;
		char filepath[256];
		strcpy_s(filepath, SHADERPATH);
		strcat_s(filepath, _filename);

		if (featurelevel == 0xa000)hr = D3DX11CompileFromFile(filepath, 0, 0, "main", "vs_4_0", SHADERFLAG | D3D10_SHADER_PACK_MATRIX_COLUMN_MAJOR, 0, 0, &VS, &VError, 0);
		if (featurelevel == 0xa100)hr = D3DX11CompileFromFile(filepath, 0, 0, "main", "vs_4_1", SHADERFLAG | D3D10_SHADER_PACK_MATRIX_COLUMN_MAJOR, 0, 0, &VS, &VError, 0);
		if (featurelevel >= 0xb000)hr = D3DX11CompileFromFile(filepath, 0, 0, "main", "vs_5_0", SHADERFLAG | D3D10_SHADER_PACK_MATRIX_COLUMN_MAJOR, 0, 0, &VS, &VError, 0);

		if (VError)
			verror = VError->GetBufferPointer();
		char* errorv = (char*)verror;
		UNREFERENCED_PARAMETER(errorv);
		if (hr != S_OK) { print("Graphics: Vertex Shader: Failed to create vertex shader (%s) \n", _filename); return 1; }
		hr = device->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &verstexshader->vertexshader);
		if (hr != S_OK) { print("Graphics: Vertex Shader: Failed to create vertex shader (%s) \n", _filename); return 1; }

		D3D11_INPUT_ELEMENT_DESC shaderlayout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL"  , 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT   , 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		UINT numElements = ARRAYSIZE(shaderlayout);
		hr = device->CreateInputLayout(shaderlayout, numElements, VS->GetBufferPointer(), VS->GetBufferSize(), &verstexshader->layout);
		if (hr != S_OK) { print("Graphics: Vertex Shader: Failed to create vertex shader (%s) \n", _filename); return 1; }

		if (VS)VS->Release();
		if (VError)VError->Release();
		print("Graphics: Vertex Shader: Initialized (%s) \n", _filename);
		*_verstexshader = verstexshader;
		return 0;
	}
	void __forceinline  VertexShaderSet(VertexShader* _shader)
	{
		context->VSSetShader(_shader->vertexshader, 0, 0);
	}
	void __forceinline  VertexShaderReset()
	{
		context->VSSetShader(0, 0, 0);
	}
	UINT8				HullShaderCreate(HullShader **_hullshader, char* _filename)
	{
		HullShader *hullshader = new HullShader;
		HRESULT hr;
		ID3D10Blob*HS, *HError;
		LPVOID herror = NULL;
		char filepath[256];
		strcpy_s(filepath, SHADERPATH);
		strcat_s(filepath, _filename);

		if (featurelevel < 0xb000) { print("Graphics: Hull Shader: Failed to create hull graphics hardware not supported need atleast DirectX 11 (%s) \n", _filename); return 1; }
		if (featurelevel >= 0xb000)hr = D3DX11CompileFromFile(filepath, 0, 0, "main", "hs_5_0", SHADERFLAG, 0, 0, &HS, &HError, 0);

		if (HError)
			herror = HError->GetBufferPointer();
		char* errorh = (char*)herror;
		UNREFERENCED_PARAMETER(errorh);
		if (hr != S_OK) { print("Graphics: Hull Shader: Failed to create hull shader (%s) \n", _filename);	return 1; }
		hr = device->CreateHullShader(HS->GetBufferPointer(), HS->GetBufferSize(), NULL, &hullshader->hullshader);
		if (hr != S_OK) { print("Graphics: Hull Shader: Failed to create hull shader (%s) \n", _filename); return 1; }
		if (HS)HS->Release();
		if (HError)HError->Release();
		print("Graphics: Hull Shader: Initialized (%s) \n", _filename);
		*_hullshader = hullshader;
		return 0;
	}
	void __forceinline  HullShaderSet(HullShader* _shader)
	{
		context->HSSetShader(_shader->hullshader, 0, 0);
	}
	void __forceinline  HullShaderReset()
	{
		context->HSSetShader(0, 0, 0);
	}
	UINT8				DomainShaderCreate(DomainShader **_domainshader, char* _filename)
	{
		DomainShader *domainshader = new DomainShader;
		HRESULT hr;
		ID3D10Blob*DS, *DError;
		LPVOID herror = NULL;
		char filepath[256];
		strcpy_s(filepath, SHADERPATH);
		strcat_s(filepath, _filename);

		if (featurelevel < 0xb000) { print("Graphics: Domain Shader: Failed to create domain graphics hardware not supported need atleast DirectX 11 (%s) \n", _filename); return 1; }
		if (featurelevel >= 0xb000)hr = D3DX11CompileFromFile(filepath, 0, 0, "main", "ds_5_0", SHADERFLAG, 0, 0, &DS, &DError, 0);

		if (DError)
			herror = DError->GetBufferPointer();
		char* errord = (char*)perror;
		UNREFERENCED_PARAMETER(errord);
		if (hr != S_OK) { print("Graphics: Domain Shader: Failed to create domain shader (%s) \n", _filename);	return 1; }
		hr = device->CreateDomainShader(DS->GetBufferPointer(), DS->GetBufferSize(), NULL, &domainshader->domainshader);
		if (hr != S_OK) { print("Graphics: Domain Shader: Failed to create domain shader (%s) \n", _filename); return 1; }
		if (DS)DS->Release();
		if (DError)DError->Release();
		print("Graphics: Domain Shader: Initialized (%s) \n", _filename);
		*_domainshader = domainshader;
		return 0;
	}
	void __forceinline  DomainShaderSet(DomainShader* _shader)
	{
		context->DSSetShader(_shader->domainshader, 0, 0);
	}
	void __forceinline  DomainShaderReset()
	{
		context->DSSetShader(0, 0, 0);
	}
	UINT8				GeometryShaderCreate(GeometryShader **_geometryshader, char* _filename)
	{
		GeometryShader *geometryshader = new GeometryShader;
		HRESULT hr;
		ID3D10Blob*GS, *GError;
		LPVOID gerror = NULL;
		char filepath[256];
		strcpy_s(filepath, SHADERPATH);
		strcat_s(filepath, _filename);

		if (featurelevel == 0xa000)hr = D3DX11CompileFromFile(filepath, 0, 0, "main", "gs_4_0", SHADERFLAG, 0, 0, &GS, &GError, 0);
		if (featurelevel == 0xa100)hr = D3DX11CompileFromFile(filepath, 0, 0, "main", "gs_4_1", SHADERFLAG, 0, 0, &GS, &GError, 0);
		if (featurelevel >= 0xb000)hr = D3DX11CompileFromFile(filepath, 0, 0, "main", "gs_5_0", SHADERFLAG, 0, 0, &GS, &GError, 0);

		if (GError)
			gerror = GError->GetBufferPointer();
		char* errorg = (char*)gerror;
		UNREFERENCED_PARAMETER(errorg);
		if (hr != S_OK) { print("Graphics: Geometry Shader: Failed to create geometry shader (%s) \n", _filename);	return 1; }
		hr = device->CreateGeometryShader(GS->GetBufferPointer(), GS->GetBufferSize(), NULL, &geometryshader->geometryshader);
		if (hr != S_OK) { print("Graphics: Geometry Shader: Failed to create geometry shader (%s) \n", _filename); return 1; }
		if (GS)GS->Release();
		if (GError)GError->Release();
		print("Graphics: Geometry Shader: Initialized (%s) \n", _filename);
		*_geometryshader = geometryshader;
		return 0;
	}
	void __forceinline  GeometryShaderSet(GeometryShader* _shader)
	{
		context->GSSetShader(_shader->geometryshader, 0, 0);
	}
	void __forceinline  GeometryShaderReset()
	{
		context->GSSetShader(0, 0, 0);
	}
	UINT8				PixelShaderCreate(PixelShader **_pixelshader, char* _filename)
	{
		PixelShader *pixelshader = new PixelShader;
		HRESULT hr;
		ID3D10Blob*PS, *PError;
		LPVOID perror = NULL;
		char filepath[256];
		strcpy_s(filepath, SHADERPATH);
		strcat_s(filepath, _filename);

		if (featurelevel == 0xa000)hr = D3DX11CompileFromFile(filepath, 0, 0, "main", "ps_4_0", SHADERFLAG | D3D10_SHADER_PACK_MATRIX_COLUMN_MAJOR, 0, 0, &PS, &PError, 0);
		if (featurelevel == 0xa100)hr = D3DX11CompileFromFile(filepath, 0, 0, "main", "ps_4_1", SHADERFLAG | D3D10_SHADER_PACK_MATRIX_COLUMN_MAJOR, 0, 0, &PS, &PError, 0);
		if (featurelevel >= 0xb000)hr = D3DX11CompileFromFile(filepath, 0, 0, "main", "ps_5_0", SHADERFLAG | D3D10_SHADER_PACK_MATRIX_COLUMN_MAJOR, 0, 0, &PS, &PError, 0);
		if (PError)
			perror = PError->GetBufferPointer();
		char* errorp = (char*)perror;
		UNREFERENCED_PARAMETER(errorp);
		if (hr != S_OK) { print("Graphics: Pixel Shader: Failed to create pixel shader (%s) \n", _filename);	return 1; }
		hr = device->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &pixelshader->pixelshader);
		if (hr != S_OK) { print("Graphics: Pixel Shader: Failed to create pixel shader (%s) \n", _filename); return 1; }
		if (PS)PS->Release();
		if (PError)PError->Release();
		print("Graphics: Pixel Shader: Initialized (%s) \n", _filename);
		*_pixelshader = pixelshader;
		return 0;
	}
	void __forceinline  PixelShaderSet(PixelShader* _shader)
	{
		context->PSSetShader(_shader->pixelshader, 0, 0);
	}
	void __forceinline  PixelShaderReset()
	{
		context->PSSetShader(0, 0, 0);
	}
	UINT8				ComputeShaderCreate(ComputeShader **_computeshader, char* _filename)
	{
		ComputeShader *computeshader = new ComputeShader;
		HRESULT hr;
		ID3D10Blob*CS=0, *CError=0;
		LPVOID cerror = NULL;
		char filepath[256];
		strcpy_s(filepath, SHADERPATH);
		strcat_s(filepath, _filename);

		if (featurelevel < 0xb000) { print("Graphics: Compute Shader: Failed to create compute graphics hardware not supported need atleast DirectX 11 (%s) \n", _filename); return 1; }
		if (featurelevel >= 0xb000)hr = D3DX11CompileFromFile(filepath, 0, 0, "main", "cs_5_0", SHADERFLAG, 0, 0, &CS, &CError, 0);
		if (CError)
			cerror = CError->GetBufferPointer();
		char* errorc = (char*)cerror;
		UNREFERENCED_PARAMETER(errorc);
		if (hr != S_OK) { print("Graphics: Compute Shader: Failed to create compute shader (%s) \n", _filename);	return 1; }
		hr = device->CreateComputeShader(CS->GetBufferPointer(), CS->GetBufferSize(), NULL, &computeshader->computeshader);
		if (hr != S_OK) { print("Graphics: Compute Shader: Failed to create compute shader (%s) \n", _filename); return 1; }
		if (CS)CS->Release();
		if (CError)CError->Release();
		print("Graphics: Compute Shader: Initialized (%s) \n", _filename);
		*_computeshader = computeshader;
		return 0;		
	}
	void __forceinline  ComputeShaderSet(ComputeShader* _shader)
	{
		context->CSSetShader(_shader->computeshader, 0, 0);
	}
	void __forceinline  ComputeShaderReset()
	{
		context->CSSetShader(0, 0, 0);
	}

	void __forceinline  Compute(UINT32 _threadx, UINT32 _thready, UINT32 _threadz)
	{
		context->Dispatch(_threadx, _thready, _threadz);
	}
	void __forceinline  Draw(UINT32 _threadx)
	{
		context->Draw(_threadx, 0);
	}
	void __forceinline  Draw(UINT32 _threadx, UINT32 _thready)
	{
		context->DrawInstanced(_threadx, _thready, 0, 0);
	}
	void __forceinline  DrawIndexed(UINT32 _threadx)
	{
		context->DrawIndexed(_threadx, 0 , 0);
	}
	void __forceinline  DrawIndexedInstanced(UINT32 _threadx, UINT32 _thready)
	{
		context->DrawIndexedInstanced(_threadx, _thready, 0, 0, 0);
	}

	Graphics()
	{
		ZeroMemory(this, sizeof(Graphics));
	}
	~Graphics()
	{
		delete backbuffer;
		if (context)context->Release();  context=0;
		if (swapchain)swapchain->Release();  swapchain=0;
		if (device)device->Release();  device=0;
		if (debug)debug->Release(); debug=0;
	}
};