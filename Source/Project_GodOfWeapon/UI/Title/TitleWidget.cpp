// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleWidget.h"

void UTitleWidget::CallGameStart()
{
	if(OnGameStart.IsBound())
	{
		OnGameStart.Broadcast();
	}
}
