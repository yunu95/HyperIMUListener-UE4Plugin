// Fill out your copyright notice in the Description page of Project Settings.


#include "IMUVector3d.h"

IMUVector3d::IMUVector3d()
{
    x = y = z = 0;
}

IMUVector3d::~IMUVector3d()
{
}
IMUVector3d::operator FVector() {
    return FVector(x, y, z);
}
