#include "rWindow.h"
#include "rEngine.h"
#include "Viewport.h"

#include <Util\Macros.h>

#include <iostream>
#include <algorithm>

#include <boost/algorithm/string.hpp>   

#include <Util\Logger.h>

static void GLFW_error(int error,const char* desc){
	LOG_ERROR("GLFW Error: " << error << " (" << desc << ")");
}

void GLFW_resize(GLFWwindow *win,int w,int h){
	rWindow *window = rWindow::_windows[win];
	window->onResize(glm::ivec2(w,h));
}

void GLFW_mouseButton(GLFWwindow *win,int button,int state){
	rWindow *window = rWindow::_windows[win];
	window->onMouseClick(button,state);
}

void GLFW_mouseMotion(GLFWwindow *win,int x,int y){
	rWindow *window = rWindow::_windows[win];

	if(window->_prevMouse.x == -1){
		window->_prevMouse.x = x;
		window->_prevMouse.y = y;
	}

	window->omMouseMove(glm::ivec2(x-window->_prevMouse.x,window->_prevMouse.y-y));
	window->_prevMouse.x = x;
	window->_prevMouse.y = y;
}

void GLFW_mouseEnter(GLFWwindow *win,int enter){
	rWindow *window = rWindow::_windows[win];

	if(enter){
		window->_prevMouse.x = -1;
		window->_prevMouse.y = -1;
	}
}


std::map<GLFWwindow*,rWindow*> rWindow::_windows;

rWindowHints::rWindowHints():
size(600,400),
title("Unnamed window - rEngine"),
monitor(NULL),
share(NULL)
{
	
}


rWindow::rWindow() :  _parent(0) , _prevMouse(-1,-1){
}


rWindow::~rWindow(){
	destroy();
}

void rWindow::destroy(){
	for(int i = _childWindows.size()-1 ; i>= 0 ; i--){
		//(_childWindows[i])->destroy();
		glfwSetWindowShouldClose(_childWindows[i]->_window,true);
		_childWindows[i]->_parent = 0;
	}

	if(_parent){
		auto it = std::find(_parent->_childWindows.begin(),_parent->_childWindows.end(),this);
		if(it != _parent->_childWindows.end())
			_parent->_childWindows.erase(it);
		_parent = 0;
	}
	if(_window != 0)
		glfwDestroyWindow(_window);
	_window = 0;
}

void rWindow::updateAll(){
	GLFWwindow *win = 0;
	while(true){
		IT_FOR(_windows,w){
			if(w->second->shouldClose()){
				win = w->first;
				break;
			}
		}
		if(win){
			auto w = _windows[win];
			_windows.erase(win);
			delete w;
			win = 0;
		}else
			break;
	}
		

	IT_FOR(_windows,w){
		w->second->redraw();
	}
	
}

void rWindow::onResize(glm::ivec2 size){
	this->_size = size;
	IT_FOR(_resizeListeners,l){
		(*l)->onResize(size);
	}
}
void rWindow::omMouseMove(glm::ivec2 delta){
	IT_FOR(_mouseMotionListener,l){
		(*l)->mouseMotion(delta);
	}
}
void rWindow::onMouseClick(int button,int state){
	IT_FOR(_mouseButtonListener,l){
		(*l)->mouseClick(button,state);
	}
}

void rWindow::addResizeListener(ResizeListener *listener){
	_resizeListeners.push_back(listener);
}

void rWindow::addMouseMotionListener(MouseMotionListener *listener){
	_mouseMotionListener.push_back(listener);
}

void rWindow::addMouseButtonListener(MouseButtonListener *listener){
	_mouseButtonListener.push_back(listener);
}

void rWindow::removeResizeListener(ResizeListener *listener){
	auto it = std::find(_resizeListeners.begin() , _resizeListeners.end() , listener);
	if(it != _resizeListeners.end() )
		_resizeListeners.erase(it);
}

void rWindow::removeMouseMotionListener(MouseMotionListener *listener){
	auto it = std::find(_mouseMotionListener.begin() , _mouseMotionListener.end() , listener);
	if(it != _mouseMotionListener.end() )
		_mouseMotionListener.erase(it);
}

void rWindow::removeMouseButtonListener(MouseButtonListener *listener){
	auto it = std::find(_mouseButtonListener.begin() , _mouseButtonListener.end() , listener);
	if(it != _mouseButtonListener.end() )
		_mouseButtonListener.erase(it);
}

void rWindow::setClearColor(const glm::vec4 &color){
	_clearColor = color;
	glClearColor(color.r,color.g,color.b,color.a);
}
glm::vec4 rWindow::getClearColor()const{return _clearColor;}

