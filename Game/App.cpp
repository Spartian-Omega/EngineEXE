#include "pch.h"
#include "App.h"
#include "Game.h"

namespace Game {

    App::App()
    {
    }

    App::~App()
    {
    }

    winrt::Windows::ApplicationModel::Core::IFrameworkView App::CreateView()
    {
        return *this;
    }

    winrt::Windows::Foundation::IAsyncAction App::AsyncThread()
    {

        co_await winrt::resume_background();
        while (true);
    }

    void App::Initialize(winrt::Windows::ApplicationModel::Core::CoreApplicationView const& applicationView)
    {
        m_game = std::make_unique<Game>();
        m_exit = false;
        m_visible = true;

    }

    void App::Initialize()
    {
        // Create a Direct2D device.
        CreateDirect2DDevice();

        // To create a composition graphics device, we need to QI for another interface
        winrt::com_ptr<ABI::Windows::UI::Composition::ICompositorInterop> compositorInterop{ m_compositor.as<ABI::Windows::UI::Composition::ICompositorInterop>() };

        // Create a graphics device backed by our D3D device
        winrt::com_ptr<ABI::Windows::UI::Composition::ICompositionGraphicsDevice> compositionGraphicsDeviceIface;
        winrt::check_hresult(compositorInterop->CreateGraphicsDevice(
            m_d2dDevice.get(),
            compositionGraphicsDeviceIface.put()));
        m_compositionGraphicsDevice = compositionGraphicsDeviceIface.as<winrt::Windows::UI::Composition::CompositionGraphicsDevice>();
    }

    void App::Uninitialize()
    {
        m_game.reset();
    }

    void App::Load(winrt::hstring const&)
    {

    }

    void App::Run()
    {
        winrt::Windows::UI::Core::CoreWindow window = winrt::Windows::UI::Core::CoreWindow::GetForCurrentThread();
        window.Activate();
        winrt::Windows::UI::Core::CoreDispatcher dispatcher = window.Dispatcher();
        while (!m_exit)
        {
            if (m_visible)
            {
                m_game->Tick();

                dispatcher.ProcessEvents(winrt::Windows::UI::Core::CoreProcessEventsOption::ProcessAllIfPresent);
            }
            else
            {
                dispatcher.ProcessEvents(winrt::Windows::UI::Core::CoreProcessEventsOption::ProcessOneAndAllPending);
            }
        }
    }

    void App::SetWindow(winrt::Windows::UI::Core::CoreWindow const& window)
    {
        winrt::Windows::UI::Composition::Compositor compositor;
        winrt::Windows::UI::Composition::ContainerVisual root = compositor.CreateContainerVisual();
        m_target = compositor.CreateTargetForCurrentView();
        m_target.Root(root);
        m_visuals = root.Children();

        window.PointerPressed({ this, &App::OnPointerPressed });
        window.PointerMoved({ this, &App::OnPointerMoved });

        window.PointerReleased([&](auto&& ...)
            {
                m_selected = nullptr;
            });
    }

    void App::OnPointerPressed(IInspectable const&, winrt::Windows::UI::Core::PointerEventArgs const& args)
    {
        //winrt::Windows::Foundation::Numerics::float2 const point = args.CurrentPoint().Position();

        //for (winrt::Windows::UI::Composition::Visual visual : m_visuals)
        //{
        //    winrt::Windows::Foundation::Numerics::float3 const offset = visual.Offset();
        //    winrt::Windows::Foundation::Numerics::float2 const size = visual.Size();

        //    if (point.x >= offset.x &&
        //        point.x < offset.x + size.x &&
        //        point.y >= offset.y &&
        //        point.y < offset.y + size.y)
        //    {
        //        m_selected = visual;
        //        m_offset.x = offset.x - point.x;
        //        m_offset.y = offset.y - point.y;
        //    }
        //}

        //if (m_selected)
        //{
        //    m_visuals.Remove(m_selected);
        //    m_visuals.InsertAtTop(m_selected);
        //}
        //else
        //{
        //    AddVisual(point);
        //}
    }

    void App::OnPointerMoved(IInspectable const&, winrt::Windows::UI::Core::PointerEventArgs const& args)
    {
        if (m_selected)
        {
            winrt::Windows::Foundation::Numerics::float2 const point = args.CurrentPoint().Position();

            m_selected.Offset(
                {
                    point.x + m_offset.x,
                    point.y + m_offset.y,
                    0.0f
                });
        }
    }

