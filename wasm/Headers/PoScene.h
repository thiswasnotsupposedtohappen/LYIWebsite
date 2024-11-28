struct Scene
{
	UINT32 objectcount;
	char **objectname;

	BOOL Load(char *filename)
	{
		File file;
		char filepath[BUFFERSIZE * 2];
		strcpy_s(filepath, OBJECTPATH);
		strcat_s(filepath, filename);
		strcat_s(filepath, ".scene");

		if (file.Open(filepath))return 1;
		file.Read(&objectcount,sizeof(UINT32));
		objectname = new char*[objectcount];
		for (UINT32 i = 0; i < objectcount; i++)
		{
			objectname[i] = new char[BUFFERSIZE];
			file.Read(objectname[i], sizeof(char)*BUFFERSIZE);
		}
		file.Close();
		return 0;
	}
	BOOL Save(char *filename)
	{
		File file;
		char filepath[BUFFERSIZE * 2];
		strcpy_s(filepath, OBJECTPATH);
		strcat_s(filepath, filename);
		strcat_s(filepath, ".scene");

		if (file.Create(filepath))return 1;
		if (file.Open(filepath))return 1;
		file.Write(&objectcount, sizeof(UINT32));
		for (UINT32 i = 0; i < objectcount; i++)
			file.Write(objectname[i], sizeof(char)*BUFFERSIZE);

		file.Close();
		return 0;
	}
	Scene()
	{
		ZeroMemory(this, sizeof(Scene));
	}
	~Scene()
	{
		for (UINT32 i = 0; i < objectcount; i++)
			delete[] objectname[i];
		delete[] objectname;
	}
};