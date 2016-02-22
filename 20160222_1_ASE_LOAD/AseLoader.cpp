#include "StdAfx.h"
#include "AseLoader.h"
#include "Asciitok.h"

AseLoader::AseLoader()
{
	ZeroMemory(token, sizeof(char) * 1024);
}

AseLoader::~AseLoader(void)
{
	int i = 0;
}

AseFrame* AseLoader::Load( char* filename )
{
	char fullPath[1024];
	strcpy_s(fullPath, ASE_DIRECTORY);
	strcat_s(fullPath, filename);

	fopen_s(&filePointer, fullPath, "r");
	if ( filePointer )
	{
		while ( true )
		{
			char* aseToken = GetToken();
			if ( aseToken == nullptr )
				break;
			if ( IsEqual(aseToken, ID_SCENE) )
			{
				SkipBlock();
			}
			else if ( IsEqual(aseToken, ID_MATERIAL_LIST) )
			{
				Process_MATERIAL_LIST();
			}
			else if ( IsEqual(aseToken, ID_GEOMETRY) )
			{
				AseFrame* frame = new AseFrame;
				if ( rootFrame == nullptr )
					rootFrame = frame;
				Process_GEOMOBJECT(frame);
			}
		}

		fclose(filePointer);
	}

	for ( auto iter = materialTextures.begin(); iter != materialTextures.end(); ++iter )
	{
		SAFE_RELEASE(*iter);
	}

	rootFrame->CalcOrigLocalTransform(nullptr);

	return rootFrame;
}

char* AseLoader::GetToken()
{
	int readCount = 0;
	bool isQuote = false;

	while(true)
	{
		char c = fgetc(filePointer);
		
		if (feof(filePointer)) break;
		
		if( c == '\"' )
		{
			if (isQuote)
			{
				break;
			}

			isQuote = true;
			continue;
		}

		if(!isQuote && IsWhite(c))
		{
			if ( readCount == 0 )
				continue;
			break;
		}

		token[readCount++] = c;
	} 

	if ( readCount == 0 )
		return nullptr;

	token[readCount] = '\0';

	return token;
}

float AseLoader::GetFloat()
{
	return (float)atof(GetToken());
}

int AseLoader::GetInteger()
{
	return atoi(GetToken());
}

bool AseLoader::IsWhite( char c )
{
	return c < 33;
}

bool AseLoader::IsEqual( char* s1, char* s2 )
{
	return strcmp(s1, s2) == 0;
}

void AseLoader::SkipBlock()
{
	int level = 0;
	do 
	{
		char* aseToken = GetToken();
		if (IsEqual(aseToken, "{"))
		{
			level++;
		}
		else if (IsEqual(aseToken, "}"))
		{
			level--;
		}
	} while ( level > 0 );
}

void AseLoader::Process_MATERIAL_LIST()
{
	int level = 0;
	do 
	{
		char* aseToken = GetToken();
		if (IsEqual(aseToken, "{"))
		{
			level++;
		}
		else if (IsEqual(aseToken, "}"))
		{
			level--;
		}
		else if (IsEqual(aseToken, ID_MATERIAL_COUNT))
		{
			materialTextures.resize(GetInteger());
		}
		else if (IsEqual(aseToken, ID_MATERIAL))
		{
			int mtRef = GetInteger();
			materialTextures[mtRef] = new MaterialTexture;
			Process_MATERIAL(materialTextures[mtRef]);
		}
	} while ( level > 0 );
}

void AseLoader::Process_MATERIAL(OUT MaterialTexture* mt)
{
	D3DMATERIAL9& material = mt->material;
	ZeroMemory(&material, sizeof(D3DMATERIAL9));

	int level = 0;
	do 
	{
		char* aseToken = GetToken();
		if (IsEqual(aseToken, "{"))
		{
			level++;
		}
		else if (IsEqual(aseToken, "}"))
		{
			level--;
		}
		else if (IsEqual(aseToken, ID_AMBIENT))
		{
			//
		}
		else if (IsEqual(aseToken, ID_DIFFUSE))
		{
			//
		}
		else if (IsEqual(aseToken, ID_SPECULAR))
		{
			//
		}
		else if (IsEqual(aseToken, ID_MAP_DIFFUSE))
		{
			Process_MAP_DIFFUSE(mt);
		}
	} while ( level > 0 );
}

