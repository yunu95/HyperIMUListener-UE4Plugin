// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#pragma pack(8)

#include "CoreMinimal.h"

/**
 * 
 */
class HYPERIMULISTENER_API IMUVector3d
{
public:
	IMUVector3d();
	~IMUVector3d();
    float x, y, z;
    operator FVector();
};
