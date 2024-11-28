UINT32 skipcount = 0;
struct Object
{
protected:
	Graphics *graphics;
public:

	struct Material
	{		
		float4 diffuse;
		float4 specular;
		float specularpower;
		float textured;

		char name[BUFFERSIZE];
		char map[BUFFERSIZE];
		::Graphics::Texture *texture;
		::Graphics::ConstantBuffer *materialbuffer;
		Material()
		{
			ZeroMemory(this, sizeof(Material));
		}
		~Material()
		{
			delete texture;
			delete materialbuffer;
			ZeroMemory(this, sizeof(Material));
		}
	};
	struct Mesh
	{
		struct Vertex
		{
			float3 pos;
			float3 normal;
			float2 tex;
		};
		struct Bone
		{
			char name[BUFFERSIZE];
			UINT32 index;
			FLOAT *weight;
			Bone()
			{
				ZeroMemory(this, sizeof(Bone));
			}
			~Bone()
			{
				delete[] weight;
				ZeroMemory(this, sizeof(Bone));
			}
		};

		char name[BUFFERSIZE];

		char parentname[BUFFERSIZE];
		UINT32 parentindex;
		Mesh* parent;

		Matrix frametransformation;

		Matrix *animationkey;
		UINT32 key;

		UINT32	indexcount;
		UINT32 *index;
		::Graphics::IndexBuffer	*indexbuffer;

		UINT32 vertexcount;
		Vertex *vertex;
		::Graphics::Buffer	*vertexbuffer;

		UINT32 bonecount;
		Bone *bone;		
		::Graphics::Buffer	*weightbuffer;
		FLOAT *boneworld; BOOL boneworldlock;
		::Graphics::ConstantBuffer *boneworldbuffer;

		FLOAT	*data;
		::Graphics::ConstantBuffer *databuffer;

		UINT32 materialindex;
		
		Matrix	world; BOOL	worldlock;
		::Graphics::ConstantBuffer	*worldbuffer;		

		Mesh()
		{
			ZeroMemory(this, sizeof(Mesh));
		}
		~Mesh()
		{
			delete[] animationkey;

			delete[] index;
			delete indexbuffer;

			delete[] vertex;
			delete vertexbuffer;

			delete data;
			delete databuffer;

			delete[] bone;			
			delete weightbuffer;
			delete[] boneworld;
			delete boneworldbuffer;

			delete worldbuffer;			
			ZeroMemory(this, sizeof(Mesh));
		}
	};
	struct CollisionSphere 
	{
		float3 position;
		float radius;

		CollisionSphere()
		{
			ZeroMemory(this, sizeof(CollisionSphere));
		}
		CollisionSphere(float3 _position, float _radius)
		{
			position = _position;
			radius = _radius;
		}
		void operator =(CollisionSphere _collisionsphere)
		{
			memcpy_s(this, sizeof(CollisionSphere), &_collisionsphere, sizeof(CollisionSphere));
		}
	};

	char name[BUFFERSIZE];
	UINT32 animationkeycount;
	UINT32 materialcount;
	Material *material;
	UINT32 meshcount;
	Mesh *mesh;	
	Matrix world; BOOL	worldlock;
	::Graphics::ConstantBuffer	*worldbuffer;
	Matrix scale;
	float counter;

	UINT32 collisionspherecount;
	CollisionSphere *collisionsphere;
	float mass; 
	float momentofinertia;
	float restitution;
	float friction;
	float drag;

	Matrix position;
	Matrix rotation;
	float3 velocity;
	float3 angularvelocity;