void AseLoader::Process_MAP_DIFFUSE(OUT MaterialTexture* mt)
{
	int level = 0;
	do 
	{
		char* aseToken = GetToken();
		if (IsEqual(aseToken, "{"))
		{
			level++;
		}
		else if (IsEqual(aseToken, "}"))
		{
			level--;
		}
		else if (IsEqual(aseToken, ID_BITMAP))
		{
			//
		}
	} while (level > 0);
}

void AseLoader::Process_GEOMOBJECT(OUT AseFrame* frame)
{
	int level = 0;
	do 
	{
		char* aseToken = GetToken();
		if (IsEqual(aseToken, "{"))
		{
			level++;
		}
		else if (IsEqual(aseToken, "}"))
		{
			level--;
		}
		else if (IsEqual(aseToken, ID_NODE_TM))
		{
			Process_NODE_TM(frame);
		}
		else if (IsEqual(aseToken, ID_NODE_NAME))
		{		
			//
			std::string nodeName = GetToken();
			frame->SetNodeName(nodeName);
			mapFrame[nodeName] = frame;
		}
		else if (IsEqual(aseToken, ID_NODE_PARENT))
		{		
			//
			std::string parentName = GetToken();
			mapFrame[parentName]->AddChild(frame);
		}
		else if (IsEqual(aseToken, ID_MESH))
		{		
			Process_MESH(frame);
		}
		else if (IsEqual(aseToken, ID_MATERIAL_REF))
		{		
			//
		}
		else if (IsEqual(aseToken, ID_TM_ANIMATION))
		{		
			Process_TM_ANIMATION(frame);
		}
	} while (level > 0);
}

void AseLoader::Process_MESH(OUT AseFrame* frame)
{
	std::vector<D3DXVECTOR3> position;
	std::vector<D3DXVECTOR2> uv;
	std::vector<FVF_PositionNormalTexture>& vertexArray = frame->GetVertexArray();
	int level = 0;
	do 
	{
		char* aseToken = GetToken();
		if (IsEqual(aseToken, "{"))
		{
			level++;
		}
		else if (IsEqual(aseToken, "}"))
		{
			level--;
		}
		else if (IsEqual(aseToken, ID_MESH_NUMVERTEX))
		{		
			//
			position.resize(GetInteger());
		}
		else if (IsEqual(aseToken, ID_MESH_NUMFACES))
		{		
			//
		}
		else if (IsEqual(aseToken, ID_MESH_VERTEX_LIST))
		{		
			Process_MESH_VERTEX_LIST(position);
		}
		else if (IsEqual(aseToken, ID_MESH_FACE_LIST))
		{		
			Process_MESH_FACE_LIST(position, vertexArray);
		}
		else if (IsEqual(aseToken, ID_MESH_NUMTVERTEX))
		{		
			//
		}
		else if (IsEqual(aseToken, ID_MESH_TVERTLIST))
		{		
			Process_MESH_TVERTLIST(uv);
		}
		else if (IsEqual(aseToken, ID_MESH_TFACELIST))
		{
			Process_ID_MESH_TFACELIST(uv, vertexArray);
		}
		else if (IsEqual(aseToken, ID_MESH_NORMALS))
		{
			Process_MESH_NORMALS(vertexArray);
		}
		
	} while (level > 0);

	D3DXMATRIXA16& world = frame->GetWorldTransform();
	D3DXMATRIXA16 inverseWorld;
	D3DXMatrixInverse(&inverseWorld, 0, &world);
	for ( size_t i = 0; i < vertexArray.size(); ++i )
	{
		D3DXVec3TransformCoord(&vertexArray[i].pos, &vertexArray[i].pos, &inverseWorld);
		D3DXVec3TransformNormal(&vertexArray[i].normal, &vertexArray[i].normal, &inverseWorld);
	}
}

void AseLoader::Process_MESH_VERTEX_LIST( OUT std::vector<D3DXVECTOR3>& pos )
{
	int level = 0;
	do 
	{
		char* aseToken = GetToken();
		if (IsEqual(aseToken, "{"))
		{
			level++;
		}
		else if (IsEqual(aseToken, "}"))
		{
			level--;
		}
		else if (IsEqual(aseToken, ID_MESH_VERTEX))
		{		
			//
			int index = GetInteger();
			float x = GetFloat();
			float z = GetFloat();
			float y = GetFloat();

			pos[index] = D3DXVECTOR3(x, y, z);
		}
	} while (level > 0);
}

