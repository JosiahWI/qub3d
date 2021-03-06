#pragma once

#include <SDL.h>
#include <SDL_syswm.h>

#include <viking/WindowDescriptor.hpp>
#include <viking/IWindow.hpp>

namespace viking
{
	class SDLWindow : public IWindow
	{
	public:
		~SDLWindow();
		static SDLWindow* createWindow(WindowDescriptor descriptor, RenderingAPI api);
		virtual void poll();
		virtual void swapBuffers();
		virtual bool isRunning();
		virtual void GetSize(int& width, int& height);
		SDL_Window* GetSDLWindow();

		virtual void* getNativeWindowHandle() { return m_window; }

	protected:
		SDLWindow(WindowingAPI windowing_api);
		SDL_Window * m_window;
		SDL_GLContext m_context;
		bool m_running;
		float m_last_tick;
	private:

	};
}