	UINT8			   Initialize(Graphics *_graphics, char *_objectname, char *_filename, UINT32 _animationlength, float _mass, float _momentofinertia, float _restitution, float _friction, float _drag)
	{
		graphics = _graphics;
		char filepath[BUFFERSIZE * 2];
		strcpy_s(filepath, OBJECTPATH);
		strcat_s(filepath, _filename);

		struct xFile
		{
		private:
			fstream file;
			bool  LoadFile(char _name[])
			{
				file.open(_name);
				if (file)
					return true;
				return false;
			}
			void  CloseFile()
			{
				file.close();
			}
			void  Rewind()
			{
				file.flush();
				file.clear();
				file.seekg(ios::beg);
			}
			void  ReadLine(char buffer[])
			{
				file.getline(buffer, BUFFERSIZE);
			}
			void  ReadChar(char &c)
			{
				file.get(c);
			}
			char  ReadChar()
			{
				char c;
				file.get(c);
				return c;
			}
			void  ClearBuffer(char buffer[])
			{
				for (unsigned short i = 0; i<BUFFERSIZE&&buffer[i] != '\0'; buffer[i++] = '\0');
			}
			void  ReadToken(char* token)
			{
				char c;
				ClearBuffer(token);
				do	c = ReadChar();
				while (c == 0 || c == '\n' || c == ' ' || c == ',' || c == ';' || c == '\"');
				for (UINT16 i = 0; i < BUFFERSIZE && !file.eof(); i++)
				{
					token[i] = c;
					c = ReadChar();
					if (c == 0 || c == '\n' || c == ' ' || c == ',' || c == ';' || c == '\"')break;
				}
			}
			void  ReadToken(char* token, UINT32 count)
			{
				for (UINT32 i = 0; i < count; i++)
					ReadToken(token);
			}
			void  FindToken(char* token, char* tokentomatch)
			{
				do ReadToken(token);
				while (strcmp(token, tokentomatch));
			}

			UINT32 materialread;
			UINT32 meshread;

			UINT8 Ptemplate()
			{
				char token[BUFFERSIZE];
				ReadToken(token);
				ReadToken(token);
				if (strcmp("{", token))return 1;
				do
				{
					ReadToken(token);
					if (file.eof())return 1;
				} while (strcmp("}", token));
				return 0;
			}
			UINT8 PMaterial()
			{
				char token[BUFFERSIZE];
				float r, g, b, a;

				ReadToken(token); strcpy_s(material[materialread].name, token);

				ReadToken(token); if (strcmp("{", token))return 1;
				{
					ReadToken(token); r = (float)atof(token); ReadToken(token); g = (float)atof(token); ReadToken(token); b = (float)atof(token);	ReadToken(token); a = (float)atof(token); material[materialread].diffuse = float4(r, g, b, a);
					ReadToken(token); r = (float)atof(token); material[materialread].specularpower = r;
					ReadToken(token); r = (float)atof(token); ReadToken(token); g = (float)atof(token); ReadToken(token); b = (float)atof(token);	material[materialread].specular = float4(r, g, b, 1);
					ReadToken(token); r = (float)atof(token); ReadToken(token); g = (float)atof(token); ReadToken(token); b = (float)atof(token);

					while (1)
					{
						ReadToken(token);
						if (file.eof())return 1;
						if (strcmp("}", token) == 0)break;
						else if (strcmp("TextureFilename", token) == 0)
						{
							ReadToken(token); if (strcmp("{", token))return 1;
							{
								ReadToken(token);
								material[materialread].textured = true;
								strcpy_s(material[materialread].map, token);
							}
							ReadToken(token); if (strcmp("}", token))return 1;
						}
					}
				}
				if (strcmp("}", token))return 1;
				materialread++;
				return 0;
			}
			UINT8 PFrame(char *parent = 0)
			{
				char *meshname;
				char token[BUFFERSIZE];
				if (parent)
					strcpy_s(mesh[meshread].parent, parent);
				ReadToken(token); strcpy_s(mesh[meshread].name, token);
				meshname = mesh[meshread].name;
				ReadToken(token); if (strcmp("{", token))return 1;
				while (1)
				{
					ReadToken(token);
					if (file.eof())return 1;
					if (strcmp("}", token) == 0)break;
					else if (strcmp("FrameTransformMatrix", token) == 0)
					{
						ReadToken(token); if (strcmp("{", token))return 1;
						ReadToken(token); float _00 = (float)atof(token);
						ReadToken(token); float _01 = (float)atof(token);
						ReadToken(token); float _02 = (float)atof(token);
						ReadToken(token); float _03 = (float)atof(token);
						ReadToken(token); float _10 = (float)atof(token);
						ReadToken(token); float _11 = (float)atof(token);
						ReadToken(token); float _12 = (float)atof(token);
						ReadToken(token); float _13 = (float)atof(token);
						ReadToken(token); float _20 = (float)atof(token);
						ReadToken(token); float _21 = (float)atof(token);
						ReadToken(token); float _22 = (float)atof(token);
						ReadToken(token); float _23 = (float)atof(token);
						ReadToken(token); float _30 = (float)atof(token);
						ReadToken(token); float _31 = (float)atof(token);
						ReadToken(token); float _32 = (float)atof(token);
						ReadToken(token); float _33 = (float)atof(token);
						mesh[meshread].frametransformation = Matrix(4, 4, _00, _01, _02, _03, _10, _11, _12, _13, _20, _21, _22, _23, _30, _31, _32, _33);
						mesh[meshread].keymatrix = new Matrix[animationlength];
						for (UINT32 k = 0; k < animationlength; k++)
							mesh[meshread].keymatrix[k] = Matrix(4, 4, _00, _01, _02, _03, _10, _11, _12, _13, _20, _21, _22, _23, _30, _31, _32, _33);
						ReadToken(token); if (strcmp("}", token))return 1;
					}
					else if (strcmp("Mesh", token) == 0)
					{
						ReadToken(token);
						ReadToken(token); if (strcmp("{", token))return 1;
						ReadToken(token); mesh[meshread].vertexcount = atoi(token);
						mesh[meshread].vertex = new Mesh::Vertex[mesh[meshread].vertexcount];
						for (UINT32 i = 0; i < mesh[meshread].vertexcount; i++)
						{
							ReadToken(token); mesh[meshread].vertex[i].pos.x = (float)atof(token);
							ReadToken(token); mesh[meshread].vertex[i].pos.y = (float)atof(token);
							ReadToken(token); mesh[meshread].vertex[i].pos.z = (float)atof(token);
						}
						ReadToken(token);
						mesh[meshread].indexcount = atoi(token) * 3;
						mesh[meshread].index = new UINT32[mesh[meshread].indexcount];
						for (UINT32 i = 0; i < mesh[meshread].indexcount; )
						{
							ReadToken(token);
							ReadToken(token); mesh[meshread].index[i++] = atoi(token);
							ReadToken(token); mesh[meshread].index[i++] = atoi(token);
							ReadToken(token); mesh[meshread].index[i++] = atoi(token);
						}

						UINT32 boneread = 0;
						while (1)
						{
							ReadToken(token);
							if (file.eof())return 1;
							if (strcmp("}", token) == 0)break;
							else if (strcmp("MeshNormals", token) == 0)
							{
								ReadToken(token); if (strcmp("{", token))return 1;
								ReadToken(token);
								for (UINT32 i = 0; i < mesh[meshread].vertexcount; i++)
								{
									ReadToken(token); mesh[meshread].vertex[i].normal.x = (float)atof(token);
									ReadToken(token); mesh[meshread].vertex[i].normal.y = (float)atof(token);
									ReadToken(token); mesh[meshread].vertex[i].normal.z = (float)atof(token);
								}
								ReadToken(token);
								for (UINT32 i = 0; i < mesh[meshread].indexcount; i += 3)
									ReadToken(token, 4);
								ReadToken(token); if (strcmp("}", token))return 1;
							}
							else if (strcmp("MeshMaterialList", token) == 0)
							{
								float r;
								ReadToken(token); if (strcmp("{", token))return 1;
								ReadToken(token);
								ReadToken(token); r = (float)atof(token);
								for (UINT32 i = 0; i < r; i++)ReadToken(token);

								ReadToken(token); if (strcmp("{", token))return 1;
								ReadToken(token);
								for (UINT32 i = 0; i < materialread; i++)
									if (strcmp(token, material[i].name) == 0)
										mesh[meshread].matid = i;
								ReadToken(token); if (strcmp("}", token))return 1;

								ReadToken(token); if (strcmp("}", token))return 1;
							}
							else if (strcmp("MeshTextureCoords", token) == 0)
							{
								ReadToken(token);
								ReadToken(token); if (strcmp("{", token))return 1;
								ReadToken(token);
								for (UINT32 i = 0; i < mesh[meshread].vertexcount; i++)
								{
									ReadToken(token); mesh[meshread].vertex[i].tex.x = (float)atof(token);
									ReadToken(token); mesh[meshread].vertex[i].tex.y = (float)atof(token);
								}
								ReadToken(token); if (strcmp("}", token))return 1;
							}
							else if (strcmp("XSkinMeshHeader", token) == 0)
							{
								ReadToken(token); if (strcmp("{", token))return 1;
								ReadToken(token);
								ReadToken(token);
								ReadToken(token); mesh[meshread].bonecount = atoi(token);
								mesh[meshread].bone = new Mesh::Bone[mesh[meshread].bonecount];

								ReadToken(token); if (strcmp("}", token))return 1;
							}
							else if (strcmp("SkinWeights", token) == 0)
							{
								ReadToken(token); if (strcmp("{", token))return 1;

								ReadToken(token);
								strcpy_s(mesh[meshread].bone[boneread].name, token);
								ReadToken(token); UINT32 weightedvertexcount = atoi(token);
								UINT32 *weightedvertex = new UINT32[weightedvertexcount];
								for (UINT32 i = 0; i < weightedvertexcount; i++)
								{
									ReadToken(token); weightedvertex[i] = atoi(token);
								}
								mesh[meshread].bone[boneread].weight = new FLOAT[mesh[meshread].vertexcount];
								ZeroMemory(mesh[meshread].bone[boneread].weight, sizeof(float)*mesh[meshread].vertexcount);
								for (UINT32 i = 0; i < weightedvertexcount; i++)
								{
									ReadToken(token); mesh[meshread].bone[boneread].weight[weightedvertex[i]] = (float)atof(token);
								}
								ReadToken(token, 16);

								ReadToken(token); if (strcmp("}", token))return 1;
								boneread++;
							}
						}
					}
					else if (strcmp("Frame", token) == 0)
					{
						meshread++;
						if (PFrame(meshname))return 1;
						meshread--;
					}
				}

				meshread++;
				return 0;
			}
			UINT8 PAnimationSet()
			{
				char token[BUFFERSIZE];
				char meshname[BUFFERSIZE];
				ReadToken(token);
				ReadToken(token); if (strcmp("{", token))return 1;
				while (1)
				{
					ReadToken(token);
					if (strcmp("}", token) == 0)break;
					if (file.eof())return 1;
					else if (strcmp("Animation", token) == 0)
					{
						ReadToken(token); if (strcmp("{", token))return 1;

						ReadToken(token); if (strcmp("{", token))return 1;
						ReadToken(token); strcpy_s(meshname, token);
						ReadToken(token); if (strcmp("}", token))return 1;
						ReadToken(token); if (strcmp("AnimationKey", token))return 1;
						ReadToken(token); if (strcmp("{", token))return 1;
						ReadToken(token);

						for (UINT32 i = 0; i < meshcount; i++)
							if (strcmp(mesh[i].name, meshname) == 0)
							{
								ReadToken(token);

								Matrix frametransformation(4, 4);
								for (UINT32 k = 0; k < animationlength; k++)
								{
									ReadToken(token);
									for (; k < atof(token); k++)
										mesh[i].keymatrix[k] = mesh[i].keymatrix[k - 1];

									ReadToken(token);
									ReadToken(token); float _00 = (float)atof(token);
									ReadToken(token); float _01 = (float)atof(token);
									ReadToken(token); float _02 = (float)atof(token);
									ReadToken(token); float _03 = (float)atof(token);
									ReadToken(token); float _10 = (float)atof(token);
									ReadToken(token); float _11 = (float)atof(token);
									ReadToken(token); float _12 = (float)atof(token);
									ReadToken(token); float _13 = (float)atof(token);
									ReadToken(token); float _20 = (float)atof(token);
									ReadToken(token); float _21 = (float)atof(token);
									ReadToken(token); float _22 = (float)atof(token);
									ReadToken(token); float _23 = (float)atof(token);
									ReadToken(token); float _30 = (float)atof(token);
									ReadToken(token); float _31 = (float)atof(token);
									ReadToken(token); float _32 = (float)atof(token);
									ReadToken(token); float _33 = (float)atof(token);
									mesh[i].keymatrix[k] = Matrix(4, 4, _00, _01, _02, _03, _10, _11, _12, _13, _20, _21, _22, _23, _30, _31, _32, _33);
								}
								break;
							}

						ReadToken(token); if (strcmp("}", token))return 1;
						ReadToken(token); if (strcmp("}", token))return 1;
					}
				}
				return 0;
			}
		public:

			UINT32 materialcount;
			UINT32 meshcount;
			UINT32 animationlength;

			struct Material
			{
				char name[BUFFERSIZE];
				float4 diffuse;
				float4 specular;
				float specularpower;
				char map[BUFFERSIZE];
				bool textured;
				Material()
				{
					ZeroMemory(this, sizeof(Material));
				}
				~Material()
				{
					ZeroMemory(this, sizeof(Material));
				}

			}*material;
			struct Mesh
			{
				char parent[BUFFERSIZE];
				char name[BUFFERSIZE];
				UINT32   *index;
				struct Vertex
				{
					float3 pos;
					float3 normal;
					float2 tex;
				} *vertex;
				Matrix frametransformation;
				Matrix *keymatrix;
				struct Bone
				{
					char name[BUFFERSIZE];
					FLOAT *weight;
					Bone()
					{
						ZeroMemory(this, sizeof(Bone));
					}
					~Bone()
					{
						delete[] weight;
						ZeroMemory(this, sizeof(Bone));
					}
				}*bone;

				UINT32 indexcount;
				UINT32 vertexcount;
				UINT32 bonecount;
				UINT32 matid;
				Mesh()
				{
					ZeroMemory(this, sizeof(Mesh));
				}
				~Mesh()
				{
					delete[] index;
					delete[] vertex;
					delete[] keymatrix;
					delete[] bone;
					ZeroMemory(this, sizeof(Mesh));
				}
			}*mesh;

			UINT8 LoadX(char* _filename, UINT32 _animationlength)
			{

				print("X File Loader: Reading File (%s)\n", _filename);
				char buffer[BUFFERSIZE];
				char token[BUFFERSIZE];
				char filepath[BUFFERSIZE + 1024];
				strcpy_s(filepath, _filename);
				//strcat_s(filepath, _filename);
				animationlength = _animationlength;
				//OPEN
				if (!LoadFile(filepath)) { print("X File Loader: Failed to open file\n"); return 1; }
				print("X File Loader : Counting objects\n", _filename);
				//SKIP HEADER
				for (UINT8 i = 0; i < 100; i++)ReadLine(buffer);
				//COUNT
				while (!file.eof())
				{
					ReadToken(token);
					if (!strcmp("FrameTransformMatrix", token)) meshcount++;
					if (!strcmp("Material", token)) materialcount++;
				}
				Rewind();
				//ALLOCATE
				mesh = new Mesh[meshcount];
				material = new Material[materialcount];
				meshread = 0;
				materialread = 0;

				//PARSE
				ReadLine(buffer);
				while (1)
				{
					ReadToken(token);
					if (file.eof())
					{
						CloseFile(); return 0;
					}
					else if (strcmp("template", token) == 0)
					{
						if (Ptemplate()) { CloseFile(); return 1; }
					}
					else if (strcmp("Material", token) == 0)
					{
						print("X File Loader : Reading %d/%d materials\n", materialread, materialcount);
						if (PMaterial()) { CloseFile(); return 1; }
					}
					else if (strcmp("Frame", token) == 0)
					{
						print("X File Loader : Reading %d/%d geometries\n", meshread, meshcount);
						if (PFrame()) { CloseFile(); return 1; }
					}
					else if (strcmp("AnimationSet", token) == 0)
					{
						print("X File Loader : Reading animation data\n");
						if (PAnimationSet()) { CloseFile(); return 1; }
					}
					else
					{
						CloseFile(); return 1;
					}
				}
				CloseFile();
				return 0;
			}
			xFile()
			{
				materialcount = 0;
				meshcount = 0;
				material = 0;
				mesh = 0;
				meshread = 0;
				materialread = 0;
			}
			~xFile()
			{
				delete[] mesh;
				delete[] material;
				materialcount = 0;
				meshcount = 0;
				material = 0;
				mesh = 0;
				meshread = 0;
				materialread = 0;
			}
		}*xfile = new xFile;
		if (xfile->LoadX(filepath, _animationlength))return 1;

		strcpy_s(name, _objectname);
		animationkeycount = _animationlength;

		materialcount = xfile->materialcount;		
		material = new Material[materialcount]();
		for (UINT32 m = 0; m < materialcount; m++)
		{
			strcpy_s(material[m].name, xfile->material[m].name);
			strcpy_s(material[m].map, xfile->material[m].map);
			material[m].diffuse = xfile->material[m].diffuse;
			material[m].specular = xfile->material[m].specular;
			material[m].specularpower = xfile->material[m].specularpower;
			material[m].textured = xfile->material[m].textured;		

			strcpy_s(filepath, OBJECTPATH);
			strcat_s(filepath, (material[m].map));
			if (material[m].textured)
				if (graphics->TextureCreate(&material[m].texture, filepath, R8G8B8A8_UNORM, CONSTANT, 0))return 1;
			if (graphics->ConstantBufferCreate(&material[m].materialbuffer, sizeof(FLOAT) * 12, &material[m], CONSTANT)) return 1;
		}

		meshcount = xfile->meshcount;
		mesh = new Mesh[meshcount]();
		for (UINT32 m = 0; m < meshcount; m++)
		{
			strcpy_s(mesh[m].name, xfile->mesh[m].name);	
			if(xfile->mesh[m].parent[0])
				for (UINT32 mp = 0; mp < meshcount; mp++)
					if (strcmp(xfile->mesh[m].parent, xfile->mesh[mp].name) == 0)
					{
						strcpy_s(mesh[m].parentname, xfile->mesh[mp].name);
						mesh[m].parent = &mesh[mp];
						mesh[m].parentindex = mp;
						break;
					}
			mesh[m].frametransformation = xfile->mesh[m].frametransformation;			
			
			mesh[m].animationkey = new Matrix[animationkeycount];
			memcpy(mesh[m].animationkey, xfile->mesh[m].keymatrix, sizeof(Matrix)*animationkeycount);

			if (xfile->mesh[m].indexcount&&xfile->mesh[m].vertexcount)
			{
				mesh[m].indexcount = xfile->mesh[m].indexcount;
				mesh[m].index = new UINT32[mesh[m].indexcount];
				memcpy(mesh[m].index, xfile->mesh[m].index, sizeof(UINT32)*mesh[m].indexcount);
				if (graphics->IndexBufferCreate(&mesh[m].indexbuffer, mesh[m].indexcount, mesh[m].index, CONSTANT))return 1;
				
				mesh[m].vertexcount = xfile->mesh[m].vertexcount;
				mesh[m].vertex = new Mesh::Vertex[mesh[m].vertexcount];
				memcpy(mesh[m].vertex, xfile->mesh[m].vertex, sizeof(Mesh::Vertex)*mesh[m].vertexcount);
				if (graphics->BufferCreate(&mesh[m].vertexbuffer, sizeof(Mesh::Vertex), mesh[m].vertexcount, mesh[m].vertex, CONSTANT))return 1;

				mesh[m].bonecount = xfile->mesh[m].bonecount;
				mesh[m].bone = new Mesh::Bone[mesh[m].bonecount];
				if (mesh[m].bonecount)
				{
					FLOAT *weightbuffer = new FLOAT[mesh[m].vertexcount * mesh[m].bonecount];
					for (UINT32 b = 0; b < mesh[m].bonecount; b++)
					{
 						strcpy_s(mesh[m].bone[b].name, xfile->mesh[m].bone[b].name);

						mesh[m].bone[b].weight = new FLOAT[mesh[m].vertexcount];
						memcpy(mesh[m].bone[b].weight, xfile->mesh[m].bone[b].weight, sizeof(FLOAT)*mesh[m].vertexcount);
						for (UINT32 v = 0; v < mesh[m].vertexcount; v++)
							weightbuffer[(b*mesh[m].vertexcount) + v] = mesh[m].bone[b].weight[v];
						
						for (UINT32 mb = 0; mb < meshcount; mb++)
							if (strcmp(xfile->mesh[m].bone[b].name, xfile->mesh[mb].name) == 0)
							{
								mesh[m].bone[b].index = mb;
								break;
							}
					}
					if (graphics->BufferCreate(&mesh[m].weightbuffer, sizeof(FLOAT), mesh[m].vertexcount* mesh[m].bonecount, weightbuffer, CONSTANT))return 1;
					delete weightbuffer;

					mesh[m].boneworld = new FLOAT[mesh[m].bonecount * 16];
					if (graphics->ConstantBufferCreate(&mesh[m].boneworldbuffer, sizeof(FLOAT)*(mesh[m].bonecount * 16), mesh[m].boneworld, VARIABLE)) return 1;					
				}

				mesh[m].data = new FLOAT[4];
				mesh[m].data[0] = (FLOAT)mesh[m].vertexbuffer->count;
				mesh[m].data[1] = (FLOAT)mesh[m].bonecount;
				if (graphics->ConstantBufferCreate(&mesh[m].databuffer, sizeof(FLOAT) * 4, mesh[m].data, CONSTANT)) return 1;

				mesh[m].materialindex = xfile->mesh[m].matid;

				if(graphics->ConstantBufferCreate(&mesh[m].worldbuffer, sizeof(FLOAT) * 16, &mesh[m].world, VARIABLE)) return 1;
			}			
		}
		if (graphics->ConstantBufferCreate(&worldbuffer, sizeof(FLOAT) * 16, &world, VARIABLE)) return 1;

		scale = Matrix(4, 4); scale.Identity();

		collisionspherecount = 0;
		collisionsphere = 0;

		mass = _mass;
		momentofinertia = _momentofinertia;
		position = Matrix(4, 4); position.Identity();
		rotation = Matrix(4, 4); rotation.Identity();
		velocity = float3(0, 0, 0);
		angularvelocity = float3(0, 0, 0);
		restitution = _restitution;
		friction = _friction;
		drag = _drag;

		delete xfile;
		return 0;
	}
	UINT8			   Load(Graphics *_graphics,char *_objectname)
	{
		graphics = _graphics;
		char filepath[BUFFERSIZE * 2];
		strcpy_s(filepath, OBJECTPATH);
		strcat_s(filepath, _objectname);
		strcat_s(filepath, ".object");

		{
			File file;
			if (file.Open(filepath))return 1;

			file.Read(name, sizeof(char)*BUFFERSIZE);
			file.Read(&animationkeycount, sizeof(UINT32));
			file.Read(&materialcount, sizeof(UINT32));
			file.Read(&meshcount, sizeof(UINT32));
			file.Read(&scale, sizeof(float3));

			material = new Material[materialcount];
			for (UINT8 m = 0; m < materialcount; m++)
			{
				file.Read(&material[m].diffuse, sizeof(float4));
				file.Read(&material[m].specular, sizeof(float4));
				file.Read(&material[m].specularpower, sizeof(float));
				file.Read(&material[m].textured, sizeof(float));
				file.Read(material[m].name, sizeof(char)*BUFFERSIZE);
				file.Read(material[m].map, sizeof(char)*BUFFERSIZE);
			}
			mesh = new Mesh[meshcount];
			for (UINT8 m = 0; m < meshcount; m++)
			{
				file.Read(mesh[m].name, sizeof(char)*BUFFERSIZE);

				file.Read(mesh[m].parentname, sizeof(char)*BUFFERSIZE);
				file.Read(&mesh[m].parentindex, sizeof(UINT32));
				if(mesh[m].parentname[0])
					mesh[m].parent = &mesh[mesh[m].parentindex];

				file.Read(&mesh[m].frametransformation, sizeof(Matrix));

				mesh[m].animationkey = new Matrix[animationkeycount];
				file.Read(mesh[m].animationkey, sizeof(Matrix)*animationkeycount);
				
				file.Read(&mesh[m].indexcount, sizeof(UINT32));
				mesh[m].index = new UINT32[mesh[m].indexcount];
				file.Read(mesh[m].index, sizeof(UINT32)*mesh[m].indexcount);
				
				file.Read(&mesh[m].vertexcount, sizeof(UINT32));
				mesh[m].vertex = new Mesh::Vertex[mesh[m].vertexcount];
				file.Read(mesh[m].vertex, sizeof(Mesh::Vertex)*mesh[m].vertexcount);
				
				file.Read(&mesh[m].bonecount, sizeof(UINT32));
				mesh[m].bone = new Mesh::Bone[mesh[m].bonecount];
				for (UINT32 b = 0; b < mesh[m].bonecount; b++)
				{
					file.Read(mesh[m].bone[b].name, sizeof(char)*BUFFERSIZE);
					file.Read(&mesh[m].bone[b].index, sizeof(UINT32));
					mesh[m].bone[b].weight = new FLOAT[mesh[m].vertexcount];
					file.Read(mesh[m].bone[b].weight, sizeof(FLOAT)*mesh[m].vertexcount);
				}
				file.Read(&mesh[m].materialindex, sizeof(UINT32));
			}
			file.Read(&scale, sizeof(Matrix));

			file.Read(&collisionspherecount, sizeof(UINT32));
			collisionsphere = new CollisionSphere[collisionspherecount];
			for (UINT32 s = 0; s < collisionspherecount; s++)
				file.Read(&collisionsphere[s], sizeof(CollisionSphere));
			file.Read(&mass, sizeof(float));
			file.Read(&momentofinertia, sizeof(float));
			file.Read(&restitution, sizeof(float));
			file.Read(&friction, sizeof(float));
			file.Read(&drag, sizeof(float));
			file.Read(&position, sizeof(Matrix));
			file.Read(&rotation, sizeof(Matrix));
			file.Read(&velocity, sizeof(float3));
			file.Read(&angularvelocity, sizeof(float3));

			file.Close();
		}

		for (UINT32 m = 0; m < materialcount; m++)
		{
			strcpy_s(filepath, OBJECTPATH);
			strcat_s(filepath, material[m].map);
			if (material[m].textured)
				if (graphics->TextureCreate(&material[m].texture, filepath, R8G8B8A8_UNORM, CONSTANT, 0))return 1;
			if (graphics->ConstantBufferCreate(&material[m].materialbuffer, sizeof(FLOAT) * 12, &material[m], CONSTANT)) return 1;
		}
		for (UINT32 m = 0; m < meshcount; m++)
			if (mesh[m].indexcount&&mesh[m].vertexcount)
			{
				if (graphics->IndexBufferCreate(&mesh[m].indexbuffer, mesh[m].indexcount, mesh[m].index, CONSTANT))return 1;
				if (graphics->BufferCreate(&mesh[m].vertexbuffer, sizeof(Mesh::Vertex), mesh[m].vertexcount, mesh[m].vertex, CONSTANT))return 1;

				if (mesh[m].bonecount)
				{
					FLOAT *weightbuffer = new FLOAT[mesh[m].vertexcount * mesh[m].bonecount];
					for (UINT32 b = 0; b < mesh[m].bonecount; b++)
					{
						for (UINT32 v = 0; v < mesh[m].vertexcount; v++)
							weightbuffer[(b*mesh[m].vertexcount) + v] = mesh[m].bone[b].weight[v];
					}
					if (graphics->BufferCreate(&mesh[m].weightbuffer, sizeof(FLOAT), mesh[m].vertexcount* mesh[m].bonecount, weightbuffer, CONSTANT))return 1;
					delete weightbuffer;

					mesh[m].boneworld = new FLOAT[mesh[m].bonecount * 16];
					if (graphics->ConstantBufferCreate(&mesh[m].boneworldbuffer, sizeof(FLOAT)*(mesh[m].bonecount * 16), mesh[m].boneworld, VARIABLE)) return 1;
				}

				mesh[m].data = new FLOAT[4];
				mesh[m].data[0] = (FLOAT)mesh[m].vertexbuffer->count;
				mesh[m].data[1] = (FLOAT)mesh[m].bonecount;
				if (graphics->ConstantBufferCreate(&mesh[m].databuffer, sizeof(FLOAT) * 4, mesh[m].data, CONSTANT)) return 1;

				if (graphics->ConstantBufferCreate(&mesh[m].worldbuffer, sizeof(FLOAT) * 16, &mesh[m].world, VARIABLE)) return 1;
			}
		if (graphics->ConstantBufferCreate(&worldbuffer, sizeof(FLOAT) * 16, &world, VARIABLE)) return 1;
		return 0;
	}
	UINT8			   Save()
	{
		char filepath[BUFFERSIZE * 2];
		strcpy_s(filepath, OBJECTPATH);
		strcat_s(filepath, name);
		strcat_s(filepath, ".object");

		File file;
		if (file.Create(filepath))return 1;
		if (file.Open(filepath))return 1;

		file.Write(name, sizeof(char)*BUFFERSIZE);
		file.Write(&animationkeycount, sizeof(UINT32));
		file.Write(&materialcount, sizeof(UINT32));
		file.Write(&meshcount, sizeof(UINT32));
		file.Write(&scale, sizeof(float3));
		
		for (UINT32 m = 0; m < materialcount; m++)
		{			
			file.Write(&material[m].diffuse, sizeof(float4));
			file.Write(&material[m].specular, sizeof(float4));
			file.Write(&material[m].specularpower, sizeof(float));			
			file.Write(&material[m].textured, sizeof(float));
			file.Write(material[m].name, sizeof(char)*BUFFERSIZE);
			file.Write(material[m].map, sizeof(char)*BUFFERSIZE);
		}
		for (UINT32 m = 0; m < meshcount; m++)
		{
			file.Write(mesh[m].name, sizeof(char)*BUFFERSIZE);

			file.Write(mesh[m].parentname, sizeof(char)*BUFFERSIZE);
			file.Write(&mesh[m].parentindex, sizeof(UINT32));

			file.Write(&mesh[m].frametransformation, sizeof(Matrix));

			file.Write(mesh[m].animationkey, sizeof(Matrix)*animationkeycount);

			file.Write(&mesh[m].indexcount, sizeof(UINT32));
			file.Write(mesh[m].index, sizeof(UINT32)*mesh[m].indexcount);

			file.Write(&mesh[m].vertexcount, sizeof(UINT32));
			file.Write(mesh[m].vertex, sizeof(Mesh::Vertex)*mesh[m].vertexcount);

			file.Write(&mesh[m].bonecount, sizeof(UINT32));
			for (UINT32 b = 0; b < mesh[m].bonecount; b++)
			{
				file.Write(mesh[m].bone[b].name, sizeof(char)*BUFFERSIZE);
				file.Write(&mesh[m].bone[b].index, sizeof(UINT32));
				file.Write(mesh[m].bone[b].weight, sizeof(FLOAT)*mesh[m].vertexcount);
			}			
			file.Write(&mesh[m].materialindex, sizeof(UINT32));
		}
		file.Write(&scale, sizeof(Matrix));

		file.Write(&collisionspherecount, sizeof(UINT32));
		for (UINT32 s = 0; s < collisionspherecount; s++)
			file.Write(&collisionsphere[s], sizeof(CollisionSphere));
		file.Write(&mass, sizeof(float));
		file.Write(&momentofinertia, sizeof(float));
		file.Write(&restitution, sizeof(float));
		file.Write(&friction, sizeof(float));
		file.Write(&drag, sizeof(float));
		file.Write(&position, sizeof(Matrix));
		file.Write(&rotation, sizeof(Matrix));
		file.Write(&velocity, sizeof(float3));
		file.Write(&angularvelocity, sizeof(float3));

		file.Close();
		return 0;
	}
	void __forceinline PlayAnimation(float speed, UINT32 start, UINT32 end, BOOL loop)
	{
		counter += ((float)100 / (float)frequency)*speed;
		if (counter<(float)start || counter>(float)end)
			if (speed > 0)
			{
				if (loop)
					counter = (float)start;
				else
					counter = (float)end;
			}
			else if (speed < 0)
			{
				if (loop)
					counter = (float)end;
				else
					counter = (float)start;
			}
		for (UINT32 i = 0; i<meshcount; i++)
			mesh[i].key = (UINT32)(counter);
	}
	void __forceinline Update(UINT32 id)
	{
		if (!mesh[id].indexcount)return;
		Matrix computationmatrix(4, 4);

		computationmatrix = mesh[id].animationkey[mesh[id].key];
		computationmatrix.Transpose();
		if (!mesh[id].worldlock)
		{
			mesh[id].worldlock = true;
			mesh[id].world = computationmatrix;
			mesh[id].worldlock = false;
		}

		computationmatrix.rows = computationmatrix.columns = 4;
		computationmatrix.Identity();
		computationmatrix = computationmatrix * scale;
		computationmatrix = computationmatrix * rotation;
		computationmatrix = computationmatrix * position;
		computationmatrix.Transpose();
		if (!worldlock)
		{
			worldlock = true;
			world = computationmatrix;
			worldlock = false;
		}

		if (mesh[id].bonecount)
			for (UINT8 b = 0; b < mesh[id].bonecount; b++)
			{
				struct Functions
				{
					Matrix ParentFrameTransformInverse(Mesh *_mesh)
					{
						if (_mesh->parent)
							return (ParentFrameTransformInverse(_mesh->parent))*(!_mesh->frametransformation);
						return !_mesh->frametransformation;
					}
					Matrix BoneTransformation(Mesh *_mesh)
					{
						Matrix result;
						result = ParentFrameTransformInverse(_mesh);
						Mesh *__mesh = _mesh;
						do
						{
							result = result*__mesh->animationkey[__mesh->key];
							__mesh = __mesh->parent;
						} while (__mesh);
						return result;
					}
				}bonetransformation;
				Matrix boneworldbuffer;
				boneworldbuffer = bonetransformation.BoneTransformation(&mesh[mesh[id].bone[b].index]);
				boneworldbuffer.Transpose();
				if (!mesh[id].boneworldlock)
				{
					mesh[id].boneworldlock = true;
					memcpy((mesh[id].boneworld + (16 * b)), &boneworldbuffer, sizeof(FLOAT) * 16);
					mesh[id].boneworldlock = false;
				}
			}
	}
	void __forceinline Update()
	{
		for (unsigned int i = 0; i < meshcount; i++)
			Update(i);
	}
	void __forceinline Draw(UINT32 id)
	{
		if (!mesh[id].indexcount)return;

		if (!mesh[id].worldlock)
		{
			mesh[id].worldlock = true;
			graphics->ConstantBufferUpdate(mesh[id].worldbuffer);
			mesh[id].worldlock = false;
		}
		if (!worldlock)
		{
			worldlock = true;
			graphics->ConstantBufferUpdate(worldbuffer);
			worldlock = false;
		}
		graphics->ConstantBufferSet(mesh[id].databuffer, 0, 1, 0, 0, 0, 0, 0);
		graphics->ConstantBufferSet(mesh[id].worldbuffer, 1, 1, 0, 0, 0, 0, 0);
		graphics->ConstantBufferSet(worldbuffer, 2, 1, 0, 0, 0, 0, 0);
		if (mesh[id].bonecount)
		{
			if (!mesh[id].boneworldlock)
			{
				mesh[id].boneworldlock = true;
				graphics->ConstantBufferUpdate(mesh[id].boneworldbuffer);
				mesh[id].boneworldlock = false;
			}
			graphics->ConstantBufferSet(mesh[id].boneworldbuffer, 3, 1, 0, 0, 0, 0, 0);
			graphics->BufferSetShaderResouceView(mesh[id].weightbuffer, 1, 1, 0, 0, 0, 0, 0);
		}
		graphics->ConstantBufferSet(material[mesh[id].materialindex].materialbuffer, 0, 0, 0, 0, 0, 1, 0);

		if (material[mesh[id].materialindex].textured)
			graphics->TextureSetShaderResouceView(material[mesh[id].materialindex].texture, 0, 0, 0, 0, 0, 1, 0);
		graphics->IndexBufferSet(mesh[id].indexbuffer);
		graphics->BufferSetShaderResouceView(mesh[id].vertexbuffer, 0, 1, 0, 0, 0, 0, 0);
		graphics->DrawIndexed(mesh[id].indexbuffer->count);
	}
	void __forceinline Draw()
	{
		for (unsigned int i = 0; i < meshcount; i++)
			Draw(i);
	}
	void __forceinline DrawObjectInstanced(UINT32 id, UINT32 _instancecount)
	{
		//Need Fix
		graphics->DrawIndexedInstanced(mesh[id].indexbuffer->count, _instancecount);
	}
	void __forceinline DrawObjectInstanced(UINT32 _instancecount)
	{
		for (unsigned int i = 0; i <meshcount; i++)
			DrawObjectInstanced(_instancecount, i);
	}
	Object()
	{
		ZeroMemory(this, sizeof(Object));
	}
	~Object()
	{
		delete[] collisionsphere;
		delete[] mesh;
		delete[] material;
		if (worldbuffer)delete worldbuffer;
		ZeroMemory(this, sizeof(Object));
	}
};