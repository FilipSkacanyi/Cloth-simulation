#include "Texture.h"
#include "WICTextureLoader.h"


Texture::Texture()
{
	m_texture = nullptr;
}


Texture::~Texture()
{
	// Release the texture resource.
	if (m_texture)
	{
		m_texture->Release();
		m_texture = 0;
	}

}

bool Texture::Initialize(ID3D11Device * device, WCHAR * filename)
{
	HRESULT result;

	result = DirectX::CreateWICTextureFromFile(device, L"fabric.jpg", (ID3D11Resource**)&m_texture2D, &m_texture);

	if (FAILED(result))
	{
		return false;
	}

	return true;
}

ID3D11ShaderResourceView * Texture::getTexture()
{
	return m_texture;
}
