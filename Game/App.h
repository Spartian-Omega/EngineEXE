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
        void Initialize();
        void Uninitialize();
        void Load(winrt::hstring const&);
        void Run();
        void SetWindow(winrt::Windows::UI::Core::CoreWindow const& window);
        void OnPointerPressed(IInspectable const&, winrt::Windows::UI::Core::PointerEventArgs const& args);
        void OnPointerMoved(IInspectable const&, winrt::Windows::UI::Core::PointerEventArgs const& args);
        void AddVisual(winrt::Windows::Foundation::Numerics::float2 const point);


        void CreateDirect2DDevice(); // Direct2D Helper Function
        void App::OnDirect3DDeviceLost(DeviceLostHelper const*, DeviceLostEventArgs const&);


    public:
        winrt::Windows::UI::Composition::CompositionTarget m_target{ nullptr };
        winrt::Windows::UI::Composition::VisualCollection m_visuals{ nullptr };
        winrt::Windows::UI::Composition::Visual m_selected{ nullptr };
        winrt::Windows::Foundation::Numerics::float2 m_offset{};


        // The device that owns the surface.
        winrt::Windows::UI::Composition::CompositionGraphicsDevice m_compositionGraphicsDevice{ nullptr };       
        winrt::Windows::UI::Composition::Compositor m_compositor{ nullptr };

        // Direct2D Items
        winrt::com_ptr<::ID2D1Device> m_d2dDevice;
        winrt::com_ptr<::IDXGIDevice> m_dxgiDevice;
        DeviceLostHelper m_deviceLostHelper;

        std::unique_ptr<class Game> m_game;
        bool m_exit;
        bool m_visible;


    };
}