#include "Camera.h"
#include "MathHelper.h"

namespace Dementia{


	Camera::Camera()
		: m_position(XMVectorSet(0.0f, 0.0f, -15.0f, 0.0f)), 
		  mRight(XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f)),
		  mUp(XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f)),
		  mLook(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f))
	{
		SetLens(0.25f*MathHelper::Pi, 1.0f, 1.0f, 1000.0f);
	}

	Camera::~Camera()
	{
	}

	XMVECTOR Camera::GetPosition() const
	{
		return m_position;
	}

	void Camera::SetPosition(XMVECTOR position)
	{
		m_position = position;
	}

	XMVECTOR Camera::GetRight()const
	{
		return mRight;
	}

	XMVECTOR Camera::GetUp()const
	{
		return mUp;
	}

	XMVECTOR Camera::GetLook() const
	{
		return mLook;
	}

	float Camera::GetNearZ()const
	{
		return mNearZ;
	}

	float Camera::GetFarZ()const
	{
		return mFarZ;
	}

	float Camera::GetAspect()const
	{
		return mAspect;
	}

	float Camera::GetFovY()const
	{
		return mFovY;
	}

	float Camera::GetFovX()const
	{
		float halfWidth = 0.5f*GetNearWindowWidth();
		return 2.0f*atan(halfWidth / mNearZ);
	}

	float Camera::GetNearWindowWidth()const
	{
		return mAspect * mNearWindowHeight;
	}

	float Camera::GetNearWindowHeight()const
	{
		return mNearWindowHeight;
	}

	float Camera::GetFarWindowWidth()const
	{
		return mAspect * mFarWindowHeight;
	}

	float Camera::GetFarWindowHeight()const
	{
		return mFarWindowHeight;
	}

	void Camera::SetLens(float fovY, float aspect, float zn, float zf)
	{
		// cache properties
		mFovY = fovY;
		mAspect = aspect;
		mNearZ = zn;
		mFarZ = zf;

		mNearWindowHeight = 2.0f * mNearZ * tanf( 0.5f*mFovY );
		mFarWindowHeight  = 2.0f * mFarZ * tanf( 0.5f*mFovY );

		mProj = XMMatrixPerspectiveFovLH(mFovY, mAspect, mNearZ, mFarZ);
	}

	void Camera::LookAt(FXMVECTOR pos, FXMVECTOR target, FXMVECTOR worldUp)
	{
		m_position = pos;
		mLook = XMVector3Normalize(XMVectorSubtract(target, pos));
		mRight = XMVector3Normalize(XMVector3Cross(worldUp, mLook));
		mUp = XMVector3Cross(mLook, mRight);

	}


	XMMATRIX Camera::View()const
	{
		return mView;
	}

	XMMATRIX Camera::Proj()const
	{
		return mProj;
	}

	XMMATRIX Camera::ViewProj()const
	{
		return XMMatrixMultiply(View(), Proj());
	}

	void Camera::Strafe(float d)
	{
		XMVECTOR s = XMVectorReplicate(d);
		m_position += s*mRight;
	}

	void Camera::Walk(float d)
	{
		XMVECTOR s = XMVectorReplicate(d);
		m_position += s*mLook;
	}

	void Camera::Pitch(float angle)
	{
		// Rotate up and look vector about the right vector.
		XMMATRIX R = XMMatrixRotationAxis(mRight, angle);

		mUp = XMVector3TransformNormal(mUp, R);
		mLook = XMVector3TransformNormal(mLook, R);
	}

	void Camera::RotateY(float angle)
	{
		// Rotate the basis vectors about the world y-axis.

		XMMATRIX R = XMMatrixRotationY(angle);

		mRight = XMVector3TransformNormal(mRight, R);
		mUp = XMVector3TransformNormal(mUp, R);
		mLook = XMVector3TransformNormal(mLook, R);
	}

	void Camera::UpdateViewMatrix()
	{
		XMVECTOR R = mRight;
		XMVECTOR U = mUp;
		XMVECTOR L = mLook;
		XMVECTOR P = m_position;

		// Keep camera's axes orthogonal to each other and of unit length.
		L = XMVector3Normalize(L);
		U = XMVector3Normalize(XMVector3Cross(L, R));

		// U, L already ortho-normal, so no need to normalize cross product.
		R = XMVector3Cross(U, L); 

		// Fill in the view matrix entries.
		float x = -XMVectorGetX(XMVector3Dot(P, R));
		float y = -XMVectorGetX(XMVector3Dot(P, U));
		float z = -XMVectorGetX(XMVector3Dot(P, L));

		mRight = R;
		mUp = U;
		mLook = L;

		XMFLOAT4 right;
		XMFLOAT4 up;
		XMFLOAT4 look;

		XMStoreFloat4(&right, mRight);
		XMStoreFloat4(&up, mUp);
		XMStoreFloat4(&look, mLook);

		XMFLOAT4X4 view = { right.x, up.x, look.x, 0.0f,
							right.y, up.y, look.y, 0.0f,
							right.z, up.z, look.z, 0.0f,
							x,		 y,	   z,      1.0f };

		mView = XMLoadFloat4x4(&view);
	}

}