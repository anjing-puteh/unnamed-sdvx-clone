#pragma once
#include <Audio/Sample.hpp>
extern class OpenGL* g_gl;
extern class GUIState g_guiState;
extern class Graphics::Window* g_gameWindow;
extern float g_aspectRatio;
extern Vector2i g_resolution;
extern class Application* g_application;
extern class JobSheduler* g_jobSheduler;
extern class Input g_input;

// GUI
extern class GUIRenderer* g_guiRenderer;
extern Ref<class Canvas> g_rootCanvas;
extern Ref<class CommonGUIStyle> g_commonGUIStyle;

class Application
{
public:
	Application();
	~Application();

	// Runs the application
	int32 Run();
	
	void SetCommandLine(int32 argc, char** argv);
	void SetCommandLine(const char* cmdLine);

	class Game* LaunchMap(const String& mapPath);
	void Shutdown();

	void AddTickable(class IApplicationTickable* tickable, class IApplicationTickable* insertBefore = nullptr);
	void RemoveTickable(class IApplicationTickable* tickable);

	// Current running map path (full file path)
	String GetCurrentMapPath();

	// Current loaded skin;
	String GetCurrentSkin();

	// Retrieves application command line parameters
	const Vector<String>& GetAppCommandLine() const;

	// Gets a basic template for a render state, with all the application variables initialized
	RenderState GetRenderStateBase() const;
	RenderQueue* GetRenderQueueBase();

#ifdef LoadImage
#undef LoadImage
#endif
	Image LoadImage(const String& name);
	Graphics::Image LoadImageExternal(const String & name);
	Texture LoadTexture(const String& name);
	Texture LoadTexture(const String & name, const bool& external);
	Material LoadMaterial(const String& name);
	Sample LoadSample(const String& name, const bool& external = false);
	Graphics::Font LoadFont(const String& name, const bool& external = false);
	class lua_State* LoadScript(const String& name);
	void LoadGauge(bool hard);
	void DrawGauge(float rate, float x, float y, float w, float h, float deltaTime);
	int FastText(String text, float x, float y, int size, int align);
	float GetAppTime() const { return m_lastRenderTime; }
	float GetRenderFPS() const;
	Material GetFontMaterial() const;
	Transform GetGUIProjection() const;
	void StoreNamedSample(String name, Sample sample);
	void PlayNamedSample(String name);

private:
	bool m_LoadConfig();
	void m_SaveConfig();

	bool m_Init();
	void m_MainLoop();
	void m_Tick();
	void m_Cleanup();
	void m_OnKeyPressed(int32 key);
	void m_OnKeyReleased(int32 key);
	void m_OnWindowResized(const Vector2i& newSize);
	void m_SetNvgLuaBindings(class lua_State* state);

	RenderState m_renderStateBase;
	RenderQueue m_renderQueueBase;
	Vector<String> m_commandLine;
	Map<String, Graphics::Font> m_fonts;
	Map<String, Sample> m_samples;
	Material m_fontMaterial;
	Material m_fillMaterial;
	class HealthGauge* m_gauge;

	String m_lastMapPath;
	class Beatmap* m_currentMap = nullptr;

	float m_lastRenderTime;
	float m_deltaTime;
	bool m_allowMapConversion;
	String m_skin;
};
