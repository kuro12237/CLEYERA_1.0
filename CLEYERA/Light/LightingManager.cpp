#include "LightingManager.h"

LightingManager* LightingManager::GetInstance()
{
    static LightingManager instance;
    return &instance;
}

void LightingManager::Initialize()
{
    //Buffer生成
    LightingManager::GetInstance()->buffer_ = CreateResources::CreateBufferResource(sizeof(uint32_t));
    LightingManager::GetInstance()->structureBuffer_ = CreateResources::CreateBufferResource(sizeof(PointLight_param) * LightingManager::GetInstance()->NumLight_);

    //descripter生成
    LightingManager::GetInstance()->dsvHandle_ = DescriptorManager::CreateInstancingSRV(
        LightingManager::GetInstance()->NumLight_,
        LightingManager::GetInstance()->structureBuffer_,
        sizeof(PointLight_param)
    );
}

void LightingManager::AddList(Light* instance)
{
    LightingManager::GetInstance()->LightDatas_.push_back(instance);
    LightingManager::GetInstance()->NowTotalLightData_++;
}
list<Light*> LightingManager::GetLightData()
{
    list<Light*>result =LightingManager::GetInstance()->LightDatas_;
    LightingManager::GetInstance()->LightDatas_.clear();
    return result;
}

void LightingManager::TransfarBuffers()
{
    TransfarBuffer();
    TransfarStructureBuffer();
}

void LightingManager::TransfarBuffer()
{
    uint32_t* TotalLight;
    LightingManager::GetInstance()->buffer_->Map(0, nullptr, reinterpret_cast<void**>(&TotalLight));
    *TotalLight = LightingManager::GetInstance()->NowTotalLightData_;
    LightingManager::GetInstance()->buffer_->Unmap(0, nullptr);
}

void LightingManager::TransfarStructureBuffer()
{
    PointLight_param* param;
    LightingManager::GetInstance()->structureBuffer_->Map(0, nullptr, reinterpret_cast<void**>(&param));

    uint32_t count = 0;
    for (Light* instance : LightingManager::GetInstance()->LightDatas_)
    {
        param[count].color = instance->color_;
        param[count].decay = instance->decay_;
        param[count].intencity = instance->intencity_;
        param[count].position = instance->position_;
        param[count].radious = instance->radious_;
        count++;
        //上限に達したら
        if (count==LightingManager::GetInstance()->NumLight_)
        {
            break;
        }
    }
    LightingManager::GetInstance()->structureBuffer_->Unmap(0, nullptr);
}
