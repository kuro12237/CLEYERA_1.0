#include "Light.h"

void Light::Initialize()
{
	CreateBuffer();

}

void Light::TransfarData()
{
	buffer_->Map(0, nullptr, reinterpret_cast<void**>(&data_));
	data_->color = color_;
	data_->intencity = intencity_;
	data_->position = position_;
	data_->decay = decay_;
	data_->radious = radious_;
	buffer_->Unmap(0, nullptr);
}

void Light::CreateBuffer()
{
	buffer_ = CreateResources::CreateBufferResource(sizeof(PointLight_param));
}
