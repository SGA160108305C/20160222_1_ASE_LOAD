#pragma once
#include "GameState.h"
#include "GameState_DX_Base.h"
#include "GameState_FVF.h"
#include "GameState_Texture.h"
#include "GameState_HierarchyAnimation.h"
#include "GameState_Light.h"
#include "GameState_OBJ_Load.h"
#include "GameState_Picking.h"
#include "GameState_VertexBuffer.h"
#include "GameState_ASE_Load.h"


enum GameStateType
{
	STATE_DIRECT_X_BASE = 0,	//기본 윈도우 프레임워크. DirectX초기화
	STATE_FVF,					//FVF, DrawPrimitive(D3D로 그리드와 박스 그리기)
	STATE_TEXTURE,				//텍스쳐 매핑 및 매니저, 디바이스 릴리즈(큐브맨만들기)
	STATE_HIERARCHY_ANIMATION,	//유사 애니메이션(하이라키 구조)
	STATE_LIGHT,				//조명과 머티리얼, 노멀 백터(조명 설치하기)
	STATE_OBJ_LOAD,				//OBJ파일로 모델그리기(다른 파일 열어봐서 툴별 차이도 확인)
	STATE_PICK_BASE,			//D3DXIntersectTri(피킹, 키보드이동)
	STATE_VERTEX_BUFFER,		//버텍스 버퍼	
	STAET_ASE_LOAD,				//ASE(로딩 및 애니메이션.쿼터니언과 오른손 좌표계(y,z, uv, 삼각형 감기는 순서)) - 3일
	STATE_ACTIONS,				//보간, 델리게이트
	STATE_COLLISION,			//충돌처리와 기본 메시 만들기
	STATE_PICK_MOUSE,			//마우스 피킹( 스크린 좌표 => 3D 좌표 )
	STATE_UI,					//UI 및 폰트 출력( bind도 )
	STATE_PATH_FIND,			//다익스트라 알고리즘, A*알고리즘 - 3일
	STATE_HEIGHTMAP,			//Height맵
	STATE_SKINNING,				//스키닝
	STATE_FRUSTUM_CULLING,		//프러스텀 컬링
	STATE_BLENDING,				//블랜딩
	STATE_PARTICLE,				//파티클
	STATE_SHADER,				//쉐이더
	STATE_THREAD,				//쓰레드
	NUM_OF_STATE
};

class GameStateManager
{
private:
	GameStateManager();
	GameStateManager(const GameStateManager& other);
	~GameStateManager();

public:
	static GameStateManager& Get()
	{
		static GameStateManager instance;
		return instance;
	}

	void Initialize();
	void Destroy();
	void Update();
	void Render();
	LRESULT InputProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	bool ChangeGameState(GameStateType state);

protected:
	GameStateType currentState = GameStateType::STATE_DIRECT_X_BASE;
	GameState* gameStates[GameStateType::NUM_OF_STATE];
};

