#pragma once
#include <string>
#include <d3d11.h>

class Texture
{
public:
	Texture();
	~Texture();



	bool Initialize(ID3D11Device*, std::wstring);

	ID3D11ShaderResourceView* getTexture();

private:
	ID3D11ShaderResourceView * m_texture;
	ID3D11Texture2D* m_texture2D = nullptr;
};

