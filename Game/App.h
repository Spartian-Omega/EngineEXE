#pragma once

namespace Game {
    struct App : winrt::implements<App, winrt::Windows::ApplicationModel::Core::IFrameworkViewSource, winrt::Windows::ApplicationModel::Core::IFrameworkView>
    {
    public:
        App();
        ~App();

        winrt::Windows::ApplicationModel::Core::IFrameworkView CreateView();
        winrt::Windows::Foundation::IAsyncAction AsyncThread();
        void Initialize(winrt::Windows::ApplicationModel::Core::CoreApplicationView const&);
        void Uninitialize();
        void Load(winrt::hstring const&);
        void Run();
        void SetWindow(winrt::Windows::UI::Core::CoreWindow const& window);
        void OnPointerPressed(IInspectable const&, winrt::Windows::UI::Core::PointerEventArgs const& args);
        void OnPointerMoved(IInspectable const&, winrt::Windows::UI::Core::PointerEventArgs const& args);
        void AddVisual(winrt::Windows::Foundation::Numerics::float2 const point);
    public:
        winrt::Windows::UI::Composition::CompositionTarget m_target{ nullptr };
        winrt::Windows::UI::Composition::VisualCollection m_visuals{ nullptr };
        winrt::Windows::UI::Composition::Visual m_selected{ nullptr };
        winrt::Windows::Foundation::Numerics::float2 m_offset{};

        std::unique_ptr<class Game> m_game;
        bool m_exit;
        bool m_visible;
    };
}