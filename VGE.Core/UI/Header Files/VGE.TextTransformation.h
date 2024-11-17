// Implementation of the VGE_TextTransformation class
#pragma once
#ifndef VGE_TEXTTRANSFORMATION_H
#define VGE_TEXTTRANSFORMATION_H

#include <string>

class VGE_TextTransformation {
public:
	VGE_TextTransformation();
	~VGE_TextTransformation();
	std::string TransformText(const std::string& text);
};

#endif // VGE_TEXTTRANSFORMATION_H