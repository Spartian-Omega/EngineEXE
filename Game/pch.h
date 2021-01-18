#pragma once
#include <windows.h>
#include <D2d1_1.h>
#include <D3d11_4.h>
#include <Dwrite.h>
#include <Windows.Graphics.DirectX.Direct3D11.interop.h>
#include <Windows.ui.composition.interop.h>
#include <unknwn.h>

#include <winrt/Windows.ApplicationModel.Core.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Graphics.DirectX.h>
#include <winrt/Windows.Graphics.DirectX.Direct3D11.h>
#include <winrt/Windows.UI.Composition.h>
#include <winrt/Windows.UI.Core.h>
#include <winrt/Windows.UI.Input.h>


//#include <winrt/Windows.Foundation.Collections.h>
//#include <winrt/Windows.Graphics.Display.Core.h>

#include "DeviceLostHelper.h"

// Currently referencing this v
// https://docs.microsoft.com/en-us/windows/uwp/composition/composition-native-interop
// Specifically this v
// https://docs.microsoft.com/en-us/windows/uwp/composition/composition-native-interop#cwinrt-usage-example