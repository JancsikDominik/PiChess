#ifndef PLUMPIE_HPP
#define PLUMPIE_HPP

#include "Debugging/Debug.hpp"
#include "Debugging/Console.hpp"

#include "GLFWWrappers/KeyEvent.hpp"
#include "GLFWWrappers/ResizeEvent.hpp"
#include "GLFWWrappers/MouseEvent.hpp"

namespace Plum::GLFW { class Window; }
namespace Plum { class Renderer; }

namespace Plum
{

class AppBase : public KeyEventObserver,
			    public ResizeEventObserver,
				public MouseEventObserver
{
public:
	enum class BackendApi
	{
		Unknown,
		OpenGL,
		// Vulkan // MAYBE? or DirectX12
	};

	AppBase();
	virtual ~AppBase();

	/**
	 * \brief Runs the application
	 */
	void Run();

protected:

	/**
	 * \brief Have to call this to specify which backend api should be used, if we don't specify the renderer will be a nullptr
	 * \param api The backend api to be used
	 */
	void SetBackendApi(BackendApi api);

	/**
	 * \brief Will be called before the main loop, used to set things up
	 */
	virtual void StartUp() = 0;

	/**
	 * \brief Will be called before every frame render, should be used to, well, update things
	 * \param currTimeStamp current time stamp in seconds
	 */
	virtual void Update(double currTimeStamp) = 0;

	/**
	 * \brief Runs when keyboard key pressed
	 */
	virtual void OnKeyEvent(const KeyEvent& keyevent) = 0;

	/**
	 * \brief runs when mouse click happened/mouse moved
	 */
	virtual void OnMouseEvent(const MouseEvent& mouseevent) = 0;

	/**
	 * \brief runs when window has been resized
	 * \param width new width of the window
	 * \param height new height of the window
	 */
	virtual void OnResize(uint32_t width, uint32_t height) = 0;

	Renderer* m_renderer;
	GLFW::Window* m_window;

private:
	void InitGlew() const;
	void PrintRenderingAPIVersion() const;

	BackendApi m_renderingAPI;
	Debug::Console m_console;
};
	
}


#endif