void AseLoader::Process_MESH_FACE_LIST(IN std::vector<D3DXVECTOR3>& pos, OUT std::vector<FVF_PositionNormalTexture>& vertex)
{
	int level = 0;
	do 
	{
		char* aseToken = GetToken();
		if (IsEqual(aseToken, "{"))
		{
			level++;
		}
		else if (IsEqual(aseToken, "}"))
		{
			level--;
		}
		else if (IsEqual(aseToken, ID_MESH_FACE))
		{		
			//
		}
	} while (level > 0);
}

void AseLoader::Process_MESH_TVERTLIST(OUT std::vector<D3DXVECTOR2>& uv)
{
	int level = 0;
	do 
	{
		char* aseToken = GetToken();
		if (IsEqual(aseToken, "{"))
		{
			level++;
		}
		else if (IsEqual(aseToken, "}"))
		{
			level--;
		}
		else if (IsEqual(aseToken, ID_MESH_TVERT))
		{		
			//
		}
	} while (level > 0);
}

void AseLoader::Process_ID_MESH_TFACELIST(IN std::vector<D3DXVECTOR2>& uv, OUT std::vector<FVF_PositionNormalTexture>& vertex)
{
	int level = 0;
	do 
	{
		char* aseToken = GetToken();
		if (IsEqual(aseToken, "{"))
		{
			level++;
		}
		else if (IsEqual(aseToken, "}"))
		{
			level--;
		}
		else if (IsEqual(aseToken, ID_MESH_TFACE))
		{		
			//
		}
	} while (level > 0);
}

void AseLoader::Process_MESH_NORMALS(OUT std::vector<FVF_PositionNormalTexture>& vertex)
{
	int level = 0;
	int index = 0;
	int modIndex[] = {0, 2, 1};
	int count = 0;
	do 
	{
		char* aseToken = GetToken();
		if (IsEqual(aseToken, "{"))
		{
			level++;
		}
		else if (IsEqual(aseToken, "}"))
		{
			level--;
		}
		else if (IsEqual(aseToken, ID_MESH_FACENORMAL))
		{		
			//
		}
		else if (IsEqual(aseToken, ID_MESH_VERTEXNORMAL))
		{
			//
		}
	} while (level > 0);
}

void AseLoader::Process_NODE_TM(OUT AseFrame* frame)
{
	D3DXMATRIXA16& world = frame->GetWorldTransform();
	D3DXMatrixIdentity(&world);

	int level = 0;
	do 
	{
		char* aseToken = GetToken();
		if (IsEqual(aseToken, "{"))
		{
			level++;
		}
		else if (IsEqual(aseToken, "}"))
		{
			level--;
		}
		else if (IsEqual(aseToken, ID_TM_ROW0))
		{		
			//
		}
		else if (IsEqual(aseToken, ID_TM_ROW1))
		{		
			//
		}
		else if (IsEqual(aseToken, ID_TM_ROW2))
		{		
			//
		}
		else if (IsEqual(aseToken, ID_TM_ROW3))
		{		
			//
		}
	} while (level > 0);

}

void AseLoader::Process_TM_ANIMATION(OUT AseFrame* frame)
{
	int level = 0;
	do 
	{
		char* aseToken = GetToken();
		if (IsEqual(aseToken, "{"))
		{
			level++;
		}
		else if (IsEqual(aseToken, "}"))
		{
			level--;
		}
		else if (IsEqual(aseToken, ID_POS_TRACK))
		{
			Process_POS_TRACK(frame);
		}
		else if (IsEqual(aseToken, ID_ROT_TRACK))
		{
			Process_ROT_TRACK(frame);
		}
	} while (level > 0);

}

void AseLoader::Process_POS_TRACK(OUT AseFrame* frame)
{
	std::vector<PositionSample>& posTrack = frame->GetPosTrack();
	int level = 0;
	do 
	{
		char* aseToken = GetToken();
		if (IsEqual(aseToken, "{"))
		{
			level++;
		}
		else if (IsEqual(aseToken, "}"))
		{
			level--;
		}
		else if (IsEqual(aseToken, ID_POS_SAMPLE))
		{
			//
		}
	} while (level > 0);

}

void AseLoader::Process_ROT_TRACK(OUT AseFrame* frame)
{
	std::vector<RotateSample>& rotTrack = frame->GetRotTrack();
	int level = 0;
	do 
	{
		char* aseToken = GetToken();
		if (IsEqual(aseToken, "{"))
		{
			level++;
		}
		else if (IsEqual(aseToken, "}"))
		{
			level--;
		}
		else if (IsEqual(aseToken, ID_ROT_SAMPLE))
		{		
			//
		}
	} while (level > 0);
}



