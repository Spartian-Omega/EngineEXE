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
        winrt::Windows::Foundation::Numerics::float2 const point = args.CurrentPoint().Position();

        for (winrt::Windows::UI::Composition::Visual visual : m_visuals)
        {
            winrt::Windows::Foundation::Numerics::float3 const offset = visual.Offset();
            winrt::Windows::Foundation::Numerics::float2 const size = visual.Size();

            if (point.x >= offset.x &&
                point.x < offset.x + size.x &&
                point.y >= offset.y &&
                point.y < offset.y + size.y)
            {
                m_selected = visual;
                m_offset.x = offset.x - point.x;
                m_offset.y = offset.y - point.y;
            }
        }

        if (m_selected)
        {
            m_visuals.Remove(m_selected);
            m_visuals.InsertAtTop(m_selected);
        }
        else
        {
            AddVisual(point);
        }
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

}

int __stdcall wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
    winrt::Windows::ApplicationModel::Core::CoreApplication::Run(winrt::make<Game::App>());
}
