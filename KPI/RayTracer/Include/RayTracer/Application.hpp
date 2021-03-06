#pragma once


#include "RayTracer/RayTracer.hpp"
#include "RayTracer/TraceContext.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include "SceneReader.hpp"


class JSONValue;

namespace RayTracer
{
	class Application
	{
	public:
		Application( const std::string& scene );
		~Application();

		int					Run();
		std::ostream&		Log();

	private:
		//
		bool				OpenScene();
		bool				OpenOutput();

		//
		bool InstallNodeTypes();

		//
		std::string			mSceneFilename;
		TraceContext		mContext;
		std::ofstream		mLog;
		SceneReader::NodeFactory mNodeTypes;
	};
}
