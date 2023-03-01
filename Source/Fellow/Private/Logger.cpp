// Fill out your copyright notice in the Description page of Project Settings.


#include "Logger.h"

Logger::Logger()
{
}

Logger::~Logger()
{
}

void Logger::Log(FName Text)
{
	UE_LOG(LogTemp, Warning, TEXT("Debug log %s"), *Text.ToString());
}

void Logger::Log(FName Text, FName Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Debug log %s %s"), *Text.ToString(), *Value.ToString());
}


void Logger::Log(FName Text, float Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Debug log %s %f"), *Text.ToString(), Value);
}

void Logger::Log(FName Text, bool Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Debug log %s %d"), *Text.ToString(), Value);
}