    void App::AddVisual(winrt::Windows::Foundation::Numerics::float2 const point)
    {
        winrt::Windows::UI::Composition::Compositor compositor = m_visuals.Compositor();
        winrt::Windows::UI::Composition::SpriteVisual visual = compositor.CreateSpriteVisual();
        static  winrt::Windows::UI::Color colors[] =
        {
            { 0xDC, 0x5B, 0x9B, 0xD5 },
            { 0xDC, 0xED, 0x7D, 0x31 },
            { 0xDC, 0x70, 0xAD, 0x47 },
            { 0xDC, 0xFF, 0xC0, 0x00 }
        };

        static unsigned last = 0;
        unsigned const next = ++last % _countof(colors);
        visual.Brush(compositor.CreateColorBrush(colors[next]));

        float const BlockSize = 100.0f;

        visual.Size(
            {
                BlockSize,
                BlockSize
            });

        visual.Offset(
            {
                point.x - BlockSize / 2.0f,
                point.y - BlockSize / 2.0f,
                0.0f,
            });

        m_visuals.InsertAtTop(visual);

        m_selected = visual;
        m_offset.x = -BlockSize / 2.0f;
        m_offset.y = -BlockSize / 2.0f;
    }


    void App::CreateDirect2DDevice()
    {
        uint32_t createDeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

        // Array with DirectX hardware feature levels in order of preference.
        D3D_FEATURE_LEVEL featureLevels[] =
        {
            D3D_FEATURE_LEVEL_11_1,
            D3D_FEATURE_LEVEL_11_0,
            D3D_FEATURE_LEVEL_10_1,
            D3D_FEATURE_LEVEL_10_0,
            D3D_FEATURE_LEVEL_9_3,
            D3D_FEATURE_LEVEL_9_2,
            D3D_FEATURE_LEVEL_9_1
        };

        // Create the Direct3D 11 API device object and a corresponding context.
        winrt::com_ptr<::ID3D11Device> d3DDevice;
        winrt::com_ptr<::ID3D11DeviceContext> d3DImmediateContext;
        D3D_FEATURE_LEVEL d3dFeatureLevel{ D3D_FEATURE_LEVEL_9_1 };

        winrt::check_hresult(
            ::D3D11CreateDevice(
                nullptr, // Default adapter.
                D3D_DRIVER_TYPE_HARDWARE,
                0, // Not asking for a software driver, so not passing a module to one.
                createDeviceFlags, // Set debug and Direct2D compatibility flags.
                featureLevels,
                ARRAYSIZE(featureLevels),
                D3D11_SDK_VERSION,
                d3DDevice.put(),
                &d3dFeatureLevel,
                d3DImmediateContext.put()
            )
        );

        // Initialize Direct2D resources.
        D2D1_FACTORY_OPTIONS d2d1FactoryOptions{ D2D1_DEBUG_LEVEL_NONE };

        // Initialize the Direct2D Factory.
        winrt::com_ptr<::ID2D1Factory1> d2D1Factory;
        winrt::check_hresult(
            ::D2D1CreateFactory(
                D2D1_FACTORY_TYPE_SINGLE_THREADED,
                __uuidof(d2D1Factory),
                &d2d1FactoryOptions,
                d2D1Factory.put_void()
            )
        );

        // Create the Direct2D device object.
        // Obtain the underlying DXGI device of the Direct3D device.
        m_dxgiDevice = d3DDevice.as<::IDXGIDevice>();

        m_d2dDevice = nullptr;
        winrt::check_hresult(
            d2D1Factory->CreateDevice(m_dxgiDevice.get(), m_d2dDevice.put())
        );

        m_deviceLostHelper.WatchDevice(m_dxgiDevice);
        m_deviceLostHelper.DeviceLost({ this, &App::OnDirect3DDeviceLost });
    }

    void App::OnDirect3DDeviceLost(DeviceLostHelper const* /* sender */, DeviceLostEventArgs const& /* args */)
    {
        // Create a new Direct2D device.
        CreateDirect2DDevice();

        // Restore our composition graphics device to good health.
        winrt::com_ptr<ABI::Windows::UI::Composition::ICompositionGraphicsDeviceInterop> compositionGraphicsDeviceInterop{ m_compositionGraphicsDevice.as<ABI::Windows::UI::Composition::ICompositionGraphicsDeviceInterop>() };
        winrt::check_hresult(compositionGraphicsDeviceInterop->SetRenderingDevice(m_d2dDevice.get()));
    }
}

int __stdcall wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
    winrt::Windows::ApplicationModel::Core::CoreApplication::Run(winrt::make<Game::App>());
}

