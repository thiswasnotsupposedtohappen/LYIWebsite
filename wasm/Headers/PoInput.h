typedef struct MOUSESTATE
{
	LONG lX;
	LONG lY;
	LONG lZ;
	BYTE rgbButtons[4];
}mousestate;
struct Mouse
{
	HWND hwnd;
	LPDIRECTINPUT8 device;
	LPDIRECTINPUTDEVICE8 mouse;
	MOUSESTATE mousestate;
	MOUSESTATE mouseupstate;
	MOUSESTATE mousedownstate;

	short Initialize(HWND _hwnd, HINSTANCE _hinstance)
	{
		HRESULT hr;
		hwnd = _hwnd;
		hr = DirectInput8Create(_hinstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&device, NULL);
		if (hr != S_OK) { print("Mouse: Failed to create device \n"); return 1; }
		hr = device->CreateDevice(GUID_SysMouse, &mouse, NULL);
		if (hr != S_OK) { print("Mouse: Failed to create device \n"); return 1; }
		mouse->SetDataFormat(&c_dfDIMouse);
		mouse->SetCooperativeLevel(hwnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
		print("Mouse: Initialized \n");
		return 0;
	}
	void Update()
	{
		MOUSESTATE previouskeystate;
		memcpy(&previouskeystate, &mousestate, sizeof(MOUSESTATE));
		mouse->Acquire();
		mouse->GetDeviceState(sizeof(MOUSESTATE), (LPVOID)&mousestate);

		if (mousestate.rgbButtons[0] && !previouskeystate.rgbButtons[0]) { mousedownstate.rgbButtons[0] = 1; mouseupstate.rgbButtons[0] = 0; }
		else if (!mousestate.rgbButtons[0] && previouskeystate.rgbButtons[0]) { mousedownstate.rgbButtons[0] = 0; mouseupstate.rgbButtons[0] = 1; }
		else { mousedownstate.rgbButtons[0] = 0; mouseupstate.rgbButtons[0] = 0; }

		if (mousestate.rgbButtons[1] && !previouskeystate.rgbButtons[1]) { mousedownstate.rgbButtons[1] = 1; mouseupstate.rgbButtons[1] = 0; }
		else if (!mousestate.rgbButtons[1] && previouskeystate.rgbButtons[1]) { mousedownstate.rgbButtons[1] = 0; mouseupstate.rgbButtons[1] = 1; }
		else { mousedownstate.rgbButtons[1] = 0; mouseupstate.rgbButtons[1] = 0; }

		if (mousestate.rgbButtons[2] && !previouskeystate.rgbButtons[2]) { mousedownstate.rgbButtons[2] = 1; mouseupstate.rgbButtons[2] = 0; }
		else if (!mousestate.rgbButtons[2] && previouskeystate.rgbButtons[2]) { mousedownstate.rgbButtons[2] = 0; mouseupstate.rgbButtons[2] = 1; }
		else { mousedownstate.rgbButtons[2] = 0; mouseupstate.rgbButtons[2] = 0; }

		if (mousestate.rgbButtons[3] && !previouskeystate.rgbButtons[3]) { mousedownstate.rgbButtons[3] = 1; mouseupstate.rgbButtons[3] = 0; }
		else if (!mousestate.rgbButtons[3] && previouskeystate.rgbButtons[3]) { mousedownstate.rgbButtons[3] = 0; mouseupstate.rgbButtons[3] = 1; }
		else { mousedownstate.rgbButtons[3] = 0; mouseupstate.rgbButtons[3] = 0; }
	}
	INT32 __forceinline Dx()
	{
		return mousestate.lX;
	}
	INT32 __forceinline Dy()
	{
		return mousestate.lY;
	}
	INT32 __forceinline Dz()
	{
		return mousestate.lZ;
	}
	INT32 __forceinline X()
	{
		POINT p;
		if (GetCursorPos(&p))
			if (ScreenToClient(hwnd, &p))
				return p.x;
		return 0;
	}
	INT32 __forceinline Y()
	{
		POINT p;
		if (GetCursorPos(&p))
			if (ScreenToClient(hwnd, &p))
				return p.y;
		return 0;
	}
	UINT8 __forceinline LeftMouseButton()
	{
		return mousestate.rgbButtons[0];
	}
	UINT8 __forceinline NextMouseButton()
	{
		return mousestate.rgbButtons[2];
	}
	UINT8 __forceinline BackMouseButton()
	{
		return mousestate.rgbButtons[3];
	}
	UINT8 __forceinline LeftMouseButtonDown()
	{
		return mousedownstate.rgbButtons[0];
	}
	UINT8 __forceinline RightMouseButtonDown()
	{
		return mousedownstate.rgbButtons[1];
	}
	UINT8 __forceinline NextMouseButtonDown()
	{
		return mousedownstate.rgbButtons[2];
	}
	UINT8 __forceinline BackMouseButtonDown()
	{
		return mousedownstate.rgbButtons[3];
	}
	UINT8 __forceinline LeftMouseButtonUp()
	{
		return mouseupstate.rgbButtons[0];
	}
	UINT8 __forceinline RightMouseButtonUp()
	{
		return mouseupstate.rgbButtons[1];
	}
	UINT8 __forceinline NextMouseButtonUp()
	{
		return mouseupstate.rgbButtons[2];
	}
	UINT8 __forceinline BackMouseButtonUp()
	{
		return mouseupstate.rgbButtons[3];
	}
	Mouse()
	{
		ZeroMemory(this, sizeof(Mouse));
	}
	~Mouse()
	{
		if (device)device->Release(); device = NULL;
		if (mouse)mouse->Release(); mouse = NULL;
		ZeroMemory(this, sizeof(Mouse));
	}
};
struct Keyboard
{
	HWND hwnd;
	LPDIRECTINPUT8 device;
	LPDIRECTINPUTDEVICE8 keyboard;
	UINT8 keystate[256];	
	UINT8 keyupstate[256];
	UINT8 keydownstate[256];

	
	UINT8  Initialize(HWND _hwnd, HINSTANCE hinstance)
	{
		HRESULT hr;
		hwnd = _hwnd;
		hr = DirectInput8Create(hinstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&device, NULL);
		if (hr != S_OK) { print("Keyboard: Failed to create device \n"); return 1; }
		hr = device->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
		if (hr != S_OK) { print("Keyboard: Failed to create device \n"); return 1; }
		keyboard->SetDataFormat(&c_dfDIKeyboard);
		keyboard->SetCooperativeLevel(hwnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
		print("Keyboard: Initialized \n");
		return 0;
	}
	void __forceinline Update()
	{
		UINT8 previouskeystate[256];
		memcpy(previouskeystate, keystate, sizeof(keystate));
		keyboard->Acquire();
		keyboard->GetDeviceState(256, (LPVOID)keystate);

		for (UINT16 i = 0; i < 256; i++)
		{
			if (keystate[i] && !previouskeystate[i]) { keydownstate[i] = 1; keyupstate[i] = 0; }
			else if (!keystate[i] && previouskeystate[i]) { keydownstate[i] = 0; keyupstate[i] = 1; }
			else { keydownstate[i] = 0; keyupstate[i] = 0; }
		}
	}
	UINT8 __forceinline  Key(WORD key)
	{
		if (keystate[key] & 0x80) return 1;
		return 0;
	}
	UINT8 __forceinline  KeyDown(WORD key)
	{		
		if (keydownstate[key])return 1;
		return 0;
	}
	UINT8 __forceinline  KeyUp(WORD key)
	{
		if (keyupstate[key])return 1;
		return 0;
	}
	void __forceinline AppendKeyCharacterToString(char *string,rsize_t stringlength)
	{
			if (KeyDown(DIK_0) || KeyDown(DIK_NUMPAD0))strcat_s(string, stringlength, "0"); else
			if (KeyDown(DIK_1) || KeyDown(DIK_NUMPAD1))strcat_s(string, stringlength, "1"); else
			if (KeyDown(DIK_2) || KeyDown(DIK_NUMPAD2))strcat_s(string, stringlength, "2"); else
			if (KeyDown(DIK_3) || KeyDown(DIK_NUMPAD3))strcat_s(string, stringlength, "3"); else
			if (KeyDown(DIK_4) || KeyDown(DIK_NUMPAD4))strcat_s(string, stringlength, "4"); else
			if (KeyDown(DIK_5) || KeyDown(DIK_NUMPAD5))strcat_s(string, stringlength, "5"); else
			if (KeyDown(DIK_6) || KeyDown(DIK_NUMPAD6))strcat_s(string, stringlength, "6"); else
			if (KeyDown(DIK_7) || KeyDown(DIK_NUMPAD7))strcat_s(string, stringlength, "7"); else
			if (KeyDown(DIK_8) || KeyDown(DIK_NUMPAD8))strcat_s(string, stringlength, "8"); else
			if (KeyDown(DIK_9) || KeyDown(DIK_NUMPAD9))strcat_s(string, stringlength, "9"); else

			if (KeyDown(DIK_A))strcat_s(string, stringlength, "a"); else
			if (KeyDown(DIK_B))strcat_s(string, stringlength, "b"); else
			if (KeyDown(DIK_C))strcat_s(string, stringlength, "c"); else
			if (KeyDown(DIK_D))strcat_s(string, stringlength, "d"); else
			if (KeyDown(DIK_E))strcat_s(string, stringlength, "e"); else
			if (KeyDown(DIK_F))strcat_s(string, stringlength, "f"); else
			if (KeyDown(DIK_G))strcat_s(string, stringlength, "g"); else
			if (KeyDown(DIK_H))strcat_s(string, stringlength, "h"); else
			if (KeyDown(DIK_I))strcat_s(string, stringlength, "i"); else
			if (KeyDown(DIK_J))strcat_s(string, stringlength, "j"); else
			if (KeyDown(DIK_K))strcat_s(string, stringlength, "k"); else
			if (KeyDown(DIK_L))strcat_s(string, stringlength, "l"); else
			if (KeyDown(DIK_M))strcat_s(string, stringlength, "m"); else
			if (KeyDown(DIK_N))strcat_s(string, stringlength, "n"); else
			if (KeyDown(DIK_O))strcat_s(string, stringlength, "o"); else
			if (KeyDown(DIK_P))strcat_s(string, stringlength, "p"); else
			if (KeyDown(DIK_Q))strcat_s(string, stringlength, "q"); else
			if (KeyDown(DIK_R))strcat_s(string, stringlength, "r"); else
			if (KeyDown(DIK_S))strcat_s(string, stringlength, "s"); else
			if (KeyDown(DIK_T))strcat_s(string, stringlength, "t"); else
			if (KeyDown(DIK_U))strcat_s(string, stringlength, "u"); else
			if (KeyDown(DIK_V))strcat_s(string, stringlength, "v"); else
			if (KeyDown(DIK_W))strcat_s(string, stringlength, "w"); else
			if (KeyDown(DIK_X))strcat_s(string, stringlength, "x"); else
			if (KeyDown(DIK_Y))strcat_s(string, stringlength, "y"); else
			if (KeyDown(DIK_Z))strcat_s(string, stringlength, "z"); else
			if (KeyDown(DIK_PERIOD))strcat_s(string, stringlength, "."); else
			if (KeyDown(DIK_DECIMAL))strcat_s(string, stringlength, "."); else
			if (KeyDown(DIK_MINUS))strcat_s(string, stringlength, "-"); else
			if (KeyDown(DIK_SUBTRACT))strcat_s(string, stringlength, "-"); else
			if (KeyDown(DIK_BACKSPACE)) 
			{
				if(string[0])
					for (UINT8 i = 0; i < BUFFERSIZE;i++)
						if (string[i] == 0)
						{
							string[i - 1] = 0;
							break;
						}
			}
			if (KeyDown(DIK_DELETE))
			{
				ZeroMemory(string, stringlength);
			}
	}
	Keyboard()
	{
		ZeroMemory(this, sizeof(Keyboard));
	}
	~Keyboard()
	{
		KillTimer(hwnd, (UINT_PTR)this);
		if (device)device->Release(); device = NULL;
		if (keyboard)keyboard->Release(); keyboard = NULL;
		ZeroMemory(this, sizeof(Keyboard));
	}
};
struct XboxController
{
	XINPUT_STATE xboxcontrollerstate;
	XINPUT_STATE xboxcontrollerstateprevious;
	XINPUT_VIBRATION vibration;

