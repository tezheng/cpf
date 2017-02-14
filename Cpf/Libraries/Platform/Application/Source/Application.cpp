//////////////////////////////////////////////////////////////////////////
#include "Application/Application.hpp"


//////////////////////////////////////////////////////////////////////////
using namespace Cpf;

//////////////////////////////////////////////////////////////////////////
Platform::iGLContext::~iGLContext()
{}

//////////////////////////////////////////////////////////////////////////
const Math::Vector2i iWindow::Centered(0x2FFF0000, 0x2FFF0000);

iWindow::~iWindow()
{}


//////////////////////////////////////////////////////////////////////////
Application::Application()
	: mRunning(true)
//	, mCommandLine("Cpf::Application")
{}


Application::~Application()
{}


bool Application::IsRunning() const
{
	return mRunning;
}


void Application::Quit()
{
	if (Emit<OnQuit>())
		mRunning = false;
}

//////////////////////////////////////////////////////////////////////////
WindowDesc::WindowDesc(WindowedApplication* app)
	: mpApplication(app)
	, mTitle("")
	, mPosition(iWindow::Centered)
	, mSize(Math::Vector2i(200, 200))
	, mFlags(0)
{}

WindowDesc& WindowDesc::Title(const String& title)
{
	mTitle = title;
	return *this;
}

WindowDesc& WindowDesc::Position(const Math::Vector2i& pos)
{
	mPosition = pos;
	return *this;
}

WindowDesc& WindowDesc::Size(const Math::Vector2i& size)
{
	mSize = size;
	return *this;
}

WindowDesc& WindowDesc::Flags(uint32_t flags)
{
	mFlags = flags;
	return *this;
}

WindowDesc::operator iWindow* () const
{
	iWindow* result = nullptr;
	if (mpApplication->Create(*this, &result))
		return result;
	return nullptr;
}