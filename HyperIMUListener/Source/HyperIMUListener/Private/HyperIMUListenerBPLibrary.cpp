// Copyright Epic Games, Inc. All Rights Reserved.

#include "HyperIMUListenerBPLibrary.h"
#include "HyperIMUListener.h"

void* UHyperIMUListenerBPLibrary::dllHandle = NULL;
void (*UHyperIMUListenerBPLibrary::cleanUpObjects)() = NULL;
void (*UHyperIMUListenerBPLibrary::setServerPortNumber)(int) = NULL;
void (*UHyperIMUListenerBPLibrary::getLatestAccel)(IMUVector3d*) = NULL;
void (*UHyperIMUListenerBPLibrary::getLatestMagnetometer)(IMUVector3d*) = NULL;
void (*UHyperIMUListenerBPLibrary::getLatestGravity)(IMUVector3d*) = NULL;
void (*UHyperIMUListenerBPLibrary::getLatestOrientationEuler)(IMUVector3d*) = NULL;
void (*UHyperIMUListenerBPLibrary::getLatestAngularSpeed)(IMUVector3d*) = NULL;

UHyperIMUListenerBPLibrary::UHyperIMUListenerBPLibrary(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}

UHyperIMUListenerBPLibrary::~UHyperIMUListenerBPLibrary()
{
    UnloadDll();
}


void UHyperIMUListenerBPLibrary::LoadDll(int portNumber) {
    if (dllHandle)
        UnloadDll();
    FString dllPath = FPaths::ProjectPluginsDir();
    //dllPath.AppendChars("HyperIMUListener/Resources/IMU_Server.dll", 41);
    dllPath.AppendChars("/HyperIMUListener/Resources/IMU_Server.dll", 42);
    dllHandle = FPlatformProcess::GetDllHandle(*dllPath);
    UE_LOG(LogTemp, Log, TEXT("%s"), *dllPath);
    FString setServerPortNumberStr = "setServerPortNumber";
    FString cleanUpObjectsStr = "cleanUpObjects";
    FString getLatestAccelStr = "getLatestAccel";
    FString getLatestMagnetometerStr = "getLatestMagnetometer";
    FString getLatestGravityStr = "getLatestGravity";
    FString getLatestOrientationEulerStr = "getLatestOrientationEuler";
    FString getLatestAngularSpeedStr = "getLatestAngularSpeed";
    setServerPortNumber = (void(*)(int))FPlatformProcess::GetDllExport(dllHandle, *setServerPortNumberStr);
    cleanUpObjects = (void(*)())FPlatformProcess::GetDllExport(dllHandle, *cleanUpObjectsStr);
    getLatestAccel = (void(*)(IMUVector3d*))FPlatformProcess::GetDllExport(dllHandle, *getLatestAccelStr);
    getLatestMagnetometer = (void(*)(IMUVector3d*))FPlatformProcess::GetDllExport(dllHandle, *getLatestMagnetometerStr);
    getLatestGravity = (void(*)(IMUVector3d*))FPlatformProcess::GetDllExport(dllHandle, *getLatestGravityStr);
    getLatestOrientationEuler = (void(*)(IMUVector3d*))FPlatformProcess::GetDllExport(dllHandle, *getLatestOrientationEulerStr);
    getLatestAngularSpeed = (void(*)(IMUVector3d*))FPlatformProcess::GetDllExport(dllHandle, *getLatestAngularSpeedStr);

    setServerPortNumber(portNumber);
}
void UHyperIMUListenerBPLibrary::UnloadDll() {
    if (dllHandle != NULL)
    {
        cleanUpObjects();
        FPlatformProcess::FreeDllHandle(dllHandle);
        setServerPortNumber = NULL;
        cleanUpObjects = NULL;
        getLatestAccel = NULL;
        getLatestMagnetometer = NULL;
        getLatestGravity = NULL;
        getLatestOrientationEuler = NULL;
        getLatestAngularSpeed = NULL;
        dllHandle = NULL;
    }
}
FVector UHyperIMUListenerBPLibrary::GetLatestAccel() {
    IMUVector3d val;
    //if (dllHandle == NULL)
    //    LoadDll();
    if (getLatestAccel)
        UHyperIMUListenerBPLibrary::getLatestAccel(&val);
    return val;
}
FVector UHyperIMUListenerBPLibrary::GetLatestMagnetometer() {
    IMUVector3d val;
    //if (dllHandle == NULL)
    //    LoadDll();
    if (getLatestMagnetometer)
        UHyperIMUListenerBPLibrary::getLatestMagnetometer(&val);
    return val;
}
FVector UHyperIMUListenerBPLibrary::GetLatestGravity() {
    IMUVector3d val;
    //if (dllHandle == NULL)
    //    LoadDll();
    if (getLatestGravity)
        UHyperIMUListenerBPLibrary::getLatestGravity(&val);
    return val;
}
FVector UHyperIMUListenerBPLibrary::GetLatestOrientationEuler() {
    IMUVector3d val;
    //if (dllHandle == NULL)
    //    LoadDll();
    if (getLatestOrientationEuler)
        UHyperIMUListenerBPLibrary::getLatestOrientationEuler(&val);
    return val;
}
FVector UHyperIMUListenerBPLibrary::GetLatestAngularSpeed() {
    IMUVector3d val;
    //if (dllHandle == NULL)
    //    LoadDll();
    if (getLatestAngularSpeed)
        UHyperIMUListenerBPLibrary::getLatestAngularSpeed(&val);
    return val;
}