	short Initialize()
	{
		ZeroMemory(&xboxcontrollerstate, sizeof(XINPUT_STATE));
		ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
		return 0;
	}
	void __forceinline Update()
	{		
		xboxcontrollerstateprevious = xboxcontrollerstate;
		ZeroMemory(&xboxcontrollerstate, sizeof(XINPUT_STATE));
		XInputGetState(0, &xboxcontrollerstate);

		XInputSetState(0, &vibration);
	}
	bool DPadUpButton()
	{
		return (xboxcontrollerstate.Gamepad.wButtons & 0x0001);
	}
	bool DPadDownButton()
	{
		return (xboxcontrollerstate.Gamepad.wButtons & 0x0002);
	}
	bool DPadLeftButton()
	{
		return (xboxcontrollerstate.Gamepad.wButtons & 0x0004);
	}
	bool DPadRightButton()
	{
		return (xboxcontrollerstate.Gamepad.wButtons & 0x0008);
	}
	bool StartButton()
	{
		return (xboxcontrollerstate.Gamepad.wButtons & 0x0010);
	}
	bool BackButton()
	{
		return (xboxcontrollerstate.Gamepad.wButtons & 0x0020);
	}
	bool ThumbLeftButton()
	{
		return (xboxcontrollerstate.Gamepad.wButtons & 0x0040);
	}
	bool ThumbRightButton()
	{
		return (xboxcontrollerstate.Gamepad.wButtons & 0x0080);
	}
	bool ShoulderLeftButton()
	{
		return (xboxcontrollerstate.Gamepad.wButtons & 0x0100);
	}
	bool ShoulderRightButton()
	{
		return (xboxcontrollerstate.Gamepad.wButtons & 0x0200);
	}
	bool AButton()
	{
		return (xboxcontrollerstate.Gamepad.wButtons & 0x1000);
	}
	bool BButton()
	{
		return (xboxcontrollerstate.Gamepad.wButtons & 0x2000);
	}
	bool CButton()
	{
		return (xboxcontrollerstate.Gamepad.wButtons & 0x4000);
	}
	bool DButton()
	{
		return (xboxcontrollerstate.Gamepad.wButtons & 0x8000);
	}

