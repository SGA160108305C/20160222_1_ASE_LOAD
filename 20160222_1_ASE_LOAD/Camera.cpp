#include "stdafx.h"
#include "Camera.h"


Camera::Camera()
{
	prevMousePos.x = 0;
	prevMousePos.y = 0;
}

Camera::~Camera()
{
}

void Camera::Initialize(D3DXVECTOR3* target /*= nullptr*/)
{
	lookTarget = target;

	D3DXMATRIXA16 matView;
	D3DXMATRIXA16 matProjection;
	D3DXMatrixLookAtLH(&matView, &eyePosition, &lookAt, &upVector);
	GameManager::GetDevice()->SetTransform(D3DTS_VIEW, &matView);

	D3DXMatrixPerspectiveFovLH(&matProjection, D3DX_PI * 0.25f, (float)RESOLUTION_X / (float)RESOLUTION_Y, 1.0f, 10000.0f);
	GameManager::GetDevice()->SetTransform(D3DTS_PROJECTION, &matProjection);

}

void Camera::Destroy()
{
}

void Camera::Update()
{
	D3DXMATRIXA16 matRotationX, matRotationY;
	D3DXMATRIXA16 matRotation;
	D3DXMatrixRotationX(&matRotationX, camRotX);
	D3DXMatrixRotationY(&matRotationY, camRotY);
	matRotation = matRotationX * matRotationY;

	eyePosition = D3DXVECTOR3(0, 0, -camDistance);
	D3DXVec3TransformCoord(&eyePosition, &eyePosition, &matRotation);

	if ( lookTarget )
	{
		lookAt = (*lookTarget);
		eyePosition = (*lookTarget) + eyePosition;
	}

	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &eyePosition, &lookAt, &upVector);
	GameManager::GetDevice()->SetTransform(D3DTS_VIEW, &matView);

}

LRESULT Camera::CameraInputProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch ( message )
	{
		case WM_RBUTTONDOWN:
			isDrag = true;
			prevMousePos.x = GET_X_LPARAM(lParam);
			prevMousePos.y = GET_Y_LPARAM(lParam);
			break;
		case WM_RBUTTONUP:
			isDrag = false;
			break;
		case WM_MOUSEMOVE:
			{
				if ( isDrag )
				{
					POINT currentMousePos;
					currentMousePos.x = GET_X_LPARAM(lParam);
					currentMousePos.y = GET_Y_LPARAM(lParam);
					float fDeltaX = (float)(currentMousePos.x - prevMousePos.x);
					float fDeltaY = (float)(currentMousePos.y - prevMousePos.y);

					camRotX += ( fDeltaY / 100.f );
					camRotY += ( fDeltaX / 100.f );

					if ( camRotX < -D3DX_PI / 0.5f + 0.0001f )
						camRotX = -D3DX_PI / 0.5f + 0.0001f;

					if ( camRotX > D3DX_PI / 0.5f - 0.0001f )
						camRotX = D3DX_PI / 0.5f - 0.0001f;

					prevMousePos = currentMousePos;
				}
			}
			break;
		case WM_MOUSEWHEEL:
			camDistance += -GET_WHEEL_DELTA_WPARAM(wParam) / 100.f;
			if ( camDistance < 1.0f )
				camDistance = 1.0f;
			break;
	}

	return 0;
}
