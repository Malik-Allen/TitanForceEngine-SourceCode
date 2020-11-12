#include "Engine.h"
#include "App.h"
#include "../Devices/Window.h"
#include "../Debug/Debug.h"

#include <iostream>

std::unique_ptr<Engine> Engine::g_engineInstance( nullptr );

Engine::Engine() :
	m_engineClock( nullptr ),
	m_isRunning( false ),
	m_isAppRunning( false ),
	m_fps( 120 ),
	m_app(nullptr),
	m_window(nullptr)
{}

Engine::~Engine() {}

// Initializes Engine Components
bool Engine::Init( const unsigned int fps, const int windowWidth, const int windowHeight )
{
	Debug::DebugInit ();
	Debug::SetSeverity ( MessageType::TYPE_INFO );

	m_engineClock = new EngineClock();
	if (m_engineClock == nullptr)
	{
		Debug::FatalError ( "Engine Failed to initialize Engine Clock!", __FILE__, __LINE__ );
		return false;
	}

	m_fps = fps;
	m_engineClock->SetFPS( m_fps );


	m_window = new Window();
	const char* appName = "Titan Force Engine";
	if ( m_app != nullptr )	
		// If an application already exists lets name the window after that application
	{
		appName = m_app->GetAppName();
	}

	if ( m_window->OnCreate( appName, windowWidth, windowHeight ) == false )
	{
		Debug::FatalError( "Engine Failed to Create Window!", __FILE__, __LINE__ );
		return false;
	}

	m_isRunning = true;
	return m_isRunning;
}

bool Engine::LoadApplication(App* app)
{

	if (app == nullptr) {
		Debug::Error ( "Failed to Load Application in Engine. App is null!", __FILE__, __LINE__ );
		return false;
	}

	m_app = app;

	return m_isAppRunning = m_app->OnCreate();
}



void Engine::Run()
{

	while ( m_isRunning )
	{
		m_engineClock->UpdateFrameTicks();
		Update(m_engineClock->GetDeltaTime() );
		Sleep(m_engineClock->GetSleepTime(m_engineClock->GetFPS() ) );
	}

	if ( !m_isRunning )
	{
		OnDestroy();
	}

}

bool Engine::IsRunning() const
{
	return m_isRunning;
}

bool Engine::IsAppRunning() const
{
	return m_isAppRunning;
}

void Engine::Exit()
{
	m_isRunning = false;
}

void Engine::ExitApp()
{
	m_isAppRunning = false;
}

Engine* Engine::Get()
{
	if (g_engineInstance == nullptr )
	{
		g_engineInstance.reset( new Engine );
		return g_engineInstance.get();
	}
	return g_engineInstance.get();
}


void Engine::OnDestroy()
{
	ExitApp();
	if (m_app) {
		delete m_app;
		m_app = nullptr;
	}

	if ( m_window )
	{
		m_window->OnDestroy();
		delete m_window;
		m_window = nullptr;
	}


	if (m_engineClock) {
		delete m_engineClock;
		m_engineClock = nullptr;
	}

}

void Engine::Update( const float deltaTime ) {

	std::cout << "Tick Time: " << deltaTime << std::endl;

	if ( m_app != nullptr )
	{
		if ( m_isAppRunning )
		{
			m_app->Update ( deltaTime );
		}
		else
		{
			m_app->OnDestroy ();
		}
	}

}


