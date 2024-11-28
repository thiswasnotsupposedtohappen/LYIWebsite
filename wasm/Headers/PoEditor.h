struct Editor
{	
	Mouse *mouse;
	Keyboard *keyboard;
	Physics *physics;
	Graphics *graphics;
	Graphics::VertexShader	 *vertexshader;
	Graphics::PixelShader	 *pixelshaderdiffuseonly;
	GUIButton *buttonobject;
		GUIButton *buttonobjectnew;
			GUILabel  *labelobjectnewobjectname;
			GUIText   *textobjectnewobjectname;
			GUILabel  *labelobjectnewfilename;
			GUIText   *textobjectnewfilename;
			GUILabel  *labelobjectnewanimationlength;
			GUIText   *textobjectnewanimationlength;
			GUILabel  *labelobjectnewmass;
			GUIText   *textobjectnewmass;
			GUILabel  *labelobjectnewmomentofinertia;
			GUIText   *textobjectnewmomentofinertia;
			GUILabel  *labelobjectnewrestitution;
			GUIText   *textobjectnewrestitution;
			GUILabel  *labelobjectnewfriction;
			GUIText   *textobjectnewfriction;
			GUILabel  *labelobjectnewdrag;
			GUIText   *textobjectnewdrag;
			GUIButton *buttonobjectnewload;
		GUIButton *buttonobjectload;
			GUILabel  *labelobjectloadobjectname;
			GUIText   *textobjectloadobjectname;
			GUIButton *buttonobjectloadload;
		GUIButton *buttonobjectsave;
			GUILabel  *labelobjectsaveobjectname;
			GUIText   *textobjectsaveobjectname;
			GUIButton *buttonobjectsavesave;
		GUIButton *buttonobjectedit;
			GUILabel  *labelobjecteditobjectname;
			GUIText   *textobjecteditobjectname;
			GUIButton *buttonobjecteditget;
			GUILabel  *labelobjecteditmass;
			GUIText   *textobjecteditmass;
			GUILabel  *labelobjecteditmomentofinertia;
			GUIText   *textobjecteditmomentofinertia;
			GUILabel  *labelobjecteditrestitution;
			GUIText   *textobjecteditrestitution;
			GUILabel  *labelobjecteditfriction;
			GUIText   *textobjecteditfriction;
			GUILabel  *labelobjecteditdrag;
			GUIText   *textobjecteditdrag;
			GUILabel  *labelobjecteditcentreofmass;
			GUIText   *textobjecteditcentreofmassx;
			GUIText   *textobjecteditcentreofmassy;
			GUIText   *textobjecteditcentreofmassz;
			GUILabel  *labelobjecteditposition;
			GUIText   *textobjecteditpositionx;
			GUIText   *textobjecteditpositiony;
			GUIText   *textobjecteditpositionz;
			GUILabel  *labelobjecteditrotation;
			GUIText   *textobjecteditrotationx;
			GUIText   *textobjecteditrotationy;
			GUIText   *textobjecteditrotationz;
			GUILabel  *labelobjecteditvelocity;
			GUIText   *textobjecteditvelocityx;
			GUIText   *textobjecteditvelocityy;
			GUIText   *textobjecteditvelocityz;
			GUILabel  *labelobjecteditangularvelocity;
			GUIText   *textobjecteditangilarvelocityx;
			GUIText   *textobjecteditangilarvelocityy;
			GUIText   *textobjecteditangilarvelocityz;
			GUILabel  *labelobjecteditcollisionsphere;
			GUIText   *textobjecteditcollisionspherex;
			GUIText   *textobjecteditcollisionspherey;
			GUIText   *textobjecteditcollisionspherez;
			GUIText   *textobjecteditcollisionspherer;
			GUIButton *buttonobjecteditcollisionspherenext;
			GUIButton *buttonobjecteditcollisionsphereprevious;
			GUIButton *buttonobjecteditcollisionsphereadd;
			GUIButton *buttonobjecteditcollisionsphereremove;
			GUIButton *buttonobjecteditupdate;
		GUIButton *buttonobjectremove;
	GUIButton *buttonscene;
		GUIButton *buttonsceneload;
			GUILabel  *labelsceneloadscenename;
			GUIText   *textsceneloadscenename;
			GUIButton *buttonsceneloadload;
		GUIButton *buttonscenesave;
			GUILabel  *labelscenesavescenename;
			GUIText   *textscenesavescenename;
			GUIButton *buttonscenesavesave;

	UINT32 *objectcount;
	Object **object;	
	INT32 currentcollisionsphereindex;
	Object *collisionsphereunselected;
	Object *collisionsphereselected;
	Scene *scene;

	#define	HOME			0x0000
	#define	OBJECT			0x0001
	#define	SCENE			0x0100	
	#define	OBJECTNEW		0x0002
	#define	OBJECTLOAD		0x0004	
	#define	OBJECTSAVE		0x0008
	#define	OBJECTREMOVE	0x0010
	#define	OBJECTEDIT		0x0020
	#define	SCENELOAD		0x0200
	#define	SCENESAVE		0x0400
	UINT16 tab;

	UINT8 Initialize(Graphics *_graphics, Physics *_physics, Mouse *_mouse, Keyboard *_keyboard, UINT32 *_objectcount, Object **_object, Scene *_scene)
	{
		graphics = _graphics;
		physics = _physics;
		mouse = _mouse;
		keyboard = _keyboard;
		objectcount = _objectcount;
		object = _object;
		scene = _scene;
		if (graphics->VertexShaderCreate(&vertexshader, "vertexshader.hlsl"))return 1;
		if (graphics->PixelShaderCreate(&pixelshaderdiffuseonly, "pixelshaderdiffuseonly.hlsl"))return 1;
		if (collisionsphereunselected->Load(graphics, "collisionsphereunselected"))return 1;
		if (collisionsphereselected->Load(graphics, "collisionsphereselected"))return 1;

		#define editorunpressedcolor  float4(200.0f / 255.0f, 200.0f / 255.0f, 200.0f / 255.0f, 1.0f)
		#define editorhoveredcolor  float4(220.0f / 255.0f, 220.0f / 255.0f, 220.0f / 255.0f, 1.0f)
		#define editorpressedcolor  float4(255.0f / 255.0f, 152.0f / 255.0f, 0.0f / 255.0f, 1.0f)
		#define editorunselectedcolor  float4(250.0f / 255.0f, 250.0f / 255.0f, 250.0f / 255.0f, 1.0f)
		#define editorselectedcolor  float4(220.0f / 255.0f, 230.0f / 255.0f, 240.0f / 255.0f, 1.0f)
		#define editorlabelcolor float4(100.0f / 255.0f, 100.0f / 255.0f, 100.0f / 255.0f, 1.0f)
		if (buttonobject->		Initialize(graphics, mouse, keyboard, "  Object", editorunpressedcolor, editorhoveredcolor, editorpressedcolor, 0x000000))return 1;
			if (buttonobjectnew->	Initialize(graphics, mouse, keyboard, "   New  ", editorunpressedcolor, editorhoveredcolor, editorpressedcolor, 0x000000))return 1;
				if (labelobjectnewobjectname->		Initialize(graphics, editorlabelcolor ," Object Name:", 0x000000))return 1;
				if (textobjectnewobjectname->		Initialize(graphics, mouse, keyboard, editorunselectedcolor, editorselectedcolor, editorselectedcolor, 0x000000))return 1;
				if (labelobjectnewfilename->		Initialize(graphics, editorlabelcolor, "   File Name:", 0x000000))return 1;
				if (textobjectnewfilename->			Initialize(graphics, mouse, keyboard, editorunselectedcolor, editorselectedcolor, editorselectedcolor, 0x000000))return 1;
				if (labelobjectnewanimationlength->	Initialize(graphics, editorlabelcolor, "   Animation:", 0x000000))return 1;
				if (textobjectnewanimationlength->	Initialize(graphics, mouse, keyboard, editorunselectedcolor, editorselectedcolor, editorselectedcolor, 0x000000))return 1;
				if (labelobjectnewmass->			Initialize(graphics, editorlabelcolor, "        Mass:", 0x000000))return 1;
				if (textobjectnewmass->				Initialize(graphics, mouse, keyboard, editorunselectedcolor, editorselectedcolor, editorselectedcolor, 0x000000))return 1;
				if (labelobjectnewmomentofinertia->	Initialize(graphics, editorlabelcolor, "         MOI:", 0x000000))return 1;
				if (textobjectnewmomentofinertia->	Initialize(graphics, mouse, keyboard, editorunselectedcolor, editorselectedcolor, editorselectedcolor, 0x000000))return 1;
				if (labelobjectnewrestitution->		Initialize(graphics, editorlabelcolor, "  Restituion:", 0x000000))return 1;
				if (textobjectnewrestitution->		Initialize(graphics, mouse, keyboard, editorunselectedcolor, editorselectedcolor, editorselectedcolor, 0x000000))return 1;
				if (labelobjectnewfriction->		Initialize(graphics, editorlabelcolor, "    Friction:", 0x000000))return 1;
				if (textobjectnewfriction->			Initialize(graphics, mouse, keyboard, editorunselectedcolor, editorselectedcolor, editorselectedcolor, 0x000000))return 1;
				if (labelobjectnewdrag->			Initialize(graphics, editorlabelcolor, "        Drag:", 0x000000))return 1;
				if (textobjectnewdrag->				Initialize(graphics, mouse, keyboard, editorunselectedcolor, editorselectedcolor, editorselectedcolor, 0x000000))return 1;
				if (buttonobjectnewload->			Initialize(graphics, mouse, keyboard, "   Load ", editorunpressedcolor, editorhoveredcolor, editorpressedcolor, 0x000000))return 1;
			if (buttonobjectload->	Initialize(graphics, mouse, keyboard, "   Load ", editorunpressedcolor, editorhoveredcolor, editorpressedcolor, 0x000000))return 1;
				if (labelobjectloadobjectname->		Initialize(graphics, editorlabelcolor ," Object Name:", 0x000000))return 1;
				if (textobjectloadobjectname->		Initialize(graphics, mouse, keyboard, editorunselectedcolor, editorselectedcolor, editorselectedcolor, 0x000000))return 1;
				if (buttonobjectloadload->			Initialize(graphics, mouse, keyboard, "   Load ", editorunpressedcolor, editorhoveredcolor, editorpressedcolor, 0x000000))return 1;
			if (buttonobjectsave->	Initialize(graphics, mouse, keyboard, "   Save ", editorunpressedcolor, editorhoveredcolor, editorpressedcolor, 0x000000))return 1;
				if (labelobjectsaveobjectname->		Initialize(graphics, editorlabelcolor ," Object Name:", 0x000000))return 1;
				if (textobjectsaveobjectname->		Initialize(graphics, mouse, keyboard, editorunselectedcolor, editorselectedcolor, editorselectedcolor, 0x000000))return 1;
				if (buttonobjectsavesave->			Initialize(graphics, mouse, keyboard, "   Save ", editorunpressedcolor, editorhoveredcolor, editorpressedcolor, 0x000000))return 1;
			if (buttonobjectedit->				Initialize(graphics, mouse, keyboard, "   Edit ", editorunpressedcolor, editorhoveredcolor, editorpressedcolor, 0x000000))return 1;
				if (labelobjecteditobjectname->		Initialize(graphics, editorlabelcolor ," Object Name:", 0x000000))return 1;
				if (textobjecteditobjectname->		Initialize(graphics, mouse, keyboard, editorunselectedcolor, editorselectedcolor, editorselectedcolor, 0x000000))return 1;
				if (buttonobjecteditget->			Initialize(graphics, mouse, keyboard, "   Get  ", editorunpressedcolor, editorhoveredcolor, editorpressedcolor, 0x000000))return 1;
				if (labelobjecteditmass->			Initialize(graphics, editorlabelcolor, "        Mass:", 0x000000))return 1;
				if (textobjecteditmass->			Initialize(graphics, mouse, keyboard, editorunselectedcolor, editorselectedcolor, editorselectedcolor, 0x000000))return 1;
				if (labelobjecteditmomentofinertia->Initialize(graphics, editorlabelcolor, "         MOI:", 0x000000))return 1;
				if (textobjecteditmomentofinertia->	Initialize(graphics, mouse, keyboard, editorunselectedcolor, editorselectedcolor, editorselectedcolor, 0x000000))return 1;
				if (labelobjecteditrestitution->	Initialize(graphics, editorlabelcolor, "  Restituion:", 0x000000))return 1;
				if (textobjecteditrestitution->		Initialize(graphics, mouse, keyboard, editorunselectedcolor, editorselectedcolor, editorselectedcolor, 0x000000))return 1;
				if (labelobjecteditfriction->		Initialize(graphics, editorlabelcolor, "    Friction:", 0x000000))return 1;
				if (textobjecteditfriction->		Initialize(graphics, mouse, keyboard, editorunselectedcolor, editorselectedcolor, editorselectedcolor, 0x000000))return 1;
				if (labelobjecteditdrag->			Initialize(graphics, editorlabelcolor, "        Drag:", 0x000000))return 1;
				if (textobjecteditdrag->			Initialize(graphics, mouse, keyboard, editorunselectedcolor, editorselectedcolor, editorselectedcolor, 0x000000))return 1;
				if (labelobjecteditcentreofmass->	Initialize(graphics, editorlabelcolor, "         COM:", 0x000000))return 1;
				if (textobjecteditcentreofmassx->	Initialize(graphics, mouse, keyboard, editorunselectedcolor, editorselectedcolor, editorselectedcolor, 0x000000))return 1;
				if (textobjecteditcentreofmassy->	Initialize(graphics, mouse, keyboard, editorunselectedcolor, editorselectedcolor, editorselectedcolor, 0x000000))return 1;
				if (textobjecteditcentreofmassz->	Initialize(graphics, mouse, keyboard, editorunselectedcolor, editorselectedcolor, editorselectedcolor, 0x000000))return 1;
				if (labelobjecteditposition->		Initialize(graphics, editorlabelcolor, "    Position:", 0x000000))return 1;
				if (textobjecteditpositionx->		Initialize(graphics, mouse, keyboard, editorunselectedcolor, editorselectedcolor, editorselectedcolor, 0x000000))return 1;
				if (textobjecteditpositiony->		Initialize(graphics, mouse, keyboard, editorunselectedcolor, editorselectedcolor, editorselectedcolor, 0x000000))return 1;
				if (textobjecteditpositionz->		Initialize(graphics, mouse, keyboard, editorunselectedcolor, editorselectedcolor, editorselectedcolor, 0x000000))return 1;
				if (labelobjecteditrotation->		Initialize(graphics, editorlabelcolor, "    Rotation:", 0x000000))return 1;
				if (textobjecteditrotationx->		Initialize(graphics, mouse, keyboard, editorunselectedcolor, editorselectedcolor, editorselectedcolor, 0x000000))return 1;
				if (textobjecteditrotationy->		Initialize(graphics, mouse, keyboard, editorunselectedcolor, editorselectedcolor, editorselectedcolor, 0x000000))return 1;
				if (textobjecteditrotationz->		Initialize(graphics, mouse, keyboard, editorunselectedcolor, editorselectedcolor, editorselectedcolor, 0x000000))return 1;
				if (labelobjecteditvelocity->		Initialize(graphics, editorlabelcolor, "    Velocity:", 0x000000))return 1;
				if (textobjecteditvelocityx->		Initialize(graphics, mouse, keyboard, editorunselectedcolor, editorselectedcolor, editorselectedcolor, 0x000000))return 1;
				if (textobjecteditvelocityy->		Initialize(graphics, mouse, keyboard, editorunselectedcolor, editorselectedcolor, editorselectedcolor, 0x000000))return 1;
				if (textobjecteditvelocityz->		Initialize(graphics, mouse, keyboard, editorunselectedcolor, editorselectedcolor, editorselectedcolor, 0x000000))return 1;
				if (labelobjecteditangularvelocity->Initialize(graphics, editorlabelcolor, "Ang.Velocity:", 0x000000))return 1;
				if (textobjecteditangilarvelocityx->Initialize(graphics, mouse, keyboard, editorunselectedcolor, editorselectedcolor, editorselectedcolor, 0x000000))return 1;
				if (textobjecteditangilarvelocityy->Initialize(graphics, mouse, keyboard, editorunselectedcolor, editorselectedcolor, editorselectedcolor, 0x000000))return 1;
				if (textobjecteditangilarvelocityz->Initialize(graphics, mouse, keyboard, editorunselectedcolor, editorselectedcolor, editorselectedcolor, 0x000000))return 1;
				if (labelobjecteditcollisionsphere->Initialize(graphics, editorlabelcolor, "Coll. Sphere:", 0x000000))return 1;
				if (textobjecteditcollisionspherex->Initialize(graphics, mouse, keyboard, editorunselectedcolor, editorselectedcolor, editorselectedcolor, 0x000000))return 1;
				if (textobjecteditcollisionspherey->Initialize(graphics, mouse, keyboard, editorunselectedcolor, editorselectedcolor, editorselectedcolor, 0x000000))return 1;
				if (textobjecteditcollisionspherez->Initialize(graphics, mouse, keyboard, editorunselectedcolor, editorselectedcolor, editorselectedcolor, 0x000000))return 1;
				if (textobjecteditcollisionspherer->Initialize(graphics, mouse, keyboard, editorunselectedcolor, editorselectedcolor, editorselectedcolor, 0x000000))return 1;
				if (buttonobjecteditcollisionspherenext->		Initialize(graphics, mouse, keyboard, " >", editorunpressedcolor, editorhoveredcolor, editorpressedcolor, 0x000000))return 1;
				if (buttonobjecteditcollisionsphereprevious->	Initialize(graphics, mouse, keyboard, " <", editorunpressedcolor, editorhoveredcolor, editorpressedcolor, 0x000000))return 1;
				if (buttonobjecteditcollisionsphereadd->		Initialize(graphics, mouse, keyboard, " +", editorunpressedcolor, editorhoveredcolor, editorpressedcolor, 0x000000))return 1;
				if (buttonobjecteditcollisionsphereremove->		Initialize(graphics, mouse, keyboard, " -", editorunpressedcolor, editorhoveredcolor, editorpressedcolor, 0x000000))return 1;
				if (buttonobjecteditupdate->		Initialize(graphics, mouse, keyboard, "  Update", editorunpressedcolor, editorhoveredcolor, editorpressedcolor, 0x000000))return 1;
			if (buttonobjectremove->Initialize(graphics, mouse, keyboard, "  Remove", editorunpressedcolor, editorhoveredcolor, editorpressedcolor, 0x000000))return 1;
		if (buttonscene->		Initialize(graphics, mouse, keyboard, "  Scene ", editorunpressedcolor, editorhoveredcolor, editorpressedcolor, 0x000000))return 1;
			if (buttonsceneload->	Initialize(graphics, mouse, keyboard, "   Load ", editorunpressedcolor, editorhoveredcolor, editorpressedcolor, 0x000000))return 1;
				if (labelsceneloadscenename->		Initialize(graphics, editorlabelcolor ,"  Scene Name:", 0x000000))return 1;
				if (textsceneloadscenename->		Initialize(graphics, mouse, keyboard, editorunselectedcolor, editorselectedcolor, editorselectedcolor, 0x000000))return 1;
				if (buttonsceneloadload->			Initialize(graphics, mouse, keyboard, "   Load ", editorunpressedcolor, editorhoveredcolor, editorpressedcolor, 0x000000))return 1;
			if (buttonscenesave->	Initialize(graphics, mouse, keyboard, "   Save ", editorunpressedcolor, editorhoveredcolor, editorpressedcolor, 0x000000))return 1;
				if (labelscenesavescenename->		Initialize(graphics, editorlabelcolor ,"  Scene Name:", 0x000000))return 1;
				if (textscenesavescenename->		Initialize(graphics, mouse, keyboard, editorunselectedcolor, editorselectedcolor, editorselectedcolor, 0x000000))return 1;
				if (buttonscenesavesave->			Initialize(graphics, mouse, keyboard, "   Save ", editorunpressedcolor, editorhoveredcolor, editorpressedcolor, 0x000000))return 1;
		return 0;	
	}
	void Update()
	{
		if (buttonobject->Update(10, 10, 100, 25))tab = OBJECT;
		if (buttonscene->UpdateAlignTrailing(buttonobject, 10, 0, 100, 25))tab = SCENE;
		if (tab & OBJECT)
		{
			if (buttonobjectnew->UpdateAlignFollowing(buttonobject, 0, 10, 100, 25))tab = OBJECT | OBJECTNEW;
			if (tab & OBJECTNEW)
			{
				labelobjectnewobjectname->UpdateAlignFollowing(buttonobjectnew, -2, 8, 344, 29);
				textobjectnewobjectname->UpdateAlign(labelobjectnewobjectname, 132, 2, 210, 25);
				labelobjectnewfilename->UpdateAlignFollowing(labelobjectnewobjectname, 0, 6, 344, 29);
				textobjectnewfilename->UpdateAlign(labelobjectnewfilename, 132, 2, 210, 25);
				labelobjectnewanimationlength->UpdateAlignFollowing(labelobjectnewfilename, 0, 6, 344, 29);
				textobjectnewanimationlength->UpdateAlign(labelobjectnewanimationlength, 132, 2, 210, 25);
				labelobjectnewmass->UpdateAlignFollowing(labelobjectnewanimationlength, 0, 6, 344, 29);
				textobjectnewmass->UpdateAlign(labelobjectnewmass, 132, 2, 210, 25);
				labelobjectnewmomentofinertia->UpdateAlignFollowing(labelobjectnewmass, 0, 6, 344, 29);
				textobjectnewmomentofinertia->UpdateAlign(labelobjectnewmomentofinertia, 132, 2, 210, 25);
				labelobjectnewrestitution->UpdateAlignFollowing(labelobjectnewmomentofinertia, 0, 6, 344, 29);
				textobjectnewrestitution->UpdateAlign(labelobjectnewrestitution, 132, 2, 210, 25);
				labelobjectnewfriction->UpdateAlignFollowing(labelobjectnewrestitution, 0, 6, 344, 29);
				textobjectnewfriction->UpdateAlign(labelobjectnewfriction, 132, 2, 210, 25);
				labelobjectnewdrag->UpdateAlignFollowing(labelobjectnewfriction, 0, 6, 344, 29);
				textobjectnewdrag->UpdateAlign(labelobjectnewdrag, 132, 2, 210, 25);
				if (buttonobjectnewload->UpdateAlignFollowing(textobjectnewdrag, -132, 10, 100, 25))ObjectNew(textobjectnewobjectname->string);
			}
			if (buttonobjectload->UpdateAlignTrailing(buttonobjectnew, 10, 0, 100, 25))tab = OBJECT | OBJECTLOAD;
			if (tab & OBJECTLOAD)
			{
				labelobjectloadobjectname->UpdateAlignFollowing(buttonobjectnew, -2, 8, 344, 29);
				textobjectloadobjectname->UpdateAlign(labelobjectloadobjectname, 132, 2, 210, 25);
				if (buttonobjectloadload->UpdateAlignFollowing(textobjectloadobjectname, -132, 10, 100, 25))ObjectLoad(textobjectloadobjectname->string);
			}
			if (buttonobjectsave->UpdateAlignTrailing(buttonobjectload, 10, 0, 100, 25))tab = OBJECT | OBJECTSAVE;
			if (tab & OBJECTSAVE)
			{
				labelobjectsaveobjectname->UpdateAlignFollowing(buttonobjectnew, -2, 8, 344, 29);
				textobjectsaveobjectname->UpdateAlign(labelobjectsaveobjectname, 132, 2, 210, 25);
				if (buttonobjectsavesave->UpdateAlignFollowing(textobjectsaveobjectname, -132, 10, 100, 25))ObjectSave(textobjectsaveobjectname->string);
			}
			if (buttonobjectedit->UpdateAlignTrailing(buttonobjectsave, 10, 0, 100, 25))tab = OBJECT | OBJECTEDIT;
			if (tab & OBJECTEDIT)
			{
				labelobjecteditobjectname->UpdateAlignFollowing(buttonobjectnew, -2, 8, 344, 29);
				textobjecteditobjectname->UpdateAlign(labelobjecteditobjectname, 132, 2, 210, 25);
				if (buttonobjecteditget->UpdateAlignFollowing(textobjecteditobjectname, -132, 10, 100, 25))ObjectGet(textobjecteditobjectname->string);
				labelobjecteditmass->UpdateAlignFollowing(buttonobjecteditget, -2, 8, 344, 29);
				textobjecteditmass->UpdateAlign(labelobjecteditmass, 132, 2, 210, 25);
				labelobjecteditmomentofinertia->UpdateAlignFollowing(labelobjecteditmass, 0, 6, 344, 29);
				textobjecteditmomentofinertia->UpdateAlign(labelobjecteditmomentofinertia, 132, 2, 210, 25);
				labelobjecteditrestitution->UpdateAlignFollowing(labelobjecteditmomentofinertia, 0, 6, 344, 29);
				textobjecteditrestitution->UpdateAlign(labelobjecteditrestitution, 132, 2, 210, 25);
				labelobjecteditfriction->UpdateAlignFollowing(labelobjecteditrestitution, 0, 6, 344, 29);
				textobjecteditfriction->UpdateAlign(labelobjecteditfriction, 132, 2, 210, 25);
				labelobjecteditdrag->UpdateAlignFollowing(labelobjecteditfriction, 0, 6, 344, 29);
				textobjecteditdrag->UpdateAlign(labelobjecteditdrag, 132, 2, 210, 25);
				labelobjecteditcentreofmass->UpdateAlignFollowing(labelobjecteditdrag, 0, 6, 454, 29);
				textobjecteditcentreofmassx->UpdateAlign(labelobjecteditcentreofmass, 132, 2, 100, 25);
				textobjecteditcentreofmassy->UpdateAlignTrailing(textobjecteditcentreofmassx, 10, 0, 100, 25);
				textobjecteditcentreofmassz->UpdateAlignTrailing(textobjecteditcentreofmassy, 10, 0, 100, 25);
				labelobjecteditposition->UpdateAlignFollowing(labelobjecteditcentreofmass, 0, 6, 454, 29);
				textobjecteditpositionx->UpdateAlign(labelobjecteditposition, 132, 2, 100, 25);
				textobjecteditpositiony->UpdateAlignTrailing(textobjecteditpositionx, 10, 0, 100, 25);
				textobjecteditpositionz->UpdateAlignTrailing(textobjecteditpositiony, 10, 0, 100, 25);
				labelobjecteditrotation->UpdateAlignFollowing(labelobjecteditposition, 0, 6, 454, 29);
				textobjecteditrotationx->UpdateAlign(labelobjecteditrotation, 132, 2, 100, 25);
				textobjecteditrotationy->UpdateAlignTrailing(textobjecteditrotationx, 10, 0, 100, 25);
				textobjecteditrotationz->UpdateAlignTrailing(textobjecteditrotationy, 10, 0, 100, 25);
				labelobjecteditvelocity->UpdateAlignFollowing(labelobjecteditrotation, 0, 6, 454, 29);
				textobjecteditvelocityx->UpdateAlign(labelobjecteditvelocity, 132, 2, 100, 25);
				textobjecteditvelocityy->UpdateAlignTrailing(textobjecteditvelocityx, 10, 0, 100, 25);
				textobjecteditvelocityz->UpdateAlignTrailing(textobjecteditvelocityy, 10, 0, 100, 25);
				labelobjecteditangularvelocity->UpdateAlignFollowing(labelobjecteditvelocity, 0, 6, 454, 29);
				textobjecteditangilarvelocityx->UpdateAlign(labelobjecteditangularvelocity, 132, 2, 100, 25);
				textobjecteditangilarvelocityy->UpdateAlignTrailing(textobjecteditangilarvelocityx, 10, 0, 100, 25);
				textobjecteditangilarvelocityz->UpdateAlignTrailing(textobjecteditangilarvelocityy, 10, 0, 100, 25);
				labelobjecteditcollisionsphere->UpdateAlignFollowing(labelobjecteditangularvelocity, 0, 6, 564, 29);
				textobjecteditcollisionspherex->UpdateAlign(labelobjecteditcollisionsphere, 132, 2, 100, 25);
				textobjecteditcollisionspherey->UpdateAlignTrailing(textobjecteditcollisionspherex, 10, 0, 100, 25);
				textobjecteditcollisionspherez->UpdateAlignTrailing(textobjecteditcollisionspherey, 10, 0, 100, 25);
				textobjecteditcollisionspherer->UpdateAlignTrailing(textobjecteditcollisionspherez, 10, 0, 100, 25);
				if (buttonobjecteditcollisionsphereprevious->UpdateAlignTrailing(textobjecteditcollisionspherer, 10, 0, 30, 25))ObjectNextCollisionSphere(textobjecteditobjectname->string);
				if (buttonobjecteditcollisionspherenext->UpdateAlignTrailing(buttonobjecteditcollisionsphereprevious, 10, 0, 30, 25))ObjectPreviousCollisionSphere(textobjecteditobjectname->string);
				if (buttonobjecteditcollisionsphereadd->UpdateAlignTrailing(buttonobjecteditcollisionspherenext, 10, 0, 30, 25))ObjectAddCollisionSphere(textobjecteditobjectname->string);
				if (buttonobjecteditcollisionsphereremove->UpdateAlignTrailing(buttonobjecteditcollisionsphereadd, 10, 0, 30, 25))ObjectRemoveCollisionSphere(textobjecteditobjectname->string);
				if (buttonobjecteditupdate->UpdateAlignFollowing(textobjecteditcollisionspherex, -132, 10, 100, 25))ObjectUpdate(textobjecteditobjectname->string);
			}
			if (buttonobjectremove->UpdateAlignTrailing(buttonobjectedit, 10, 0, 100, 25))tab = OBJECT | OBJECTREMOVE;
		}
		if (tab & SCENE)
		{
			if (buttonsceneload->UpdateAlignFollowing(buttonobject, 0, 10, 100, 25))tab = SCENE|SCENELOAD;
			if (tab & SCENELOAD)
			{
				labelsceneloadscenename->UpdateAlignFollowing(buttonobjectnew, -2, 8, 344, 29);
				textsceneloadscenename->UpdateAlign(labelsceneloadscenename, 132, 2, 210, 25);
				if (buttonsceneloadload->UpdateAlignFollowing(textsceneloadscenename, -132, 10, 100, 25))SceneLoad(textsceneloadscenename->string);
			}
			if (buttonscenesave->UpdateAlignTrailing(buttonsceneload, 10, 0, 100, 25))tab = SCENE|SCENESAVE;
			if (tab & SCENESAVE)
			{
				labelscenesavescenename->UpdateAlignFollowing(buttonobjectnew, -2, 8, 344, 29);
				textscenesavescenename->UpdateAlign(labelscenesavescenename, 132, 2, 210, 25);
				if (buttonscenesavesave->UpdateAlignFollowing(textscenesavescenename, -132, 10, 100, 25))SceneSave(textscenesavescenename->string);
			}
		}
	}
	void Render()
	{
		buttonobject->Render();
		buttonscene->Render();
		if (tab & OBJECT)
		{
			buttonobjectnew->Render();
			if (tab & OBJECTNEW)
			{
				labelobjectnewobjectname->Render();
				textobjectnewobjectname->Render();
				labelobjectnewfilename->Render();
				textobjectnewfilename->Render();
				labelobjectnewanimationlength->Render();
				textobjectnewanimationlength->Render();
				labelobjectnewmass->Render();
				textobjectnewmass->Render();
				labelobjectnewmomentofinertia->Render();
				textobjectnewmomentofinertia->Render();
				labelobjectnewrestitution->Render();
				textobjectnewrestitution->Render();
				labelobjectnewfriction->Render();
				textobjectnewfriction->Render();
				labelobjectnewdrag->Render();
				textobjectnewdrag->Render();
				buttonobjectnewload->Render();
			}
			buttonobjectload->Render();
			if (tab & OBJECTLOAD)
			{
				labelobjectloadobjectname->Render();
				textobjectloadobjectname->Render();
				buttonobjectloadload->Render();
			}
			buttonobjectsave->Render();
			if (tab & OBJECTSAVE)
			{
				labelobjectsaveobjectname->Render();
				textobjectsaveobjectname->Render();
				buttonobjectsavesave->Render();
			}
			buttonobjectedit->Render();
			if (tab & OBJECTEDIT)
			{
				labelobjecteditobjectname->Render();
				textobjecteditobjectname->Render();
				buttonobjecteditget->Render();
				labelobjecteditmass->Render();
				textobjecteditmass->Render();
				labelobjecteditmomentofinertia->Render();
				textobjecteditmomentofinertia->Render();
				labelobjecteditrestitution->Render();
				textobjecteditrestitution->Render();
				labelobjecteditfriction->Render();
				textobjecteditfriction->Render();
				labelobjecteditdrag->Render();
				textobjecteditdrag->Render();
				labelobjecteditcentreofmass->Render();
				textobjecteditcentreofmassx->Render();
				textobjecteditcentreofmassy->Render();
				textobjecteditcentreofmassz->Render();
				labelobjecteditposition->Render();
				textobjecteditpositionx->Render();
				textobjecteditpositiony->Render();
				textobjecteditpositionz->Render();
				labelobjecteditrotation->Render();
				textobjecteditrotationx->Render();
				textobjecteditrotationy->Render();
				textobjecteditrotationz->Render();
				labelobjecteditvelocity->Render();
				textobjecteditvelocityx->Render();
				textobjecteditvelocityy->Render();
				textobjecteditvelocityz->Render();
				labelobjecteditangularvelocity->Render();
				textobjecteditangilarvelocityx->Render();
				textobjecteditangilarvelocityy->Render();
				textobjecteditangilarvelocityz->Render();
				labelobjecteditcollisionsphere->Render();
				textobjecteditcollisionspherex->Render();
				textobjecteditcollisionspherey->Render();
				textobjecteditcollisionspherez->Render();
				textobjecteditcollisionspherer->Render();
				buttonobjecteditcollisionspherenext->Render();
				buttonobjecteditcollisionsphereprevious->Render();
				buttonobjecteditcollisionsphereadd->Render();
				buttonobjecteditcollisionsphereremove->Render();
				buttonobjecteditupdate->Render();
				//DrawCollisionSphere(textobjecteditobjectname->string);
			}
			buttonobjectremove->Render();
		}
		if (tab & SCENE)
		{
			buttonsceneload->Render();
			if (tab & SCENELOAD)
			{
				labelsceneloadscenename->Render();
				textsceneloadscenename->Render();
				buttonsceneloadload->Render();
			}
			buttonscenesave->Render();
			if (tab & SCENESAVE)
			{
				labelscenesavescenename->Render();
				textscenesavescenename->Render();
				buttonscenesavesave->Render();
			}
		}
	}
	void ObjectLoad(char *_objectname)
	{
		object[*objectcount] = new Object();
		if (object[*objectcount]->Load(graphics, _objectname))
		{
			delete object[*objectcount];
			print("unable load object file\n");
			return;
		}
		(*objectcount)++;
		for (UINT32 i = 0; i < *objectcount; i++)object[i]->Update();
		print("object loaded\n");
	}
	void ObjectSave(char *_objectname)
	{
		for (UINT32 i = 0; i < *objectcount; i++)
		{
			if (strcmp(object[i]->name, _objectname) == 0)
			{
				if (object[i]->Save())
				{
					print("unable save object file");
					return;
				}
				print("object saved\n");
				return;
			}
		}
		print("object not found\n");
	}
	void ObjectNew(char *_objectname)
	{
		object[*objectcount] = new Object();
		if (object[*objectcount]->Initialize(graphics, _objectname, textobjectnewfilename->string, atoi(textobjectnewanimationlength->string), (float)atof(textobjectnewmass->string), (float)atof(textobjectnewmomentofinertia->string), (float)atof(textobjectnewrestitution->string), (float)atof(textobjectnewfriction->string), (float)atof(textobjectnewdrag->string)))
		{
			delete object[*objectcount];
			print("unable load object file\n");
			return;
		}
		(*objectcount)++;
		for (UINT32 i = 0; i < *objectcount; i++)object[i]->Update();
		print("object loaded\n");
	}
	void ObjectGet(char *_objectname)
	{
		for (UINT32 i = 0; i < *objectcount; i++)
		{
			if (strcmp(object[i]->name, _objectname) == 0)
			{
				float4 position = float4(0, 0, 0, 1); position = position * object[i]->position;
				float4 rotation = float4(0, 0, 0, 1); rotation = rotation * object[i]->rotation;
				sprintf_s(textobjecteditmass->string, "%f", object[i]->mass);
				sprintf_s(textobjecteditmomentofinertia->string, "%f", object[i]->momentofinertia);
				sprintf_s(textobjecteditrestitution->string, "%f", object[i]->restitution);
				sprintf_s(textobjecteditfriction->string, "%f", object[i]->friction);
				sprintf_s(textobjecteditdrag->string, "%f", object[i]->drag);
				sprintf_s(textobjecteditcentreofmassx->string, "%f", position.x);
				sprintf_s(textobjecteditcentreofmassy->string, "%f", position.y);
				sprintf_s(textobjecteditcentreofmassz->string, "%f", position.z);
				sprintf_s(textobjecteditpositionx->string, "%f", position.x);
				sprintf_s(textobjecteditpositiony->string, "%f", position.y);
				sprintf_s(textobjecteditpositionz->string, "%f", position.z);
				sprintf_s(textobjecteditrotationx->string, "%f", rotation.x);
				sprintf_s(textobjecteditrotationy->string, "%f", rotation.y);
				sprintf_s(textobjecteditrotationz->string, "%f", rotation.z);
				sprintf_s(textobjecteditvelocityx->string, "%f", object[i]->velocity.x);
				sprintf_s(textobjecteditvelocityy->string, "%f", object[i]->velocity.y);
				sprintf_s(textobjecteditvelocityz->string, "%f", object[i]->velocity.z);
				sprintf_s(textobjecteditangilarvelocityx->string, "%f", object[i]->angularvelocity.x);
				sprintf_s(textobjecteditangilarvelocityy->string, "%f", object[i]->angularvelocity.y);
				sprintf_s(textobjecteditangilarvelocityz->string, "%f", object[i]->angularvelocity.z);
				if (object[i]->collisionspherecount)
				{
					sprintf_s(textobjecteditcollisionspherex->string, "%f", object[i]->collisionsphere[currentcollisionsphereindex].position.x);
					sprintf_s(textobjecteditcollisionspherey->string, "%f", object[i]->collisionsphere[currentcollisionsphereindex].position.y);
					sprintf_s(textobjecteditcollisionspherez->string, "%f", object[i]->collisionsphere[currentcollisionsphereindex].position.z);
					sprintf_s(textobjecteditcollisionspherer->string, "%f", object[i]->collisionsphere[currentcollisionsphereindex].radius);
				}
				else
				{
					strcpy_s(textobjecteditcollisionspherex->string, "");
					strcpy_s(textobjecteditcollisionspherey->string, "");
					strcpy_s(textobjecteditcollisionspherez->string, "");
					strcpy_s(textobjecteditcollisionspherer->string, "");
				}
				print("object found\n");
				return;
			}
		}
		print("object not found\n");
	}
	void ObjectUpdate(char *_objectname)
	{
		for (UINT32 i = 0; i < *objectcount; i++)
		{
			if (strcmp(object[i]->name, _objectname) == 0)
			{
				object[i]->mass = (float)atof(textobjecteditmass->string);
				object[i]->momentofinertia = (float)atof(textobjecteditmomentofinertia->string);
				object[i]->restitution = (float)atof(textobjecteditrestitution->string);
				object[i]->friction = (float)atof(textobjecteditfriction->string);
				object[i]->drag = (float)atof(textobjecteditdrag->string);
				if (object[i]->collisionspherecount)
				{
					object[i]->collisionsphere[currentcollisionsphereindex].position.x = (float)atof(textobjecteditcollisionspherex->string);
					object[i]->collisionsphere[currentcollisionsphereindex].position.y = (float)atof(textobjecteditcollisionspherey->string);
					object[i]->collisionsphere[currentcollisionsphereindex].position.z = (float)atof(textobjecteditcollisionspherez->string);
					object[i]->collisionsphere[currentcollisionsphereindex].radius = (float)atof(textobjecteditcollisionspherer->string);
				}
				physics->Position(object[i], float3((float)atof(textobjecteditpositionx->string), (float)atof(textobjecteditpositiony->string), (float)atof(textobjecteditpositionz->string)));
				physics->Rotation(object[i], float3((float)atof(textobjecteditrotationx->string), (float)atof(textobjecteditrotationy->string), (float)atof(textobjecteditrotationz->string)));
				physics->Velocity(object[i], float3((float)atof(textobjecteditvelocityx->string), (float)atof(textobjecteditvelocityy->string), (float)atof(textobjecteditvelocityz->string)));
				physics->AngularVelocity(object[i], float3((float)atof(textobjecteditangilarvelocityx->string), (float)atof(textobjecteditangilarvelocityy->string), (float)atof(textobjecteditangilarvelocityz->string)));

				ObjectGet(object[i]->name);
				for (UINT32 o = 0; o < *objectcount; o++)object[o]->Update();
				print("object updated\n");
				return;
			}
		}
		print("object not found\n");
	}
	void ObjectNextCollisionSphere(char *_objectname)
	{
		for (UINT32 i = 0; i < *objectcount; i++)
		{
			if (strcmp(object[i]->name, _objectname) == 0)
			{
				currentcollisionsphereindex++;
				if (currentcollisionsphereindex >= (INT32)object[i]->collisionspherecount)currentcollisionsphereindex = 0;
				ObjectGet(object[i]->name);
				print("object updated\n");
				return;
			}
		}
		print("object not found\n");
	}
	void ObjectPreviousCollisionSphere(char *_objectname)
	{
		for (UINT32 i = 0; i < *objectcount; i++)
		{
			if (strcmp(object[i]->name, _objectname) == 0)
			{
				currentcollisionsphereindex--;
				if (currentcollisionsphereindex < 0)currentcollisionsphereindex = object[i]->collisionspherecount - 1;
				ObjectGet(object[i]->name);
				print("object updated\n");
				return;
			}
		}
		print("object not found\n");
	}
	void ObjectAddCollisionSphere(char *_objectname)
	{
		for (UINT32 i = 0; i < *objectcount; i++)
		{
			if (strcmp(object[i]->name, _objectname) == 0)
			{
				float4 position; position = position * object[i]->position;
				physics->AddCollisionSphere(object[i], position.x, position.y, position.y,1.0f);
				ObjectGet(object[i]->name);
				for (UINT32 o = 0; o < *objectcount; o++)object[i]->Update();
				print("object updated\n");
				return;
			}
		}
		print("object not found\n");
	}
	void ObjectRemoveCollisionSphere(char *_objectname)
	{
		for (UINT32 i = 0; i < *objectcount; i++)
		{
			if (strcmp(object[i]->name, _objectname) == 0)
			{
				physics->RemoveCollisionSphere(object[i],currentcollisionsphereindex);
				ObjectGet(object[i]->name);
				for (UINT32 o = 0; o < *objectcount; o++)object[i]->Update();
				print("object updated\n");
				return;
			}
		}
		print("object not found\n");
	}
	void DrawCollisionSphere(Object *_object)
	{
		Matrix computationmatrix(4, 4);
		computationmatrix.Identity();
		computationmatrix = computationmatrix * _object->rotation;
		computationmatrix = computationmatrix * _object->position;
		graphics->SetRenderTarget();
		for (INT32 s = 0; s < (INT32)_object->collisionspherecount; s++)
		{
			graphics->PixelShaderSet(pixelshaderdiffuseonly);
			if (s == currentcollisionsphereindex)
			{
				float4 transformedposition = float4(_object->collisionsphere[s].position.x, _object->collisionsphere[s].position.y, _object->collisionsphere[s].position.z, 1) * computationmatrix;
				collisionsphereselected->scale.Identity();
				collisionsphereselected->scale.Scale(_object->collisionsphere[s].radius, _object->collisionsphere[s].radius, _object->collisionsphere[s].radius);
				collisionsphereselected->position.Identity();
				collisionsphereselected->position.Translate(transformedposition.x, transformedposition.y, transformedposition.z);
				collisionsphereselected->Update();
				collisionsphereselected->Draw();
			}
			float4 transformedposition = float4(_object->collisionsphere[s].position.x, _object->collisionsphere[s].position.y, _object->collisionsphere[s].position.z, 1) * computationmatrix;
			collisionsphereunselected->scale.Identity();
			collisionsphereunselected->scale.Scale(_object->collisionsphere[s].radius, _object->collisionsphere[s].radius, _object->collisionsphere[s].radius);
			collisionsphereunselected->position.Identity();
			collisionsphereunselected->position.Translate(transformedposition.x, transformedposition.y, transformedposition.z);
			collisionsphereunselected->Update();
			collisionsphereunselected->Draw();
		}
	}
	void DrawCollisionSphere(char *_objectname)
	{
		if (_objectname[0])
		{
			for (UINT32 i = 0; i < *objectcount; i++)
			{
				if (strcmp(object[i]->name, _objectname) == 0)
				{
					Matrix computationmatrix(4, 4);
					computationmatrix.Identity();
					computationmatrix = computationmatrix * object[i]->rotation;
					computationmatrix = computationmatrix * object[i]->position;
					graphics->SetRenderTarget();
					for (INT32 s = 0; s < (INT32)object[i]->collisionspherecount; s++)
					{						
						graphics->PixelShaderSet(pixelshaderdiffuseonly);
						if (s == currentcollisionsphereindex)
						{
							float4 transformedposition = float4(object[i]->collisionsphere[s].position.x, object[i]->collisionsphere[s].position.y, object[i]->collisionsphere[s].position.z, 1) * computationmatrix;
							collisionsphereselected->scale.Scale(object[i]->collisionsphere[s].radius, object[i]->collisionsphere[s].radius, object[i]->collisionsphere[s].radius);
							collisionsphereselected->position.Translate(transformedposition.x, transformedposition.y, transformedposition.z);
							collisionsphereselected->Update();
							collisionsphereselected->Draw();
						}
						float4 transformedposition = float4(object[i]->collisionsphere[s].position.x, object[i]->collisionsphere[s].position.y, object[i]->collisionsphere[s].position.z, 1) * computationmatrix;
						collisionsphereunselected->scale.Scale(object[i]->collisionsphere[s].radius, object[i]->collisionsphere[s].radius, object[i]->collisionsphere[s].radius);
						collisionsphereunselected->position.Translate(transformedposition.x, transformedposition.y, transformedposition.z);
						collisionsphereunselected->Update();
						collisionsphereunselected->Draw();
					}
					return;
				}
			}
			print("object not found\n");
		}		
	}
	/*void ObjectAddCollisionSphere(char *_objectname, float x, float y, float z, float r)
	{
		for (UINT32 i = 0; i < objectcount; i++)
		{
			if (strcmp(_objectname, object[i]->name) == 0)
			{
				physics->AddCollisionSphere(object[i], x, y, z, r);
				return;
			}
		}
		print("object not found");
	}*/
	void SceneLoad(char *_scenename)
	{
		if (scene->Load(_scenename))
		{
			print("failed to open scene file\n");
			return;
		}
		for (UINT32 i = 0; i < scene->objectcount; i++)
		{
			object[i] = new Object();
			if (object[i]->Load(graphics, scene->objectname[i]))
			{
				print("failed to load entire scene");
				return;
			}
			(*objectcount)++;
		}
		print("scene loade\nd");
	}
	void SceneSave(char *_scenename)
	{
		scene->objectcount = *objectcount;
		scene->objectname = new char*[scene->objectcount];
		for (UINT32 i = 0; i < *objectcount; i++)
		{
			if (object[i]->Save())
			{
				print("failed to save entire scene\n");
				return;
			}
			scene->objectname[i] = new char[BUFFERSIZE];
			strcpy_s(scene->objectname[i], sizeof(object[i]->name), object[i]->name);
		}
		if (scene->Save(_scenename))
		{
			print("failed to save entire scene");
			return;
		}
		print("scene saved\n");
	}

	Editor()
	{
		ZeroMemory(this, sizeof(Editor));
		collisionsphereunselected = new Object();
		collisionsphereselected = new Object();

		buttonobject = new GUIButton();
			buttonobjectnew = new GUIButton();
				labelobjectnewobjectname = new GUILabel();
				textobjectnewobjectname = new GUIText();
				labelobjectnewfilename = new GUILabel();
				textobjectnewfilename = new GUIText();
				labelobjectnewanimationlength = new GUILabel();
				textobjectnewanimationlength = new GUIText();
				labelobjectnewmass = new GUILabel();
				textobjectnewmass = new GUIText();
				labelobjectnewmomentofinertia = new GUILabel();
				textobjectnewmomentofinertia = new GUIText();
				labelobjectnewrestitution = new GUILabel();
				textobjectnewrestitution = new GUIText();
				labelobjectnewfriction = new GUILabel();
				textobjectnewfriction = new GUIText();
				labelobjectnewdrag = new GUILabel();
				textobjectnewdrag = new GUIText();
				buttonobjectnewload = new GUIButton();
			buttonobjectload = new GUIButton();
				labelobjectloadobjectname = new GUILabel();
				textobjectloadobjectname = new GUIText();
				buttonobjectloadload = new GUIButton();
			buttonobjectsave = new GUIButton();
				labelobjectsaveobjectname = new GUILabel();
				textobjectsaveobjectname = new GUIText();
				buttonobjectsavesave = new GUIButton();
			buttonobjectedit = new GUIButton();
				labelobjecteditobjectname = new GUILabel();
				textobjecteditobjectname = new GUIText();
				buttonobjecteditget = new GUIButton();
				labelobjecteditmass = new GUILabel();
				textobjecteditmass = new GUIText();
				labelobjecteditmomentofinertia = new GUILabel();
				textobjecteditmomentofinertia = new GUIText();
				labelobjecteditrestitution = new GUILabel();
				textobjecteditrestitution = new GUIText();
				labelobjecteditfriction = new GUILabel();
				textobjecteditfriction = new GUIText();
				labelobjecteditdrag = new GUILabel();
				textobjecteditdrag = new GUIText();
				labelobjecteditcentreofmass = new GUILabel();
				textobjecteditcentreofmassx = new GUIText();
				textobjecteditcentreofmassy = new GUIText();
				textobjecteditcentreofmassz = new GUIText();
				labelobjecteditposition = new GUILabel();
				textobjecteditpositionx = new GUIText();
				textobjecteditpositiony = new GUIText();
				textobjecteditpositionz = new GUIText();
				labelobjecteditrotation = new GUILabel();
				textobjecteditrotationx = new GUIText();
				textobjecteditrotationy = new GUIText();
				textobjecteditrotationz = new GUIText();
				labelobjecteditvelocity = new GUILabel();
				textobjecteditvelocityx = new GUIText();
				textobjecteditvelocityy = new GUIText();
				textobjecteditvelocityz = new GUIText();
				labelobjecteditangularvelocity = new GUILabel();
				textobjecteditangilarvelocityx = new GUIText();
				textobjecteditangilarvelocityy = new GUIText();
				textobjecteditangilarvelocityz = new GUIText();
				labelobjecteditcollisionsphere = new GUILabel();
				textobjecteditcollisionspherex = new GUIText();
				textobjecteditcollisionspherey = new GUIText();
				textobjecteditcollisionspherez = new GUIText();
				textobjecteditcollisionspherer = new GUIText();
				buttonobjecteditcollisionspherenext = new GUIButton();
				buttonobjecteditcollisionsphereprevious = new GUIButton();
				buttonobjecteditcollisionsphereadd = new GUIButton();
				buttonobjecteditcollisionsphereremove = new GUIButton();
				buttonobjecteditupdate = new GUIButton();
			buttonobjectremove = new GUIButton();
		buttonscene = new GUIButton();
			buttonsceneload = new GUIButton();
				labelsceneloadscenename = new GUILabel();
				textsceneloadscenename = new GUIText();
				buttonsceneloadload = new GUIButton();
			buttonscenesave = new GUIButton();
				labelscenesavescenename = new GUILabel();
				textscenesavescenename = new GUIText();
				buttonscenesavesave = new GUIButton();
	}
	~Editor()
	{
		delete buttonobject;
			delete buttonobjectnew;
				delete labelobjectnewobjectname;
				delete textobjectnewobjectname;
				delete labelobjectnewfilename;
				delete textobjectnewfilename;
				delete labelobjectnewanimationlength;
				delete textobjectnewanimationlength;
				delete labelobjectnewmass;
				delete textobjectnewmass;
				delete labelobjectnewmomentofinertia;
				delete textobjectnewmomentofinertia;
				delete labelobjectnewrestitution;
				delete textobjectnewrestitution;
				delete labelobjectnewfriction;
				delete textobjectnewfriction;
				delete labelobjectnewdrag;
				delete textobjectnewdrag;
				delete buttonobjectnewload;
			delete buttonobjectload;
				delete labelobjectloadobjectname;
				delete textobjectloadobjectname;
				delete buttonobjectloadload;
			delete buttonobjectsave;
				delete labelobjectsaveobjectname;
				delete textobjectsaveobjectname;
				delete buttonobjectsavesave;
			delete buttonobjectedit;
				delete labelobjecteditobjectname;
				delete textobjecteditobjectname;
				delete buttonobjecteditget;
				delete labelobjecteditmass;
				delete textobjecteditmass;
				delete labelobjecteditmomentofinertia;
				delete textobjecteditmomentofinertia;
				delete labelobjecteditrestitution;
				delete textobjecteditrestitution;
				delete labelobjecteditfriction;
				delete textobjecteditfriction;
				delete labelobjecteditdrag;
				delete textobjecteditdrag;
				delete labelobjecteditcentreofmass;
				delete textobjecteditcentreofmassx;
				delete textobjecteditcentreofmassy;
				delete textobjecteditcentreofmassz;
				delete labelobjecteditposition;
				delete textobjecteditpositionx;
				delete textobjecteditpositiony;
				delete textobjecteditpositionz;
				delete labelobjecteditrotation;
				delete textobjecteditrotationx;
				delete textobjecteditrotationy;
				delete textobjecteditrotationz;
				delete labelobjecteditvelocity;
				delete textobjecteditvelocityx;
				delete textobjecteditvelocityy;
				delete textobjecteditvelocityz;
				delete labelobjecteditangularvelocity;
				delete textobjecteditangilarvelocityx;
				delete textobjecteditangilarvelocityy;
				delete textobjecteditangilarvelocityz;
				delete labelobjecteditcollisionsphere;
				delete textobjecteditcollisionspherex;
				delete textobjecteditcollisionspherey;
				delete textobjecteditcollisionspherez;
				delete textobjecteditcollisionspherer;
				delete buttonobjecteditcollisionspherenext;
				delete buttonobjecteditcollisionsphereprevious;
				delete buttonobjecteditcollisionsphereadd;
				delete buttonobjecteditcollisionsphereremove;
				delete buttonobjecteditupdate;
			delete buttonobjectremove;
		delete buttonscene;
			delete buttonsceneload;
				delete labelsceneloadscenename;
				delete textsceneloadscenename;
				delete buttonsceneloadload;
			delete buttonscenesave;
				delete labelscenesavescenename;
				delete textscenesavescenename;
				delete buttonscenesavesave;

		delete collisionsphereunselected;
		delete collisionsphereselected;
		delete vertexshader;
		delete pixelshaderdiffuseonly;
		ZeroMemory(this, sizeof(Editor));
	}
};