	bool DPadUpButtonDown()
	{
		return (xboxcontrollerstate.Gamepad.wButtons & 0x0001) && !(xboxcontrollerstateprevious.Gamepad.wButtons & 0x0001);
	}
	bool DPadDownButtonDown()
	{
		return (xboxcontrollerstate.Gamepad.wButtons & 0x0002) && !(xboxcontrollerstateprevious.Gamepad.wButtons & 0x0002);
	}
	bool DPadLeftButtonDown()
	{
		return (xboxcontrollerstate.Gamepad.wButtons & 0x0004) && !(xboxcontrollerstateprevious.Gamepad.wButtons & 0x0004);
	}
	bool DPadRightButtonDown()
	{
		return (xboxcontrollerstate.Gamepad.wButtons & 0x0008) && !(xboxcontrollerstateprevious.Gamepad.wButtons & 0x0008);
	}
	bool StartButtonDown()
	{
		return (xboxcontrollerstate.Gamepad.wButtons & 0x0010) && !(xboxcontrollerstateprevious.Gamepad.wButtons & 0x0010);
	}
	bool BackButtonDown()
	{
		return (xboxcontrollerstate.Gamepad.wButtons & 0x0020) && !(xboxcontrollerstateprevious.Gamepad.wButtons & 0x0020);
	}
	bool ThumbLeftButtonDown()
	{
		return (xboxcontrollerstate.Gamepad.wButtons & 0x0040) && !(xboxcontrollerstateprevious.Gamepad.wButtons & 0x0040);
	}
	bool ThumbRightButtonDown()
	{
		return (xboxcontrollerstate.Gamepad.wButtons & 0x0080) && !(xboxcontrollerstateprevious.Gamepad.wButtons & 0x0080);
	}
	bool ShoulderLeftButtonDown()
	{
		return (xboxcontrollerstate.Gamepad.wButtons & 0x0100) && !(xboxcontrollerstateprevious.Gamepad.wButtons & 0x0100);
	}
	bool ShoulderRightButtonDown()
	{
		return (xboxcontrollerstate.Gamepad.wButtons & 0x0200) && !(xboxcontrollerstateprevious.Gamepad.wButtons & 0x0200);
	}
	bool AButtonDown()
	{
		return (xboxcontrollerstate.Gamepad.wButtons & 0x1000) && !(xboxcontrollerstateprevious.Gamepad.wButtons & 0x1000);
	}
	bool BButtonDown()
	{
		return (xboxcontrollerstate.Gamepad.wButtons & 0x2000) && !(xboxcontrollerstateprevious.Gamepad.wButtons & 0x2000);
	}
	bool CButtonDown()
	{
		return (xboxcontrollerstate.Gamepad.wButtons & 0x4000) && !(xboxcontrollerstateprevious.Gamepad.wButtons & 0x4000);
	}
	bool DButtonDown()
	{
		return (xboxcontrollerstate.Gamepad.wButtons & 0x8000) && !(xboxcontrollerstateprevious.Gamepad.wButtons & 0x8000);
	}

