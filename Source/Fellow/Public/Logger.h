// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class FELLOW_API Logger
{
public:
	Logger();
	~Logger();

	static void Log(FName Text);
	static void Log(FName Text, FName Value);
	static void Log(FName Text, float Value);
	static void Log(FName Text, bool Value);
};