void rWindow::redraw(){

	glfwMakeContextCurrent(_window);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	IT_FOR(_viewports,v){
		(*v)->draw();
	}

	glfwSwapBuffers(_window);
    glfwPollEvents();
}

rWindow* rWindow::OpenWindow(rWindowHints hints){

	rWindow* win = new rWindow();
	
	if (!glfwInit())
        exit(EXIT_FAILURE);
	
	

	glfwSetErrorCallback(GLFW_error);
	win->_window = glfwCreateWindow(hints.size.x, //size x
									hints.size.y, //size y
									hints.title.c_str(), //window title
									hints.monitor, // monitor to create window at
									(hints.share == NULL) ? NULL :  hints.share->_window);

	if(hints.share != NULL){
		hints.share->_childWindows.push_back(win);
		win->_parent = hints.share;
	}

	if (!win->_window){
	
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

	_windows[win->_window] = win;
	win->_size = hints.size;

	
	
	glfwMakeContextCurrent(win->_window);
	if(glewInit() != GLEW_OK)
	{
		LOG_ERROR( "Failed to init glew");
		return false;
	}
	
	win->setClearColor(glm::vec4(0.3,0.3,0.3,0));
	win->setClearColor(glm::vec4(1,1,1,1));
	
	OpenGLInfo::printOGLInformation();
	LOG_INFO("GLFW Version:\t" << glfwGetVersionString());

	glfwSetWindowSizeCallback(win->_window,GLFWwindowsizefun(GLFW_resize));
	glfwSetMouseButtonCallback(win->_window,GLFWmousebuttonfun(GLFW_mouseButton));
	glfwSetCursorPosCallback(win->_window,GLFWcursorposfun(GLFW_mouseMotion));
	glfwSetCursorEnterCallback(win->_window,GLFWcursorenterfun(GLFW_mouseEnter));

	return win;
}

void rWindow::ReadXML(rEngine *engine,tinyxml2::XMLElement *window){
	rWindowHints hints;
		
	auto size = window->FirstChildElement("size");
	auto title = window->FirstChildElement("title");
	auto share = window->FirstChildElement("share");
	auto viewport = window->FirstChildElement("viewport");

	if(size){
		std::string val = size->GetText();
		int w=0,h=0;

		auto it = val.find(' ');
		w = atoi(val.substr(0,it).c_str());
		h = atoi(val.substr(it).c_str());
		if(w>1 && h>1)
			hints.size =glm::ivec2(w,h);
	}
			
	if(title){
		std::string val = title->GetText();
		if(val.length()!=0)
			hints.title = val;
	}
			
	if(share){
		std::string val = share->GetText();
		auto win = IDObject::GetObjectD<rWindow>(val);
		if(win)
			hints.share = win;
	}
			

	rWindow *win = rWindow::OpenWindow(hints);
	std::string id = window->Attribute("id");
	if(id.length()!=0)
		win->setID(id);
	
	LOG_DEBUG("Creating Viewports for window " << id);
	while(viewport){
		std::string type = viewport->Attribute("type");
		boost::algorithm::to_lower(type);
		LOG_DEBUG("type: " << type);
		auto texture = viewport->FirstChildElement("texture");
		std::string textureID,textureSRC;
		textureID = texture->Attribute("name");
		LOG_DEBUG("texture: " << textureID);
		auto c  = texture->Attribute("src");
		textureSRC =  (!c) ? "" : c;
		if(textureSRC.length()!=0)
			Texture::loadTexture(textureID,textureSRC);
			
		Viewport *vp = 0;
		if(type == "fullscreen"){
			vp = new FullscreenViewport(win);
		}
		else if(type == "relativeviewport"){
			glm::vec2 topLeft;
			glm::vec2 size;
			std::string tl = viewport->FirstChildElement("topleft")->GetText();  //TODO this will crash if topleft does not exist
			std::string s = viewport->FirstChildElement("size")->GetText();
			
			auto it = tl.find(' ');
			topLeft.x = atof(tl.substr(0,it).c_str());
			topLeft.y = atof(tl.substr(it).c_str());
			
			it = s.find(' ');
			size.x = atof(s.substr(0,it).c_str());
			size.y = atof(s.substr(it).c_str());

			vp = new RelativeViewport(win,topLeft,size);
		}
		else{
			LOG_ERROR("No or unsupported viewport type: " << type);
		}

		if(vp == 0)
			continue;
		vp->setTexture(textureID);
		win->addViewport(vp);
		viewport = viewport->NextSiblingElement("viewport");
	}
}
