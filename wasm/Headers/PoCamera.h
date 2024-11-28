 struct Camera
{
private:
	Graphics	*graphics;
	Mouse		*mouse;
	Keyboard	*keyboard;
	Graphics::ConstantBuffer	*viewprojectionbuffer;
public:
	Matrix view;
	Matrix projection;
	float mousex, mousey, mousez;
	float posx, posy, posz, lookx, looky, lookz, upx, upy, upz;
	PO_TYPES projectionytpe;

	UINT8		  Initialize(Graphics *_graphics, Mouse *_mouse, Keyboard *_keyboard,PO_TYPES _projectiontype, float _zoomorwidth, float _ratioorheight, float _near, float _far)
	{
		graphics = _graphics;
		mouse = _mouse;
		keyboard = _keyboard;
		projectionytpe = _projectiontype;
		if (graphics->ConstantBufferCreate(&viewprojectionbuffer, sizeof(FLOAT) * 16 * 2, 0, VARIABLE)) return 1;
		view.rows = view.columns = 4;
		projection.rows = projection.columns = 4;
		if (projectionytpe == PERSPECTIVE)
			projection = GenerateProjectionMatrixPrespective(_zoomorwidth, _ratioorheight, _near, _far);
		else if (projectionytpe == ORTHOGRAPHIC)
			projection = GenerateProjectionMatrixOrthographic(_zoomorwidth, _ratioorheight, _near, _far);
		else
			return 1;
		projection.Transpose();
		return 0;
	}
	void __inline SetEye(float _posx, float _posy, float _posz, float _lookx, float _looky, float _lookz, float _upx, float _upy, float _upz)
	{
		posx = _posx; posy = _posy; posz = _posz;
		lookx = _lookx; looky = _looky; lookz = _lookz;
		upx = _upx; upy = _upy; upz = _upz;
		view = GenerateEyeMatrix(_posx, _posy, _posz, _lookx, _looky, _lookz, _upx, _upy, _upz);
		view.Transpose();
	}
	void __inline SetProjection(float _zoomorwidth, float _ratioorheight, float _near, float _far)
	{
		if(projectionytpe == PERSPECTIVE)
		projection = GenerateProjectionMatrixPrespective(_zoomorwidth, _ratioorheight, _near, _far);
		else
		projection = GenerateProjectionMatrixOrthographic(_zoomorwidth, _ratioorheight, _near, _far);
		projection.Transpose();
	}
	void __inline FlyCam(float linearspeed, float rotationalspeed)
	{
		mousex += 0.0000005f*rotationalspeed*(float)mouse->Dx();
		mousey += 0.0000005f*rotationalspeed*(float)mouse->Dy();
		posx += 0.000005f*linearspeed*(sinf((mousex)*PI / 180.0f))*keyboard->Key(DIK_W);
		posz += 0.000005f*linearspeed*(cosf((mousex)*PI / 180.0f))*keyboard->Key(DIK_W);
		posx -= 0.000005f*linearspeed*(sinf((mousex)*PI / 180.0f))*keyboard->Key(DIK_S);
		posz -= 0.000005f*linearspeed*(cosf((mousex)*PI / 180.0f))*keyboard->Key(DIK_S);
		posx += 0.000005f*linearspeed*(cosf((mousex)*PI / 180.0f))*keyboard->Key(DIK_D);
		posz -= 0.000005f*linearspeed*(sinf((mousex)*PI / 180.0f))*keyboard->Key(DIK_D);
		posx -= 0.000005f*linearspeed*(cosf((mousex)*PI / 180.0f))*keyboard->Key(DIK_A);
		posz += 0.000005f*linearspeed*(sinf((mousex)*PI / 180.0f))*keyboard->Key(DIK_A);

		posy += 0.000005f*linearspeed*(float)keyboard->Key(DIK_E);
		posy -= 0.000005f*linearspeed*(float)keyboard->Key(DIK_Q);

		lookx = (posx + (sinf((mousex)*3.14f / 180.0f)));
		lookz = (posz + (cosf((mousex)*3.14f / 180.0f)));
		looky = (posy - ((mousey)*3.14f / 180.0f));
		SetEye(posx, posy, posz, lookx, looky, lookz, upx, upy, upz);
	}
	void __inline ChaseCam(Object *object)
	{
		mousex += mouse->Dx() / 10.0f;
		mousey += mouse->Dy() / 10.0f;
		mousez += mouse->Dz() / 10.0f;

		float4 up = float4(0, 1, 0, 1); up = up * object->rotation;
		float4 look = float4(0, 0, 0, 1); look = look * object->position;
		float4 position = float4(0, 75, -700 + mousez, 1);
		Matrix rotations(4, 4);
		rotations.Identity();
		rotations.RotateX(mousey);
		rotations.RotateY(-mousex);
		position = position * rotations;
		position = look + position * object->rotation;		

		lookx = look.x;
		looky = look.y;
		lookz = look.z;
		posx = position.x;
		posy = position.y;
		posz = position.z;
		upx = up.x;
		upy = up.y;
		upz = up.z;
		SetEye(posx, posy, posz, lookx, looky, lookz, upx, upy, upz);

 	//	float4 position = float4(0, 0, 0, 1);position = position * object->position;
		//float4 upvector = float4(0, 1, 0, 1); upvector = upvector * object->rotation;

		//mousex += mouse->Dx() / 100.0f;
		//mousey += mouse->Dy() / 100.0f;
		//mousez -= mouse->Dz() / 100.0f;
		//float distance = mousez + mousey;
		//posy = 50 + position.y + (distance)*sinf((mousey)*PI / 180.0f);
		//posx = position.x + (mousez*cosf((mousey)*PI / 180.0f))*sinf((mousex)*PI / 180.0f);
		//posz = position.z + (mousez*cosf((mousey)*PI / 180.0f))*cosf((mousex)*PI / 180.0f);
		//lookx = position.x;
		//looky = 50 + position.y;
		//lookz = position.z;
		//upx = 0;
		//upy = 1;
		//upz = 0;
		//SetEye(posx, posy, posz, lookx, looky, lookz, upx, upy, upz);
	}
	void __inline SetViewProjectionBuffer(UINT8 _slot, bool _VS, bool _HS, bool _DS, bool _GS, bool _PS, bool _CS)
	{
		float data[32];
		memcpy(&data[0], &view, sizeof(float) * 16);
		memcpy(&data[16], &projection, sizeof(float) * 16);
		graphics->ConstantBufferUpload(viewprojectionbuffer, data);
		if (_VS)graphics->ConstantBufferSet(viewprojectionbuffer, _slot, 1, 0, 0, 0, 0, 0);
		if (_HS)graphics->ConstantBufferSet(viewprojectionbuffer, _slot, 0, 1, 0, 0, 0, 0);
		if (_DS)graphics->ConstantBufferSet(viewprojectionbuffer, _slot, 0, 0, 1, 0, 0, 0);
		if (_GS)graphics->ConstantBufferSet(viewprojectionbuffer, _slot, 0, 0, 0, 1, 0, 0);
		if (_PS)graphics->ConstantBufferSet(viewprojectionbuffer, _slot, 0, 0, 0, 0, 1, 0);
		if (_CS)graphics->ConstantBufferSet(viewprojectionbuffer, _slot, 0, 0, 0, 0, 0, 1);
	}

	Camera()
	{
		ZeroMemory(this, sizeof(Camera));
		mousex = 0; mousey = 0; mousez = 250;
		posx = 0;	posy = 50;	posz = -100;
		lookx = 0;	looky = 0;	lookz = 0;
		upx;		upy = 1;	upz = 0;
	}
	~Camera()
	{
		if (viewprojectionbuffer)delete viewprojectionbuffer;
		ZeroMemory(this, sizeof(Camera));
	}
};