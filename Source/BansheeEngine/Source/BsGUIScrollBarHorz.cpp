//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#include "BsGUIScrollBarHorz.h"
#include "BsGUIDimensions.h"

namespace BansheeEngine
{
	GUIScrollBarHorz::GUIScrollBarHorz(const String& styleName, const GUIDimensions& dimensions)
		:GUIScrollBar(true, styleName, dimensions)
	{

	}

	GUIScrollBarHorz::~GUIScrollBarHorz()
	{

	}

	GUIScrollBarHorz* GUIScrollBarHorz::create(const String& styleName)
	{
		return new (bs_alloc<GUIScrollBarHorz>()) GUIScrollBarHorz(getStyleName<GUIScrollBarHorz>(styleName), GUIDimensions::create());
	}

	GUIScrollBarHorz* GUIScrollBarHorz::create(const GUIOptions& options, const String& styleName)
	{
		return new (bs_alloc<GUIScrollBarHorz>()) GUIScrollBarHorz(getStyleName<GUIScrollBarHorz>(styleName), GUIDimensions::create(options));
	}

	const String& GUIScrollBarHorz::getGUITypeName()
	{
		static String typeName = "ScrollBarHorz";
		return typeName;
	}
}