	bool DPadUpButtonUp()
	{
		return !(xboxcontrollerstate.Gamepad.wButtons & 0x0001) && (xboxcontrollerstateprevious.Gamepad.wButtons & 0x0001);
	}
	bool DPadDownButtonUp()
	{
		return !(xboxcontrollerstate.Gamepad.wButtons & 0x0002) && (xboxcontrollerstateprevious.Gamepad.wButtons & 0x0002);
	}
	bool DPadLeftButtonUp()
	{
		return !(xboxcontrollerstate.Gamepad.wButtons & 0x0004) && (xboxcontrollerstateprevious.Gamepad.wButtons & 0x0004);
	}
	bool DPadRightButtonUp()
	{
		return !(xboxcontrollerstate.Gamepad.wButtons & 0x0008) && (xboxcontrollerstateprevious.Gamepad.wButtons & 0x0008);
	}
	bool StartButtonUp()
	{
		return !(xboxcontrollerstate.Gamepad.wButtons & 0x0010) && (xboxcontrollerstateprevious.Gamepad.wButtons & 0x0010);
	}
	bool BackButtonUp()
	{
		return !(xboxcontrollerstate.Gamepad.wButtons & 0x0020) && (xboxcontrollerstateprevious.Gamepad.wButtons & 0x0020);
	}
	bool ThumbLeftButtonUp()
	{
		return !(xboxcontrollerstate.Gamepad.wButtons & 0x0040) && (xboxcontrollerstateprevious.Gamepad.wButtons & 0x0040);
	}
	bool ThumbRightButtonUp()
	{
		return !(xboxcontrollerstate.Gamepad.wButtons & 0x0080) && (xboxcontrollerstateprevious.Gamepad.wButtons & 0x0080);
	}
	bool ShoulderLeftButtonUp()
	{
		return !(xboxcontrollerstate.Gamepad.wButtons & 0x0100) && (xboxcontrollerstateprevious.Gamepad.wButtons & 0x0100);
	}
	bool ShoulderRightButtonUp()
	{
		return !(xboxcontrollerstate.Gamepad.wButtons & 0x0200) && (xboxcontrollerstateprevious.Gamepad.wButtons & 0x0200);
	}
	bool AButtonUp()
	{
		return (!(xboxcontrollerstate.Gamepad.wButtons & 0x1000)) && (xboxcontrollerstateprevious.Gamepad.wButtons & 0x1000);
	}
	bool BButtonUp()
	{
		return (!(xboxcontrollerstate.Gamepad.wButtons & 0x2000)) && (xboxcontrollerstateprevious.Gamepad.wButtons & 0x2000);
	}
	bool CButtonUp()
	{
		return (!(xboxcontrollerstate.Gamepad.wButtons & 0x4000)) && (xboxcontrollerstateprevious.Gamepad.wButtons & 0x4000);
	}
	bool DButtonUp()
	{
		return (!(xboxcontrollerstate.Gamepad.wButtons & 0x8000)) && (xboxcontrollerstateprevious.Gamepad.wButtons & 0x8000);
	}

	int32 TriggerLeft()
	{
		return xboxcontrollerstate.Gamepad.bLeftTrigger;
	}
	int32 TriggerRight()
	{
		return xboxcontrollerstate.Gamepad.bRightTrigger;
	}
	int32 StickLeftX()
	{
		return xboxcontrollerstate.Gamepad.sThumbLX;
	}
	int32 StickLeftY()
	{
		return xboxcontrollerstate.Gamepad.sThumbLY;
	}
	int32 StickRightX()
	{
		return xboxcontrollerstate.Gamepad.sThumbRX;
	}
	int32 StickRightY()
	{
		return xboxcontrollerstate.Gamepad.sThumbRY;
	}

	void VibrateLeft(uint16 intensity)
	{		
		vibration.wLeftMotorSpeed = intensity;
	}
	void VibrateRight(uint16 intensity)
	{
		vibration.wRightMotorSpeed = intensity;
	}
};